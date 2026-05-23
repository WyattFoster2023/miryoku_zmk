// K54 (right top row, outermost) emits a digit 1–9,0,A,B per ZMK layer index
// so you can confirm split connectivity: central half types letters, K54 types
// the layer's diagnostic number when the right half is connected.

#pragma once

// Layer index → number key (see layer_list.h U_* constants).
#define ML_DIAG_K54_0  &kp N1
#define ML_DIAG_K54_1  &kp N2
#define ML_DIAG_K54_2  &kp N3
#define ML_DIAG_K54_3  &kp N4
#define ML_DIAG_K54_4  &kp N5
#define ML_DIAG_K54_5  &kp N6
#define ML_DIAG_K54_6  &kp N7
#define ML_DIAG_K54_7  &kp N8
#define ML_DIAG_K54_8  &kp N9
#define ML_DIAG_K54_9  &kp N0
#define ML_DIAG_K54_10 &kp A
#define ML_DIAG_K54_11 &kp B
