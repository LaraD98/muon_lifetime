cmake_minimum_required(VERSION 3.10)
project(muon_lifetime)

set(CMAKE_BUILD_TYPE Debug)
set(PROJECT_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(PROJECT_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(PROJECT_CONFIG_DIR "${CMAKE_CURRENT_SOURCE_DIR}/config")
set(PROJECT_BINARY_DIR "${CMAKE_CURRENT_BINARY_DIR}/bin")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})

include(cmake/version.cmake)

configure_file("${PROJECT_CONFIG_DIR}/global.h.in"
               "${PROJECT_INCLUDE_DIR}/global.h")

configure_file("${PROJECT_CONFIG_DIR}/run"
               "${PROJECT_BINARY_DIR}/run")
find_package(Geant4 REQUIRED)


set(Geant4_CXX_FLAGS "")
set(Geant4_CXX_FLAGS_DEBUG "")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_options(
  -Wno-c++98-compat
  -Wno-c++98-compat-bind-to-temporary-copy
  -Wno-padded
  -Wwrite-strings
  -Wpointer-arith
  -Woverloaded-virtual
  -Wall
  -Wextra
  -Wpedantic
  -Wshadow
  -Werror
  -O3
  )


include(cmake/files.cmake)

include(${Geant4_USE_FILE})

add_custom_target(clangformat COMMAND clang-format -style=WebKit -i ${ALL_SOURCES_AND_HEADERS})

add_executable(${PROJECT_NAME} ${SIM_SOURCE_FILES} ${SIM_HEADER_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
    "${PROJECT_INCLUDE_DIR}"
    )
target_link_libraries(${PROJECT_NAME}
    ${Geant4_LIBRARIES}
    pthread
    )
