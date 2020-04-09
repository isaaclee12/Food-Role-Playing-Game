cmake_minimum_required(VERSION 3.8)
project(IL-AL-Final-Project-MPL)

set(CMAKE_CXX_STANDARD 17)

add_executable(IL-AL-Final-Project-MPL main.cpp Boss_Children.h Spell_Caster.h)
add_executable(IL-AL-Final-Project-MPL-Testing testing.cpp Boss_Children.h Spell_Caster.h)