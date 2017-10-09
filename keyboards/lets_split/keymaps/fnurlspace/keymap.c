/* 
 * fnurlspace layout for 40% ortholinear keyboards
 * Jody Foo 2017
 */

/* Features:
 *
 *
 */

// Boilerplate and pre-setup {{{1

// includes {{{2
#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"
extern keymap_config_t keymap_config;

// Enumerate layers {{{2
enum fnurlspace_layers {
  _QWERTY,
  _PLEFT,
  _PRIGHT,
  _FN,
  _NAV,
  _GAME,
  _NUM,
  _PLANCK,
  _ADJUST,
  _HYPER
};

// Custom keycodes, used in process_record_user() {{{2
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  FN,
  NAV,
  NAVLOCK,
  HYPEROS,
  GAME,
  VIMSAVE,
  NONE
};

// Tap Dance aliases and IDs {{{2
enum {
    TD_GUI_LAUNCHBAR  = 0,
    TD_TAB_CYCLE_APPS = 1,
    TD_AA_CYCLE_APPS  = 2,
    TD_AE_CYCLE_WIN   = 3,
    TD_RCAPSLOCK      = 4,
    TD_LCAPSLOCK      = 5,
    TD_NAVLOCK        = 6,
    TD_HYPER_ONESHOT  = 7,
    TD_NAVHYPER       = 8,
    TD_NAVCMD         = 9,
    TD_HYPMEH         = 10,
    TD_CMDHYP         = 11,
    TD_NVCMHP         = 12
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
#define TDHYPNV TD(TD_NAVHYPER)
#define TDNVCMD TD(TD_NAVCMD)
#define TDHYPME TD(TD_HYPMEH)
#define TDCMDHY TD(TD_CMDHYP)
#define TDNVCMH TD(TD_NVCMHP)

// Aliases to use in keymaps {{{2
// Fillers to make layering more clear {{{3
//#define XXXXXX   KC_NO
#define XXXXXX   NONE
#define ______   KC_TRNS

// Layer modifiers {{{3
#define NUM_MOD MO(_NUM)

// One-shot layers {{{3
#define OSHYPER OSL(_HYPER)

// Dual-role layer keys: LT = layer when held, keycode when tapped {{{3
#define PL_SPC   LT(_PLEFT,  KC_SPC)
#define PR_SPC   LT(_PRIGHT, KC_SPC)

// Dual-role modiliers: MT = modifier when held, keycode when tapped {{{3
#define ESC_CTL MT(MOD_LCTL, KC_ESC)
#define AE_CTL  MT(MOD_LCTL, KC_P8)
#define F_CTL   MT(MOD_LCTL, KC_F)
#define J_CTL   MT(MOD_LCTL, KC_J)
#define G_CMD   MT(MOD_LGUI, KC_G)
#define H_CMD   MT(MOD_LGUI, KC_H)
#define D_OPT   MT(MOD_LALT, KC_D)
#define K_OPT   MT(MOD_LALT, KC_K)
#define S_SHIFT MT(MOD_LSFT, KC_S)
#define L_SHIFT MT(MOD_LSFT, KC_L)

// Modifier combos {{{3
#define Z_IN    LGUI(KC_EQL)
#define Z_OUT   LGUI(KC_MINS)
#define LNCHBAR LGUI(KC_SPC)
#define PRV_TAB LGUI(LALT(KC_LEFT))
#define NXT_TAB LGUI(LALT(KC_RGHT))
#define OCC     LGUI(LCTL(KC_LALT))
#define TERM    LGUI(KC_ESC)
#define FILEMAN LALT(KC_ESC)

// Layer keys {{{3
#define ADJUST MO(_ADJUST)

// }}}1

// Keymap Layers {{{1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer: US-ANSI with ÅÄÖ (KC_P7--KC_P9) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    | |   Y    |   U    |   I    |   O    |   P    |   Å    |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  |CTRL/ESC|   A    |   S    |   D    |   F    |   G    | |   H    |   J    |   K    |   L    |   Ö    |   Ä    |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    | |   N    |   M    |   ,    |   .    |   /    | Shift  |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  |  DEL   | BCKSPC |  FN    |  LALT  |TD:CMDHY| PL/SPC | | PR/SPC |TD:NCMHY|TD:HYPME|  ALT   |        | ADJUST |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    ,  KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_P7  ,\
    ESC_CTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G    ,  KC_H   , KC_J   , KC_K   , KC_L   , KC_P9  , KC_P8  ,\
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B    ,  KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, TDRCAPS,\
    KC_DEL , KC_BSPC, FN     , KC_LALT, KC_LGUI, PL_SPC  ,  PR_SPC , TDNVCMH, TDHYPME, KC_RALT, XXXXXX , ADJUST  \
),

/* HYPER layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        | HYPER Q| HYPER W| HYPER E| HYPER R| HYPER T| | HYPER Y| HYPER U| HYPER I| HYPER O| HYPER P|        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |HYPR ESC| HYPER A| HYPER S| HYPER D| HYPER F| HYPER G| | HYPER H| HYPER J| HYPER K| HYPER L|        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        | HYPER Z| HYPER X| HYPER C| HYPER V| HYPER B| | HYPER N| HYPER M| HYPER ,| HYPER .| HYPER /|        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_HYPER] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , HYPEROS,\
    KC_ESC , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , HYPEROS, HYPEROS,\
    HYPEROS, ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , HYPEROS,\
    HYPEROS, ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , HYPEROS \
),

/* Paren Left Layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   ~    |    1   |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  CTRL  |        |   <    |   {    |   (    |   [    | |   *    |   $    |   =    |   &    |   %    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | | DB/ENT |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_PLEFT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    KC_LCTL, XXXXXX , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC ,  KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, XXXXXX ,\
    ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______  ,  KC_ENT , ______ , ______ , ______ , ______ , ______  \
),

/* Paren Right Layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  CTRL  |   !    |   @    |   #    |   ^    |   +    | |   ]    |   )    |   }    |   >    |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_PRIGHT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    KC_LCTL, KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS ,  KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, XXXXXX , XXXXXX ,\
    ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC ,  ______ , ______ , ______ , ______ , ______ , ______  \
),

/* FN Layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |   F1   |   F2   |   F3   |   F4   |   F5   | |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |  F12   |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        | NAV    |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_FN] = KEYMAP( \
    XXXXXX , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5   ,  KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
    KC_LCTL, XXXXXX , XXXXXX , XXXXXX , XXXXXX , GAME    ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , KC_F12 ,\
    ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , XXXXXX  ,  XXXXXX , NAV    , ______ , ______ , ______ , ______  \
),


/* Navigation layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        | VIMSAVE|        |        |        |  TERM  | |        |PREV TAB|   UP   |NEXT TAB|  PgUp  |zIN<C-+>|
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |FILEMAN |  GAME  | |        |  LEFT  |  DOWN  | RIGHT  |  PgDn  |zOU<C-->|
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |  PREV  |  PLAY  |  NEXT  |        |        | |        |Mouse 2 |Mouse 1 |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |  FN    |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_NAV] = KEYMAP( \
    XXXXXX , XXXXXX , VIMSAVE, XXXXXX , XXXXXX , TERM    ,  XXXXXX , PRV_TAB, KC_UP  , NXT_TAB, KC_PGUP, Z_IN   ,\
    KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, FILEMAN, GAME    ,  XXXXXX , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, Z_OUT  ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, XXXXXX , XXXXXX  ,  XXXXXX , KC_BTN2, KC_BTN1, XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , FN     , ______ , ______ , XXXXXX  ,  XXXXXX , ______ , ______ , ______ , ______ , ______  \
),

/* Game layer (left side) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |  I     |        |        |        | |        |        |  W     |        |        | BCKSPC |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  H     |  J     |  K     |  L     |        |        | |  CTRL  |  A     |  S     |  D     |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  N     |        |        |        |        |        | |  Shift |        |        |        |        | ENTER  |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | PR/SPC |TD:NAVLK|        |        |        |        | |  SPC   |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_GAME] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , KC_BSPC,\
    KC_ESC , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , KC_ENT ,\
    ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_SPC , NUM_MOD, ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______  \
),

/* Game layer (right side) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |  I     |        |        |        | |        |        |  W     |        |        | BCKSPC |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  H     |  J     |  K     |  L     |        |        | |  CTRL  |  A     |  S     |  D     |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  N     |        |        |        |        |        | |  Shift |        |        |        |        | ENTER  |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | PR/SPC |TD:NAVLK|        |        |        |        | |  SPC   |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
[_GAME] = KEYMAP( \
    ______ , ______ , KC_I   , ______ , ______ , ______  ,  ______ , ______ , KC_W   , ______ , ______ , KC_BSPC,\
    KC_H   , KC_J   , KC_K   , KC_L   , ______ , ______  ,  KC_LCTL, KC_A   , KC_S   , KC_D   , ______ , ______ ,\
    KC_N   , ______ , ______ , ______ , ______ , ______  ,  KC_LSFT, ______ , ______ , ______ , ______ , KC_ENT ,\
    PR_SPC , TDNVCMD, ______ , ______ , ______ , ______  ,  KC_SPC , NUM_MOD, NAV    , ______ , ______ , ______  \
),
*/

/* Numeric Layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   0    |   1    |   2    |   3    |        |        | |   0    |   1    |   2    |   3    |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  ESC   |   4    |   5    |   6    |        |        | |  ESC   |   4    |   5    |   6    |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |   0    |   7    |   8    |   9    |        |        | |   0    |   7    |   8    |   9    |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_NUM] = KEYMAP( \
    KC_0   , KC_1   , KC_2   , KC_3   , XXXXXX , XXXXXX  ,  KC_0   , KC_1   , KC_2   , KC_3   , XXXXXX , ______ ,\
    KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX  ,  KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX ,\
    KC_0   , KC_7   , KC_8   , KC_9   , XXXXXX , XXXXXX  ,  KC_0   , KC_7   , KC_8   , KC_9   , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______  \
),

/* Adjust Layer (FN + NAV) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        | Reset  |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------|--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_ADJUST] = KEYMAP( \
    XXXXXX , RESET  , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
    XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
    ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , FN     , ______  ,  ______ , NAV    , ______ , ______ , ______ , ______  \
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
  ______ , ______ , ______ , ______ , FN     , ______ , ______ , NAV    , ______ , ______ , ______ , ______  \
),

};
// }}}1

// Audio {{{1
// Notification sounds {{{2
#define NAV_ON_SONG    M__NOTE(_D5, 2),
#define NAV_OFF_SONG   M__NOTE(_D4, 2),
#define HYPER_ON_SONG  M__NOTE(_F5, 2),
#define HYPER_OFF_SONG M__NOTE(_F4, 2),
#define GAME_ON_SONG   M__NOTE(_A5, 2),
#define GAME_OFF_SONG  M__NOTE(_A4, 2),
#define CAPS_SONG      M__NOTE(_G5, 2),
#define MEH_ON_SONG    M__NOTE(_FS5, 2),
#define CMD_ON_SONG    M__NOTE(_G5, 2),

// Create song arrays {{{2
#ifdef AUDIO_ENABLE
  float game_on_song[][2]   = SONG(GAME_ON_SONG);
  float game_off_song[][2]  = SONG(GAME_OFF_SONG);
  float nav_on_song[][2]    = SONG(NAV_ON_SONG);
  float nav_off_song[][2]   = SONG(NAV_OFF_SONG);
  float hyper_on_song[][2]  = SONG(HYPER_ON_SONG);
  float hyper_off_song[][2] = SONG(HYPER_OFF_SONG);
  float caps_song[][2]      = SONG(CAPS_SONG);
  float meh_on_song[][2]         = SONG(MEH_ON_SONG);
  float cmd_on_song[][2]         = SONG(CMD_ON_SONG);
#endif

//}}}1

// Advanced Tap Dancing functions {{{1
// nav_and_lock_dance_finished() {{{2
void nav_and_lock_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for the momentary NAV layer
    case 1:
      layer_on(_NAV);
      break;
    case 2:
      // Tap twice or holding after twice: toggle NAVLOCK
      if (IS_LAYER_ON(_NAV)) {
        layer_off(_NAV);
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(nav_off_song);
        #endif
      } else {
        layer_on(_NAV);
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(nav_on_song);
        #endif
      }
      break;
  }
}

// nav_and_lock_dance_reset() - release momentary NAV {{{2
void nav_and_lock_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_NAV);
  }
}

// hyper_and_hyperos_finished() HYPER when tapped once and held, HYPER One-shot when double tapped and held {{{2
void hyper_and_hyperos_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for momentary HYPER and turning off HYPER layer
    case 1:
      // unprime hyper one-shot if tapped once
      if (IS_LAYER_ON(_HYPER)) {
        layer_off(_HYPER);
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_off_song);
        #endif
      }

      // momentary hyper
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      break;
    case 2:
      // Second tap always activates HYPER layer
      layer_on(_HYPER);
	  #ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(hyper_on_song);
	  #endif
      break;
  }
}

// hyper_and_hyperos_dance_reset() - release HYPER mod {{{2
void hyper_and_hyperos_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // release HYPER
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
  }
}

// navhyper_dance_finished() - nav when held, hyper when double tapped + held {{{2
void navhyper_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for NAV-layer.
    case 1:
      layer_on(_NAV);
      break;
    case 2:
      // Tapping twice + hold = momentary hyper
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(hyper_on_song);
      #endif
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      break;
  }
}

// navhyper_reset() - release _NAV or HYPER {{{2
void navhyper_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // deactivate momentary NAV layer
      layer_off(_NAV);
      break;
    case 2:
      // otherwise release hyper modifiers
      unregister_code(KC_LGUI);
      unregister_code(KC_LALT);
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
      break;
  }
}

// navcmd_dance_finished() - nav when held, CMD when double tapped + held {{{2
void navcmd_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for NAV-layer.
    case 1:
      layer_on(_NAV);
      break;
    case 2:
      // Tapping twice + hold = momentary cmd
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(cmd_on_song);
      #endif
      register_code(KC_LGUI);
      break;
  }
}

// navcmd_reset() - release _NAV {{{2
void navcmd_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // deactivate momentary NAV layer
      layer_off(_NAV);
      break;
    case 2:
      // otherwise release cmd modifier
      unregister_code(KC_LGUI);
      break;
  }
}

// navcmdhyper_dance_finished() - nav, cmd and hyper {{{2
void navcmdhyper_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for NAV-layer.
    case 1:
      layer_on(_NAV);
      break;
    case 2:
      // Tapping twice + hold = momentary cmd
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(cmd_on_song);
      #endif
      register_code(KC_LGUI);
      break;
    case 3:
      // Tapping twice + hold = momentary hyper
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(hyper_on_song);
      #endif
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      break;
  }
}

// navcmdhyper_dance_reset() - release _NAV, CMD or HYPER {{{2
void navcmdhyper_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // deactivate momentary NAV layer
      layer_off(_NAV);
      break;
    case 2:
      // otherwise release cmd modifier
      unregister_code(KC_LGUI);
      break;
    case 3:
      // otherwise release hyper modifiers
      unregister_code(KC_LGUI);
      unregister_code(KC_LALT);
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
      break;
  }
}

// cmdhyper_dance_finished() - CMD when held, HYPER when double tapped + held {{{2
void cmdhyper_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for momentary CMD
    case 1:
      register_code(KC_LGUI);
      break;
    case 2:
      // Tapping twice + hold = momentary HYPER
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(hyper_on_song);
      #endif
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LSFT);
      register_code(KC_LCTL);
      break;
  }
}

// cmdhyper_dance_reset() - release CMD/HYPER {{2
void cmdhyper_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // deactivate momentary CMD
      unregister_code(KC_LGUI);
      break;
    case 2:
      // otherwise release HYPER modifier
      unregister_code(KC_LGUI);
      unregister_code(KC_LALT);
      unregister_code(KC_LSFT);
      unregister_code(KC_LCTL);
      break;
  }
}

// hypme_dance_finished() - HYPWE when held, MEH when double tapped + held {{{2
void hypermeh_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for momentary HYPER.
    case 1:
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      break;
    case 2:
      // Tapping twice + hold = momentary MEH
      // add meh modifiers
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(meh_on_song);
      #endif
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LSFT);
      break;
  }
}

// hypme_dance_reset() - release HYPER/MEH{{2
void hypermeh_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // deactivate momentary HYPER
      unregister_code(KC_LGUI);
      unregister_code(KC_LALT);
      unregister_code(KC_LCTL);
      unregister_code(KC_LSFT);
      break;
    case 2:
      // otherwise release meh modifier
      unregister_code(KC_LGUI);
      unregister_code(KC_LALT);
      unregister_code(KC_LSFT);
      break;
  }
}

// fnhyper_dance_finished() {{{2
void fnhyper_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for the momentary FN-layer.
    // Tap once or hold: Turn off HYPER if on, otherwise hold HYPER
    case 1:
      // turn off hyper and make a sound if HYPER was on
      if (IS_LAYER_ON(_HYPER)) {
        layer_off(_HYPER);
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_off_song);
        #endif
      }

      // always function as FN
      layer_on(_FN);
      break;
    // Second tap toggles the HYPER layer
    case 2:
      // Toggle _HYPER off
      if (IS_LAYER_ON(_HYPER)) {
        layer_off(_HYPER);
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_off_song);
        #endif
      // otherwise toggle _HYPER off
      } else {
        layer_on(_HYPER);
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_on_song);
        #endif
      }
      break;
  }
}

// fnhyper_dance_reset {{{2
void fnhyper_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  // After a tap dance if there was only one tap, neither FN or HYPER layers
  // should be activated.
  if (state->count == 1) {
    layer_off(_FN);
  }
}

// caps_dance_finished() {{{2
void caps_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      register_code(KC_RSFT);
      break;
    case 2:
      register_code(KC_CAPS);
      break;
  }
}

// caps_dance_reset() {{{2
void caps_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      unregister_code(KC_RSFT);
      break;
    case 2:
      unregister_code(KC_CAPS);
      #ifdef AUDIO_ENABLE
      stop_all_notes();
      PLAY_SONG(caps_song);
      #endif
      break;
    }
}
// }}}1

// Tap Dance Actions {{{1
qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_GUI_LAUNCHBAR]  = ACTION_TAP_DANCE_DOUBLE(KC_LGUI   , LGUI(KC_SPC)),
    [TD_TAB_CYCLE_APPS] = ACTION_TAP_DANCE_DOUBLE(KC_TAB    , LGUI(KC_TAB)),
    [TD_AA_CYCLE_APPS]  = ACTION_TAP_DANCE_DOUBLE(KC_P7     , LGUI(KC_TAB)),
    [TD_AE_CYCLE_WIN]   = ACTION_TAP_DANCE_DOUBLE(KC_P8     , LALT(KC_TAB)),
    [TD_LCAPSLOCK]      = ACTION_TAP_DANCE_DOUBLE(KC_LSFT   , KC_CAPS),
    [TD_RCAPSLOCK]      = ACTION_TAP_DANCE_FN_ADVANCED(NULL , caps_dance_finished              , caps_dance_reset),
    [TD_NAVLOCK]        = ACTION_TAP_DANCE_FN_ADVANCED(NULL , nav_and_lock_dance_finished      , nav_and_lock_dance_reset),
    [TD_NAVHYPER]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL , navhyper_dance_finished          , navhyper_dance_reset),
    [TD_HYPER_ONESHOT]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL , hyper_and_hyperos_dance_finished , hyper_and_hyperos_dance_reset),
    [TD_NAVCMD]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL , navcmd_dance_finished            , navcmd_dance_reset),
    [TD_NVCMHP]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL , navcmdhyper_dance_finished       , navcmdhyper_dance_reset),
    [TD_CMDHYP]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL , cmdhyper_dance_finished          , cmdhyper_dance_reset),
    [TD_HYPMEH]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL , hypermeh_dance_finished          , hypermeh_dance_reset)
};
// }}}1

// process_record_user: Tri layer, game layer, hyper keys {{{1
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // switch for both keypressed and keyrelease {{{2
  switch (keycode) {
    case NONE:    // Don't do anything {{{2
      if (record->event.pressed) {
        // Do nothing.
        // KC_NO seems to reset layers
      }
      return false;
      break;
    case FN:      // _FN layer + tri layer {{{2
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_FN, _NAV, _ADJUST);
      } else {
        layer_off(_FN);
        update_tri_layer(_FN, _NAV, _ADJUST);
      }
      return false;
      break;
    case NAV:     // _NAV layer + tri layer {{{2
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_FN, _NAV, _ADJUST);
      } else {
        layer_off(_NAV);
        update_tri_layer(_FN, _NAV, _ADJUST);
      }
      return false;
      break;
    case GAME:    // Toggle _GAME layer {{{2
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
    case NAVLOCK:  // Toggle _NAV layer {{2
      if (record->event.pressed) {
        if (IS_LAYER_ON(_NAV)) {
          layer_off(_NAV);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(nav_off_song);
          #endif
        } else {
          layer_on(_NAV);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(nav_on_song);
          #endif
        }
      }
      return false;
      break;
    case HYPEROS: // Prime _HYPER one shot {{{2
      if (record->event.pressed) {
        if (IS_LAYER_ON(_HYPER)) {
          layer_off(_HYPER);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(hyper_off_song);
          #endif
        } else {
          layer_on(_HYPER);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(hyper_on_song);
          #endif
        }
      }
      return false;
  } // }}}2 end keypress/keyrelease

  // Only for pressed. {{{2
  if (record->event.pressed) {
    switch (keycode) {
      // Macros
      case VIMSAVE: // <esc>:w<cr>
        SEND_STRING(SS_TAP(X_ESCAPE)":w"SS_TAP(X_ENTER)"");
        return false;
      default:     // Hyper One-shot Layer: add modifiers and go back to default layer (One-shot) 
        if (IS_LAYER_ON(_HYPER)) {
          // turn off hyper layer
          layer_off(_HYPER);

          // add hyper modifiers
          register_code(KC_LGUI);
          register_code(KC_LALT);
          register_code(KC_LCTL);
          register_code(KC_LSFT);

          // tap the pressed key
          register_code(keycode);
          unregister_code(keycode);

          // then release hyper modifiers
          unregister_code(KC_LGUI);
          unregister_code(KC_LALT);
          unregister_code(KC_LCTL);
          unregister_code(KC_LSFT);
        
          // done processing
          return false;
        }
    } // end pressed switch
  } // end pressed
  return true;
}
// }}}1

/* vim: set fdm=marker: */
