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
    #define STARTUP_SONG SONG(M__NOTE(_C5, 2))
    #define GOODBYE_SONG SONG(M__NOTE(_G4, 2))
    // #define STARTUP_SONG SONG(PLANCK_SOUND)
    // #define STARTUP_SONG SONG(NO_SOUND)

    #define AUDIO_ON_SONG  SONG(M__NOTE(_A5, 2))
    #define AUDIO_OFF_SONG SONG(M__NOTE(_A4, 2))
#endif

#define MUSIC_MASK (keycode != KC_NO)

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1
//#define MIDI_BASIC

#endif
// }}}1

/* vim: set fdm=marker: */

