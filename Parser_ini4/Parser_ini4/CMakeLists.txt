cmake_minimum_required(VERSION 3.30)

# имя проекта
project(ConfigParser)

# стандарт C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# исходные файлы
set(SOURCES
    main.cpp
    Parser_ini.cpp
    Lib_ini.cpp
    Menu.cpp
)

# исполняемый файл
add_executable(ConfigParser ${SOURCES})