/* 
 * @file WARG_GPS.h
 * @author Serj Babayan
 * @created April 23, 2017, 2:07 PM
 * Contains driver implemenation for the WARG GPS breakout that communicates via SPI
 * 
 * @copyright Waterloo Aerial Robotics Group 2017 \n
 *   https://raw.githubusercontent.com/UWARG/PICpilot/master/LICENCE
 */

#ifndef WARG_GPS_H
#define	WARG_GPS_H

#include "../../Common/Interfaces/SPI.h"

/** What interface the GPS module communcates over */
#define WARG_GPS_SPI_INTERFACE 2

#define WARG_GPS_SPI_MODE SPI_MODE3

#define WARG_GPS_SPI_FREQ_KHZ 2000

#define WARG_GPS_SPI_SYNCHRONIZATION_BYTE 0x7E
#endif

