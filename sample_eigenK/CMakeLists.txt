if( DEFINED EIGEN_S_LIB AND EIGEN_S_INC )
  message(STATUS "Display: EIGEN_S_LIB= ${EIGEN_S_LIB}")
  separate_arguments(EIGEN_S_LIB)
  set(TESTS2 diagonalize_eigen_s)

  foreach(name ${TESTS2})
    include_directories(${name} ${EIGEN_S_INC})
    add_executable(${name} eigen_s_wrap.f  ${name}.cpp)
    target_link_libraries(${name} rokko ${EIGEN_S_LIB})

  endforeach(name)
endif()


if( DEFINED EIGEN_SX_LIB AND EIGEN_SX_INC )
  message(STATUS "Display: EIGEN_SX_LIB= ${EIGEN_SX_LIB}")
  separate_arguments(EIGEN_SX_LIB)
  set(TESTS2 diagonalize_eigen_sx)

  foreach(name ${TESTS2})
    include_directories(${name} ${EIGEN_SX_INC})
    add_executable(${name} eigen_sx_wrap.f  ${name}.cpp)
    target_link_libraries(${name} rokko ${EIGEN_SX_LIB})
  endforeach(name)
endif()
