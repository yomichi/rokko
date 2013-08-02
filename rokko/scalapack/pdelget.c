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

void ROKKO_pdelget(char scope, char top, double* alpha,
                   const double* A, int ia, int ja, const int* descA) {
  pdelget_(&scope, &top, alpha, A, &ia, &ja, descA);
}