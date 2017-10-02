// disable debuging for a smaller firmware image
#ifndef NO_DEBUG
#define NO_DEBUG
#endif

#define TAPPING_TERM 200    // Defines how many ms before keyup for the event to count as a tap
#define PERMISSIVE_HOLD     // Ignore TAPPING_TERM if key was used as a modifier even within TAPPING_TERM
#define TAPPING_FORCE_HOLD  // When holding a dual role modifier, prioritize modifier role over key repeat

#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

// Audio {{{1
#ifdef AUDIO_ENABLE
    #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define DEFAULT_LAYER_SONGS { SONG(QWERTY_SOUND), \
                                  SONG(COLEMAK_SOUND), \
                                  SONG(DVORAK_SOUND) \
                                }
#endif

#define MUSIC_MASK (keycode != KC_NO)

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
                                
#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
//#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
//#define MIDI_TONE_KEYCODE_OCTAVES 2

#endif
// }}}1

/* vim: set fdm=marker: */

