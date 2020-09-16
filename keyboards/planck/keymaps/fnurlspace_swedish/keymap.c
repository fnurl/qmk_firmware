/* 
 * The fnurlspace40_se keymap for 40% (4x12, 48 key) (ortholinear) keyboards
 * Uses swedish keymap to be compatible with ordinary swedish keyboard layout
 * setting.
 *
 * Jody Foo 2017, 2018, 2020
 * last modified: 2020-09-16
 */

/* Keymap Features:
 * - Compatibility with Planck and Lets Split and prepared for adding
 *   additional keyboard hardware
 * - Swedish KB layout based on std ANSI-US (standard Swedish os layout)
 * - Fallback ANSI layer
 * - Parenthesis/Symbol layer (lef/right symetric parenthesis)
 * - Function key layer
 * - Keyboard hardware layer (DFU mode, Planck music mode etc)
 * - Navigational layer (using GUI modifier)
 * - Fallback navigation layer (using CTRL as modifier)
 *     - to enable fallback, double tap dance key in lower left corner
 * - Left handed gaming mode
 */

// Boilerplate and pre-setup {{{1

// includes {{{2
#include QMK_KEYBOARD_H

// Swedish keymap aliases, using SE_ prefix instead of KC_
//#include "keymap_swedish.h"

// Uncomment if config for the Planck
#include "action_layer.h"
#include "muse.h"

extern keymap_config_t keymap_config;

// Swedish keyboard mappings for *Mac*, except for 0-9 and a-z {{{2

// Neutral Row 1 {{{3
#define SE_LABK      KC_GRV  // <
#define SE_PLUS      KC_MINS // +
#define SE_ACUT_DEAD KC_EQL  // ´ (dead)

// Neutral Row 2 {{{3
#define SE_ARNG      KC_LBRC // å
#define SE_DIAE_DEAD KC_RBRC // ¨ (dead)
#define SE_QUOT      KC_BSLS // '

// Neutral Row 3 {{{3
#define SE_ODIA KC_SCLN // ö
#define SE_ADIA KC_QUOT // ä

// Neutral Row 4 {{{3
#define SE_COMM KC_COMM // ,
#define SE_DOT  KC_DOT  // .
#define SE_MINS KC_SLSH // /

// Shifted Row 1 {{{3
#define SE_RABK     LSFT(SE_LABK)      // >
#define SE_EXLM     LSFT(KC_1)         // !
#define SE_DQUO     LSFT(KC_2)         // "
#define SE_HASH     LSFT(KC_3)         // #
#define SE_EURO     LSFT(KC_4)         // €
#define SE_PERC     LSFT(KC_5)         // %
#define SE_AMPR     LSFT(KC_6)         // &
#define SE_SLSH     LSFT(KC_7)         // /
#define SE_LPRN     LSFT(KC_8)         // (
#define SE_RPRN     LSFT(KC_9)         // )
#define SE_EQL      LSFT(KC_0)         // =
#define SE_QUES     LSFT(SE_PLUS)      // ?
#define SE_GRV_DEAD LSFT(SE_ACUT_DEAD) // ` (dead)

// Shifted Row 2 {{{3
#define SE_CIRC_DEAD LSFT(SE_DIAE_DEAD) // ^ (dead)
#define SE_ASTR      LSFT(SE_QUOT)      // *

// Shifted Row 4 {{{3
#define SE_SCLN LSFT(SE_COMM) // ;
#define SE_COLN LSFT(SE_DOT)  // :
#define SE_UNDS LSFT(SE_MINS) // _

// Alt (Opt) Row 1 (excluding non-ANSI glyphs) {{{3
#define SE_AT   LALT(KC_1)         // @
#define SE_DLR  LALT(KC_4)         // $
#define SE_PIPE LALT(KC_7)         // |
#define SE_LBRC LALT(KC_8)         // [
#define SE_RBRC LALT(KC_9)         // ]
#define SE_ACUT LALT(SE_ACUT_DEAD) // ´ (not dead)

// AltGr (Opt) Row 2 (excluding non-ANSI glyphs) {{{3
#define SE_TILD LALT(SE_DIAE_DEAD) // ~ (dead)

// Shift + AltGr (Opt) Row 1 (excluding non-ANSI glyphs) {{{3
#define SE_BSLS LSFT(SE_PIPE) // backslash char
#define SE_LCBR LSFT(SE_LBRC) // {
#define SE_RCBR LSFT(SE_RBRC) // }
#define SE_GRV  LSFT(SE_ACUT) // `

// Shift + AltGr (Opt) Row 2 (excluding non-ANSI glyphs) {{{3
#define SE_CIRC LSFT(SE_TILD) // ^


// Enumerate layers {{{2
enum fnurlspace_layers {
  _QWERTY_SE,       // QWERTY. Swedish with ANSI slash (by @fnurl)
  _PLEFT_SE,        // Parens & symbols, left
  _PRIGHT_SE,       // Parens & symbols, right 
  _QWERTY_ANSI,     // QWERTY. ANSI, standard US variant
  _PLEFT_ANSI,        // Parens & symbols, left
  _PRIGHT_ANSI,       // Parens & symbols, right 
  _FN,              // F-keys (F1 through F12)
  _HYPER_MEH,       // Hyper/Meh (Shift+CTRL+ALT+GUI / Shift+CTRL+ALT) key compatability layer
  _USE_CTRL,        // used as a state indicator
  _NAV,             // Navigation keys using GUI (arrows, pgup/pgdown, media keys, key combos)
  _NAVCTRL,         // Navigation keys using CTRL (arrows, pgup/pgdown, media keys, key combos)
  _GAME1,           // Left split game mode (left thumb is SPACE)
  //_GAME2,           // Right split game mode (map WASD to right split)
  _NUM1,            // Number keys for Left split game mode
  //_NUM2,            // Number keys for Right split game mode
  _PLANCK,          // Hardware commands (general) + Planck specific functionality
  //_ADJUST           // Hardware commands (general)
};


// Cross Keyboard Compatibility {{{2
//
// Uncomment if config for the Lets Split
//#define _HWDLAYER        _ADJUST
//#define KB_LAYOUT_LAYER  LAYOUT_ortho_4x12 

// Uncomment if config for the Planck
#define _HWDLAYER        _PLANCK 
#define KB_LAYOUT_LAYER  LAYOUT_planck_grid

// Custom keycodes, used in process_record_user() {{{2
// QWERTY = SAFE_RANGE adds all the standard keys first to the enumeration.
enum custom_keycodes {
  QWERTY = SAFE_RANGE,   // Default ANSI key codes
  ANSIUS,                // Key for enabling _QWERTY_ANSIUS layer
  FN,                    // Key for enabling _FN layer
  NAV,                   // Key for enabling _NAV layer
  NAVCTRL,               // Key for enabling _NAVCTRL (CTRL based navigation layer)
  GAME1,                 // Key for toggeling _GAME1 layer on/off
  //GAME2,                 // Key for toggeling _GAME2 layer on/off
  VIMSAVE,               // Key for expanding macro for saving in Vim.
  NONE                   // NOOP key for readability.
};
 

// Tap Dance aliases and IDs {{{2
enum tap_dances {
    //TD_RSHIFT_CAPS,
    //TD_RSHIFT_BTN1,
    //TD_HYPER,
    //TD_HYPER_ONESHOT,
    TD_CMD_HYPER,
    TD_ALT_MEH,
    TD_CTRL_NAVCTRL,
    TD_CTRL_USECTRL
};

// Tap dance aliases (use in layout) {{{3
//#define TDRSCAP  TD(TD_RSHIFT_CAPS)
//#define TDRSBT1  TD(TD_RSHIFT_BTN1)
//#define TDHYPER  TD(TD_HYPER)
//#define TDHYPOS  TD(TD_HYPER_ONESHOT)
//#define TDHYPME  TD(TD_HYPER_MEH)
#define TDCMDHY  TD(TD_CMD_HYPER)
#define TDALTME  TD(TD_ALT_MEH)
#define TDCNAVC  TD(TD_CTRL_NAVCTRL)
#define TDCUSEC  TD(TD_CTRL_USECTRL)


// Aliases to use in keymaps {{{2

// Fillers to make layering more clear {{{3
#define XXXXXX   NONE
#define ______   KC_TRNS

// Layer modifiers {{{3
#define NUM1MOD  MO(_NUM1)
//#define NUM2MOD  MO(_NUM2)

// Dual-role layer keys: LT = layer when held, keycode when tapped {{{3
#define PL_SPCSE LT(_PLEFT_SE,  KC_SPC)
#define PR_SPCSE LT(_PRIGHT_SE, KC_SPC)
#define PL_SPC   LT(_PLEFT_ANSI,  KC_SPC)
#define PR_SPC   LT(_PRIGHT_ANSI, KC_SPC)

// Dual-role modiliers: MT = modifier when held, keycode when tapped {{{3
// bad idea using character keys as dual role keys. hard to type.
#define ESC_CTL  MT(MOD_LCTL, KC_ESC)

// GUI/CTRL modifier combos {{{3
// TODO: additional for ANSI plus/minus and left/right braces?
#define Z_ING    LGUI(SE_PLUS)
#define Z_OUTG   LGUI(SE_MINS)
#define Z_INC    LCTL(SE_PLUS)
#define Z_OUTC   LCTL(SE_MINS)

#define CMDLBRC  LGUI(SE_LBRC)
#define CMDRBRC  LGUI(SE_RBRC)

#define CMDLARR  LGUI(KC_LEFT)
#define CMDRARR  LGUI(KC_RGHT)
#define CMDPGDN  LGUI(KC_PGDN)
#define CMDPGUP  LGUI(KC_PGUP)
#define CTLLARR  LCTL(KC_LEFT)
#define CTLRARR  LCTL(KC_RGHT)
#define CTLPGDN  LCTL(KC_PGDN)
#define CTLPGUP  LCTL(KC_PGUP)

// GUI/CTRL + Alt
#define PRVTABG  LGUI(LALT(KC_LEFT))
#define NXTTABG  LGUI(LALT(KC_RGHT))
#define PRVTABC  LCTL(LALT(KC_LEFT))
#define NXTTABC  LCTL(LALT(KC_RGHT))
// }}}1


// Keymap Layers {{{1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* _QWERTY_SE: Base layer. Swedish layout with ANSI slash {{{2
   Based on standard Swedish keyboard layout with åäö. 
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    | |   Y    |   U    |   I    |   O    |   P    |   Å    |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  |CTRL/ESC|   A    |   S    |   D    |   F    |   G    | |   H    |   J    |   K    |   L    |   Ö    |   Ä    |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    | |   N    |   M    |   ,    |   .    |   /    | Shift  |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  |TD:CUSEC|  ESC   |  FN    |TD:ALTME|TD:CMDHY| PL/SPC | | PR/SPC |  NAV   |  CMD   |  ALT   | BCKSPC | ENTER  |
  `-----------------------------------------------------+ +-----------------------------------------------------'
  NOTE: Right half, bottom row, second key from the right is broken on my Lets Split (i.e. BCKSPC above).
*/
[_QWERTY_SE] = KB_LAYOUT_LAYER(
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    ,  KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , SE_ARNG,\
   ESC_CTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G    ,  KC_H    , KC_J   , KC_K   , KC_L   , SE_ODIA, SE_ADIA,\
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B    ,  KC_N    , KC_M   , KC_COMM, KC_DOT , SE_SLSH, KC_RSFT,\
   TDCUSEC, KC_ESC , FN     , TDALTME, TDCMDHY, PL_SPCSE,  PR_SPCSE, NAV    , KC_RGUI, KC_RALT, KC_BSPC, KC_ENT  \
),

/* _PLEFT_SE: Paren Left Layer, Swedish {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   ~    |    1   |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |   <    |   {    |   (    |   [    | |   *    |   $    |   =    |   &    |   %    |   ?    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    | |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | | DB/ENT |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_PLEFT_SE] = KB_LAYOUT_LAYER(
   SE_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , SE_GRV ,\
   ______ , XXXXXX , SE_LABK, SE_LCBR, SE_LPRN, SE_LBRC ,  SE_ASTR, SE_DLR , SE_EQL , SE_AMPR, SE_PERC, SE_QUES,\
   ______ , XXXXXX , XXXXXX , SE_UNDS, SE_MINS, SE_COLN ,  SE_SCLN, SE_DQUO, SE_QUOT, SE_PIPE, SE_BSLS, ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  KC_ENT , ______ , ______ , ______ , XXXXXX , XXXXXX  \
),

/* _PRIGHT_SE: Paren Right Layer, Swedish {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |   !    |   @    |   #    |   ^    |   +    | |   ]    |   )    |   }    |   >    |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    | |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_PRIGHT_SE] = KB_LAYOUT_LAYER(
    SE_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , SE_GRV ,\
    ______ , SE_EXLM, SE_AT  , SE_HASH, SE_CIRC, SE_PLUS ,  SE_RBRC, SE_RPRN, SE_RCBR, SE_RABK, XXXXXX , XXXXXX ,\
    ______ , XXXXXX , XXXXXX , SE_UNDS, SE_MINS, SE_COLN ,  SE_SCLN, SE_DQUO, SE_QUOT, SE_PIPE, SE_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC ,  ______ , ______ , ______ , ______ , XXXXXX , XXXXXX  \
),

/* _QWERTY_ANSI: Base layer. ANSI-US (standard ANSI US) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |  Tab   |   Q    |   W    |   E    |   R    |   T    | |   Y    |   U    |   I    |   O    |   P    |   [    |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  |CTRL/ESC|   A    |   S    |   D    |   F    |   G    | |   H    |   J    |   K    |   L    |   ;    |   '    |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  | Shift  |   Z    |   X    |   C    |   V    |   B    | |   N    |   M    |   ,    |   .    |   /    | Shift  |
  |--------+--------+--------+--------+--------+--------| |--------+--------+--------+--------+--------+--------|
  |TD:CNAVC|  ESC   |  FN    |TD:ALTME|TD:CMDHY| PL/SPC | | PR/SPC |  NAV   |  CMD   |  ALT   | BCKSPC | ENTER  |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_QWERTY_ANSI] = KB_LAYOUT_LAYER(
   KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T    ,  KC_Y    , KC_U   , KC_I   , KC_O   , KC_P   , KC_LBRC,\
   ESC_CTL, KC_A   , KC_S   , KC_D   , KC_F   , KC_G    ,  KC_H    , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT,\
   KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B    ,  KC_N    , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT,\
   TDCUSEC, KC_ESC , FN     , TDALTME, TDCMDHY, PL_SPC  ,  PR_SPC  , NAV    , KC_RGUI, KC_RALT, KC_BSPC, KC_ENT  \
),

/* _PLEFT_ANSI: Paren Left Layer ANSI {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   ~    |    1   |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |   <    |   {    |   (    |   [    | |   *    |   $    |   =    |   &    |   %    |D acute |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    | |   ;    |   "    |   '    |   |    |   \    |D umlaut|
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | | DB/ENT |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_PLEFT_ANSI] = KB_LAYOUT_LAYER(
   KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
   ______ , XXXXXX , KC_LABK, KC_LCBR, KC_LPRN, KC_LBRC ,  KC_ASTR, KC_DLR , KC_EQL , KC_AMPR, KC_PERC, XXXXXX ,\
   ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN ,  KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  KC_ENT , ______ , ______ , ______ , XXXXXX , XXXXXX  \
),

/* _PRIGHT_ANSI: Paren Right Layer, ANSI {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   ~    |   1    |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |   `    |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |   !    |   @    |   #    |   ^    |   +    | |   ]    |   )    |   }    |   >    |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |   _    |   -    |   :    | |   ;    |   "    |   '    |   |    |   \    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |  BSPC  | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_PRIGHT_ANSI] = KB_LAYOUT_LAYER(
    KC_TILD, KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_GRV ,\
    ______ , KC_EXLM, KC_AT  , KC_HASH, KC_CIRC, KC_PLUS ,  KC_RBRC, KC_RPRN, KC_RCBR, KC_RABK, XXXXXX , XXXXXX ,\
    ______ , XXXXXX , XXXXXX , KC_UNDS, KC_MINS, KC_COLN ,  KC_SCLN, KC_DQUO, KC_QUOT, KC_PIPE, KC_BSLS, ______ ,\
    ______ , ______ , ______ , ______ , ______ , KC_BSPC ,  ______ , ______ , ______ , ______ , XXXXXX , XXXXXX  \
),

/* _FN: FN Layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |   F1   |   F2   |   F3   |   F4   |   F5   | |   F6   |   F7   |   F8   |   F9   |  F10   |  F11   |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |  F12   |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        | KP ENT |  DEL   |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_FN] = KB_LAYOUT_LAYER(
   XXXXXX , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5   ,  KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 ,\
   ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , KC_F12 ,\
   ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ ,\
   ______ , XXXXXX , ______ , ______ , ______ , XXXXXX  ,  XXXXXX , ______ , ______ , ______ , KC_PENT, KC_DEL  \
),

/* _HYPER_MEH: HYPER MEH layer {{{2

  The _HYPER_MEH layer is used for HYPER (GUI+CTRL+ALT+SHIFT) modified keys (both
  momentary and One-Shot). The HYPER layer is needed in order for HYPER + ESC
  to work.
  
  When used for momentary keypresses, the layer is turned on and the HYPER
  modifier is registered (see tap dance related sections).
 
  One Shot is deprecated. 
  For One-Shot HYPER modifications, the _HYPER_MEH layer is enabled and left on to
  indicate One-Shot mode (see tap dances). Upon keypress, the HYPER modifier
  is added to the registered keypress and the _HYPER_MEH layer is deactivated (see
  general keypressed case further down).

  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_HYPER_MEH] = KB_LAYOUT_LAYER(
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______  \
),

/* _USE_CTRL: Use NAVCTRL layer status ... because I am not sure how to edit any other kind of state {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_USE_CTRL] = KB_LAYOUT_LAYER(
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______  \
),

/* _NAV: Navigation layer (Default: Using GUI for modified keys) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |        | CMDLARR| CMDRARR|        | |CMDPGUP |PREV TAB|   UP   |NEXT TAB|  PgUp  |Zoom In |
  |--------+--------+--------+--------+--------+--------+ +--------+ -------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        | GAME1  | |CMDPGDN |  LEFT  |  DOWN  | RIGHT  |  PgDn  |Zoom Out|
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |  PLAY  |  PREV  |  NEXT  |        | ANSIUS | |        |CMDLARR |        |CMDRARR |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |CMDLBRC | |CMDRBRC |        |        |        |        | BCKSPC |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_NAV] = KB_LAYOUT_LAYER(
   XXXXXX , XXXXXX , XXXXXX , CMDLARR, CMDRARR, XXXXXX  ,  CMDPGUP, PRVTABG, KC_UP  , NXTTABG, KC_PGUP, Z_ING  ,\
   ______ , KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , GAME1   ,  CMDPGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, Z_OUTG ,\
   ______ , KC_MPLY, KC_MRWD, KC_MFFD, XXXXXX , ANSIUS  ,  XXXXXX , CMDLARR, XXXXXX , CMDRARR, XXXXXX , ______ ,\
   XXXXXX , XXXXXX , ______ , ______ , ______ , CMDLBRC ,  CMDRBRC, ______ , ______ , ______ , XXXXXX , KC_BSPC \
),

/* _NAVCTRL: Navigation layer (Variant: Using CTRL instead of GUI for modified keys) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |        | CTLLARR| CTLRARR|        | |CTRLPGUP|PREV TAB|   UP   |NEXT TAB|  PgUp  |Zoom In |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |  MUTE  |  V DN  |  V UP  |        | GAME1  | |CTRLPGDN|  LEFT  |  DOWN  | RIGHT  |  PgDn  |Zoom Out|
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |  PLAY  |  PREV  |  NEXT  |        | ANSIUS | |        |CTLLARR |        |CTLRARR |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        | BCKSPC |
  `-----------------------------------------------------+ +-----------------------------------------------------'
 */
[_NAVCTRL] = KB_LAYOUT_LAYER(
   XXXXXX , XXXXXX , XXXXXX , CTLLARR, CTLRARR, XXXXXX  ,  CTLPGUP, PRVTABC, KC_UP  , NXTTABC, KC_PGUP, Z_INC  ,\
   ______ , KC_MUTE, KC_VOLD, KC_VOLU, XXXXXX , GAME1   ,  CTLPGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, Z_OUTC ,\
   ______ , KC_MPLY, KC_MRWD, KC_MFFD, XXXXXX , ANSIUS  ,  XXXXXX , CTLLARR, XXXXXX , CTLRARR, XXXXXX , ______ ,\
   ______ , XXXXXX , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , XXXXXX , KC_BSPC \
),

/* _GAME1: Game layer {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | L_CTRL |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | SPACE  |NUM1MOD |        |        |        |        | |        |        |        |        |        |  ENTER |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_GAME1] = KB_LAYOUT_LAYER(
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   KC_LCTL, ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______ ,\
   KC_SPC , NUM1MOD, ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , KC_ENT  \
),

/* _GAME2 (off): Game layer (left/right [wasd]/[ijkl] swapped) {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |        |        |  I     |        |        |        | |        |        |  W     |        |        | BCKSPC |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  H     |  J     |  K     |  L     |        |        | |  CTRL  |  A     |  S     |  D     |        | ENTER  |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  N     |        |        |        |        |        | |  Shift |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | PR/SPC |TD:NAVHY|        |        |        |        | |  SPC   | NUM2MOD|        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
/*[_GAME2] = KB_LAYOUT_LAYER(
   ______ , ______ , KC_I   , ______ , ______ , ______  ,  ______ , ______ , KC_W   , ______ , ______ , KC_BSPC,\
   KC_H   , KC_J   , KC_K   , KC_L   , ______ , ______  ,  KC_LCTL, KC_A   , KC_S   , KC_D   , ______ , KC_ENT ,\
   KC_N   , ______ , ______ , ______ , ______ , ______  ,  KC_LSFT, ______ , ______ , ______ , ______ , KC_UP  ,\
   PR_SPC , TDNVHYP, ______ , ______ , ______ , ______  ,  KC_SPC , NUM2MOD, ______ , KC_LEFT, KC_RGHT, KC_DOWN \
),*/

/* _NUM1: Numeric Layer 1 {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   `    |   1    |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  ESC   |   4    |   5    |   6    |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | ENTER  |   7    |   8    |   9    |   0    |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  | BCKSPC |        |   0    |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
[_NUM1] = KB_LAYOUT_LAYER(
   KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXX ,\
   KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
   KC_ENT , KC_7   , KC_8   , KC_9   , KC_0   , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
   KC_BSPC, ______ , KC_0   , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______  \
),

/* _NUM2 (off): Numeric Layer 2 {{{2
  ,-----------------------------------------------------+ +-----------------------------------------------------.
  |   0    |   1    |   2    |   3    |   4    |   5    | |   6    |   7    |   8    |   9    |   0    |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |  ESC   |   4    |   5    |   6    |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |   7    |   8    |   9    |        |        | |        |        |        |        |        |        |
  |--------+--------+--------+--------+--------+--------+ +--------+--------+--------+--------+--------+--------|
  |        |        |        |        |        |        | |        |        |        |        |        |        |
  `-----------------------------------------------------+ +-----------------------------------------------------'
*/
/*[_NUM2] = KB_LAYOUT_LAYER(
   KC_0   , KC_1   , KC_2   , KC_3   , KC_4   , KC_5    ,  KC_0   , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,\
   KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX  ,  KC_ESC , KC_4   , KC_5   , KC_6   , XXXXXX , XXXXXX ,\
   XXXXXX , KC_7   , KC_8   , KC_9   , XXXXXX , XXXXXX  ,  XXXXXX , KC_7   , KC_8   , KC_9   , XXXXXX , XXXXXX ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , NUM2MOD, ______ , ______ , ______ , ______  \
),
*/

/* _ADJUST (off): Adjust Layer (FN + NAV) (lets split) {{{2
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
/*
[_ADJUST] = KB_LAYOUT_LAYER(
   XXXXXX , RESET  , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
   XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
   XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX  ,  XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
   ______ , ______ , ______ , ______ , ______ , ______  ,  ______ , ______ , ______ , ______ , ______ , ______  \
),
*/

/* _PLANCK: Planck Layer (FN + NAV) (Planck) {{{2
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
[_PLANCK] = KB_LAYOUT_LAYER(
  XXXXXX , RESET  , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , AU_ON  , MU_ON  , MUV_IN , MU_MOD , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , AU_OFF , MU_OFF , MUV_DE , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX , XXXXXX ,\
  XXXXXX , XXXXXX , ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX , ______ , XXXXXX , XXXXXX , XXXXXX , XXXXXX  \
),

};
// }}}1

// Audio {{{1
// Notification sounds {{{2
#define HYPER_ON_SONG    M__NOTE(_G5, 4),
#define HYPER_OFF_SONG   M__NOTE(_G4, 4),
#define GAME1_ON_SONG    M__NOTE(_A4, 8), M__NOTE(_A5, 8),
#define GAME1_OFF_SONG   M__NOTE(_A5, 8), M__NOTE(_A4, 8),
#define CAPS_SONG        M__NOTE(_E5, 4),
#define MEH_ON_SONG      M__NOTE(_FS5, 4),
#define MEH_OFF_SONG     M__NOTE(_FS4, 4),
#define CMD_ON_SONG      M__NOTE(_F5, 4),
#define CMD_OFF_SONG     M__NOTE(_F4, 4),
#define ANSI_ON_SONG     M__NOTE(_E4, 8), M__NOTE(_E5, 8),
#define ANSI_OFF_SONG    M__NOTE(_E5, 8), M__NOTE(_E4, 8),
#define NAVCTRL_ON_SONG  M__NOTE(_D4, 8), M__NOTE(_D5, 8),
#define NAVCTRL_OFF_SONG M__NOTE(_D5, 8), M__NOTE(_D4, 8)

// Create song arrays {{{2
#ifdef AUDIO_ENABLE
  float hyper_on_song[][2]    = SONG(HYPER_ON_SONG);
  float hyper_off_song[][2]   = SONG(HYPER_OFF_SONG);
  float game_on_song[][2]     = SONG(GAME1_ON_SONG);
  float game_off_song[][2]    = SONG(GAME1_OFF_SONG);
  float caps_song[][2]        = SONG(CAPS_SONG);
  float meh_on_song[][2]      = SONG(MEH_ON_SONG);
  float meh_off_song[][2]     = SONG(MEH_OFF_SONG);
  float cmd_on_song[][2]      = SONG(CMD_ON_SONG);
  float cmd_off_song[][2]     = SONG(CMD_OFF_SONG);
  float navctrl_on_song[][2]  = SONG(NAVCTRL_ON_SONG);
  float navctrl_off_song[][2] = SONG(NAVCTRL_OFF_SONG);
#endif
//}}}1

// Advanced Tap Dancing functions {{{1
/**
 * The _finished() functions are used when the tap dance cutoff timer has
 * elapsed. I.e. no more taps will be counted as part of the current tap dance.
 * The tap dance key is still pressed and held when the _finished() function is
 * called.
 * 
 * The _reset() functions are called when the key is released and usually
 * contains some kind of conditional for different amount of taps.
 **/ 

/*
// HYPER momentary modifier. Tap dance implementation. {{{2
// hyper_layer_finished() HYPER when tapped once and held {{{3
void hyper_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for momentary HYPER and turning off HYPER layer
    case 1:
      // momentary press HYPER
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      
      // enabled _HYPER_MEH layer for HYPER+ESC to work
      layer_on(_HYPER_MEH);
    break;
  }
}

// hyper_layer_reset() - release HYPER mod and deactivate _HYPER_MEH layer {{{3
void hyper_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // momentary release HYPER
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
    
    // disable _HYPER_MEH layer
    layer_off(_HYPER_MEH);
  }
}
// }}}2
*/

/*
// HYPER / HYPER One-Shot Tap dance {{{2
// hyper_and_hyperos_finished() HYPER when tapped once and held, HYPER One-shot when double tapped and held {{{3
void hyper_and_hyperos_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {

    // Tapping/holding once is for momentary HYPER and turning off HYPER layer
    case 1:
      // check if ONE SHOT was activated previously.
      // if so, unprime hyper one-shot if tapped/held once
      if (IS_LAYER_ON(_HYPER_MEH)) {
        // _HYPER_MEH layer kept on for HYPER+ESC

        // Notify of One-Shot beind deactivated
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_off_song);
        #endif
      }

      // use as momentary hyper
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LCTL);
      register_code(KC_LSFT);
      break;
    
    // Second tap toggles HYPER layer lock for HYPER One-Shot
    case 2:
      // toggle OFF _HYPER_MEH layer and "un-arm" HYPER One-Shot
      if (IS_LAYER_ON(_HYPER_MEH)) {
        layer_off(_HYPER_MEH);
        
        // HYPER disarm sound
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_off_song);
        #endif
      }

      // toggle ON _HYPER_MEH layer, i.e. "arm" HYPER One-Shot
      else {
        layer_on(_HYPER_MEH);
        
        // HYPER arm sound
        #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_on_song);
        #endif
      }
      break;
  }
}

// hyper_and_hyperos_dance_reset() - release HYPER mod {{{3
void hyper_and_hyperos_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    // release HYPER
    unregister_code(KC_LGUI);
    unregister_code(KC_LALT);
    unregister_code(KC_LCTL);
    unregister_code(KC_LSFT);
  }
  
  // no state->count == 2 clause. all toggle stuff is handled during key press
}
// }}}2
*/

// CMD / HYPER Tap dance {{{2
// cmdhyper_dance_finished() - CMD when held, HYPER when double tapped + held {{{3
void cmdhyper_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // Tapping/holding once is for momentary CMD
    case 1:
      register_code(KC_LGUI);
      break;
    case 2:
      // Tapping twice + hold = momentary HYPER
      register_code(KC_LGUI);
      register_code(KC_LALT);
      register_code(KC_LSFT);
      register_code(KC_LCTL);

      #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_on_song);
      #endif
      break;
  }
}

// cmdhyper_dance_reset() - release CMD/HYPER {{{3
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

      #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(hyper_off_song);
      #endif
      break;
  }
}
// }}}2

// ALT / MEH Tap dance {{{2
// altmeh_dance_finished() - ALT when held, MEH when double tapped + held {{{3
void altmeh_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {

    // Tapping+holding once is for momentary LALT.
    case 1:
      register_code(KC_LALT);
      break;

    // Tapping+holding twice is for momentary MEH
    case 2:
      // add meh modifiers
      register_code(KC_LCTL);
      register_code(KC_LALT);
      register_code(KC_LSFT);

      #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(meh_on_song);
      #endif
      break;
  }
}

// altmeh_dance_reset() - release ALT/MEH {{{3
void altmeh_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // release momentary ALT
      unregister_code(KC_LALT);
      break;
    case 2:
      // release momentary MEH 
      unregister_code(KC_LCTL);
      unregister_code(KC_LALT);
      unregister_code(KC_LSFT);

      #ifdef AUDIO_ENABLE
        stop_all_notes();
        PLAY_SONG(meh_off_song);
      #endif
      break;
  }
}
// }}}2

// CTRL / USE_CTRL tap dance {{{2
// ctrl_usectrl_dance_finished() {{{3
void ctrl_usectrl_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
     // Tapping/holding once is for the momentary CTRL. 
    case 1:
      register_code(KC_LCTL);
      break;

    // Second tap is to toggle _USECTRL
    case 2:
      if (IS_LAYER_ON(_USE_CTRL)) {
          layer_off(_USE_CTRL);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(navctrl_off_song);
          # endif
      } else {
          layer_on(_USE_CTRL);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(navctrl_on_song);
          # endif
      }
      break;
  }
}

// ctrl_usectrl_dance_reset {{{3
void ctrl_usectrl_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // momentary CTRL off
    case 1:
      unregister_code(KC_LCTL);
      break;
    
    // Its a toggle, so only do stuff on press
    case 2:
      break;
  }
}
// }}}2

// CTRL / NAVCTRL tap dance {{{2
// ctrl_navctrl_dance_finished() {{{3
void ctrl_navctrl_dance_finished(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
     // Tapping/holding once is for the momentary FN-layer. 
    case 1:
      register_code(KC_LCTL);
      break;

    // Second tap is for momentary _NAVCTRL (if _NAV if on)
    case 2:
      if (IS_LAYER_ON(_NAV)) {
          layer_on(_NAVCTRL);
      }
      else {
        if (IS_LAYER_ON(_NAVCTRL)) {
          layer_off(_NAVCTRL);
	}
      }
      break;
  }
}

// ctrlnavctrl_dance_reset {{{3
void ctrl_navctrl_dance_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    // momentary CTRL off
    case 1:
      unregister_code(KC_LCTL);
      break;
    
    // momentary _NAVCTRL off (if it is on)
    case 2:
      if (IS_LAYER_ON(_NAVCTRL)) {
        layer_off(_NAVCTRL);
      }
      break;
  }
}
// }}}2

// }}}1

// Tap Dance Actions {{{1
qk_tap_dance_action_t tap_dance_actions[] = {
    //[TD_RSHIFT_CAPS]   = ACTION_TAP_DANCE_DOUBLE(KC_RSFT,   KC_CAPS),
    //[TD_RSHIFT_BTN1]   = ACTION_TAP_DANCE_DOUBLE(KC_RSFT,   KC_BTN1),
    //[TD_HYPER]         = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hyper_layer_finished,             hyper_layer_reset),
    //[TD_HYPER_ONESHOT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, hyper_and_hyperos_dance_finished, hyper_and_hyperos_dance_reset),
    [TD_CMD_HYPER]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, cmdhyper_dance_finished,          cmdhyper_dance_reset),
    [TD_ALT_MEH]       = ACTION_TAP_DANCE_FN_ADVANCED(NULL, altmeh_dance_finished,            altmeh_dance_reset),
    [TD_CTRL_USECTRL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_usectrl_dance_finished,      ctrl_usectrl_dance_reset)
    //[TD_CTRL_NAVCTRL]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ctrl_navctrl_dance_finished,      ctrl_navctrl_dance_reset)
};
// }}}1

// process_record_user: Tri layer, game layer, hyper keys {{{1
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // switch for both keypressed and keyrelease {{{2
  switch (keycode) {
    case NONE:      // Don't do anything {{{3
      if (record->event.pressed) {
        // Do nothing.
        // KC_NO seems to reset layers
      }
      return false;
      break;

    case ANSIUS:    // Toggle QWERTY_ANSI layer {{{3
      if (record->event.pressed) {
        if (IS_LAYER_ON(_QWERTY_ANSI)) {
          layer_off(_QWERTY_ANSI);
        } else {
          layer_on(_QWERTY_ANSI);
        }
      }
      return false;
      break;

    case FN:        // _FN layer + tri layer {{{3
      if (record->event.pressed) {
        layer_on(_FN);
        update_tri_layer(_FN, _NAV, _HWDLAYER);
      } else {
        layer_off(_FN);
        update_tri_layer(_FN, _NAV, _HWDLAYER);
      }
      return false;
      break;

    case NAV:       // _NAV layer + tri layer {{{3
      // key pressed
      if (record->event.pressed) {
        // turn on the correct NAV layer depending on if the _USE_CTRL layer is
        // on or off
        if (IS_LAYER_ON(_USE_CTRL)) {
          layer_on(_NAVCTRL);
          update_tri_layer(_FN, _NAVCTRL, _HWDLAYER);
        } else {
          layer_on(_NAV);
          update_tri_layer(_FN, _NAV, _HWDLAYER);
        }
      }
      
      // key released
      else {
        // turn off the correct NAV layer depending on if the _USE_CTRL layer is
        // on or off
        if (IS_LAYER_ON(_USE_CTRL)) {
          layer_off(_NAVCTRL);
          update_tri_layer(_FN, _NAVCTRL, _HWDLAYER);
        } else {
          layer_off(_NAV);
          update_tri_layer(_FN, _NAV, _HWDLAYER);
        }
      }
	  
      return false;
      break;


    case GAME1:     // Toggle _GAME1 layer {{{3
      if (record->event.pressed) {
        if (IS_LAYER_ON(_GAME1)) {
          layer_off(_GAME1);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(game_off_song);
          #endif
        } else {
          layer_on(_GAME1);
          #ifdef AUDIO_ENABLE
            stop_all_notes();
            PLAY_SONG(game_on_song);
          #endif
        }
      }
      return false;
      break;
  } // }}}2 end keypress/keyrelease

  // Only for pressed. {{{2
  if (record->event.pressed) {
    switch (keycode) {
      // Macros
      case VIMSAVE: // Vim save macro. <esc>:w<cr>  {{{3
        SEND_STRING(SS_TAP(X_ESCAPE)":w"SS_TAP(X_ENTER)"");
        return false;

      default:      // HYPER One-Shot if _HYPER_MEH layer is on
        // add modifiers, register keycode and go back to default layer  {{{3
        if (IS_LAYER_ON(_HYPER_MEH)) {
		
          // turn off hyper layer
          layer_off(_HYPER_MEH);

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
      // }}}3
    } // end switch(keycode)
  } // end event.pressed
  return true;
}
// }}}1

/* vim: set fdm=marker commentstring=//\ %s: */
