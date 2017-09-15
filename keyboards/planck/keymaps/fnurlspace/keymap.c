/* Copyright 2015-2017 Jack Humbert {{{1
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 * }}}1 */

// includes {{{1
#include "planck.h"
#include "action_layer.h"

extern keymap_config_t keymap_config;
// }}}1

// mac
#define CHECK_BIT(var,pos) ((var) & (1<<(pos)))

// Layers {{{1

enum planck_layers {
  _QWERTY,
  _PLEFT,
  _PRIGHT,
  _FN,
  _NAV,
  _NUM,
  _GAME,
  _ADJUST
};  // }}}1

// planck keycodes, used in process_record_user() {{{1
enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  PLEFT,
  PRIGHT,
  FN,
  NAV,
  NUM,
  GAME
};

// Tap Dance {{{1
enum {
    TD_GUI_LAUNCHBAR = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
    // tap LGUI twice for LGUI+SPC
    [TD_GUI_LAUNCHBAR] = ACTION_TAP_DANCE_DOUBLE(KC_LGUI, LGUI(KC_SPC))
};
// }}}1

// Aliases to use in keymaps {{{1

// Fillers to make layering more clear
#define ______   KC_TRNS
#define XXXXXX   KC_NO

// Layer modifiers and toggles
#define FN_MOD   MO(_FN)
#define NAV_MOD  MO(_NAV)
#define NUM_MOD  MO(_NUM)

// Dual-role keys: LT = layer when held, keycode when tapped
#define PL_SPC   LT(_PLEFT, KC_SPC)
#define PR_SPC   LT(_PRIGHT, KC_SPC)

// Dual-role keys: MT = modifier when held, keycode when tapped
#define CTL_ESC  MT(MOD_LCTL, KC_ESC)

// Modifier combos
#define Z_IN  LGUI(KC_EQL)
#define Z_OUT LGUI(KC_MINS)
#define HYPER LCTL(LSFT(LALT(KC_LGUI)))

// Tap dances
#define TD_LB TD(TD_GUI_LAUNCHBAR)
// }}}1

// keymap layers {{{1
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  KP7   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | CT/EC  |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |  KP9   |  KP8   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   ,    |   .    |   /    |  Shift |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  | HYPER  |  LCTRL |  LALT  |  LGUI  |   FN   | PL_SPC | PR_SPC |  NAV   |  RGUI  |  RALT  |  RCTRL | HYPER  |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_QWERTY] = KEYMAP( \
    KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_P7  ,\
    CTL_ESC, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_P9  , KC_P8  ,\
    KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,\
    HYPER  , KC_LCTL, KC_LALT, TD_LB  , FN     , PL_SPC , PR_SPC , NAV    , KC_RGUI, KC_RALT, KC_RCTL, HYPER   \
),
// }}}2

/* Paren Left Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   ~    |    1   |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    | CMD-+  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   `    |        |   <    |   {    |   (    |   [    |   *    |   $    |   =    |   &    |   %    | CMD--  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   ~    |   `    |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |  ENT   |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_PLEFT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , Z_IN   ,\
    KC_GRV , ______ , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC, KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, Z_OUT  ,\
    ______ , ______ , ______ , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , KC_ENT , ______ , ______ , ______ , ______ , ______  \
),
// }}}2

/* Paren Right Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    | CMD-+  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   `    |   !    |   @    |   #    |   ^    |   +    |   ]    |   )    |   }    |   >    |        | CMD--  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |   ~    |   `    |   _    |   -    |   :    |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
 */
[_PRIGHT] = KEYMAP( \
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , Z_IN   ,\
    KC_GRV , KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS, KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, ______ , Z_OUT  ,\
    ______ , ______ , ______ , KC_UNDS, KC_MINS, KC_COLN, KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC, ______ , ______ , ______ , ______ , ______ , ______  \
),
// }}}2

/* FN Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |   F1   |   F2   |   F3   |   F4   |   F5   |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        |  GAME  |        |        |        |        |        |  F12   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |  PREV  |  PLAY  |  NEXT  |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_FN] = KEYMAP( \
    ______ , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
    ______ , KC_MUTE, KC_VOLD, KC_VOLU, ______ , GAME   , ______ , ______ , ______ , ______ , ______ , KC_F12 ,\
    ______ , KC_MRWD, KC_MPLY, KC_MFFD, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ \
),
// }}}2

/* Navigation layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |  HOME  |   UP   |  END   |  PGUP  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |  LEFT  |  DOWN  |  RIGHT |  PGDN  |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_NAV] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_HOME, KC_UP  , KC_END , KC_PGUP,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
),
// }}}2

/* Numeric Layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |   1    |   2    |   3    |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   4    |   5    |   6    |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |   7    |   8    |   9    |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_NUM] = KEYMAP( \
    KC_1   , KC_2   , KC_3   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_4   , KC_5   , KC_6   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_7   , KC_8   , KC_9   , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
),
// }}}2

/* Game layer {{{2
  ,-----------------------------------------------------------------------------------------------------------.
  |        |        |        |        |        |        |        |        |        |        |        |  ESC   |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  CTRL  |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |  SPC   |  NUM   |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
*/
[_GAME] = KEYMAP( \
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , KC_ESC ,\
    KC_LCTL, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
    KC_SPC , NUM_MOD, ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______  \
),
// }}}2


/* Adjust (FN + NAV)
  ,-----------------------------------------------------------------------------------------------------------.
  |        | Reset  |        |        |        |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|--------|
  |        |        | MusMode| Aud on | Audoff |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------|--------+--------+--------+--------+--------+--------|
  |        | Voice- | Voice+ | Mus on | Musoff |        |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        |        |        |        |        |        |        |
  `-----------------------------------------------------------------------------------------------------------'
  AG_NORM = Mac Mods
  AG_SWAP = Win Mods
 */
[_ADJUST] = KEYMAP( \
  ______ , RESET  , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
  ______ , ______ , MU_MOD , AU_ON  , AU_OFF , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
  ______ , MUV_DE , MUV_IN , MU_ON  , MU_OFF , ______ , ______ , ______ , ______ , ______ , ______ , ______ ,\
  ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ , ______ \
),

};
// }}}1

// audio and other stuff {{{1
#ifdef AUDIO_ENABLE
  float plover_song[][2]     = SONG(PLOVER_SOUND);
  float plover_gb_song[][2]  = SONG(PLOVER_GOODBYE_SOUND);
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FN:
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_FN, _NAV, _ADJUST);
      } else {
        layer_off(_FN);
        update_tri_layer(_FN, _NAV, _ADJUST);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        layer_on(_NAV);
        update_tri_layer(_FN, _NAV, _ADJUST);
      } else {
        layer_off(_NAV);
        update_tri_layer(_FN, _NAV, _ADJUST);
      }
      return false;
      break;
    /*
    case BACKLIT:
      if (record->event.pressed) {
        register_code(KC_RSFT);
        #ifdef BACKLIGHT_ENABLE
          backlight_step();
        #endif
      } else {
        unregister_code(KC_RSFT);
      }
      return false;
      break;
    */
    case GAME:
      if (record->event.pressed) {
        layer_off(_FN);
        layer_off(_NAV);
        layer_off(_ADJUST);
        if (CHECK_BIT(layer_state, _GAME)) {
            layer_off(_GAME);
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_gb_song);
            #endif
        } else {
            layer_on(_GAME);
            #ifdef AUDIO_ENABLE
                stop_all_notes();
                PLAY_SONG(plover_song);
            #endif
        }
        /*
        if (!eeconfig_is_enabled()) {
            eeconfig_init();
        }
        keymap_config.raw = eeconfig_read_keymap();
        keymap_config.nkro = 1;
        eeconfig_update_keymap(keymap_config.raw);
        */
      }
      return false;
      break;
  }
  return true;
}

// }}}1

/* vim: set fdm=marker: */
