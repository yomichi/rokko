#ifndef ROKKO_SCALAPACK_DISTRIBUTED_MATRIX_HPP
#define ROKKO_SCALAPACK_DISTRIBUTED_MATRIX_HPP

#include <cstdlib>
//#include <mpi.h>

#include <rokko/scalapack/grid.hpp>
#include <rokko/scalapack/scalapack.hpp>

//#include <rokko/distributed_matrix.hpp>

namespace rokko {

template<typename T> //, typename GRID_MAJOR = rokko::R>
class distributed_matrix
{
};


template<> //, typename GRID_MAJOR>
class actual_distributed_matrix<rokko::scalapack> //, GRID_MAJOR>
{
public:
  template <typename GRID_MAJOR = rokko::grid_row_major>
  actual_distributed_matrix(const distributed_matrix& mat, const actual_grid& g_in)
    : m_global(m_global), n_global(n_global), myrank(g_in.myrank), nprocs(g_in.nprocs), myrow(g_in.myrow), mycol(g_in.mycol), nprow(g_in.nprow), npcol(g_in.npcol), ictxt(g_in.ictxt), g(g_in)
  {
  }

  ~distributed_matrix()
  {
    //std::cout << "Destructor ~Distributed_Matrix()" << std::endl;
    delete[] array;
    array = NULL;
  }

  double* get_array()
  {
    return array;
  }

  int get_row_size() const
  {
    const int local_offset_block = global_i / mb;
    return (local_offset_block - myrow) / nprow * mb + global_i % mb;
  }

  int get_col_size() const
  {
    const int local_offset_block = global_j / nb;
    return (local_offset_block - mycol) / npcol * nb + global_j % nb;
  }

  int translate_l2g_row(const int& local_i) const
  {
    return (myrow * mb) + local_i + (local_i / mb) * mb * (nprow - 1);
  }

  int translate_l2g_col(const int& local_j) const
  {
    return (mycol * nb) + local_j + (local_j / nb) * nb * (npcol - 1);
  }

  int translate_g2l_row(const int& global_i) const
  {
    const int local_offset_block = global_i / mb;
    return (local_offset_block - myrow) / nprow * mb + global_i % mb;
  }

  int translate_g2l_col(const int& global_j) const
  {
    const int local_offset_block = global_j / nb;
    return (local_offset_block - mycol) / npcol * nb + global_j % nb;
  }

  bool is_gindex_myrow(const int& global_i) const
  {
    int local_offset_block = global_i / mb;
    return (local_offset_block % nprow) == myrow;
  }

  bool is_gindex_mycol(const int& global_j) const
  {
    int local_offset_block = global_j / nb;
    return (local_offset_block % npcol) == mycol;
  }

  void set_local(int local_i, int local_j, double value)
  {
    array[local_j * m_local + local_i] = value;
  }

  void set_global(int global_i, int global_j, double value)
  {
    if ((is_gindex_myrow(global_i)) && (is_gindex_mycol(global_j)))
      set_local(translate_g2l_row(global_i), translate_g2l_col(global_j), value);
  }

  void calculate_grid(int proc_rank, int& proc_row, int& proc_col) const
  {
    proc_row = proc_rank / npcol;
    proc_col = proc_rank % npcol;
  }

  int calculate_grid_row(int proc_rank) const
  {
    return proc_rank / npcol;
  }

  int calculate_grid_col(int proc_rank) const
  {
    return proc_rank % npcol;
  }

  void print() const
  {
    /* each proc prints it's local_array out, in order */
    for (int proc=0; proc<nprocs; ++proc) {
      if (proc == myrank) {
	printf("Rank = %d  myrow=%d mycol=%d\n", myrank, myrow, mycol);
	printf("Local Matrix:\n");
	for (int ii=0; ii<m_local; ++ii) {
	  for (int jj=0; jj<n_local; ++jj) {
	    printf("%3.2f ",array[jj * m_local + ii]);
	  }
	  printf("\n");
	}
	printf("\n");
      }
      MPI_Barrier(MPI_COMM_WORLD);
    }
}

  int m_global, n_global;
  double* array;
  int mb, nb;
  int m_local, n_local;
  // variables of class Grid
  int myrank, nprocs;
  int myrow, mycol;
  int nprow, npcol;

  //template<typename GRID_MAJOR>
  //const
  const rokko::grid_base& g;
  //grid<rokko::scalapack>& g;
  //void* g;

  int lld;
  int ictxt;
  //typedef GRID_MAJOR grid_major_type;

private:
  int info;
};


void print_matrix(const rokko::distributed_matrix<rokko::scalapack>& mat)
{
  // each proc prints it's local_array out, in order
  for (int proc=0; proc<mat.nprocs; ++proc) {
    if (proc == mat.myrank) {
      printf("Rank = %d  myrow=%d mycol=%d\n", mat.myrank, mat.myrow, mat.mycol);
      printf("Local Matrix:\n");
      for (int ii=0; ii<mat.m_local; ++ii) {
	for (int jj=0; jj<mat.n_local; ++jj) {
	  printf("%3.2f ", mat.array[jj * mat.m_local + ii]);
	}
	printf("\n");
      }
      printf("\n");
    }
    MPI_Barrier(MPI_COMM_WORLD);
  }
}

} // namespace rokko

#endif // ROKKO_SCALAPACK_DISTRIBUTED_MATRIX_HPP

