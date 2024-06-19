cmake_minimum_required(VERSION 3.29)

project(
  byrg
  VERSION 1.0
  LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 20)

set(SOURCES
    src/Bitmap.cpp
    src/Bitmap.h
    src/Board.cpp
    src/Board.h
    src/Cell.h
    src/Clock.cpp
    src/Clock.h
    src/Command.cpp
    src/Command.h
    src/Game.cpp
    src/Game.h
    src/globals.h
    src/main.cpp
    src/Move.h
    src/MoveGenerator.cpp
    src/MoveGenerator.h
    src/Piece.cpp
    src/Piece.h
    src/PieceSet.cpp
    src/PieceSet.h
    src/PieceVariant.cpp
    src/PieceVariant.h
    src/Response.cpp
    src/Response.h
    src/Score.h
    src/SearchResult.cpp
    src/SearchResult.h
    src/StrUtil.cpp
    src/StrUtil.h
)

add_executable(${PROJECT_NAME} ${SOURCES})
