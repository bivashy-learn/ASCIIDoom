cmake_minimum_required(VERSION 3.29)
project(DoomConsole)

set(CMAKE_CXX_STANDARD 20)

add_executable(DoomConsole main.cpp
        Game.cpp
        Game.h
        Graphics.cpp
        Graphics.h
        model/Entity.h
        model/Camera.cpp
        model/Camera.h
        model/Map.cpp
        model/Map.h
        model/Player.cpp
        model/Player.h)
