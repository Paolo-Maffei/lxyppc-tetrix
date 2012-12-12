/*
  June 2012

  BaseFlightPlus Rev -

  An Open Source STM32 Based Multicopter

  Includes code and/or ideas from:

  1)AeroQuad
  2)BaseFlight
  3)CH Robotics
  4)MultiWii
  5)S.O.H. Madgwick

  Designed to run on Naze32 Flight Control Board

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

///////////////////////////////////////////////////////////////////////////////
// Frame Timing Defines and Variables
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////
// Frame Timing Defines
///////////////////////////////////////

#define FRAME_COUNT   1000

#define COUNT_500HZ   2         // Number of 1000 Hz frames for 500 Hz Loop
#define COUNT_200HZ   5         // Number of 1000 Hz frames for 200 Hz Loop
#define COUNT_100HZ   10        // Number of 1000 Hz frames for 100 Hz Loop
#define COUNT_50HZ    20        // Number of 1000 Hz frames for  50 Hz Loop
#define COUNT_10HZ    100       // Number of 1000 Hz frames for  10 Hz Loop
#define COUNT_5HZ     200       // Number of 1000 Hz frames for   5 Hz Loop
#define COUNT_1HZ     1000      // Number of 1000 Hz frames for   1 Hz Loop

///////////////////////////////////////
// Frame Timing Variables
///////////////////////////////////////

extern uint16_t frameCounter;

extern uint8_t frame_500Hz;
extern uint8_t frame_200Hz;
extern uint8_t frame_100Hz;
extern uint8_t frame_50Hz;
extern uint8_t frame_10Hz;
extern uint8_t frame_5Hz;
extern uint8_t frame_1Hz;

extern uint32_t deltaTime1000Hz, executionTime1000Hz, previous1000HzTime;
extern uint32_t deltaTime500Hz, executionTime500Hz, previous500HzTime;
extern uint32_t deltaTime200Hz, executionTime200Hz, previous200HzTime;
extern uint32_t deltaTime100Hz, executionTime100Hz, previous100HzTime;
extern uint32_t deltaTime50Hz, executionTime50Hz, previous50HzTime;
extern uint32_t deltaTime10Hz, executionTime10Hz, previous10HzTime;
extern uint32_t deltaTime5Hz, executionTime5Hz, previous5HzTime;
extern uint32_t deltaTime1Hz, executionTime1Hz, previous1HzTime;

extern float dt500Hz, dt200Hz, dt100Hz;

extern uint8_t systemReady;

///////////////////////////////////////////////////////////////////////////////

void systemInit(void);

///////////////////////////////////////////////////////////////////////////////

void delayMicroseconds(uint32_t us);

///////////////////////////////////////////////////////////////////////////////

void delay(uint32_t ms);

///////////////////////////////////////////////////////////////////////////////

uint32_t micros(void);

///////////////////////////////////////////////////////////////////////////////

uint32_t millis(void);

///////////////////////////////////////////////////////////////////////////////

void failureMode(uint8_t mode);

///////////////////////////////////////////////////////////////////////////////

void systemReset(bool toBootloader);

///////////////////////////////////////////////////////////////////////////////
