/* tremquo -- test file for mpfr_remquo and mpfr_remainder

Copyright 2007, 2008 Free Software Foundation, Inc.
Contributed by the Arenaire and Cacao projects, INRIA.

This file is part of the MPFR Library.

The MPFR Library is free software; you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version.

The MPFR Library is distributed in the hope that it will be useful, but
WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public
License for more details.

You should have received a copy of the GNU Lesser General Public License
along with the MPFR Library; see the file COPYING.LIB.  If not, write to
the Free Software Foundation, Inc., 51 Franklin St, Fifth Floor, Boston,
MA 02110-1301, USA. */

#include <stdio.h>
#include <stdlib.h>

#include "mpfr-test.h"

int
main (int argc, char *argv[])
{
  mpfr_t x, y, r;
  long q[1];

  if (argc == 3) /* usage: tremquo x y (rnd=GMP_RNDN implicit) */
    {
      mpfr_init2 (x, BITS_PER_MP_LIMB);
      mpfr_init2 (y, BITS_PER_MP_LIMB);
      mpfr_init2 (r, BITS_PER_MP_LIMB);
      mpfr_set_str (x, argv[1], 10, GMP_RNDN);
      mpfr_set_str (y, argv[2], 10, GMP_RNDN);
      mpfr_remquo (r, q, x, y, GMP_RNDN);
      printf ("r=");
      mpfr_out_str (stdout, 10, 0, r, GMP_RNDN);
      printf (" q=%ld\n", q[0]);
      mpfr_clear (x);
      mpfr_clear (y);
      mpfr_clear (r);
      return 0;
    }

  tests_start_mpfr ();

  mpfr_init (x);
  mpfr_init (y);
  mpfr_init (r);

  /* special values */
  mpfr_set_nan (x);
  mpfr_set_ui (y, 1, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN(mpfr_nan_p (r));

  mpfr_set_ui (x, 1, GMP_RNDN);
  mpfr_set_nan (y);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN(mpfr_nan_p (r));

  mpfr_set_inf (x, 1); /* +Inf */
  mpfr_set_ui (y, 1, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_nan_p (r));

  mpfr_set_inf (x, 1); /* +Inf */
  mpfr_set_ui (y, 0, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_nan_p (r));

  mpfr_set_inf (x, 1); /* +Inf */
  mpfr_set_inf (y, 1);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_nan_p (r));

  mpfr_set_ui (x, 0, GMP_RNDN);
  mpfr_set_inf (y, 1);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui (r, 0) == 0 && MPFR_IS_POS (r));
  MPFR_ASSERTN (q[0] == (long) 0);

  mpfr_set_ui (x, 0, GMP_RNDN);
  mpfr_neg (x, x, GMP_RNDN); /* -0 */
  mpfr_set_inf (y, 1);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui (r, 0) == 0 && MPFR_IS_NEG (r));
  MPFR_ASSERTN (q[0] == (long) 0);

  mpfr_set_ui (x, 17, GMP_RNDN);
  mpfr_set_inf (y, 1);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp (r, x) == 0);
  MPFR_ASSERTN (q[0] == (long) 0);

  mpfr_set_ui (x, 17, GMP_RNDN);
  mpfr_set_ui (y, 0, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_nan_p (r));

  mpfr_set_ui (x, 0, GMP_RNDN);
  mpfr_set_ui (y, 17, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui (r, 0) == 0 && MPFR_IS_POS (r));
  MPFR_ASSERTN (q[0] == (long) 0);

  mpfr_set_ui (x, 0, GMP_RNDN);
  mpfr_neg (x, x, GMP_RNDN);
  mpfr_set_ui (y, 17, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui (r, 0) == 0 && MPFR_IS_NEG (r));
  MPFR_ASSERTN (q[0] == (long) 0);

  mpfr_set_prec (x, 53);
  mpfr_set_prec (y, 53);

  /* check four possible sign combinations */
  mpfr_set_ui (x, 42, GMP_RNDN);
  mpfr_set_ui (y, 17, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui (r, 8) == 0);
  MPFR_ASSERTN (q[0] == (long) 2);
  mpfr_set_si (x, -42, GMP_RNDN);
  mpfr_set_ui (y, 17, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_si (r, -8) == 0);
  MPFR_ASSERTN (q[0] == (long) -2);
  mpfr_set_si (x, -42, GMP_RNDN);
  mpfr_set_si (y, -17, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_si (r, -8) == 0);
  MPFR_ASSERTN (q[0] == (long) 2);
  mpfr_set_ui (x, 42, GMP_RNDN);
  mpfr_set_si (y, -17, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui (r, 8) == 0);
  MPFR_ASSERTN (q[0] == (long) -2);

  mpfr_set_prec (x, 100);
  mpfr_set_prec (y, 50);
  mpfr_set_ui (x, 42, GMP_RNDN);
  mpfr_nextabove (x); /* 42 + 2^(-94) */
  mpfr_set_ui (y, 21, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui_2exp (r, 1, -94) == 0);
  MPFR_ASSERTN (q[0] == (long) 2);

  mpfr_set_prec (x, 50);
  mpfr_set_prec (y, 100);
  mpfr_set_ui (x, 42, GMP_RNDN);
  mpfr_nextabove (x); /* 42 + 2^(-44) */
  mpfr_set_ui (y, 21, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_ui_2exp (r, 1, -44) == 0);
  MPFR_ASSERTN (q[0] == (long) 2);

  mpfr_set_prec (x, 100);
  mpfr_set_prec (y, 50);
  mpfr_set_ui (x, 42, GMP_RNDN);
  mpfr_set_ui (y, 21, GMP_RNDN);
  mpfr_nextabove (y); /* 21 + 2^(-45) */
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  /* r should be 42 - 2*(21 + 2^(-45)) = -2^(-44) */
  MPFR_ASSERTN (mpfr_cmp_si_2exp (r, -1, -44) == 0);
  MPFR_ASSERTN (q[0] == (long) 2);

  mpfr_set_prec (x, 50);
  mpfr_set_prec (y, 100);
  mpfr_set_ui (x, 42, GMP_RNDN);
  mpfr_set_ui (y, 21, GMP_RNDN);
  mpfr_nextabove (y); /* 21 + 2^(-95) */
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  /* r should be 42 - 2*(21 + 2^(-95)) = -2^(-94) */
  MPFR_ASSERTN (mpfr_cmp_si_2exp (r, -1, -94) == 0);
  MPFR_ASSERTN (q[0] == (long) 2);

  /* exercise large quotient */
  mpfr_set_ui_2exp (x, 1, 65, GMP_RNDN);
  mpfr_set_ui (y, 1, GMP_RNDN);
  /* quotient is 2^65 */
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_si (r, 0) == 0);
  MPFR_ASSERTN (q[0] % 1073741824L == 0L);

  /* another large quotient */
  mpfr_set_prec (x, 65);
  mpfr_set_prec (y, 65);
  mpfr_const_pi (x, GMP_RNDN);
  mpfr_mul_2exp (x, x, 63, GMP_RNDN);
  mpfr_const_log2 (y, GMP_RNDN);
  mpfr_set_prec (r, 10);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  /* q should be 41803643793084085130, r should be 605/2048 */
  MPFR_ASSERTN (mpfr_cmp_ui_2exp (r, 605, -11) == 0);
  MPFR_ASSERTN ((q[0] > 0) && ((q[0] % 1073741824L) == 733836170L));

  /* check cases where quotient is 1.5 +/- eps */
  mpfr_set_prec (x, 65);
  mpfr_set_prec (y, 65);
  mpfr_set_prec (r, 63);
  mpfr_set_ui (x, 3, GMP_RNDN);
  mpfr_set_ui (y, 2, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  /* x/y = 1.5, quotient should be 2 (even rule), remainder should be -1 */
  MPFR_ASSERTN (mpfr_cmp_si (r, -1) == 0);
  MPFR_ASSERTN (q[0] == 2L);
  mpfr_set_ui (x, 3, GMP_RNDN);
  mpfr_nextabove (x); /* 3 + 2^(-63) */
  mpfr_set_ui (y, 2, GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  /* x/y = 1.5 + 2^(-64), quo should be 2, r should be -1 + 2^(-63) */
  MPFR_ASSERTN (mpfr_add_ui (r, r, 1, GMP_RNDN) == 0);
  MPFR_ASSERTN (mpfr_cmp_ui_2exp (r, 1, -63) == 0);
  MPFR_ASSERTN (q[0] == 2L);
  mpfr_set_ui (x, 3, GMP_RNDN);
  mpfr_set_ui (y, 2, GMP_RNDN);
  mpfr_nextabove (y); /* 2 + 2^(-63) */
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  /* x/y = 1.5 - eps, quo should be 1, r should be 1 - 2^(-63) */
  MPFR_ASSERTN (mpfr_sub_ui (r, r, 1, GMP_RNDN) == 0);
  MPFR_ASSERTN (mpfr_cmp_si_2exp (r, -1, -63) == 0);
  MPFR_ASSERTN (q[0] == 1L);

  /* bug founds by Kaveh Ghazi, 3 May 2007 */
  mpfr_set_ui (x, 2, GMP_RNDN);
  mpfr_set_ui (y, 3, GMP_RNDN);
  mpfr_remainder (r, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_si (r, -1) == 0);

  mpfr_set_si (x, -1, GMP_RNDN);
  mpfr_set_ui (y, 1, GMP_RNDN);
  mpfr_remainder (r, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_si (r, 0) == 0 && MPFR_SIGN (r) < 0);

  /* check argument reuse */
  mpfr_set_si (x, -1, GMP_RNDN);
  mpfr_set_ui (y, 1, GMP_RNDN);
  mpfr_remainder (x, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_cmp_si (x, 0) == 0 && MPFR_SIGN (x) < 0);

  mpfr_set_ui_2exp (x, 1, mpfr_get_emax () - 1, GMP_RNDN);
  mpfr_set_ui_2exp (y, 1, mpfr_get_emin (), GMP_RNDN);
  mpfr_remquo (r, q, x, y, GMP_RNDN);
  MPFR_ASSERTN (mpfr_zero_p (r) && MPFR_SIGN (r) > 0);
  MPFR_ASSERTN (q[0] == 0);

  mpfr_clear (x);
  mpfr_clear (y);
  mpfr_clear (r);

  tests_end_mpfr ();

  return 0;
}
