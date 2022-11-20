cmake_minimum_required(VERSION 3.21)

project(Mines)

set(CMAKE_CXX_STANDARD 17)

add_library(model 
        src/model/board.cpp
        src/model/board.h
        src/model/game.cpp
        src/model/game.hpp
        src/model/difficulty.hpp
        )

# Version mines
add_executable(mines_c
        src/main_c.cpp
        src/interface/exception.h
        src/interface/console.cpp
        src/interface/console.h
        )
target_link_libraries(mines_c model)