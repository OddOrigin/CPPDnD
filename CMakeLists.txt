cmake_minimum_required(VERSION 3.26)
project(cppDND)

set(CMAKE_CXX_STANDARD 17)

add_executable(cppDND main.cpp
        Creature.cpp
        Creature.h
        Hero.cpp
        Hero.h
        Jeu.cpp
        Jeu.h
        Entity.cpp
        Entity.h)
