#include "lets_split.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _L1 1
#define _L2 2
#define _L3 3
#define _L4 4
#define _L5 5

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  L1,
  L2,
  L3,
  L4,
  L5
};

// Fillers to make layering more clear
#define ______ KC_TRNS
#define XXXXXX KC_NO

#define L2_SPC LT(_L2, KC_SPC)
#define L3_SPC LT(_L3, KC_SPC)
#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define HYPER LCTL(LSFT(LALT(KC_LGUI)))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
  ,-----------------------------------------------------------------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  KP7   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | CT/EC  |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |  KP9   |  KP8   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   ,    |   .    |   /    |  Shift |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | HYPER  |        |  Ctrl  |  LALT  |  LGUI  | L2_SPC | L3_SPC |   L4   |  Left  |  Down  |   Up   |  Right |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_P7  ,\
    CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_P9  , KC_P8  ,\
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,\
    HYPER  , XXXXXX , KC_LCTL, KC_LALT, KC_LGUI, L2_SPC , L3_SPC , MO(_L4), KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT \
),

/* Layer 1 - STANDARD
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |        |        |        |  BSPC  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |   ;    |  ENT   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_L1] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_BSPC,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_SCLN, KC_ENT ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
),

/* Layer 2 - Left parens
  ,-----------------------------------------------------------------------------------------------------------.
  |   `    |    1   |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   ~    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |   <    |   {    |   (    |   [    |   *    |   $    |   =    |   &    |   %    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   ~    |   `    |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |  ENT   |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_L2] = KEYMAP( \
    KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_TILD,\
    ______ , ______ , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, ______ ,\
    ______ , KC_TILD, KC_GRV , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT , ______ , ______ , ______ , ______ , ______  \
),

/* Layer 3 - Right parens
  ,-----------------------------------------------------------------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   !    |   @    |   #    |   ^    |   +    |   ]    |   )    |   }    |   >    |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   ~    |   `    |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_L3] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    ______ , KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS, KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, ______ , ______ ,\
    ______ , KC_TILD, KC_GRV , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC, ______ , ______ , ______ , ______ , ______ , ______  \
),

/* Layer 4
  ,-----------------------------------------------------------------------------------------------------------.
  |        |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |  F14   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  MUTE  |  V DN  |  V UP  |        |        |   L5   |        |        |        |        |        |  F13   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |  F12   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |  F15   |  F16   |  F17   |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_L4] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_UP  , ______ , ______ , KC_F14 ,\
    KC_MUTE, KC_VOLD, KC_VOLU, ______ , _______, TG(_L5), ______ , KC_LEFT, KC_DOWN, KC_RGHT, ______ , KC_F13 ,\
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_F15 , KC_F16 , KC_F17  \
),

/* Layer 5 Game layer
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   SPC  |   L2   |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_L5] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_SPC , MO(_L2), ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
),

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
float tone_dvorak[][2]     = SONG(DVORAK_SOUND);
float tone_colemak[][2]    = SONG(COLEMAK_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_colemak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_COLEMAK);
      }
      return false;
      break;
    case DVORAK:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_dvorak, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_DVORAK);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
    case L1:
      if (record->event.pressed) {
        layer_on(_L1);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_L1);
        //update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
*/
