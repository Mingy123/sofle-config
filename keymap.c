
 /* Copyright 2021 Dane Evans
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
  // SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)

#define HSV_NUSH 100, 255, 100

// Light combinations
/* Diagram of the led indices
 *  On the right side they are added by 35
 * ,-----------------------------------------.         
 * |  10  |  11  |  20  |  21  |  30  |  31  |         
 * |------0------+------1------+------2------|         
 * |   9  |  12  |  19  |  22  |  29  |  32  |         
 * |------+------+------+------+------+------|         
 * |   8  |  13  |  18  |  23  |  28  |  33  |-------. 
 * |------5------+------4------+------3------|       | 
 * |   7  |  14  |  17  |  24  |  27  |  34  |-------| 
 * `-----------------------------------------/       / 
 *            |  6   |  15  |  16  |  25  | /  26   /  
 *            |      |      |      |      |/       /   
 *            `----------------------------------'     
 */
#define SET_UNDERGLOW(hsv) \
    {0, 7, hsv}, \
    {35, 7,hsv}
#define SET_NUMPAD(hsv)     \
    {35+15, 1, hsv},\
    {35+17, 3, hsv},\
      {35+22, 3, hsv},\
      {35+27, 3, hsv}
#define SET_NUMROW(hsv) \
    {10, 2, hsv}, \
      {20, 2, hsv}, \
      {30, 2, hsv}, \
        {35+ 10, 2, hsv}, \
        {35+ 20, 2, hsv}, \
        {35+ 30, 2, hsv}

#define SET_INNER_COL(hsv)    \
    {33, 4, hsv}, {35+ 33, 4, hsv}
#define SET_OUTER_COL(hsv) \
    {7, 4, hsv}, \
      {35+ 7, 4, hsv}

#define SET_WASD(hsv) \
    {13, 1, hsv}, {18, 2, hsv}, {23, 1, hsv}
#define SET_HJKL(hsv) \
    {35+18, 1, hsv}, {35+23, 1, hsv}, \
    {35+28, 1, hsv}, {35+33, 1, hsv}

#define SET_CODE(mineq, brace) \
    {35+12, 2, brace}, {35+18, 2, brace}, \
    {35+22, 2, mineq}, {35+28, 2, mineq}, \
    {28, 2, brace}, {32, 2, brace}, \
    {18, 2, mineq}, {22, 2, mineq}

#define SET_THUMB_CLUSTER(hsv)     \
    {25, 2, hsv}, \
      {35+ 25, 2, hsv}
#define SET_LAYER_ID(hsv)     \
    {0, 7, hsv}, \
    {35, 7, hsv}, \
      {7, 4, hsv}, \
        {35+7, 4, hsv}, \
      {25, 2, hsv}, \
        {35+25, 2, hsv}


enum sofle_layers {
    _DEFAULTS = 0,
    _QWERTY = 0,
    _MOVE,
    _CODE,
    _COMMAND,
    _NUMPAD,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_EC11,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | NUM/` |  1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | SWCH |
 * |-------+-----+------+------+------+------|                    |------+------+------+------+------+------|
 * |  TAB  |  Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |-------+-----+------+------+------+------|                    |------+------+------+------+------+------|
 * |  ESC  |  A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |-------+-----+------+------+------+------|  VOL  |    |  VOL  |------+------+------+------+------+------|
 * |  SHFT |  Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  | Shft |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | CTRL | LALT |  Win | Space| / MOVE  /       \ MOVE \  | CODE |ENTER | CODE | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `-----------------------------------'           '------''---------------------------'
 */
  [_QWERTY] = LAYOUT(
  //,------------------------------------------------.                      ,---------------------------------------------------.
LT(_NUMPAD,KC_GRV), KC_1, KC_2, KC_3,  KC_4,   KC_5,                         KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    MO(_COMMAND),
  //|------+-------+--------+--------+--------+------|                      |--------+-------+--------+--------+--------+---------|
  KC_TAB ,  KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
  //|------+-------+--------+--------+--------+------|                      |--------+-------+--------+--------+--------+---------|
  KC_ESC,   KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|------+-------+--------+--------+--------+------|  ===  |      |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_EC11,      KC_MUTE, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  //|------+-------+--------+--------+--------+------|  ===  |      |  ===  |--------+-------+--------+--------+--------+---------|
                 KC_LCTL, KC_LALT, KC_LGUI,  KC_SPC,  MO(_MOVE),   MO(_MOVE),KC_ENT,MO(_CODE),KC_RCTL, KC_RALT
  //            \--------+--------+--------+---------+-------|      |--------+---------+--------+---------+-------/
),

/* MOVE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |                    |  F7  |  F8  |  F9  |  F10 | F11  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | LClk | CurU | RClk |      |      |                    | LClk | RClk | MClk |      |  SS  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      | CurL | CurD | CurR | Home | PgUp |-------.    ,-------| Left | Down |  Up  | Rght |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      | Back | Frwd | Caps |  End | PgDn |-------|    |-------| ScrL | ScrD | ScrU | ScrR |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_MOVE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
    KC_F1,  KC_F2,  KC_F3,   KC_F4,   KC_F5,   KC_F6,                     KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,  KC_F12,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, KC_BTN1, KC_MS_U, KC_BTN2, KC_WH_D, KC_WH_U,                   KC_BTN1, KC_BTN2, KC_BTN3,XXXXXXX, KC_PSCR,  _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, KC_MS_L, KC_MS_D, KC_MS_R, KC_HOME, KC_PGUP,                   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, XXXXXXX,  XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______, KC_WBAK, KC_WFWD, KC_CAPS, KC_END, KC_PGDN,_______,    _______,KC_WH_L, KC_WH_D, KC_WH_U,KC_WH_R, XXXXXXX,  _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______,  KC_ENT,  _______,    _______, KC_SPC, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* CODE
 * ,----------------------------------------.                     ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |  DEL |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   |  |   _  |   +  |   {  |   }  |                    |   |  |   _  |   +  |   {  |   }  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |   -  |   =  |   [  |   ]  |-------.    ,-------|      |   -  |   =  |   [  |   ]  |   \  |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      | C+S+c| C+S+v|      |-------|    |-------|      |      |   ,  |   .  |   /  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_CODE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, KC_DEL,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR,                   KC_PIPE, KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC,                   XXXXXXX, KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BACKSLASH,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______, XXXXXXX,XXXXXXX,C(S(KC_C)), C(S(KC_V)), XXXXXXX,_______,   _______,XXXXXXX, XXXXXXX, _______, _______, _______, _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, KC_RCTL
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* COMMAND
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | RST  |      |      |      |      |      |                    | QWRT | MOVE | CODE | NUM  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | BOOT |      |      |      |      |      |                    |      |      |      |      |  SS  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | RGB  | hue^ |sat ^ | bri ^|      |      |-------.    ,-------|      |      |      |      |      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * | mode |hue dn|sat dn|bri dn|      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |  C(G(KC_LEFT)) = Control + GUI + Left
 *            `----------------------------------'           '------''---------------------------'
 */
  [_COMMAND] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  EE_CLR,  XXXXXXX, KC_BRID, KC_BRIU, XXXXXXX, XXXXXXX,               TO(_QWERTY), TO(_MOVE), TO(_CODE), TO(_NUMPAD), XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PSCR, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX,XXXXXXX,   XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                   _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
    //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |   /  |   &  |   |  |   ^  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |  F1  |  F2  |  F3  |  F4  |                    |   *  |   1  |   2  |   3  |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |  F5  |  F6  |  F7  |  F8  |-------.    ,-------|   -  |   4  |   5  |   6  |   ,  |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |  F9  |  F10 |  F11 |  F12 |-------|    |-------|   +  |   7  |   8  |   9  |   =  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |SPACE |  .   |  0   | Ret  |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NUMPAD] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_SLSH, KC_AMPR, KC_PIPE, KC_CIRC, XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, KC_F1,   KC_F2,   KC_F3,   KC_F4,                     KC_ASTR,  KC_1,   KC_2,    KC_3,   XXXXXXX, _______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, KC_F5,   KC_F6,   KC_F7,   KC_F8,                     KC_MINS,  KC_4,   KC_5,    KC_6,   KC_COMM, XXXXXXX,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, KC_F9,   KC_F10,  KC_F11,  KC_F12,_______,    _______,KC_PLUS,  KC_7,   KC_8,    KC_9,   KC_EQL,  _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, KC_DOT, KC_0,  KC_ENT
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence



/* Diagram of the led indices
 *  On the right side they are added by 35
 * ,-----------------------------------------.         
 * |  10  |  11  |  20  |  21  |  30  |  31  |         
 * |------0------+------1------+------2------|         
 * |   9  |  12  |  19  |  22  |  29  |  32  |         
 * |------+------+------+------+------+------|         
 * |   8  |  13  |  18  |  23  |  28  |  33  |-------. 
 * |------5------+------4------+------3------|       | 
 * |   7  |  14  |  17  |  24  |  27  |  34  |-------| 
 * `-----------------------------------------/       / 
 *            |  6   |  15  |  16  |  25  | /  26   /  
 *            |      |      |      |      |/       /   
 *            `----------------------------------'     
 */
const rgblight_segment_t PROGMEM layer_move_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_TEAL),
    SET_WASD(HSV_RED),
    SET_HJKL(HSV_PINK)
);

const rgblight_segment_t PROGMEM layer_code_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_LAYER_ID(HSV_BLUE),
    SET_CODE(HSV_CORAL, HSV_NUSH)
);

const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE),
  {35+31, 1, HSV_WHITE},
  {35+30, 1, HSV_TEAL},
  {35+21, 1, HSV_BLUE},
  {35+20, 1, HSV_ORANGE}
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
    SET_UNDERGLOW(HSV_ORANGE),
    SET_NUMPAD(HSV_BLUE),
    {7, 4, HSV_ORANGE},
    {25, 2, HSV_ORANGE},
    {35+6, 4, HSV_ORANGE},
    {35+25, 2, HSV_ORANGE}
    );


const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_move_lights,// overrides layer 1
    layer_code_lights,
    layer_command_lights,
    layer_numpad_lights
);

// I think the normal uncommented lines is just mapping the index of the above array to the layer
// Still no idea what the rgb commented one does
layer_state_t layer_state_set_user(layer_state_t state) {
    //rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_QWERTY));
    rgblight_set_layer_state(0, layer_state_cmp(state, _MOVE));
    rgblight_set_layer_state(1, layer_state_cmp(state, _CODE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _COMMAND));
    rgblight_set_layer_state(3, layer_state_cmp(state, _NUMPAD));
    return state;
}


void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    rgblight_mode(10);// haven't found a way to set this in a more useful way
}
#endif

#ifdef OLED_ENABLE

static const char PROGMEM logo_gap[]   = { 0x20, 0x20, 0x20, 0x20, 0x20, 0x00 };

static const char PROGMEM logo_base1[] = { 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x00 };
static const char PROGMEM logo_base2[] = { 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9A, 0x9B, 0x9C, 0x9D, 0x00 };
static const char PROGMEM logo_base3[] = { 0xB4, 0xB5, 0xB6, 0xB7, 0xB8, 0xB9, 0xBA, 0xBB, 0xBC, 0xBD, 0x00 };
static const char PROGMEM logo_base4[] = { 0xD4, 0xD5, 0xD6, 0xD7, 0xD8, 0xD9, 0xDA, 0xDB, 0xDC, 0xDD, 0x00 };

static const char PROGMEM logo_code1[] = { 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F, 0x70, 0x71, 0x72, 0x73, 0x00 };
static const char PROGMEM logo_code2[] = { 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x00 };
static const char PROGMEM logo_code3[] = { 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0x00 };
static const char PROGMEM logo_code4[] = { 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0x00 };

static const char PROGMEM logo_walk1[] = { 0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x00 };
static const char PROGMEM logo_walk2[] = { 0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x00 };
static const char PROGMEM logo_walk3[] = { 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0x00 };
static const char PROGMEM logo_walk4[] = { 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0x00 };

static void print_walk(void) {
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_walk1, false);
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_walk2, false);
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_walk3, false);
    oled_write_P(logo_gap, false); oled_write_P(logo_walk4, false);
}

static void print_map(void) {
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_code1, false);
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_code2, false);
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_code3, false);
    oled_write_P(logo_gap, false); oled_write_P(logo_code4, false);
}

static void print_base(void) {
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_base1, false);
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_base2, false);
    oled_write_P(logo_gap, false); oled_write_ln_P(logo_base3, false);
    oled_write_P(logo_gap, false); oled_write_P(logo_base4, false);
}


static void print_status(void) {
    //snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)
    oled_clear();
    switch (get_highest_layer(layer_state)) {
        case _MOVE:
            print_walk();
            break;
        case _CODE:
        case _NUMPAD:
            print_map();
            break;
        default:
            print_base();
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return rotation;
/*
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
*/
}

bool oled_task_user(void) {
    if (1 || is_keyboard_master()) {
        print_status();
    } else {
        print_base();
    }
    return false;
}

#endif

// processing custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_EC11:
            // TODO: decide on something to do when the scrolling wheel is pressed
            return false;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_WH_D);
        } else {
            tap_code(KC_WH_U);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
/*
    switch (get_highest_layer(layer_state)) {
        case _QWERTY:
            if (clockwise) {
                tap_code(KC_PGDN);
            } else {
                tap_code(KC_PGUP);
            }
        break;
    case _CODE:
    case _MOVE:
            if (clockwise) {
                tap_code(KC_DOWN);
            } else {
                tap_code(KC_UP);
            }
        break;
    default:
        break;
    }
*/
}

#endif
