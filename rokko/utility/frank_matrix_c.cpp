/*****************************************************************************
*
* Rokko: Integrated Interface for libraries of eigenvalue decomposition
*
* Copyright (C) 2012-2013 by Tatsuya Sakashita <t-sakashita@issp.u-tokyo.ac.jp>,
*                            Synge Todo <wistaria@comp-phys.org>,
*                            Tsuyoshi Okubo <t-okubo@issp.u-tokyo.ac.jp>
*
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*
*****************************************************************************/

#include <rokko/utility/frank_matrix.hpp>
#include <rokko/utility/frank_matrix_c.h>

void rokko_frank_matrix_generate_distributed_matrix(rokko_distributed_matrix* matrix) {
  if (matrix->major == rokko_matrix_col_major)
    rokko::frank_matrix::generate(
      *static_cast<rokko::distributed_matrix<rokko::matrix_col_major>*>(matrix->ptr));
  else
    rokko::frank_matrix::generate(
      *static_cast<rokko::distributed_matrix<rokko::matrix_row_major>*>(matrix->ptr));
}

void rokko_frank_matrix_generate_localized_matrix(rokko_localized_matrix* matrix) {
  if (matrix->major == rokko_matrix_col_major)
    rokko::frank_matrix::generate(
      *static_cast<rokko::localized_matrix<rokko::matrix_col_major>*>(matrix->ptr));
  else
    rokko::frank_matrix::generate(
      *static_cast<rokko::localized_matrix<rokko::matrix_row_major>*>(matrix->ptr));
}