cmake_minimum_required(VERSION 3.10)
project(Lab_06)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git  
  GIT_TAG v1.15.0)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include)

# Основные исходные файлы
set(SOURCES
    main.cpp
    src/NPC.cpp
    src/Squirrel.cpp
    src/Elf.cpp
    src/Bandit.cpp
    src/factory.cpp
    src/battlefield.cpp
    src/battle_visitor.cpp
    src/observers.cpp
)

# Заголовочные файлы
set(HEADERS
    include/NPC.hpp
    include/Squirrel.hpp
    include/Elf.hpp
    include/Bandit.hpp
    include/factory.hpp
    include/battlefield.hpp
    include/battle_visitor.hpp
    include/observers.hpp
    include/common_visitor.hpp
)

# Создание списка исходных файлов без main.cpp для тестов
set(SOURCES_WITHOUT_MAIN
    src/NPC.cpp
    src/Squirrel.cpp
    src/Elf.cpp
    src/Bandit.cpp
    src/factory.cpp
    src/battlefield.cpp
    src/battle_visitor.cpp
    src/observers.cpp
)

add_library(${PROJECT_NAME}_lib STATIC ${SOURCES_WITHOUT_MAIN} ${HEADERS})

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

enable_testing()
add_executable(tests tests/test.cpp)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(tests PRIVATE ${CMAKE_PROJECT_NAME}_lib GTest::gtest GTest::gtest_main)
add_test(NAME MyProjectTests COMMAND tests)