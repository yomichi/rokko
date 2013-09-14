#ifndef ROKKO_EIGEN3_DIAGONALIZE_H
#define ROKKO_EIGEN3_DIAGONALIZE_H

#include "rokko/localized_matrix.hpp"
#include "rokko/localized_vector.hpp"

#include <Eigen/Dense>

namespace rokko {
namespace eigen3 {

template<typename MATRIX_MAJOR>
int diagonalize(localized_matrix<MATRIX_MAJOR>& mat, localized_vector& eigvals,
                localized_matrix<MATRIX_MAJOR>& eigvecs, timer& timer_in) {
  int info;

  int dim = mat.rows();

  // eigenvalue decomposition
  timer_in.start(1);
  Eigen::SelfAdjointEigenSolver<Eigen::MatrixXd>  ES(mat);
  eigvals = ES.eigenvalues();
  eigvecs = ES.eigenvectors();
  //info = LAPACKE_dsyev(LAPACK_COL_MAJOR, 'V', 'U', dim, &mat(0,0), dim, eigvals);
  timer_in.stop(1);

  return info;
}

} // namespace eigen3
} // namespace rokko

#endif // ROKKO_EIGEN3_DIAGONALIZE_H