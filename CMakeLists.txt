cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
project(
  HeartStone
  VERSION 1.0
  LANGUAGES CXX)
add_definitions(-DLOG_FILE_PATH="${CMAKE_SOURCE_DIR}/generated/logfile.log")
set(SOURCES
  main.cpp
  ${CMAKE_SOURCE_DIR}/src/CardManager/CardFactory/Card.cpp
  ${CMAKE_SOURCE_DIR}/src/CardManager/CardManager.cpp
  ${CMAKE_SOURCE_DIR}/src/GameEngine/GameEngine.cpp
  ${CMAKE_SOURCE_DIR}/src/CardManager/Hero.cpp
  ${CMAKE_SOURCE_DIR}/src/MySocket/Socket.cpp
  ${CMAKE_SOURCE_DIR}/src/GameUi/GameUi.cpp
)

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

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/generated)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/inc)