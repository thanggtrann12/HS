    cmake_minimum_required(VERSION 3.12)

    set(CMAKE_CXX_STANDARD 17)
    project(
    HeartStone
    VERSION 1.0
    LANGUAGES CXX)

    set(GTEST_DIR ${CMAKE_SOURCE_DIR}/lib/googletest/googletest)
    set(GMOCK_DIR ${CMAKE_SOURCE_DIR}/lib/googletest/googlemock)

    # # Include the Google Test source code
    add_subdirectory(${GTEST_DIR})
    add_subdirectory(${GMOCK_DIR})

    set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/CardManager/CardFactory/Card.cpp
    ${CMAKE_SOURCE_DIR}/src/CardManager/CardManager.cpp
    ${CMAKE_SOURCE_DIR}/src/GameEngine/GameEngine.cpp
    ${CMAKE_SOURCE_DIR}/src/CardManager/Hero.cpp
    ${CMAKE_SOURCE_DIR}/src/MySocket/MySocket.cpp
    ${CMAKE_SOURCE_DIR}/src/GameUi/GameUi.cpp
    )

    set(HEADERS
    ${CMAKE_SOURCE_DIR}/inc/CardManager/CardFactory/Card.h
    ${CMAKE_SOURCE_DIR}/inc/CardManager/CardManager.h
    ${CMAKE_SOURCE_DIR}/inc/CardManager/Hero.h
    ${CMAKE_SOURCE_DIR}/inc/CardManager/CardFactory/CardFactory.h
    ${CMAKE_SOURCE_DIR}/inc/GameEngine/GameEngine.h
    ${CMAKE_SOURCE_DIR}/inc/MySocket/MySocket.h
    ${CMAKE_SOURCE_DIR}/inc/Helper/Helper.h
    ${CMAKE_SOURCE_DIR}/inc/GameUi/GameUi.h
    )

    set(TEST_SOURCES
    test.cpp
    ${SOURCES}
    ${CMAKE_SOURCE_DIR}/UT/Hero_test.cpp
    ${CMAKE_SOURCE_DIR}/UT/CardManager_test.cpp
    ${CMAKE_SOURCE_DIR}/UT/Card_test.cpp
    ${CMAKE_SOURCE_DIR}/UT/GameUi_test.cpp
    )

    # # Set the binary and library output directories
    set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/generated)

    # # Main executable
    add_executable(${PROJECT_NAME} main.cpp ${SOURCES} ${HEADERS})
    target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)

# Unit test executable
add_executable(unittest_${PROJECT_NAME} ${TEST_SOURCES} ${CMAKE_SOURCE_DIR}/UT/mock)
target_include_directories(unittest_${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc ${GTEST_DIR}/include ${GMOCK_DIR}/include)
target_link_libraries(unittest_${PROJECT_NAME} gtest gtest_main gmock)
