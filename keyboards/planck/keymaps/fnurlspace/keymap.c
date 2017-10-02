/* Jody Foo 2017 */

/* Features:
 *
 * - caps: double shift dance to toggle
 * - one shot hyper: double tab dance to activate
 * - lockable nav layer: double nav dance
 */


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

// Macros {{{2

// For checking active layer in layer_state {{{3
// deprecated, use IS_LAYER_ON(<layer>) instead
//#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// TAP_ONCE for leader key {{{3
/*
// from https://github.com/qmk/qmk_firmware/blob/5bdddb7821a229470d9895ace8686b9fcf37494a/keyboards/atreus62/keymaps/mneme/keymap.c
#define TAP_ONCE(code)  \
  register_code (code); \
  unregister_code (code)
*/

// HYPER_ONCE() for _HYPER layer
#define HYPER_DOWN SS_DOWN(X_LGUI)SS_DOWN(X_LCTL)SS_DOWN(X_LALT)SS_DOWN(X_LSFT)
#define HYPER_UP SS_UP(X_LGUI)SS_UP(X_LCTL)SS_UP(X_LALT)SS_UP(X_LSFT)
// }}}2

// Layers {{{2

enum planck_layers {
  _QWERTY,
  _PLEFT,
  _PRIGHT,
  _FN,
  _NAV,
  _GAME,
  _NUM,
  _PLANCK,
  _HYPER
};

// Custom keycodes, used in process_record_user() {{{2
enum custom_keycodes {
  FN,
  NAV,
  NAVLCK,
  HYPROS,
  GAME,
  NONE,
  HYP_A,
  HYP_B,
  HYP_C,
  HYP_D,
  HYP_E,
  HYP_F,
  HYP_G,
  HYP_H,
  HYP_I,
  HYP_J,
  HYP_K,
  HYP_L,
  HYP_M,
  HYP_N,
  HYP_O,
  HYP_P,
  HYP_Q,
  HYP_R,
  HYP_S,
  HYP_T,
  HYP_U,
  HYP_V,
  HYP_W,
  HYP_X,
  HYP_Y,
  HYP_Z,
  HYP_ESC,
  HYP_COM,
  HYP_DOT,
  HYP_SLH
};

// Tap Dance config {{{2
enum {
    TD_GUI_LAUNCHBAR = 0,
    TD_TAB_CYCLE_APPS = 1,
    TD_AA_CYCLE_APPS = 2,
    TD_AE_CYCLE_WIN = 3,
    TD_RCAPSLOCK = 4,
    TD_LCAPSLOCK = 5,
    TD_NAVLOCK = 6,
    TD_HYPER_ONESHOT = 7
};

// Double Tap Dances {{{3
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GUI_LAUNCHBAR]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC)),
    [TD_TAB_CYCLE_APPS] = ACTION_TAP_DANCE_DOUBLE(KC_TAB , LGUI(KC_TAB)),
    [TD_AA_CYCLE_APPS]  = ACTION_TAP_DANCE_DOUBLE(KC_P7  , LGUI(KC_TAB)),
    [TD_AE_CYCLE_WIN]   = ACTION_TAP_DANCE_DOUBLE(KC_P8  , LALT(KC_TAB)),
    [TD_RCAPSLOCK]      = ACTION_TAP_DANCE_DOUBLE(KC_RSFT, KC_CAPS),
    [TD_LCAPSLOCK]      = ACTION_TAP_DANCE_DOUBLE(KC_LSFT, KC_CAPS),
    [TD_NAVLOCK]        = ACTION_TAP_DANCE_DOUBLE(NAV    , NAVLCK),
    [TD_HYPER_ONESHOT]  = ACTION_TAP_DANCE_DOUBLE(KC_TAB , HYPROS)
};

// Tap dance aliases (use in layout) {{{3
#define TDGUILB TD(TD_GUI_LAUNCHBAR)
#define TDTABAP TD(TD_TAB_CYCLE_APPS)
#define TDAAAPP TD(TD_AA_CYCLE_APPS)
#define TDAEWIN TD(TD_AE_CYCLE_WIN)
#define TDRCAPS TD(TD_RCAPSLOCK)
#define TDLCAPS TD(TD_LCAPSLOCK)
#define TDNAVLK TD(TD_NAVLOCK)
#define TDHYPOS TD(TD_HYPER_ONESHOT)


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
#define OCC     LGUI(LCTL(KC_LALT))
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
  |        |        |  LALT  |  LGUI  |   FN   | PL_SPC | PR_SPC |NAV+LOCK| HYPER  |  MEH   |O-C-CMD |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    TDHYPOS, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_P7  ,\
    CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_P9  , KC_P8  ,\
    TDLCAPS, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDRCAPS,\
    ______ , XXXXXX , KC_LALT, KC_LGUI, FN     , PL_SPC , PR_SPC , TDNAVLK, KC_HYPR, KC_MEH , OCC    , KC_DEL  \
),

/* HYPER layer (US-ANSI with ÅÄÖ) {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |L:QWERTY| HYPER Q| HYPER W| HYPER E| HYPER R| HYPER T| HYPER Y| HYPER U| HYPER I| HYPER O| HYPER P|        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |HYPR ESC| HYPER A| HYPER S| HYPER D| HYPER F| HYPER G| HYPER H| HYPER J| HYPER K| HYPER L|        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        | HYPER Z| HYPER X| HYPER C| HYPER V| HYPER B| HYPER N| HYPER M| HYPER ,| HYPER .| HYPER /|        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_HYPER] = KEYMAP( \
    HYPROS, HYP_Q  , HYP_W  , HYP_E  , HYP_R  , HYP_T  , HYP_Y  , HYP_U  , HYP_I  , HYP_O  , HYP_P  , XXXXXX ,\
    HYP_ESC, HYP_A  , HYP_S  , HYP_D  , HYP_F  , HYP_G  , HYP_H  , HYP_J  , HYP_K  , HYP_L  , XXXXXX , XXXXXX ,\
    XXXXXX , HYP_Z  , HYP_X  , HYP_C  , HYP_V  , HYP_B  , HYP_N  , HYP_M  , HYP_COM, HYP_DOT, HYP_SLH, XXXXXX ,\
    XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  \
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
  |        |        |  DEL   |        |        | LnchBar|        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_FN] = KEYMAP( \
    XXXXXX , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
    KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , GAME   , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , KC_F12 ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , KC_DEL , ______ , ______ , LNCHBAR, XXXXXX , ______ , ______ , ______ , ______ , ______  \
),


/* Navigation layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |PREV TAB|   UP   |NEXT TAB|  PgUp  |zIN<C-+>|
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        |        |        |  LEFT  |  DOWN  | RIGHT  |  PgDn  |zOU<C-->|
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |  PREV  |  PLAY  |  NEXT  |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_NAV] = KEYMAP( \
    XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , PRV_TAB, KC_UP  , NXT_TAB, KC_PGUP, Z_IN   ,\
    KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , XXXXXX , XXXXXX , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, Z_OUT  ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , XXXXXX , XXXXXX , ______ , ______ , ______ , ______ , ______  \
),

/* Game layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  CTRL  |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        | ENTER  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  SPC   |  NUM   |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_GAME] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_LCTL, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT ,\
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
    ______ , ______ , ______ , ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  \
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
  ______ , AU_OFF , MU_OFF , MUV_DE , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
  ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
),

};
// }}}1

// Songs, process_record_user {{{1

// Audio {{{2
// Notification sounds {{{3
#define ON_SONG \
    Q__NOTE(_A5),    \
    E__NOTE(_A6),

#define OFF_SONG \
    Q__NOTE(_A6),     \
    E__NOTE(_A5),

// Create song arrays {{{3
#ifdef AUDIO_ENABLE
  float on_song[][2]    = SONG(ON_SONG);
  float off_song[][2]   = SONG(OFF_SONG);
#endif

// process_record_user: Tri layer, game layer, Hyper keys {{{2
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {  // {{{3
    case NONE:    // Don't do anything {{{4
      if (record->event.pressed) {
        // Do nothing.
        // KC_NO seems to reset layers
      }
      return false;
      break;
    case FN:      // _FN layer + tri layer {{{4
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_FN, _NAV, _PLANCK);
      } else {
        layer_off(_FN);
        update_tri_layer(_FN, _NAV, _PLANCK);
      }
      return false;
      break;
    case NAV:     // _NAV layer + tri layer {{{4
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_FN, _NAV, _PLANCK);
      } else {
        layer_off(_NAV);
        update_tri_layer(_FN, _NAV, _PLANCK);
      }
      return false;
      break;
    case GAME:    // Toggle _GAME layer with sound feedback {{{4
      if (record->event.pressed) {
        if (IS_LAYER_ON(_GAME)) {
          layer_off(_GAME);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(off_song);
          #endif
        } else {
          layer_on(_GAME);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(on_song);
          #endif
        }
      }
      return false;
      break;
    case NAVLCK:  // Toggle _NAV layer with sound feedback {{{4
      if (record->event.pressed) {
        if (IS_LAYER_ON(_NAV)) {
          layer_off(_NAV);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(off_song);
          #endif
        } else {
          layer_on(_NAV);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(on_song);
          #endif
        }
      }
      return false;
      break;
    case HYPROS:  // Prime _HYPER one shot with sound feedback {{{4
      if (record->event.pressed) {
        if (IS_LAYER_ON(_HYPER)) {
          layer_off(_HYPER);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(off_song);
          #endif
        } else {
          layer_on(_HYPER);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(on_song);
          #endif
        }
      }
      return false;
      break;
  } // end keypress/keyrelease

  // only key press
  // all keys are relseased when a layer is switched
  if (record->event.pressed) {
    switch(keycode) {
      case HYP_A:
        SEND_STRING(HYPER_UP"a"HYPER_DOWN);
        layer_off(_HYPER);
        return false;
        break;
    }
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
