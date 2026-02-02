cmake_minimum_required(VERSION 3.26)

# NOTE: update executable name in .github/workflows/cmake.yml:25 when changing executable name in this file
# for now, the project name is used as the executable name
set(MAIN_PROJECT_NAME "oop")
set(MAIN_EXECUTABLE_NAME "${MAIN_PROJECT_NAME}")


project(${MAIN_PROJECT_NAME})
# set(CMAKE_PROJECT_VERSION_MAJOR 0)
# set(CMAKE_PROJECT_VERSION_MINOR 0)
# set(CMAKE_PROJECT_VERSION_PATCH 1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Options.cmake)
include(cmake/CompilerFlags.cmake)
include(cmake/CopyHelper.cmake)



include_directories(include)


include(FetchContent)

set(FETCHCONTENT_QUIET OFF)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)


FetchContent_Declare(
        sfml
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG        2.6.1
)

FetchContent_MakeAvailable(sfml)


add_executable(${MAIN_EXECUTABLE_NAME}
        main.cpp
        src/Produs_Meniu.cpp
        header/Produs_Meniu.hpp
        src/Cronometru_Rabdare.cpp
        header/Cronometru_Rabdare.hpp
        src/Comanda.cpp
        header/Comanda.hpp
        src/Client_Pinguin.cpp
        header/Client_Pinguin.hpp
        src/Pinguini_Derivati.cpp
        header/Pinguini_Derivati.hpp
        src/Restaurant.cpp
        header/Restaurant.hpp
        header/Exceptii.hpp
        include/json.hpp
        header/AssetManager.hpp
        header/Utils.hpp
        src/ConfigManager.cpp
        header/ConfigManager.hpp
        src/PenguinFactory.cpp
        header/PenguinFactory.hpp
        src/Masa.cpp
        header/Masa.hpp
        src/Joc.cpp
        header/Joc.hpp
)


set_compiler_flags(RUN_SANITIZERS TRUE TARGET_NAMES ${MAIN_EXECUTABLE_NAME})

target_link_libraries(${MAIN_EXECUTABLE_NAME} PRIVATE sfml-graphics sfml-window sfml-system)


install(TARGETS ${MAIN_EXECUTABLE_NAME} DESTINATION ${DESTINATION_DIR})
if(APPLE)
    install(FILES launcher.command DESTINATION ${DESTINATION_DIR})
endif()

copy_files(FILES tastatura.txt meniu.txt COPY_TO_DESTINATION TARGET_NAME ${MAIN_EXECUTABLE_NAME})



if(WIN32)
    add_custom_command(TARGET ${MAIN_EXECUTABLE_NAME} POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:sfml-graphics>
            $<TARGET_FILE:sfml-window>
            $<TARGET_FILE:sfml-system>
            $<TARGET_FILE_DIR:${MAIN_EXECUTABLE_NAME}>
    )
endif()