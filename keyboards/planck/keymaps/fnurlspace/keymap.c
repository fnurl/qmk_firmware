/* Jody Foo 2017 */

// Boilerplate and pre-setup {{{1

/*
// for leader key
// preemptive define. defaults to 200 in quantum
#define LEADER_TIMEOUT 1000 
#include "version.h"
*/

#include "planck.h"
#include "action_layer.h"
extern keymap_config_t keymap_config;

// for checking active layer in layer_state (use IS_LAYER_ON(<layer>) instead)
//#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// TAP_ONCE for leader key {{{2
/*
// from https://github.com/qmk/qmk_firmware/blob/5bdddb7821a229470d9895ace8686b9fcf37494a/keyboards/atreus62/keymaps/mneme/keymap.c
#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)
*/

// Layers {{{2

enum planck_layers {
  _QWERTY,
  _PLEFT,
  _PRIGHT,
  _FN,
  _NAV,
  _GAME,
  _NUM,
  _PLANCK
};

// Custom keycodes, used in process_record_user() {{{2
enum custom_keycodes {
  FN,
  NAV,
  GAME,
  NONE
};

/*
// Tap Dance config {{{2
enum {
    TD_GUI_LAUNCHBAR = 0,
    TD_TAB_CYCLE_APPS = 1,
    TD_AA_CYCLE_APPS = 2,
    TD_AE_CYCLE_WIN = 3
};

// Double Tap Dances {{{3
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GUI_LAUNCHBAR]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC)),
    [TD_TAB_CYCLE_APPS] = ACTION_TAP_DANCE_DOUBLE(KC_TAB , LGUI(KC_TAB)),
    [TD_AA_CYCLE_APPS]  = ACTION_TAP_DANCE_DOUBLE(KC_P7  , LGUI(KC_TAB)),
    [TD_AE_CYCLE_WIN]   = ACTION_TAP_DANCE_DOUBLE(KC_P8  , LALT(KC_TAB))
};

// Tap dance aliases {{{3
#define TDGUILB TD(TD_GUI_LAUNCHBAR)
#define TDTABAP TD(TD_TAB_CYCLE_APPS)
#define TDAAAPP TD(TD_AA_CYCLE_APPS)
#define TDAEWIN TD(TD_AE_CYCLE_WIN)
*/

// Aliases to use in keymaps {{{2
// Fillers to make layering more clear {{{3
#define ______   KC_TRNS
//#define XXXXXX   KC_NO
#define XXXXXX   NONE

// Layer modifiers {{{3
#define NUM_MOD MO(_NUM)
//#define MOUS_MD MO(_MOUSE)

// Dual-role keys: LT = layer when held, keycode when tapped {{{3
#define PL_SPC   LT(_PLEFT,  KC_SPC)
#define PR_SPC   LT(_PRIGHT, KC_SPC)
//#define DB_BCK   LT(_DBSPACE, KC_BSPC)
//#define DB_ENT   LT(_DBSPACE, KC_ENT)

// Dual-role keys: MT = modifier when held, keycode when tapped {{{3
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)

// Modifier combos {{{3
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
  |        |        |  LALT  |  LGUI  |   FN   | PL_SPC | PR_SPC |  NAV   | HYPER  |  MEH   |        |Key Lock|
  `-----------------------------------------------------------------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_P7  ,\
    CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_P9  , KC_P8  ,\
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,\
    XXXXXX , XXXXXX , KC_LALT, KC_LGUI, FN     , PL_SPC , PR_SPC , NAV    , KC_HYPR, KC_MEH , XXXXXX , KC_LOCK \
),

/* Paren Left Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   ~    |    1   |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  CTRL  |        |   <    |   {    |   (    |   [    |   *    |   $    |   =    |   &    |   %    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | DB/ENT |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_PLEFT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    KC_LCTL, XXXXXX , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, XXXXXX ,\
    ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT , ______ , ______ , ______ , ______ , ______  \
),

/* Paren Right Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  CTRL  |   !    |   @    |   #    |   ^    |   +    |   ]    |   )    |   }    |   >    |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_PRIGHT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    KC_LCTL, KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS, KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, XXXXXX , XXXXXX ,\
    ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC, ______ , ______ , ______ , ______ , ______ , ______  \
),

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
    XXXXXX , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
    KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , GAME   , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , KC_F12 ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , LNCHBAR, XXXXXX , ______ , ______ , ______ , ______ , ______  \
),


/* Navigation layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |  WH UP |  BTN 2 |  M UP  |  BTN 1 |        |        |        |PREV TAB|   UP   |NEXT TAB|  PgUp  |zIN<C-+>|
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  WH DN |  M LFT |  M DN  |  M_RGT |        |        |        |  LEFT  |  DOWN  | RIGHT  |  PgDn  |zOU<C-->|
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_NAV] = KEYMAP( \
    KC_WH_U, KC_BTN2, KC_MS_U, KC_BTN1, XXXXXX , XXXXXX , XXXXXX , PRV_TAB, KC_UP  , NXT_TAB, KC_PGUP, Z_IN   ,\
    KC_WH_D, KC_MS_L, KC_MS_D, KC_MS_R, XXXXXX , XXXXXX , XXXXXX , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, Z_OUT  ,\
    ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , XXXXXX , XXXXXX , ______ , ______ , ______ , ______ , ______  \
),

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
),

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
    KC_0   , KC_1   , KC_2   , KC_3   , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
    KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
    KC_0   , KC_7   , KC_8   , KC_9   , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
    XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  \
),

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
  XXXXXX , RESET  , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , AU_ON  , MU_ON  , MUV_IN , MU_MOD , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , AU_OFF , MU_OFF , MUV_DE , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  \
),

};
// }}}1

// Songs, process_record_user {{{1

// Audio {{{2
// Notification sounds {{{3
#define GAME_ON_SONG \
    E__NOTE(_A5),    \
    E__NOTE(_E6),

#define GAME_OFF_SONG \
    E__NOTE(_E6),     \
    E__NOTE(_A5),

// Create song arrays {{{3
#ifdef AUDIO_ENABLE
  float game_on_song[][2]    = SONG(GAME_ON_SONG);
  float game_off_song[][2]   = SONG(GAME_OFF_SONG);
#endif

// Tri layer and game layer {{{2
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case NONE: // {{{3
        if (record->event.pressed) {
            // Do nothing.
            // KC_NO seems to reset layers
        }
        return false;
        break;
    case FN: // {{{3
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_FN, _NAV, _PLANCK);
      } else {
        layer_off(_FN);
        update_tri_layer(_FN, _NAV, _PLANCK);
      }
      return false;
      break;
    case NAV: // {{{3
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_FN, _NAV, _PLANCK);
      } else {
        layer_off(_NAV);
        update_tri_layer(_FN, _NAV, _PLANCK);
      }
      return false;
      break;
    case GAME: // {{{3
      if (record->event.pressed) {
        if (IS_LAYER_ON(_GAME)) {
            layer_off(_GAME);
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(game_off_song);
            #endif
        } else {
            layer_on(_GAME);
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(game_on_song);
            #endif
        }
      }
      return false;
      break;
  }
  return true;
}
// }}}1

// matrix_scan_user, leader key {{{1
/*
LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY (KC_R) {
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
      tap_random_base64();
    }
    SEQ_ONE_KEY (KC_V) {
      SEND_STRING (QMK_KEYBOARD);
      SEND_STRING ("/");
      SEND_STRING (QMK_KEYMAP);
      SEND_STRING (" @ ");
      SEND_STRING (QMK_VERSION);
    }
    SEQ_ONE_KEY(KC_F) {
      SEND_STRING("if yes\n\tpeanut butter\nelse\n\trice snacks");
    }
    SEQ_TWO_KEYS(KC_A, KC_S) {
      TAP_ONCE(KC_A);
    }
    SEQ_THREE_KEYS(KC_A, KC_S, KC_D) {
      register_code(KC_LGUI);
      register_code(KC_S);
      unregister_code(KC_S);
      unregister_code(KC_LGUI);
    }
  }
}
*/
// }}}1

/* vim: set fdm=marker: */
