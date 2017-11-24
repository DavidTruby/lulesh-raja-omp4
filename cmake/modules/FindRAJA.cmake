# - Try to find RAJA

find_package(OpenMP REQUIRED)

set(RAJA_CXX_FEATURES cxx_auto_type cxx_constexpr cxx_generic_lambdas)

find_path(RAJA_INCLUDE_DIR RAJA/RAJA.hpp
  HINTS ${RAJA_ROOT}/include $ENV{RAJA_ROOT}/include)
find_library(RAJA_LIBRARY NAMES RAJA libRAJA
  HINTS ${RAJA_ROOT}/lib $ENV{RAJA_ROOT}/lib)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(RAJA DEFAULT_MSG RAJA_LIBRARY RAJA_INCLUDE_DIR)
mark_as_advanced(RAJA_LIBRARY RAJA_INCLUDE_DIR)

set(RAJA_LIBRARIES ${RAJA_LIBRARY})
set(RAJA_INCLUDE_DIRS ${RAJA_INCLUDE_DIR})

add_library(RAJA INTERFACE)
target_include_directories(RAJA SYSTEM INTERFACE ${RAJA_INCLUDE_DIRS})
#target_link_libraries(RAJA INTERFACE ${RAJA_LIBRARIES})
target_compile_features(RAJA INTERFACE ${RAJA_CXX_FEATURES})
#target_compile_options(RAJA INTERFACE ${OpenMP_CXX_FLAGS})
