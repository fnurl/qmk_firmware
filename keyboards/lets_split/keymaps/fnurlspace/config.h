/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// fnurlspace additions {{{1
// disable debuging for a smaller firmware image
#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#define TAPPING_TERM 150    // Defines how many ms before keyup for the event
                            // to count as a tap
#define PERMISSIVE_HOLD     // Ignore TAPPING_TERM if key was used as a
                            // modifier even within TAPPING_TERM
#define TAPPING_FORCE_HOLD  // When holding a dual role modifier, prioritize
                            // modifier role over key repeat
// }}}1

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
// #define EE_HANDS

#endif
