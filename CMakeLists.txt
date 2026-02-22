cmake_minimum_required(VERSION 3.10)
project(arabic-engine LANGUAGES CXX)
include(FetchContent)

set(CMAKE_CXX_STANDARD 17)

FetchContent_Declare(
  webview
  GIT_REPOSITORY https://github.com/webview/webview.git
  GIT_TAG 0.12.0
)
FetchContent_MakeAvailable(webview)

include_directories(include)

file(GLOB sources
	"src/*.cpp"
)

add_executable(arabic-engine ${sources})
set(ASSETS_DIR "${CMAKE_SOURCE_DIR}/assets/web")
target_compile_definitions(arabic-engine PRIVATE ASSETS_DIR=\"${ASSETS_DIR}\")
target_link_libraries(arabic-engine PRIVATE webview::core)
if (APPLE)
  find_library(COCOA_FRAMEWORK Cocoa)
  target_link_libraries(arabic-engine PRIVATE ${COCOA_FRAMEWORK})
endif()

enable_testing()

add_executable(test_hashtable 
	tests/test_hashtable.cpp 
	src/HashTable.cpp)
add_executable(test_engine
	tests/test_engine.cpp 
	src/MorphEngine.cpp 
	src/Tree.cpp
	src/HashTable.cpp
)
add_executable(test_tree 
	tests/test_tree.cpp 
	src/Tree.cpp)

add_test(NAME EngineTest COMMAND test_engine)
add_test(NAME HashTest COMMAND test_hashtable)
add_test(NAME TreeImplTest COMMAND test_tree)
