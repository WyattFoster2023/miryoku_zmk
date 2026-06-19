// Copyright 2022 Manna Harbour
// https://github.com/manna-harbour/miryoku

#if !defined (MIRYOKU_LAYOUTMAPPING_LILY58)

#define XXX &none

#if defined(MIRYOKU_MULTI_LAYOUT)

// Extended Lily58 positions (K40–K57): outer column, top row, and inner column
// keys. Inner thumb XXX positions stay unassigned. See multi_layout/extended_keys.h.
#define MIRYOKU_LAYOUTMAPPING_LILY58( \
     K40, K41, K42, K43, K44, K45,                K49, K50, K51, K52, K53, K54, \
     K46, K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, K55, \
     K47, K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, K56, \
     K48, K20, K21, K22, K23, K24, N38, N39,      K25, K26, K27, K28, K29, K57, \
     N30, N31, K32, K33, K34,                K35, K36, K37 \
) \
K40  K41  K42  K43  K44  K45                    K49  K50  K51  K52  K53  K54 \
K46  K00  K01  K02  K03  K04                    K05  K06  K07  K08  K09  K55 \
K47  K10  K11  K12  K13  K14                    K15  K16  K17  K18  K19  K56 \
K48  K20  K21  K22  K23  K24  XXX       XXX  K25  K26  K27  K28  K29  K57 \
               K32  K33  K34  XXX       XXX  K35  K36  K37

#define MIRYOKU_KLUDGE_THUMBCOMBOS_LEFT 53 54
#define MIRYOKU_KLUDGE_THUMBCOMBOS_RIGHT 56 57

#else

// Legacy 38-key mapping (no extended positions) for builds without MIRYOKU_MULTI_LAYOUT.
#define MIRYOKU_LAYOUTMAPPING_LILY58( \
     K00, K01, K02, K03, K04,                K05, K06, K07, K08, K09, \
     K10, K11, K12, K13, K14,                K15, K16, K17, K18, K19, \
     K20, K21, K22, K23, K24,                K25, K26, K27, K28, K29, \
     N30, N31, K32, K33, K34,                K35, K36, K37, N38, N39 \
) \
XXX  XXX  XXX  XXX  XXX  XXX                 XXX  XXX  XXX  XXX  XXX  XXX \
XXX  K00  K01  K02  K03  K04                 K05  K06  K07  K08  K09  XXX \
XXX  K10  K11  K12  K13  K14                 K15  K16  K17  K18  K19  XXX \
XXX  K20  K21  K22  K23  K24  XXX       XXX  K25  K26  K27  K28  K29  XXX \
               K32  K33  K34  XXX       XXX  K35  K36  K37

#define MIRYOKU_KLUDGE_THUMBCOMBOS_LEFT 52 53
#define MIRYOKU_KLUDGE_THUMBCOMBOS_RIGHT 54 55

#endif

#endif

#define MIRYOKU_MAPPING MIRYOKU_LAYOUTMAPPING_LILY58
