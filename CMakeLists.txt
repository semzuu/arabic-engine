cmake_minimum_required(VERSION 3.10)
project(arabic-engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
include_directories(include)

file(GLOB sources
	"src/*.cpp"
)

add_executable(arabic-engine ${sources})

enable_testing()

add_executable(test_tree tests/test_tree.cpp src/tree.cpp)
add_test(NAME TreeImplTest COMMAND test_tree)

add_executable(test_hashtable tests/test_hashtable.cpp src/HashTable.cpp)
add_test(NAME HashTest COMMAND test_hashtable)