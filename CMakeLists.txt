# cmake .. -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles"

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
project(
HeartStone
VERSION 1.0
LANGUAGES CXX)

# set(GTEST_DIR ${CMAKE_SOURCE_DIR}/lib/googletest/googletest)
# set(GMOCK_DIR ${CMAKE_SOURCE_DIR}/lib/googletest/googlemock)

# # # Include the Google Test source code
# add_subdirectory(${GTEST_DIR})
# add_subdirectory(${GMOCK_DIR})

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/Player/Player.cpp
    ${CMAKE_SOURCE_DIR}/src/Hero/Hero.cpp
    ${CMAKE_SOURCE_DIR}/src/Card/Card.cpp
    ${CMAKE_SOURCE_DIR}/src/CardManager/CardManager.cpp
    ${CMAKE_SOURCE_DIR}/src/Engine/Engine.cpp
    ${CMAKE_SOURCE_DIR}/src/UI/Ui.cpp
    ${CMAKE_SOURCE_DIR}/src/MySocket/MySocket.cpp
)

set(HEADERS
    ${CMAKE_SOURCE_DIR}/inc/Player/Player.h
    ${CMAKE_SOURCE_DIR}/inc/UI/Ui.h
    ${CMAKE_SOURCE_DIR}/inc/Hero/Hero.h
    ${CMAKE_SOURCE_DIR}/inc/Card/Card.h
    ${CMAKE_SOURCE_DIR}/inc/Card/CardFactory.h
    ${CMAKE_SOURCE_DIR}/inc/assets/CardData.h
    ${CMAKE_SOURCE_DIR}/inc/assets/HeroData.h
    ${CMAKE_SOURCE_DIR}/inc/CardManager/CardManager.h
    ${CMAKE_SOURCE_DIR}/inc/Engine/Engine.h
    ${CMAKE_SOURCE_DIR}/inc/MySocket/MySocket.h
)
# set(TEST_SOURCES
# test.cpp
# ${SOURCES}
# ${CMAKE_SOURCE_DIR}/utest/Ui.utest.cpp
# ${CMAKE_SOURCE_DIR}/utest/Player.utest.cpp
# ${CMAKE_SOURCE_DIR}/utest/Hero.utest.cpp
# ${CMAKE_SOURCE_DIR}/utest/MySocket.utest.cpp
# )


# # Set the binary and library output directories
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/generated)

# # Main executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS} )
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)


# add_executable(unittest_${PROJECT_NAME} ${TEST_SOURCES} ${CMAKE_SOURCE_DIR}/utest/mock)
# target_include_directories(unittest_${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc ${GTEST_DIR}/include ${GMOCK_DIR}/include)
# target_link_libraries(unittest_${PROJECT_NAME} gtest gtest_main gmock)
