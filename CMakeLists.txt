cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
project(
  HeartStone
  VERSION 1.0
  LANGUAGES CXX)

set(SOURCES
  main.cpp
  src/Entity/Entity.cpp
  src/Entity/Minion.cpp
  src/Entity/Hero.cpp
  src/Game/Game.cpp
  src/Console/Console.cpp
  src/MySocket/Socket.cpp

)
set(HEADERS
  inc/Entity/Entity.h
  inc/Entity/Minion.h
  inc/Console/Console.h
  inc/Game/Game.h
  inc/MySocket/Socket.h
  inc/Game/GameData.h

)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE inc)
