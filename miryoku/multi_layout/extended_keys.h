// Bindings for Lily58 extended positions K40–K57.
//
// Physical layout (multi-layout mapping):
//   Left top row:     K40–K45
//   Right top row:    K49–K54  (K49–K51 = layout selectors)
//   Left outer col:   K46–K48  (rows 1–3)
//   Right outer col:  K55–K57  (rows 1–3)
//
// Miryoku mode maps spare L-keys to F13–F24 for remapping in software.
// Inner thumb XXX positions are intentionally left unassigned.

#pragma once

#include "layer_indices.h"

#define ML_SEL_MIRYOKU &to U_BASE
#define ML_SEL_GAME    &to U_GAME
#define ML_SEL_EMPTY   &to U_EMPTY

// Layout selector row (right half top row, left to right).
#define ML_LAYOUT_SELECT \
  ML_SEL_MIRYOKU, ML_SEL_GAME, ML_SEL_EMPTY, U_NA, U_NA, U_NA

// Obscure HID keys for unused L-keys in miryoku (remap in software).
#define ML_MIRYOKU_L_TOP \
  &kp F13, &kp F14, &kp F15, &kp F16, &kp F17, &kp F18
