/* 
 * File:   OrientationControl.c
 * Author: Ian Frosst
 *
 * Created on March 2, 2017, 3:29 PM
 */

#include "OrientationControl.h"
#include "main.h"


/* 
 * Floating-point PID loops for attitude control. 
 * Inspired by ArduPilot control code.
 * TODO: convert to fixed-point (integers) for increased speed 
 * (could probably do with tenth- or hundredth-degree integers)
 * 
 */

// PID control values for the basic loops
PID_val pids[PID_CHANNELS];

static uint8_t gainsUpdated = 0; // updated gain flag


// Initial PID gains. These are only used to keep sane values on startup.
const static float init_kp[PID_CHANNELS] = {1.5, 1.5, 1.5, 1.0, 1.0, 1.0, 1.0, 1.0};
const static float init_ki[PID_CHANNELS] = {0, 0, 0, 0, 0, 0, 0, 0};
const static float init_kd[PID_CHANNELS] = {3.5, 3.5, 3.5, 0, 0, 0, 0, 0};

// To be called to initialize a new PID channel
void initPID(PID_val* pid, float Kp, float Ki, float Kd, float imax) {
    pid->Kp = Kp;
    pid->Ki = Ki;
    pid->Kd = Kd;
    pid->imax = imax;
    pid->integral = 0;
    pid->lastTime = 0;
    pid->lastErr = 0;
}

void orientationInit() {
    uint8_t i;
    for (i = 0; i < PID_CHANNELS; i++) {
        initPID(&pids[i], init_kp[i], init_ki[i], init_kd[i], 0);
    }
}

PID_val* getPID(PID_channel channel) {
    return &pids[channel];
}

// PID loop function. error is (setpointValue - currentValue)
float PIDcontrol(PID_val* pid, float error) {
    float output = 0;
        
    uint32_t now = getTime();
    uint16_t delta_msec = (now - pid->lastTime);
    
    // check if we've gone too long without updating (keeps the I and D from freaking out)
    if (delta_msec > PID_RESET_TIME || pid->lastTime == 0) {
        delta_msec = 0;
        pid->integral = 0;
        pid->lastErr = error;
    }
    
    pid->lastTime = now;

    output += pid->Kp * error; // Proportional control
    
    if (delta_msec > 0) { // only compute time-sensitive control if time has elapsed
        float dTime = delta_msec / 1000.0f; // elapsed time in seconds
        
        if (fabsf(pid->Ki) > 0) { // Integral control
            pid->integral += (pid->Ki * error) * dTime;
            
            if (pid->integral < -pid->imax) { // ensure integral stays manageable
                pid->integral = -pid->imax;
            } else if (pid->integral > pid->imax) {
                pid->integral = pid->imax;
            }
            output += pid->integral;
        }

        if (fabsf(pid->Kd) > 0) { // Derivative control
            float derivative = (error - pid->lastErr) / dTime;
            pid->lastErr = error;
            output += pid->Kd * derivative;
        }
    }
    
    return output;
}

float getGain(PID_channel channel, PID_gain type){
    if (channel < PID_CHANNELS) {
        if (type == KP){
            return pids[channel].Kp;
        } else if (type == KI){
            return pids[channel].Ki;
        } else if (type == KD){
            return pids[channel].Kd;
        }
    }
    return -1; // TODO: return something better than an obviously wrong value
}

void setGain(PID_channel channel, PID_gain type, float value){
    gainsUpdated = 1;
    if (channel < PID_CHANNELS) {
        if (type == KP){
            pids[channel].Kp = value;
        } else if (type == KI){
            pids[channel].Ki = value;
        } else if (type == KD){
            pids[channel].Kd = value;
        }
    }
}

uint8_t areGainsUpdated(){
    if (gainsUpdated){
        gainsUpdated = 0;
        return 1;
    }
    return 0;
}

void forceGainUpdate(){
    gainsUpdated = 1;
}
