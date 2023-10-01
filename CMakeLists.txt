cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
project(
  HeartStone
  VERSION 1.0
  LANGUAGES CXX)

set(SOURCES
  main.cpp
  src/Units/Units.cpp
  src/Units/Minion.cpp
  src/Units/Hero.cpp
  src/Game/Game.cpp
  src/Console/Console.cpp

)
set(HEADERS
  inc/Units/Units.h
  inc/Units/Minion.h
  inc/Units/Hero.h
  inc/Console/Console.h
  inc/Game/Game.h
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE inc)
