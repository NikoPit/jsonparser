cmake_minimum_required(VERSION 4.4)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "f35a9ac6-8463-4d38-8eec-5d6008153e7d")

project(jsonparser)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_MODULE_STD ON)

add_executable(jsonparser
    main.cpp
)

target_sources(jsonparser
    PRIVATE
        FILE_SET CXX_MODULES
        FILES
            utils.cppm
            lexer.cppm
)
