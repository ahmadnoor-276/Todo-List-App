# Todo List Application

A console-based to-do list tracker written in C++ with JSON file storage.

## Features

- **Add/Edit/Delete Tasks**: Full CRUD operations for managing tasks
- **Task Completion**: Mark tasks as complete or pending, toggle completion status
- **File Persistence**: Save and load tasks in JSON format
- **Task Details**: View comprehensive task information including timestamps
- **Task Filtering**: View all tasks, completed tasks, or pending tasks
- **Task Summary**: Get statistics about task completion rates
- **User-Friendly Interface**: Console-based menu system with input validation

## Requirements

- C++17 compatible compiler (GCC 7+, Clang 5+, MSVC 2017+)
- CMake 3.10 or higher
- nlohmann/json library

## Installation

### Ubuntu/Debian
```bash
# Install dependencies
sudo apt update
sudo apt install build-essential cmake nlohmann-json3-dev

# Clone and build
git clone <repository-url>
cd "To-do List App"
mkdir build && cd build
cmake ..
make
```

### macOS
```bash
# Install dependencies using Homebrew
brew install cmake nlohmann-json

# Clone and build
git clone <repository-url>
cd "To-do List App"
mkdir build && cd build
cmake ..
make
```

### Windows (with MSVC)
```bash
# Install Visual Studio with C++ support
# Install CMake from https://cmake.org/download/

# Clone and build
git clone <repository-url>
cd "To-do List App"
mkdir build && cd build
cmake ..
cmake --build . --config Release
```

## Usage

Run the application:
```bash
./todo_app
```

### Menu Options

1. **Add new task** - Create a new task with title and optional description
2. **View all tasks** - Display all tasks in a formatted table
3. **View task details** - Show detailed information for a specific task
4. **Edit task** - Modify title and description of an existing task
5. **Delete task** - Remove a task from the list
6. **Toggle task completion** - Switch between completed and pending status
7. **Mark task as completed** - Set a task as completed
8. **Mark task as pending** - Set a task as pending
9. **View completed tasks** - Show only completed tasks
10. **View pending tasks** - Show only pending tasks
11. **View task summary** - Display statistics about task completion
12. **Save tasks to file** - Export tasks to a JSON file
13. **Load tasks from file** - Import tasks from a JSON file
14. **Clear all tasks** - Remove all tasks (with confirmation)
0. **Exit** - Save and quit the application

### Example Session

```
Welcome to the Todo List Application!

=== TODO LIST APPLICATION ===
1. Add new task
2. View all tasks
3. View task details
4. Edit task
5. Delete task
6. Toggle task completion
7. Mark task as completed
8. Mark task as pending
9. View completed tasks
10. View pending tasks
11. View task summary
12. Save tasks to file
13. Load tasks from file
14. Clear all tasks
0. Exit
Enter your choice: 1

=== ADD NEW TASK ===
Enter task title: Buy groceries
Enter task description (optional): Milk, bread, eggs
Task added successfully! ID: 1

Press Enter to continue...
```

## File Format

Tasks are stored in JSON format. Example `tasks.json`:

```json
{
    "tasks": [
        {
            "id": 1,
            "title": "Buy groceries",
            "description": "Milk, bread, eggs",
            "completed": false,
            "created_at": 1703123456,
            "updated_at": 1703123456
        },
        {
            "id": 2,
            "title": "Complete project",
            "description": "Finish the C++ todo app",
            "completed": true,
            "created_at": 1703123400,
            "updated_at": 1703123500
        }
    ]
}
```

## Project Structure

```
To-do List App/
├── CMakeLists.txt      # Build configuration
├── Task.h              # Task class header
├── Task.cpp            # Task class implementation
├── TodoList.h          # TodoList class header
├── TodoList.cpp        # TodoList class implementation
├── main.cpp            # Main application and menu system
└── README.md           # This file
```

## Class Design

### Task Class
- **Properties**: ID, title, description, completion status, timestamps
- **Methods**: Getters, setters, JSON serialization, status formatting

### TodoList Class
- **Properties**: Vector of tasks, filename for persistence
- **Methods**: CRUD operations, file I/O, task filtering, display methods

## Features in Detail

### Task Management
- Each task has a unique auto-incrementing ID
- Tasks include creation and modification timestamps
- Support for optional task descriptions
- Visual status indicators (✓ for completed, ○ for pending)

### File Operations
- Automatic loading of existing tasks on startup
- Manual save/load operations with custom filenames
- Automatic saving before application exit
- JSON format for human-readable storage

### User Interface
- Input validation for all user inputs
- Clear error messages for invalid operations
- Formatted table displays for task lists
- Confirmation prompts for destructive operations

## Error Handling

The application includes comprehensive error handling for:
- File I/O operations
- Invalid user input
- Missing tasks
- JSON parsing errors
- Memory management

## Contributing

Feel free to submit issues and enhancement requests!

## License

This project is open source and available under the MIT License. 