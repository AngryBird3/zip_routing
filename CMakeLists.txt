cmake_minimum_required(VERSION 4.0)
project(traveling_zip)

set(CMAKE_CXX_STANDARD 20)

add_library(traveling_zip_lib
        cpp20/src/hospital.cpp
        cpp20/src/order.cpp
        cpp20/src/priority_based_assignment_policy.cpp
        cpp20/src/euclidean_spatial_model.cpp
        cpp20/src/util.cpp
        cpp20/src/zip_scheduler.cpp
        cpp20/src/zip_system_factory.cpp
        cpp20/src/zip_system_state_actor.cpp
        cpp20/src/trivial_routing_policy.cpp)
target_include_directories(traveling_zip_lib PUBLIC cpp20/include)

add_executable(traveling_zip cpp20/main.cpp)
target_include_directories(traveling_zip PUBLIC cpp20/include)
target_link_libraries(traveling_zip traveling_zip_lib)

#add_subdirectory(cpp20/test)

