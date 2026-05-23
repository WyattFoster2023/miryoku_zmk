// Game HID profile: plain key presses on the left hand, layout selectors on the right top row.

#pragma once

#include "extended_keys.h"

// Left-hand 4×6 grid (home = F at row 1 col 4):
//   I Q W E R T
//   K A S D F G
//   M Z X C V B
// Thumb: LCTRL, LALT, SPACE

#define MIRYOKU_LAYER_GAME \
  &kp I, &kp Q, &kp W, &kp E, &kp R, &kp T, \
  ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_SLOT3, U_NA, U_NA, U_NA, \
  &kp K, &kp A, &kp S, &kp D, &kp F, &kp G, &none, &none, &none, &none, &none, U_NA, \
  &kp M, &kp Z, &kp X, &kp C, &kp V, &kp B, &none, &none, &none, &none, &none, U_NA, \
  U_NA, &none, &none, &none, &none, &none, &none, &none, &none, &none, &none, U_NA, \
  U_NP, U_NP, &kp LCTRL, &kp LALT, &kp SPACE, &none, &none, &none, U_NP, U_NP

#define MIRYOKU_LAYER_SLOT3 \
  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, \
  ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_SLOT3, U_NA, U_NA, U_NA, \
  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, &none, &none, &none, &none, &none, U_NA, \
  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, &none, &none, &none, &none, &none, U_NA, \
  U_NA, &none, &none, &none, &none, &none, &none, &none, &none, &none, &none, U_NA, \
  U_NP, U_NP, U_NA, U_NA, U_NA, &none, &none, &none, U_NP, U_NP

#define MIRYOKU_LAYERMAPPING_GAME  MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_SLOT3 MIRYOKU_MAPPING
