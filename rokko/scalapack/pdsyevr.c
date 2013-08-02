/*****************************************************************************
*
* Rokko: Integrated Interface for libraries of eigenvalue decomposition
*
* Copyright (C) 2012-2013 by Tatsuya Sakashita <t-sakashita@issp.u-tokyo.ac.jp>,
*                            Synge Todo <wistaria@comp-phys.org>
*
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*
*****************************************************************************/

#include "rokko/scalapack.h"

void ROKKO_pdsyevr(char jobz, char uplo, int n,
                   double* A, int ia, int ja, const int* descA,
                   double vl, double vu, int il, int iu,
                   int* m, int* nz, double* w,
                   double* Z, int iz, int jz, const int* descZ,
                   double* work, int lwork, int* iwork, int liwork, int* info) {
  pdsyevr_(&jobz, &uplo, &n, A, &ia, &ja, descA, &vl, &vu, &il, &iu, m, nz, w,
           Z, &iz, &jz, descZ, work, &lwork, iwork, &liwork, info);
}