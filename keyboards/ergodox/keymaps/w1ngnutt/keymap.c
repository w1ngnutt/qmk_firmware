#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"
#include "action_util.h"
#include "led.h"
#include "keymap.h"
#include "timer.h"

/*

# Why this Layout

This layout was based on Kinesis layout and other ErgoDox user layouts
available. It's target to be used on a MacOS but I'm pretty sure it can be
addapted to Windows and/or Linux easily.

## Function Key

The `fn` key work almost like it would in any other keyboard with the exception
it has a semi-sticky behavior. What does that mean?

Well, if you press the `fn` and release it, the keyboard will be put on the
_function layout_ and the next key stroke will be processed as if the `fn` key
was pressed. Aftwards, the leyout get back to _normal_. If you hold `fn` and
press any other key, when you release them, the keyboard leyout is back to
_normal_.

While pressing the `fn` with the left hand and strikeing the other keys on the
right hand is farly easy, the same cannot being said for the other keys on the
left side. So, instead of trying to do contorcionism with my left hand, I
decided to do a semi-sticky version of `fn`. This way, I can press the  `fn`
key with my pinky, release it and press the `1` key to issue an `F1` to the
operating system.

## Key-Pad Key

The `key pad` key is a layout switch key. If pressed, it will put the keyboard
on the _key pad layout_ and stay there until key is pressed again.

This is used to make the keyboard behave mostly like a **num pad keyboard**.

## Notes
- Regardless in which layout you are, keys from other layouts are not
  accessible. This means that if you are on the _key pad layout_, the left hand
  will be pretty much unusable.
  Of course that like anything else, there are exceptions to this rule.
  Modifiers should remain accessible throughout the layers.
- The _shift key_ is, like the _function key_, also configured to have a sticky
  behavior.
- All sticky keys have a timeout of 3 seconds.

*/

// layers
#define BASE   0
#define KEYPAD 1
#define FN     2

// macros
#define MACRO_TMUX_LDR        10
#define MACRO_COPY            11
#define MACRO_PASTE           12
#define MACRO_CLIPIT          13
#define MACRO_TMUX_SCROLL     14
#define MACRO_ROFI            15

#define M_TLDR   M(MACRO_TMUX_LDR)
#define M_CPY    M(MACRO_COPY)
#define M_PST    M(MACRO_PASTE)
#define M_CLPT   M(MACRO_CLIPIT)
#define M_TSCL   M(MACRO_TMUX_SCROLL)
#define M_RFI    M(MACRO_ROFI)

// layout available at: http://www.keyboard-layout-editor.com/#/gists/e1af6e3b6d43cf87d23cc2d8db1a2019

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Base Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * | ESC       |   1  |   2  |   3  |   4  |   5  |   6  |           | ` ~  |   7  |   8  |   9  |  0   | - _  |   = +     |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           |   Q  |   W  |   E  |   R  |   T  |M_TLDR|           |      |   Y  |   U  |   I  |   O  |   P  |   \  |    |
 * |-----------+------+------+------+------+------|      |           | Meh  |------+------+------+------+------+-----------|
 * | \ (Ctrl)  |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  | ' " (Ctrl)|
 * |-----------+------+------+------+------+------| [{   |           | ]}   |------+------+------+------+------+-----------|
 * |  LShift   |   Z  |   X  |   C  |   V  |   B  |      |           |Hyper)|   N  |   M  |   ,  |   .  |   /  |   RShift  |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | FN    | KPAD |LCtrl | LAlt | LGui |                                       | RGui | RAlt | RCtrl| KPAD |    FN |
 *     |       |      |      |      |      |                                       |      |      |  / [ |  / ] |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |M_CPY |M_PST |           | HOME | END  |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |M_CLPT|           | PgUp |      |      |
 *                                  |Backsp| TAB  |------|           |------| Enter| Space|
 *                                  |      |      |M_TSCL|           | PgDn |      |      |
 *                                  `--------------------'           `--------------------'
 *
 * M(0) = Ctrk+A (T-Mux leader)
 * M(1) = Ctrl+C (Copy)
 * M(2) = Ctrl+C (Paste)
 * M(3) = Ctrl+Alt+H (Clipt paste menu)
 * M(4) = Ctrl+A+[ (T-Mux scroll mode)
 * M(5) = LGui+Tab (launch rofi)
*/
[BASE]=KEYMAP(//left half
              KC_ESC,         KC_1,       KC_2,     KC_3,           KC_4,       KC_5,     KC_6,
              KC_GRV,         KC_Q,       KC_W,     KC_E,           KC_R,       KC_T,     M_TLDR,
              CTL_T(KC_BSLS), KC_A,       KC_S,     KC_D,           KC_F,       KC_G,
              KC_FN2,         KC_Z,       KC_X,     KC_C,           KC_V,       KC_B,     KC_LBRC,
              KC_FN1,         TG(KEYPAD), KC_LCTRL, KC_LALT,        KC_LGUI,
                                                                                M_CPY,    M_PST,
                                                                                          M_CLPT,
                                                                    KC_BSPC,    KC_TAB,   M_TSCL,
              //right half
              KC_NO,         KC_7,       KC_8,     KC_9,           KC_0,       KC_MINS,  KC_EQL,
              MEH_T(KC_PGUP), KC_Y,       KC_U,     KC_I,           KC_O,       KC_P,     KC_BSLS,
                              KC_H,       KC_J,     KC_K,           KC_L,       KC_SCLN,  CTL_T(KC_QUOT),
              ALL_T(KC_RBRC), KC_N,       KC_M,     KC_COMM,        KC_DOT,     KC_SLSH,  KC_FN2,
                              KC_RGUI,    KC_RALT,  CTL_T(KC_LBRC), KC_FN3,     KC_FN1,
              KC_HOME,        KC_END,
              KC_PGUP,
              KC_PGDN,        KC_ENT,     KC_SPC),

/* Keymap 1: KeyPad Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |           |      | LClk | RClk | MClk |      |      |           | BTab | Clear|   /  |   *  |   ^  |   (  |           |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * | M.Accel 2 |      |ScrlUp|  U   |ScrlDn|      |      |           | Tab  |   7  |   8  |   9  |   +  |   )  |           |
 * |-----------+------+------+------+------+------|      |           |      |------+------+------+------+------+-----------|
 * | M.Accel 1 |      |   L  |  D   |  R   |      |------|           |------|   4  |   5  |   6  |   -  |      |           |
 * |-----------+------+------+------+------+------|      |           |Return|------+------+------+------+------+-----------|
 * | M.Accel 0 |      |ScrlL |      |ScrlR |      |      |           |      |   1  |   2  |   3  |   =  |      |           |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     |       | XXXX |      |      |      |                                       |   0  |   .  |   ,  | XXXX |       |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      | XXXX |      |
 *                                  |      |      |------|           |------| XXXX |      |
 *                                  |      |      |      |           |      | XXXX |      |
 *                                  `--------------------'           `--------------------'
 */
[KEYPAD]=KEYMAP(//left half
                KC_NO,        KC_NO,    KC_MS_BTN1,    KC_MS_BTN2,     KC_MS_BTN3,     KC_NO,   KC_NO,
                KC_MS_ACCEL2, KC_NO,    KC_MS_WH_UP,   KC_MS_U,        KC_MS_WH_DOWN,  KC_NO,   KC_NO,
                KC_MS_ACCEL1, KC_NO,    KC_MS_L,       KC_MS_D,        KC_MS_R,        KC_NO,
                KC_MS_ACCEL0, KC_NO,    KC_MS_WH_LEFT, KC_NO,          KC_MS_WH_RIGHT, KC_NO,   KC_NO,
                KC_NO,        KC_TRNS,  KC_NO,         KC_NO,          KC_NO,
                                                                                       KC_NO,   KC_NO,
                                                                                                KC_NO,
                                                                       KC_NO,          KC_NO,   KC_NO,
                //right half
                LSFT(KC_TAB), KC_CLEAR, KC_KP_SLASH,   KC_KP_ASTERISK, KC_CIRCUMFLEX,  KC_LPRN, KC_NO,
                KC_TAB,       KC_KP_7,  KC_KP_8,       KC_KP_9,        KC_KP_PLUS,     KC_RPRN, KC_NO,
                              KC_KP_4,  KC_KP_5,       KC_KP_6,        KC_KP_MINUS,    KC_NO,   KC_NO,
                KC_KP_ENTER,  KC_KP_1,  KC_KP_2,       KC_KP_3,        KC_KP_EQUAL,    KC_NO,   KC_NO,
                                        KC_KP_0,       KC_KP_DOT,      KC_KP_COMMA,    KC_TRNS, KC_NO,
                KC_NO,        KC_NO,
                KC_NO,
                KC_NO,        KC_TRNS,  KC_NO),

/* Keymap 2: Functions Layer
 *
 * ,-----------------------------------------------------.           ,-----------------------------------------------------.
 * |     ` ~   |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |           |      |  F7  |  F8  |  F9  |  F10 |  F11 |    F12    |
 * |-----------+------+------+------+------+-------------|           |------+------+------+------+------+------+-----------|
 * |           | Stop |  Rw  |  Rec |  FF  |      | XXXX |           | XXXX |      |      |      |      |      | Vol. Down |
 * |-----------+------+------+------+------+------| XXXX |           | XXXX |------+------+------+------+------+-----------|
 * |  CapsLock | Eject| Prev | Play | Next |      |------|           |------| Left | Down |  Up  | Right|      |   Mute    |
 * |-----------+------+------+------+------+------| XXXX |           | XXXX |------+------+------+------+------+-----------|
 * |  L Shift  |      |      |      |      |      | XXXX |           | XXXX |      |      |      |      |      |  R Shift  |
 * `-----------+------+------+------+------+-------------'           `-------------+------+------+------+------+-----------'
 *     | XXXXX |      | XXXX | XXXX | XXXX |                                       | XXXX | XXXX | XXXX |      | XXXXX |
 *     `-----------------------------------'                                       `-----------------------------------'
 *                                         ,-------------.           ,-------------.
 *                                         |      |      |           |      |      |
 *                                  ,------|------|------|           |------+------+------.
 *                                  |      |      |      |           |      |      |      |
 *                                  |      |      |------|           |------|      |      |
 *                                  |      |      |      |           |      |      |      |
 *                                  `--------------------'           `--------------------'
 *
 * XXX = These keys are transparent keys that, when pressed, they issue the key from the previous layer.
 */
[FN]=KEYMAP(//left half
            KC_GRV,  KC_F1,          KC_F2,               KC_F3,               KC_F4,                 KC_F5,  KC_F6,
            KC_NO,   KC_MEDIA_STOP,  KC_MEDIA_REWIND,     KC_MEDIA_SELECT,     KC_MEDIA_FAST_FORWARD, KC_NO,  KC_TRNS,
            KC_CAPS, KC_MEDIA_EJECT, KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK,   KC_NO,
            KC_LSFT, KC_NO,          KC_NO,               KC_NO,               KC_NO,                 KC_NO,  KC_TRNS,
            KC_TRNS, KC_NO,          KC_TRNS,             KC_TRNS,             KC_TRNS,
                                                                                                      KC_NO,  KC_NO,
                                                                                                              KC_NO,
                                                                               KC_NO,                 KC_NO,  KC_NO,
            //right half
            KC_NO,   KC_F7,          KC_F8,               KC_F9,               KC_F10,                KC_F11, KC_F12,
            KC_TRNS, KC_NO,          KC_NO,               KC_NO,               KC_NO,                 KC_NO,  KC_VOLD,
                     KC_LEFT,        KC_DOWN,             KC_UP,               KC_RIGHT,              KC_NO,  KC_MUTE,
            KC_TRNS, KC_NO,          KC_NO,               KC_NO,               KC_NO,                 KC_NO,  KC_RSFT,
                     KC_TRNS,        KC_TRNS,             KC_TRNS,             KC_NO,                 KC_TRNS,
            KC_NO,   KC_NO,
            KC_NO,
            KC_NO,   KC_NO,          KC_NO)};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_ONESHOT(FN), // oneshot function key
  [2] = ACTION_MODS_ONESHOT(MOD_LSFT),  // Sticky shift light. Tap for the next keypress to be shifted. Hold for regular shift.
  [3] = ACTION_LAYER_TAP_KEY(KEYPAD, KC_RBRC),
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt) {
  // MACRODOWN only works in this function
  switch(id) {
    case MACRO_TMUX_LDR:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), D(A), END);
      }
      return MACRO(U(A), U(LCTRL), END);

    case MACRO_COPY:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), D(C), END);
      }
      return MACRO(U(C), U(LCTRL), END);

    case MACRO_PASTE:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), D(V), END);
      }
      return MACRO(U(V), U(LCTRL), END);

    case MACRO_CLIPIT:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), D(LALT), T(H), END);
      }
      return MACRO(U(LALT), U(LCTRL), END);

    case MACRO_TMUX_SCROLL:
      if (record->event.pressed) {
        return MACRO(D(LCTRL), T(A), U(LCTRL), D(LBRC), END);
      }
      return MACRO(U(LBRC), END);
    case MACRO_ROFI:
      if (record->event.pressed) {
        return MACRO(D(LGUI), T(TAB), END);
      }
      return MACRO(U(LGUI), END);
  }
  return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
};

uint8_t current_layer = BASE;

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
  uint8_t layer = biton32(layer_state);

  ergodox_led_all_off();
  ergodox_led_all_set(LED_BRIGHTNESS_LO);

  switch (layer) {
  case BASE:
    current_layer = BASE;
    break;
  case KEYPAD:
    current_layer = KEYPAD;
    break;
  default:
    // none
    break;
  }

  // layer leds
  if (current_layer == KEYPAD) {
    ergodox_right_led_3_on();
  }

  // capslock
  if (host_keyboard_leds() & (3<<USB_LED_CAPS_LOCK)) {
    ergodox_right_led_1_on();
  }

  // Temporary leds

  // The function layer takes over other layers and we need to reflect that on the leds.
  // If the current layer is the BASE, we simply turn on the FN led, but if the current
  // layer is the KEYPAD, than we must turn it off before turning on the FN led.
  if (layer == FN && !has_oneshot_layer_timed_out()) {
    ergodox_right_led_3_off();
    ergodox_right_led_2_on();
  }

  // if the shifted is pressed I show the case led in a brighter color. This is nice to
  // differenciate the shift from the capslock.
  // Notice that I make sure that we're not using the shift on a chord shortcut (pressing
  // shift togather with other modifiers).
  if((keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) &&                                 // is shift pressed and there is no other
      !(keyboard_report->mods & (~MOD_BIT(KC_LSFT) & ~MOD_BIT(KC_RSFT)))) ||                           //    modifier being pressed as well
     (get_oneshot_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) && !has_oneshot_mods_timed_out())) {  // or the one shot shift didn't timed out
    ergodox_right_led_1_set(LED_BRIGHTNESS_HI);
    ergodox_right_led_1_on();
  }
};
