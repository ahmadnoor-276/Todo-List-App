#!/bin/bash

# Build script for Todo List Application

echo "Building Todo List Application..."

# Create build directory if it doesn't exist
mkdir -p build
cd build

# Run CMake
echo "Running CMake..."
cmake ..

# Check if CMake was successful
if [ $? -eq 0 ]; then
    echo "CMake configuration successful!"
    
    # Build the project
    echo "Building project..."
    make
    
    # Check if build was successful
    if [ $? -eq 0 ]; then
        echo "Build successful!"
        echo "You can now run the application with: ./todo_app"
    else
        echo "Build failed!"
        exit 1
    fi
else
    echo "CMake configuration failed!"
    echo "Please make sure you have the required dependencies installed:"
    echo "- C++17 compatible compiler"
    echo "- CMake 3.10 or higher"
    echo "- nlohmann/json library"
    exit 1
fi 