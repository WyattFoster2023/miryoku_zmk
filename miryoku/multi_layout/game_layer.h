// Game HID profile: plain key presses on the left hand, layout selectors on K43–K45.
//
// Bindings follow MIRYOKU_BIND_LILY58 / MIRYOKU_LAYOUTMAPPING_LILY58 slot order (same as
// wrapped_layers.h). The 4×6 game grid occupies l46/a00–a04 through l48/a20–a24 on the left.

#pragma once

#include "extended_keys.h"
#include "diagnostics.h"

// Left-hand game grid (home = F at row 2 col 4):
//   l46/a00–a04:  I Q W E R T
//   l47/a10–a14:  K A S D F G
//   l48/a20–a24:  M Z X C V B
// Left top (K40–K42): ESC, 1, 2. Thumb (k32–k34): LCTRL, LALT, SPACE

#define MIRYOKU_LAYER_GAME \
  &kp ESC, &kp N1, &kp N2, ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_SLOT3, \
  &none, &none, &none, &none, &none, ML_DIAG_K54_10, \
  &kp I, &kp Q, &kp W, &kp E, &kp R, &kp T, \
  &none, &none, &none, &none, &none, &none, \
  &kp K, &kp A, &kp S, &kp D, &kp F, &kp G, \
  &none, &none, &none, &none, &none, &none, \
  &kp M, &kp Z, &kp X, &kp C, &kp V, &kp B, \
  &none, &none, &none, &none, &none, &none, \
  U_NP, U_NP, &kp LCTRL, &kp LALT, &kp SPACE, &none, &none, &none, U_NP, U_NP

#define MIRYOKU_LAYER_SLOT3 \
  &none, &none, &none, ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_SLOT3, \
  &none, &none, &none, &none, &none, ML_DIAG_K54_11, \
  &none, U_NA, U_NA, U_NA, U_NA, U_NA, \
  &none, &none, &none, &none, &none, &none, \
  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, \
  &none, &none, &none, &none, &none, &none, \
  U_NA, U_NA, U_NA, U_NA, U_NA, U_NA, \
  &none, &none, &none, &none, &none, &none, \
  U_NP, U_NP, U_NA, U_NA, U_NA, &none, &none, &none, U_NP, U_NP

#define MIRYOKU_LAYERMAPPING_GAME  MIRYOKU_MAPPING
#define MIRYOKU_LAYERMAPPING_SLOT3 MIRYOKU_MAPPING
