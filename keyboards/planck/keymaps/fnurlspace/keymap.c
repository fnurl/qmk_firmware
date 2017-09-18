/* Jody Foo 2017 */

#include "planck.h"
#include "action_layer.h"
extern keymap_config_t keymap_config;

// for checking active layer in layer_state (use IS_LAYER_ON(<layer>) instead)
//#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// already defined in quantum
//#define LEADER_TIMEOUT 300

// Layers {{{1

enum planck_layers {
  _QWERTY,
  _PLEFT,
  _PRIGHT,
  _FN,
  _NAV,
  _GAME,
  _NUM,
  _PLANCK
};  // }}}1

// Custom keycodes, used in process_record_user() {{{1
enum custom_keycodes {
  FN,
  NAV,
  GAME
}; // }}}1

// Tap Dance config {{{1
enum {
    TD_GUI_LAUNCHBAR = 0,
    TD_TAB_CYCLE_APPS = 1,
    TD_AA_CYCLE_APPS = 2,
    TD_AE_CYCLE_WIN = 3
};

// Double Tap Dances {{{2
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GUI_LAUNCHBAR]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC)),
    [TD_TAB_CYCLE_APPS] = ACTION_TAP_DANCE_DOUBLE(KC_TAB , LGUI(KC_TAB)),
    [TD_AA_CYCLE_APPS]  = ACTION_TAP_DANCE_DOUBLE(KC_P7  , LGUI(KC_TAB)),
    [TD_AE_CYCLE_WIN]   = ACTION_TAP_DANCE_DOUBLE(KC_P8  , LALT(KC_TAB))
};

// Tap dance aliases {{{2
#define TDGUILB TD(TD_GUI_LAUNCHBAR)
#define TDTABAP TD(TD_TAB_CYCLE_APPS)
#define TDAAAPP TD(TD_AA_CYCLE_APPS)
#define TDAEWIN TD(TD_AE_CYCLE_WIN)
// }}}1

// Aliases to use in keymaps {{{1
// Fillers to make layering more clear {{{2
#define ______   KC_TRNS
#define XXXXXX   KC_NO

// Layer modifiers {{{2
#define NUM_MOD MO(_NUM)
#define MOUS_MD MO(_MOUSE)

// Dual-role keys: LT = layer when held, keycode when tapped {{{2
#define PL_SPC   LT(_PLEFT,  KC_SPC)
#define PR_SPC   LT(_PRIGHT, KC_SPC)
//#define DB_BCK   LT(_DBSPACE, KC_BSPC)
//#define DB_ENT   LT(_DBSPACE, KC_ENT)

// Dual-role keys: MT = modifier when held, keycode when tapped {{{2
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)

// Modifier combos {{{2
#define Z_IN    LGUI(KC_EQL)
#define Z_OUT   LGUI(KC_MINS)
#define LNCHBAR LGUI(KC_SPC)
#define PRV_TAB LGUI(LALT(KC_LEFT))
#define NXT_TAB LGUI(LALT(KC_RGHT))
// }}}1

// Keymap Layers {{{1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer (US-ANSI with ÅÄÖ) {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |TD:P7APP|
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | CT/EC  |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |  KP9   |TD:P8WIN|
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   ,    |   .    |   /    | Shift  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | HYPER  |   MEH  |  LALT  |  LGUI  |   FN   | PL_SPC | PR_SPC |  NAV   | LEADER |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , TDAAAPP,\
    CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_P9  , TDAEWIN,\
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,\
    KC_HYPR, KC_MEH , KC_LALT, KC_LGUI, FN     , PL_SPC , PR_SPC , NAV    , KC_LEAD, XXXXXX , XXXXXX , XXXXXX  \
), // }}}2

/* Paren Left Layer {{{2
 * Tap DB/ENT to produce ENTER. Hold DB/Enter to get to the Double Space Layer
  ,-----------------------------------------------------------------------------------------------------------.
  |   `    |    1   |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    | CMD-+  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   ~    |        |   <    |   {    |   (    |   [    |   *    |   $    |   =    |   &    |   %    | CMD--  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   ~    |   `    |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | DB/ENT |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_PLEFT] = KEYMAP( \
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , Z_IN   ,\
    KC_TILD, ______ , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, Z_OUT  ,\
    ______ , ______ , ______ , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT , ______ , ______ , ______ , ______ , ______  \
), // }}}2

/* Paren Right Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   `    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    | CMD-+  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   ~    |   !    |   @    |   #    |   ^    |   +    |   ]    |   )    |   }    |   >    |        | CMD--  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   ~    |   `    |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_PRIGHT] = KEYMAP( \
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , Z_IN   ,\
    KC_TILD, KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS, KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, ______ , Z_OUT  ,\
    ______ , ______ , ______ , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC, ______ , ______ , ______ , ______ , ______ , ______  \
), // }}}2

/* Navigation layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |   UP   |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |PREV TAB|NEXT TAB|  LEFT  |  DOWN  | RIGHT  |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_NAV] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_UP  , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , PRV_TAB, NXT_TAB, KC_LEFT, KC_DOWN, KC_RGHT, ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
), // }}}2

/* FN Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        |  GAME  |        |        |        |        |        |  F12   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |  PREV  |  PLAY  |  NEXT  |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        | LnchBar|        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_FN] = KEYMAP( \
    ______ , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
    ______ , KC_MUTE, KC_VOLD, KC_VOLU, ______ , GAME   , ______ , ______ , ______ , ______ , ______ , KC_F12 ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , LNCHBAR, ______ , ______ , ______ , ______ , ______ , ______  \
), // }}}2

/* Mouse Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |  LEFT  |  DOWN  |   UP   |  RIGHT |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
/*
[_MOUSE] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_WH_D, KC_MS_U, KC_WH_U,\
    ______ , ______ , ______ , KC_BTN2, KC_BTN1, ______ , ______ , ______ , ______ , KC_MS_L, KC_MS_D, KC_MS_R,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ \
), // }}}2
*/

/* Game layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  CTRL  |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  SPC   |  NUM   |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_GAME] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_LCTL, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_SPC , NUM_MOD, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
), // }}}2

/* Numeric Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   0    |   1    |   2    |   3    |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  ESC   |   4    |   5    |   6    |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   0    |   7    |   8    |   9    |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_NUM] = KEYMAP( \
    KC_0   , KC_1   , KC_2   , KC_3   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_ESC , KC_4   , KC_5   , KC_6   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_0   , KC_7   , KC_8   , KC_9   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
), // }}}2

/* Planck Layer (FN + NAV) {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        | Reset  |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|--------|
  |        |AudioOn |Music On| Voice+ |MusicMod|        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  |        |AudioOff|MusicOff| Voice- |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_PLANCK] = KEYMAP( \
  ______ , RESET  , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
  ______ , AU_ON  , MU_ON  , MUV_IN , MU_MOD , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
  ______ , AU_OFF , MU_OFF , MUV_DE , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
  ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ \
), // }}}2

};
// }}}1

// Songs, Tri Layer and DBL layers {{{1

// Notification sounds {{{2
#define DBLEFT_ON_SONG \
    S__NOTE(_A5),      \
    S__NOTE(_E6),

#define DBLEFT_OFF_SONG \
    S__NOTE(_E6),       \
    S__NOTE(_A5),

#define DBRIGHT_ON_SONG \
    S__NOTE(_B5),      \
    S__NOTE(_F6),

#define DBRIGHT_OFF_SONG \
    S__NOTE(_F6),       \
    S__NOTE(_B5),

// Create song arrays {{{2
#ifdef AUDIO_ENABLE
  float plover_song[][2]    = SONG(PLOVER_SOUND);
  float plover_gb_song[][2] = SONG(PLOVER_GOODBYE_SOUND);
  float dbl_on_song[][2]    = SONG(DBLEFT_ON_SONG);
  float dbl_off_song[][2]   = SONG(DBLEFT_OFF_SONG);
  float dbr_on_song[][2]    = SONG(DBRIGHT_ON_SONG);
  float dbr_off_song[][2]   = SONG(DBRIGHT_ON_SONG);
#endif

// DB layer notifications {{{2
/*bool notify_dbleft  = false;*/
/*bool notify_dbright = false;*/
//bool notified_game    = false;
//bool notified_db      = false;

// matrix_scan_user {{{2
//LEADER_EXTERNS();
//void matrix_scan_user(void) {
    /*
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        SEQ_TWO_KEYS(KC_G, KC_T) {
            register_code(KC_LGUI);
            register_code(KC_LALT);
            register_code(KC_RGHT);
            unregister_code(KC_RGHT);
            unregister_code(KC_LALT);
            unregister_code(KC_LGUI);
        }
    }
    */

    /*
    // double space bar layer activation and notifiction {{{3
    if (IS_LAYER_ON(_DBSPACE)) {
        if (!notified_db) {
            #ifdef AUDIO_ENABLE
            PLAY_SONG(dbl_on_song);
            #endif
            notified_db = true;
        }
    } else if (!IS_LAYER_ON(_DBSPACE)) {
        if (notified_db) {
            #ifdef AUDIO_ENABLE
            PLAY_SONG(dbl_off_song);
            #endif
            notified_db = false;
        }
    } // }}}3
    */

    /*
    uint8_t layer = biton32(layer_state);
    switch (layer) {
        case _PLEFT:
            if (IS_LAYER_ON(_PRIGHT)) {
                layer_off(_PLEFT);
                layer_off(_PRIGHT);
                layer_on(_DBLEFT);
                #ifdef AUDIO_ENABLE
                if (!notify_db) {
                    PLAY_SONG(dbl_on_song);
                    notify_db = true;
                }
                #endif
            break;
        case _DBLEFT: // {{{3
            #ifdef AUDIO_ENABLE
            if (!notify_dbleft) {
                PLAY_SONG(dbl_on_song);
                notify_dbleft = true;
            }
            #endif
            break; // }}}3
        case _DBRIGHT: // {{{3
            #ifdef AUDIO_ENABLE
            if (!notify_dbright) {
                PLAY_SONG(dbr_on_song);
                notify_dbright = true;
            }
            #endif
            break; // }}}3
        case _GAME: // {{{3
            #ifdef AUDIO_ENABLE
            if (!notified_game) {
                PLAY_SONG(plover_song);
                notify_game = true;
            }
            #endif
            break; // }}}3
        default: // {{{3
            // notify if layers have been turned off
            if (notify_dbleft && !IS_LAYER_ON(_DBLEFT)) {
                PLAY_SONG(dbl_off_song);
                notify_dbleft = false;
            }
            if (notify_dbright && !IS_LAYER_ON(_DBRIGHT)) {
                PLAY_SONG(dbr_off_song);
                notify_dbright = false;
            }
            // turn off and notify for dbl layer
            if (notified_db) {
                PLAY_SONG(dbl_off_song);
                notified_db = false;
            }
            // turn off and notify for game layer
            if (notified_game && !IS_LAYER_ON(_GAME)) {
                PLAY_SONG(plover_gb_song);
                notify_game = false;
            }
            break; // }}}3
    } //switch
    */
//}; // }}}2

// Tri layer and game layer
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN: // {{{2
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_FN, _NAV, _PLANCK);
      } else {
        layer_off(_FN);
        update_tri_layer(_FN, _NAV, _PLANCK);
      }
      return false;
      break;
    case NAV: // {{{2
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_FN, _NAV, _PLANCK);
      } else {
        layer_off(_NAV);
        update_tri_layer(_FN, _NAV, _PLANCK);
      }
      return false;
      break;
    case GAME: // {{{2
      if (record->event.pressed) {
        if (IS_LAYER_ON(_GAME)) {
            layer_off(_GAME);
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(dbl_off_song);
            #endif
        } else {
            layer_on(_GAME);
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(dbl_on_song);
            #endif
        }
      }
      return false;
      break;
  }
  return true;
}

// }}}1

/* vim: set fdm=marker: */
