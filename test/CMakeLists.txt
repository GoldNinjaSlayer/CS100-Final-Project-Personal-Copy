CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
ADD_SUBDIRECTORY(googletest)
include_directories(
  ${CMAKE_SOURCE_DIR}/googletest/include/
  ${CMAKE_SOURCE_DIR}/googlemock/include/
)
ADD_EXECUTABLE(test
    test.cpp

)

TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)