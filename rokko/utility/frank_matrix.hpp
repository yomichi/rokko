#ifndef ROKKO_UTILITY_FRANK_MATRIX_HPP
#define ROKKO_uTILITY_FRANK_MATRIX_HPP

#include <rokko/distributed_matrix.hpp>

namespace rokko {

template<typename MATRIX_MAJOR>
void generate_frank_matrix(rokko::distributed_matrix<MATRIX_MAJOR>& mat)
{
  for(int local_i=0; local_i<mat.m_local; ++local_i) {
    for(int local_j=0; local_j<mat.n_local; ++local_j) {
      int global_i = mat.translate_l2g_row(local_i);
      int global_j = mat.translate_l2g_col(local_j);
      mat.set_local(local_i, local_j, mat.m_global - std::max(global_i, global_j) );
    }
  }
}

template<typename MATRIX_MAJOR>
void generate_frank_matrix_global(rokko::distributed_matrix<MATRIX_MAJOR>& mat)
{
  for(int global_i=0; global_i<mat.m_global; ++global_i) {
    for(int global_j=0; global_j<mat.n_global; ++global_j) {
      mat.set_global(global_i, global_j, mat.m_global - std::max(global_i, global_j) );
    }
  }
}

} // namespace rokko

#endif // ROKKO_UTILITY_FRANK_MATRIX_HPP
