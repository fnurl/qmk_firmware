/* Jody Foo 2017 */

/* Features:
 *
 * TODO: Tap stuff does not seem to be loaded e.g.
 *
 * - TAP_TERM
 * - Tap dance
 * - TT
 * - PERMISSIVE_HOLD
 *
 */

// Boilerplate and pre-setup {{{1

#include "lets_split.h"
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
  NONE
};

// Aliases to use in keymaps {{{2
// Fillers to make layering more clear {{{3
//#define XXXXXX   KC_NO
#define XXXXXX   NONE
#define ______   KC_TRNS

// Layer modifiers {{{3
#define NUM_MOD MO(_NUM)

// One-shot layers
#define OSHYPER OSL(_HYPER)

// Dual-role keys: LT = layer when held, keycode when tapped {{{3
#define PL_SPC   LT(_PLEFT,  KC_SPC)
#define PR_SPC   LT(_PRIGHT, KC_SPC)

// Dual-role keys: TT = activate layer when held, double tap toggles (uses TAPPING_TOGGLE) {{{3
#define TT_NAV TT(_NAV)


// Dual-role keys: MT = modifier when held, keycode when tapped {{{3
#define ESC_CTL MT(MOD_LCTL, KC_ESC)
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

// Layer keys {{{3
#define ADJUST MO(_ADJUST)

// }}}1

// Keymap Layers {{{1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Base layer: US-ANSI with ÅÄÖ (KC_P7--KC_P9) {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    :   Y    |   U    |   I    |   O    |   P    |   Å    |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  | CT/EC  |   A    |   S    |   D    |   F    |   G    :   H    |   J    |   K    |   L    |   Ö    |   Ä    |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    :   N    |   M    |   ,    |   .    |   /    | Shift  |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |  FN    |  LALT  | HYPER  | PL_SPC : PR_SPC |TT NAV  |        |        |        | ADJUST |
  `----------------------------------------------------- -----------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_P7  ,\
    ESC_CTL, KC_A   , S_SHIFT, D_OPT  , F_CTL  , G_CMD  , H_CMD  , J_CTL  , K_OPT  , L_SHIFT, KC_P9  , KC_P8  ,\
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,\
    KC_DEL , XXXXXX , FN     , KC_LALT, KC_HYPR, PL_SPC , PR_SPC , TT_NAV , XXXXXX , XXXXXX , XXXXXX , ADJUST  \
),

/* HYPER layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |        | HYPER Q| HYPER W| HYPER E| HYPER R| HYPER T: HYPER Y| HYPER U| HYPER I| HYPER O| HYPER P|        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |HYPR ESC| HYPER A| HYPER S| HYPER D| HYPER F| HYPER G: HYPER H| HYPER J| HYPER K| HYPER L|        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        | HYPER Z| HYPER X| HYPER C| HYPER V| HYPER B: HYPER N| HYPER M| HYPER ,| HYPER .| HYPER /|        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        :        |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
*/
[_HYPER] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , HYPEROS,\
    KC_ESC , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , HYPEROS, HYPEROS,\
    HYPEROS, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , HYPEROS,\
    HYPEROS, HYPEROS, HYPEROS, HYPEROS, HYPEROS, ______ , ______ , HYPEROS, HYPEROS, HYPEROS, HYPEROS, HYPEROS \
),

/* Paren Left Layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |   ~    |    1   |   2    |   3    |   4    |   5    :   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |  CTRL  |        |   <    |   {    |   (    |   [    :   *    |   $    |   =    |   &    |   %    |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    :   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        : DB/ENT |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
*/
[_PLEFT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    KC_LCTL, XXXXXX , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, XXXXXX ,\
    ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT , ______ , ______ , ______ , ______ , ______  \
),

/* Paren Right Layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    :   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |  CTRL  |   !    |   @    |   #    |   ^    |   +    :   ]    |   )    |   }    |   >    |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    :   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  :        |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
 */
[_PRIGHT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    KC_LCTL, KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS, KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, XXXXXX , XXXXXX ,\
    ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC, ______ , ______ , ______ , ______ , ______ , ______  \
),

/* FN Layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |        |   F1   |   F2   |   F3   |   F4   |   F5   :   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        |  GAME  :        |        |        |        |        |  F12   |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |  PREV  |  PLAY  |  NEXT  |        |        :        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        :        | NAV    |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
*/
[_FN] = KEYMAP( \
    XXXXXX , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
    KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , GAME   , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , KC_F12 ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , ______ , ______ , ______ , XXXXXX , XXXXXX , NAV    , ______ , ______ , ______ , ______  \
),


/* Navigation layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |        |        |        |        |        |        :        |PREV TAB|   UP   |NEXT TAB|  PgUp  |zIN<C-+>|
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        |        :        |  LEFT  |  DOWN  | RIGHT  |  PgDn  |zOU<C-->|
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |  PREV  |  PLAY  |  NEXT  |        |        :        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |  FN    |        |        |        :        |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
 */
[_NAV] = KEYMAP( \
    XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , PRV_TAB, KC_UP  , NXT_TAB, KC_PGUP, Z_IN   ,\
    KC_LCTL, KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , XXXXXX , XXXXXX , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, Z_OUT  ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
    ______ , ______ , FN     , ______ , ______ , XXXXXX , XXXXXX , ______ , ______ , ______ , ______ , ______  \
),

/* Game layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |        |        |        |        |        |        :        |        |  W     |        |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |  CTRL  |        |        |        |        |        :  CTRL  |  A     |  S     |  D     |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        :        |        |        |        |        | ENTER  |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |  SPC   |  NUM   |        |        |        |        :  SPC   |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
*/
[_GAME] = KEYMAP( \
    ______ , ______ , KC_I   , ______ , ______ , ______ , ______ , ______ , KC_W   , ______ , ______ , ______ ,\
    KC_H   , KC_J   , KC_K   , KC_L   , ______ , ______ , KC_LCTL, KC_A   , KC_S   , KC_D   , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT ,\
    ______ , ______ , ______ , ______ , ______ , ______ , KC_SPC , NUM_MOD, ______ , ______ , ______ , ______  \
),

/* Numeric Layer {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |   0    |   1    |   2    |   3    |        |        :   0    |   1    |   2    |   3    |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |  ESC   |   4    |   5    |   6    |        |        :  ESC   |   4    |   5    |   6    |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |   0    |   7    |   8    |   9    |        |        :   0    |   7    |   8    |   9    |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        :        |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
*/
[_NUM] = KEYMAP( \
    KC_0   , KC_1   , KC_2   , KC_3   , XXXXXX , XXXXXX , KC_0   , KC_1   , KC_2   , KC_3   , XXXXXX , XXXXXX ,\
    KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX , KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX ,\
    KC_0   , KC_7   , KC_8   , KC_9   , XXXXXX , XXXXXX , KC_0   , KC_7   , KC_8   , KC_9   , XXXXXX , XXXXXX ,\
    ______ , ______ , ______ , ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  \
),

/* Planck Layer (FN + NAV) {{{2
  ,----------------------------------------------------- -----------------------------------------------------.
  |        | Reset  |        |        |        |        :        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------|--------|
  |        |AudioOn |Music On| Voice+ |MusicMod|        :        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |AudioOff|MusicOff| Voice- |        |        :        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+-------- --------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        :        |        |        |        |        |        |
  `----------------------------------------------------- -----------------------------------------------------'
 */
[_ADJUST] = KEYMAP( \
  XXXXXX , RESET  , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
  ______ , ______ , ______ , ______ , FN     , ______ , ______ , NAV    , ______ , ______ , ______ , ______  \
),

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
        } else {
          layer_on(_GAME);
        }
      }
      return false;
      break;
    case NAVLOCK:  // Toggle _NAV layer {{2
      if (record->event.pressed) {
        if (IS_LAYER_ON(_NAV)) {
          layer_off(_NAV);
        } else {
          layer_on(_NAV);
        }
      }
      return false;
      break;
    case HYPEROS: // Prime _HYPER one shot {{{2
      if (record->event.pressed) {
        if (IS_LAYER_ON(_HYPER)) {
          layer_off(_HYPER);
        } else {
          layer_on(_HYPER);
        }
      }
      return false;
  } // }}}2 end keypress/keyrelease

  // Hyper Layer: add modifiers and go back to default layer {{{2
  if (record->event.pressed) {
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
  }

  return true;
}
// }}}1

/* vim: set fdm=marker: */

