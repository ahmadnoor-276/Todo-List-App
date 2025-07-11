cmake_minimum_required(VERSION 3.10)
project(TodoListApp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find nlohmann/json package
find_package(nlohmann_json 3.2.0 REQUIRED)

# Add executable
add_executable(todo_app main.cpp Task.cpp TodoList.cpp)

# Link nlohmann/json
target_link_libraries(todo_app nlohmann_json::nlohmann_json) 