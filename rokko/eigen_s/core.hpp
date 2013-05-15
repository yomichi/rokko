#ifndef ROKKO_EIGEN_S_CORE_HPP
#define ROKKO_EIGEN_S_CORE_HPP

#include <rokko/eigen_s/eigen_s.hpp>
#include <rokko/eigen_s/diagonalize.hpp>

namespace rokko {
namespace eigen_s {

class solver {
public:
  void initialize(int& argc, char**& argv) { }

  void finalize() { }

  void optimized_grid_size() {}

  template<typename MATRIX_MAJOR>
  void optimized_matrix_size(distributed_matrix<MATRIX_MAJOR>& mat) {
    int n = mat.get_m_global();
    int nx = ((n-1) / mat.get_nprow() + 1);
    int i1 = 6, i2 = 16 * 4, i3 = 16 * 4 * 2, nm;
    CSTAB_get_optdim(nx, i1, i2, i3, nm);  // return an optimized leading dimension of local block-cyclic matrix to nm.
    //int para_int = 0;   eigen_free_wrapper(para_int);

    int NB = 64 + 32;
    int nmz = ((n-1) / mat.get_nprow() + 1);
    nmz = ((nmz-1) / NB + 1) * NB + 1;
    int nmw = ((n-1) / mat.get_npcol() + 1);
    nmw = ((nmw-1) / NB + 1) * NB + 1;
    std::cout << "nm=" << nm << std::endl;
    std::cout << "nmz=" << nmz << std::endl;
    std::cout << "nmw=" << nmw << std::endl;
    mat.set_lld(nm);
    mat.set_length_array(std::max(nmz,nm) * nmw);
    mat.set_block_size(1, 1);
    int m_local = mat.calculate_row_size();
    int n_local = mat.calculate_col_size();
    mat.set_local_size(m_local, n_local);
  }

  template<typename MATRIX_MAJOR>
  void diagonalize(rokko::distributed_matrix<MATRIX_MAJOR>& mat, Eigen::VectorXd& eigvals,
                   rokko::distributed_matrix<MATRIX_MAJOR>& eigvecs) {
    rokko::eigen_s::diagonalize(mat, eigvals, eigvecs);
  }
};

} // namespace eigen_s
} // namespace rokko

#endif // ROKKO_EIGEN_S_CORE_HPP

