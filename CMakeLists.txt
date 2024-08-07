cmake_minimum_required(VERSION 3.28)
project(FinalSortVisualizer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)

# Find the SFML package
find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

# Add the source files
add_executable(FinalSortVisualizer
        main.cpp
        SwiftifySFML/Application.h
        SwiftifySFML/Application.cpp
        SwiftifySFML/Container.h
        SwiftifySFML/Container.cpp
        SwiftifySFML/Enumerations.h
        SwiftifySFML/Screen.h
        SwiftifySFML/Screen.cpp
        SwiftifySFML/UIComponent.h
        SwiftifySFML/UIComponent.cpp
        Screens/StartScreen.cpp
        Datasets/Dataset.h
        Datasets/Dataset.cpp
        Settings/Settings.h
        Settings/Settings.cpp
)

target_link_libraries(FinalSortVisualizer sfml-system sfml-window sfml-graphics)
