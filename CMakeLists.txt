cmake_minimum_required(VERSION 3.13)
project(seminar_http CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_BEAST
    OFF
    CACHE BOOL "Enable Boost.Beast and its example")
set(ENABLE_CPR
    ON
    CACHE BOOL "Enable cpr and its example")

if(ENABLE_BEAST)
  add_subdirectory(external/beast EXCLUDE_FROM_ALL)

  find_package(Boost COMPONENTS system)
  find_package(Threads)

  add_executable(client http_client_sync.cpp)
  target_link_libraries(client PUBLIC Boost::system Threads::Threads)
  target_include_directories(client PUBLIC external/beast/include)
endif(ENABLE_BEAST)

include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY
    https://github.com/ArthurSonzogni/nlohmann_json_cmake_fetchcontent.git
  GIT_TAG v3.7.3)

FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
  add_subdirectory(${json_SOURCE_DIR} ${json_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

if(ENABLE_CPR)
  add_subdirectory(external/cpr EXCLUDE_FROM_ALL)
  add_executable(client2 client2.cpp)
  target_link_libraries(client2 PUBLIC ${CPR_LIBRARIES})
  target_link_libraries(client2 PRIVATE nlohmann_json::nlohmann_json)
endif(ENABLE_CPR)
