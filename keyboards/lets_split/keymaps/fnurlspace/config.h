// disable debuging for a smaller firmware image
#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#define TAPPING_TERM 200    // Defines how many ms before keyup for the event to count as a tap
#define PERMISSIVE_HOLD     // Ignore TAPPING_TERM if key was used as a modifier even within TAPPING_TERM
#define TAPPING_FORCE_HOLD  // When holding a dual role modifier, prioritize modifier role over key repeat
#define TAPPING_TOGGLE 2    // Only require two taps to toggle a layer on

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

/* Use I2C or Serial, not both */

#define USE_SERIAL
// #define USE_I2C

/* Select hand configuration */

#define MASTER_LEFT
// #define _MASTER_RIGHT
// #define EE_HANDS

#endif
// }}}1

/* vim: set fdm=marker: */
