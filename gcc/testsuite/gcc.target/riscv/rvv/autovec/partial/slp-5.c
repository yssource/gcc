/* { dg-do compile } */
/* { dg-additional-options "-march=rv32gcv -mabi=ilp32d --param riscv-autovec-preference=scalable -fdump-tree-optimized-details" } */

#include <stdint-gcc.h>

void __attribute__ ((noipa))
f (int8_t *restrict a, int8_t *restrict b, int n)
{
  for (int i = 0; i < n; ++i)
    {
      a[i * 8 + 0] = b[i * 8 + 1] + 1;
      a[i * 8 + 1] = b[i * 8 + 7] + 2;
      a[i * 8 + 2] = b[i * 8 + 4] + 3;
      a[i * 8 + 3] = b[i * 8 + 8] + 4;
      a[i * 8 + 4] = b[i * 8 + 1] + 5;
      a[i * 8 + 5] = b[i * 8 + 7] + 6;
      a[i * 8 + 6] = b[i * 8 + 4] + 7;
      a[i * 8 + 7] = b[i * 8 + 8] + 8;
    }
}

/* FIXME: Since we don't have VECT cost model yet, LOAD_LANES/STORE_LANES are chosen instead of SLP.  */
/* { dg-final { scan-tree-dump-times "\.VEC_PERM" 1 "optimized" { xfail *-*-* } } } */
