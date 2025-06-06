/* Copyright 2023 Alexandre Plateau <lexplt.dev@gmail.com>
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
 */
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x5_3(
    KC_Q,   KC_W,   KC_E,  KC_R,   KC_T,            KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
    MT(MOD_LGUI,KC_A),   MT(MOD_LALT,KC_S),   MT(MOD_LSFT,KC_D),  MT(MOD_LCTL,KC_F),   KC_G,            KC_H,   MT(MOD_LCTL,KC_J),   MT(MOD_RSFT,KC_K),   MT(MOD_LALT,KC_L),   MT(MOD_LGUI,KC_SCLN),
    KC_Z,   KC_X,   KC_C,  KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLASH,
                    QK_BOOT, KC_SPACE, KC_ENTER,        KC_BSPC,   MO(2), KC_TAB
  ),

  [1] = LAYOUT_split_3x5_3(
    KC_Q,   KC_W,   KC_E,  KC_R,   KC_T,            KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,
    KC_A,   KC_S,   KC_D,  KC_F,   KC_G,            KC_H,   MT(MOD_LCTL,KC_J),   MT(MOD_RSFT,KC_K),   MT(MOD_LALT,KC_L),   MT(MOD_LGUI,KC_SCLN),
    KC_Z,   KC_X,   KC_C,  KC_V,   KC_B,            KC_N,   KC_M,   KC_COMM, KC_DOT, KC_SLASH,
                    QK_BOOT, KC_SPACE, KC_ENTER,        KC_BSPC,   MO(2), KC_TAB
  ),

  [2] = LAYOUT_split_3x5_3(
    KC_1,   KC_2,   KC_3,   KC_4,   KC_5,       KC_6,   KC_7,   KC_8,   KC_9,   KC_0,
    KC_NO,   KC_NO,   MT(MOD_LSFT,KC_MINS),   KC_NO,   KC_MINS,       KC_EQL,    KC_BSLS,   MT(MOD_RSFT,KC_LBRC),   KC_RBRC,   KC_QUOT,
    TG(1),   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_NO,   KC_ESC, KC_TAB,     KC_TRNS, KC_TRNS, KC_NO
  ),

  [3] = LAYOUT_split_3x5_3(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_NO,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_NO
  ),

  [4] = LAYOUT_split_3x5_3(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                      KC_NO,   KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_NO
  ),
};


bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(MOD_LSFT, KC_D):
            //Immediately select the hold action when another key is tapped.
            return true;
        case LT(MOD_LSFT, KC_K):
          return true;
        default:
            // Do not select the hold action when another key is tapped.
            return false;
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    // Check if layer 2 is active
    bool is_layer_2_active = (biton32(layer_state) == 2);

    if (index == 0) {  // Left encoder
        if (is_layer_2_active) {
            // Adjust volume when on layer 2
            if (clockwise) {
                tap_code(KC_VOLU);  // Volume Up
            } else {
                tap_code(KC_VOLD);  // Volume Down
            }
        } else {
            // Default to arrow keys
            if (clockwise) {
                tap_code(KC_RGHT);  // Right arrow
            } else {
                tap_code(KC_LEFT);  // Left arrow
            }
        }
    } else if (index == 1) {  // Right encoder
        if (clockwise) {
            tap_code(KC_DOWN);  // Down arrow
        } else {
            tap_code(KC_UP);    // Up arrow
        }
    }
    return false;
}
