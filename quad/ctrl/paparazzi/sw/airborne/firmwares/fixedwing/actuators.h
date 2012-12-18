/*  $Id$
 *
 * (c) 2003-2005 Pascal Brisset, Antoine Drouin
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/** \file actuators.h
 *  \brief Hardware independent API for actuators (servos, motor controllers)
 *
 */
#ifndef ACTUATORS_H
#define ACTUATORS_H

#if defined ACTUATORS

#include "paparazzi.h"

/** Defines SetActuatorsFromCommands() macro */
#include "generated/airframe.h"

/** Must be defined by specific hardware implementation */
extern void actuators_init( void );

/** Temporary storage (for debugging purpose, downlinked via telemetry) */
extern uint16_t actuators[SERVOS_NB];

#include ACTUATORS

#define SetServo(x, v) {                                        \
    Actuator(x) = SERVOS_TICS_OF_USEC(ChopServo(v,700,2400));   \
    actuators[x] = v;                                           \
  }

#else /* ACTUATORS */

// define empty SetServo makro for sim
#define SetServo(x, v) {}

#endif /* ACTUATORS */


#endif /* ACTUATORS_H */
