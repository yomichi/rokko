/*****************************************************************************
*
* Rokko: Integrated Interface for libraries of eigenvalue decomposition
*
* Copyright (C) 2013-2013 by Ryo IGARASHI <rigarash@issp.u-tokyo.ac.jp>
*
* Distributed under the Boost Software License, Version 1.0. (See accompanying
* file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
*
*****************************************************************************/

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#include <rokko/solver.hpp>

#define BOOST_TEST_MODULE test_solver
#ifndef BOOST_TEST_DYN_LINK
#include <boost/test/included/unit_test.hpp>
#else
#include <boost/test/unit_test.hpp>
#endif

BOOST_AUTO_TEST_CASE(test_solver) {
  boost::shared_ptr<rokko::solver_factory> instance(rokko::solver_factory::instance());
  BOOST_FOREACH(std::string name, instance->solver_names()) {
    rokko::solver solver(name);
    solver.initialize(boost::unit_test::framework::master_test_suite().argc,
      boost::unit_test::framework::master_test_suite().argv);
    solver.finalize();
  }
}