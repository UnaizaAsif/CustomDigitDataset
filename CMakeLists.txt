cmake_minimum_required(VERSION 3.10)

# Set the project name and C++ standard
project(CustomDigitDataset)
set(CMAKE_CXX_STANDARD 17)

# Add executable for dataset creation
add_executable(CustomDigitDataset src/main.cpp)

# Add executable for dataset verification
add_executable(VerifyDataset src/verify.cpp)

# Find SFML package
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(CustomDigitDataset sfml-graphics)
