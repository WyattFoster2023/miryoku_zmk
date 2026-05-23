// Interleave Lily58 extended keys (K40–K57) with standard miryoku layer rows.
//
// Use "MIRYOKU_WRAP_MIRYOKU MIRYOKU_ALTERNATIVES_*" (no parentheses around the
// alternatives macro) so the 40 miryoku bindings expand as separate arguments.

#pragma once

#include "extended_keys.h"

// 58-key Lily58 matrix order (matches MIRYOKU_LAYOUTMAPPING_LILY58).
#define MIRYOKU_BIND_LILY58( \
  t40,t41,t42,t43,t44,t45, s49,s50,s51,s52,s53,s54, \
  l46, a00,a01,a02,a03,a04, a05,a06,a07,a08,a09, r55, \
  l47, a10,a11,a12,a13,a14, a15,a16,a17,a18,a19, r56, \
  l48, a20,a21,a22,a23,a24, a25,a26,a27,a28,a29, r57, \
  n30,n31, k32,k33,k34, k35,k36,k37, n38,n39 \
) \
  t40,t41,t42,t43,t44,t45, s49,s50,s51,s52,s53,s54, \
  l46,a00,a01,a02,a03,a04, a05,a06,a07,a08,a09,r55, \
  l47,a10,a11,a12,a13,a14, a15,a16,a17,a18,a19,r56, \
  l48,a20,a21,a22,a23,a24, a25,a26,a27,a28,a29,r57, \
  n30,n31,k32,k33,k34, k35,k36,k37,n38,n39

// 40 miryoku matrix + thumb bindings → 58-position Lily58 list.
#define MIRYOKU_WRAP_MIRYOKU( \
  a,b,c,d,e,f,g,h,i,j, \
  k,l,m,n,o,p,q,r,s,t, \
  u,v,w,x,y,z,a1,a2,a3,a4, \
  a5,a6,a7,a8,a9,a10,a11,a12,a13,a14 \
) \
  ML_MIRYOKU_L_TOP, \
  ML_LAYOUT_SELECT_RIGHT, \
  &none, a,b,c,d,e,f, g,h,i,j, &none, \
  &none, k,l,m,n,o,p, q,r,s,t, &none, \
  &none, u,v,w,x,y,z, a1,a2,a3,a4, &none, \
  a5,a6,a7,a8,a9,a10,a11,a12,a13,a14
