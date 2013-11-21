/*
 * File:   StartupErrorCodes.c
 * Author: Chris Hajduk
 *
 * Created on October 15, 2013, 7:57 PM
 */
#include "main.h"

int lastRuntimeErrors = 0;

void checkErrorCodes(){
    if (RCONbits.TRAPR == 1) {
        if (DEBUG){
            UART1_SendString("TRAP Reset Occurred");
        }
        RCONbits.TRAPR = 0;
    }

    if (RCONbits.IOPUWR == 1) {
        if (DEBUG){
            UART1_SendString("Illegal Opcode Reset Occurred");
        }
        RCONbits.IOPUWR = 0;
    }

    if (RCONbits.VREGS == 1) {
        if (DEBUG){
            UART1_SendString("Voltage Reg Reset Occurred");
        }
        RCONbits.VREGS = 0;
    }

    if (RCONbits.EXTR == 1) {
        if (DEBUG){
            UART1_SendString("External Reset Occurred");
        }
        RCONbits.EXTR = 0;
    }

    if (RCONbits.SWR == 1) {
        if (DEBUG){
            UART1_SendString("Software Reset Occurred");
        }
        RCONbits.SWR = 0;
    }

    if (RCONbits.WDTO == 1) {
        if (DEBUG){
        UART1_SendString("Software WDT Reset Occurred");
        }
        RCONbits.WDTO = 0;
    }

    if (RCONbits.SLEEP == 1) {
        if (DEBUG){
            UART1_SendString("Sleep Mode Reset Occurred");
        }
        RCONbits.SLEEP = 0;
    }

    if (RCONbits.IDLE == 1) {
        if (DEBUG){
            UART1_SendString("Idle Mode Reset Occurred");
        }
        RCONbits.IDLE = 0;
    }

    if (RCONbits.BOR == 1) {
        if (DEBUG){
            UART1_SendString("Brown Out Reset Occurred");
        }
        RCONbits.BOR = 0;
    }

    if (RCONbits.POR == 1) {
        if (DEBUG){
            UART1_SendString("Power On Reset Occurred");
        }
        RCONbits.POR = 0;
    }
}