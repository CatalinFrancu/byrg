cmake_minimum_required(VERSION 3.29)

project(
  byrg
  VERSION 1.0
  LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

set(SOURCES
    src/Bitmap.cpp
    src/Bitmap.h
    src/Board.cpp
    src/Board.h
    src/Cell.cpp
    src/Cell.h
    src/Clock.cpp
    src/Clock.h
    src/Command.cpp
    src/Command.h
    src/CornerList.cpp
    src/CornerList.h
    src/Game.cpp
    src/Game.h
    src/globals.h
    src/main.cpp
    src/Math.cpp
    src/Math.h
    src/Move.cpp
    src/Move.h
    src/MoveGenerator.cpp
    src/MoveGenerator.h
    src/PieceSet.cpp
    src/PieceSet.h
    src/Piece.cpp
    src/Piece.h
    src/Response.cpp
    src/Response.h
    src/StrUtil.cpp
    src/StrUtil.h
    src/UndoInfo.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
