cmake_minimum_required(VERSION 3.8)
project(IL-Project5)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_executable(IL-Project5 main.cpp Boss_Children.h Spell_Caster.h)
add_executable(IL-Project5_Testing testing.cpp Boss_Children.h Spell_Caster.h)