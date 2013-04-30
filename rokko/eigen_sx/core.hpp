#ifndef ROKKO_EIGEN_SX_CORE_HPP
#define ROKKO_EIGEN_SX_CORE_HPP

#include <rokko/eigen_sx/eigen_sx.hpp>

#include <boost/noncopyable.hpp>

#include <rokko/core.hpp>

namespace rokko {

template<>
void Initialize<rokko::eigen_sx>(int& argc, char**& argv)
{
}

template<>
void Finalize<rokko::eigen_sx>()
{
}

} // namespace rokko

#endif // ROKKO_EIGEN_SX_CORE_HPP

