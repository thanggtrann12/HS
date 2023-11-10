cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)
project(
  HeartStone
  VERSION 1.0
  LANGUAGES CXX)

add_definitions(-DLOG_FILE_PATH="${CMAKE_SOURCE_DIR}/generated/logfile.log")

# Set the path to the Google Test libraries
set(GTEST_LIB_PATH ${CMAKE_SOURCE_DIR}/lib/googletest/googletest)

# List of source files for the main project
set(SOURCES
  ${CMAKE_SOURCE_DIR}/src/CardManager/CardFactory/Card.cpp
  ${CMAKE_SOURCE_DIR}/src/CardManager/CardManager.cpp
  ${CMAKE_SOURCE_DIR}/src/GameEngine/GameEngine.cpp
  ${CMAKE_SOURCE_DIR}/src/CardManager/Hero.cpp
  ${CMAKE_SOURCE_DIR}/src/MySocket/Socket.cpp
  ${CMAKE_SOURCE_DIR}/src/GameUi/GameUi.cpp

)

# List of header files for the main project
set(HEADERS
  ${CMAKE_SOURCE_DIR}/inc/CardManager/CardFactory/Card.h
  ${CMAKE_SOURCE_DIR}/inc/CardManager/CardManager.h
  ${CMAKE_SOURCE_DIR}/inc/CardManager/Hero.h
  ${CMAKE_SOURCE_DIR}/inc/CardManager/CardFactory/CardFactory.h
  ${CMAKE_SOURCE_DIR}/inc/GameEngine/GameEngine.h
  ${CMAKE_SOURCE_DIR}/inc/MySocket/Socket.h
  ${CMAKE_SOURCE_DIR}/inc/Helper/Helper.h
  ${CMAKE_SOURCE_DIR}/inc/GameUi/GameUi.h
)

# List of source files for the test executable
set(TEST_SOURCES
  test.cpp
  ${SOURCES}
  ${CMAKE_SOURCE_DIR}/UT/GameEngine/GameEngine_test.cpp
  ${CMAKE_SOURCE_DIR}/UT/MySocket/Socket_test.cpp
  ${CMAKE_SOURCE_DIR}/UT/GameUi/GameUi_test.cpp
  ${CMAKE_SOURCE_DIR}/UT/CardManager/CardManager_test.cpp
)

# Main project executable
add_executable(${PROJECT_NAME} main.cpp ${SOURCES})

# Test executable
add_executable(unittest_${PROJECT_NAME} ${TEST_SOURCES})

# Link the main project with Google Test libraries
# target_link_libraries(${PROJECT_NAME} PRIVATE
#     ${GTEST_LIB_PATH}/gtest.lib
#     ${GTEST_LIB_PATH}/gtest_main.lib
# )

# Link the test executable with Google Test libraries
# target_link_libraries(unittest_${PROJECT_NAME} PRIVATE
#     ${GTEST_LIB_PATH}/gtest.lib
#     ${GTEST_LIB_PATH}/gtest_main.lib
# )

# Include directories for both targets
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)

target_include_directories(unittest_${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)
target_include_directories(unittest_${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/googletest/googlemock/include)
target_include_directories(unittest_${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/googletest/googletest/include)
target_include_directories(unittest_${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/gmock/include)
