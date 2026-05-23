// Bindings for Lily58 extended positions K40–K57.
//
// Physical layout (multi-layout mapping):
//   Left top row:     K40–K45  (K43–K45 = profile selectors on central half)
//   Right top row:    K49–K54  (K54 = split diagnostic digit per layer)
//   Left outer col:   K46–K48  (rows 1–3)
//   Right outer col:  K55–K57  (rows 1–3)
//
// Profile selectors on K43–K45 so the central (left) MCU can switch layouts
// without the right half connected. K40–K42 and K49–K53 are unused on Miryoku.
// Inner thumb XXX positions are intentionally left unassigned.

#pragma once

#include "layer_indices.h"

#define ML_SEL_MIRYOKU &to U_BASE
#define ML_SEL_GAME    &to U_GAME
#define ML_SEL_SLOT3   &to U_SLOT3

// Left top row: K40–K42 unused, K43–K45 profile selectors.
#define ML_MIRYOKU_L_TOP \
  &none, &none, &none, ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_SLOT3

// Right top row: K49–K53 unused; K54 set per layer (diagnostic).
#define ML_LAYOUT_SELECT_RIGHT \
  &none, &none, &none, &none, &none, U_NA

// Game left top row: K40–K42 utility keys, K43–K45 profile selectors.
#define ML_GAME_L_TOP \
  &kp ESC, &kp N1, &kp N2, ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_SLOT3
