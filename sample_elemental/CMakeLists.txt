set(TESTS_ELEMENTAL diagonalize_elemental)
# diagonalize_elemental_noeigvecs)
#SymmetricEig)
# HermitianEigFromSequential Constructors)
#SymmetricEig_iterator)
#HermitianEig HermitianEigFromSequential


if( DEFINED ELEMENTAL_LIBRARIES AND ELEMENTAL_INCLUDE_DIRS )
  include_directories(${ELEMENTAL_INCLUDE_DIRS})
  foreach(name ${TESTS_ELEMENTAL})
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} rokko ${ELEMENTAL_LIBRARIES})
    #add_alps_test(${name})
  endforeach(name)
endif( DEFINED ELEMENTAL_LIBRARIES AND ELEMENTAL_INCLUDE_DIRS )
