CMAKE_MINIMUM_REQUIRED(VERSION 3.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

ADD_SUBDIRECTORY(googletest)
include_directories(
  ${CMAKE_SOURCE_DIR}/googletest/googletest/include/
  ${CMAKE_SOURCE_DIR}/googletst/googlemock/include/
)
ADD_EXECUTABLE(test
    test.cpp
    

)
find_package(SDL2 REQUIRED)
target_link_libraries(test SDL2::SDL2)


TARGET_LINK_LIBRARIES(test gtest)
TARGET_COMPILE_DEFINITIONS(test PRIVATE gtest_disable_pthreads=ON)