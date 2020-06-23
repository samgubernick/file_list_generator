# CMakeList.txt : CMake project for file_list_generator, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("file_list_generator")

# Add source to this project's executable.
add_executable (file_list_generator "file_list_generator.cpp" )

target_compile_features(file_list_generator PRIVATE cxx_std_17)
# TODO: Add tests and install targets if needed.
