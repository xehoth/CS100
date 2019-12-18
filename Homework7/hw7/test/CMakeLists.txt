include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(testIO test1.cpp)
target_link_libraries(testIO imagefiltering)

add_executable(runfilters test2.cpp)
target_link_libraries(runfilters imagefiltering)

find_package(Threads REQUIRED)
add_executable(runfiltersTh test3.cpp)
target_link_libraries(runfiltersTh imagefiltering Threads::Threads)
