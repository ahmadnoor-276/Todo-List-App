#include "TodoList.h"
#include <iostream>
#include <string>
#include <limits>
#include <iomanip> // Required for std::setw
#include <vector>  // Required for std::vector

void displayMenu() {
    std::cout << "\n=== TODO LIST APPLICATION ===" << std::endl;
    std::cout << "1. Add new task" << std::endl;
    std::cout << "2. View all tasks" << std::endl;
    std::cout << "3. View task details" << std::endl;
    std::cout << "4. Edit task" << std::endl;
    std::cout << "5. Delete task" << std::endl;
    std::cout << "6. Toggle task completion" << std::endl;
    std::cout << "7. Mark task as completed" << std::endl;
    std::cout << "8. Mark task as pending" << std::endl;
    std::cout << "9. View completed tasks" << std::endl;
    std::cout << "10. View pending tasks" << std::endl;
    std::cout << "11. View task summary" << std::endl;
    std::cout << "12. Save tasks to file" << std::endl;
    std::cout << "13. Load tasks from file" << std::endl;
    std::cout << "14. Clear all tasks" << std::endl;
    std::cout << "0. Exit" << std::endl;
    std::cout << "Enter your choice: ";
}

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

int getIntInput(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            clearInputBuffer();
            return value;
        } else {
            std::cout << "Invalid input. Please enter a number." << std::endl;
            clearInputBuffer();
        }
    }
}

void addTask(TodoList& todoList) {
    std::cout << "\n=== ADD NEW TASK ===" << std::endl;
    std::string title = getInput("Enter task title: ");
    if (title.empty()) {
        std::cout << "Title cannot be empty!" << std::endl;
        return;
    }
    
    std::string description = getInput("Enter task description (optional): ");
    todoList.addTask(title, description);
}

void viewAllTasks(const TodoList& todoList) {
    todoList.displayAllTasks();
}

void viewTaskDetails(const TodoList& todoList) {
    if (todoList.isEmpty()) {
        std::cout << "No tasks to display." << std::endl;
        return;
    }
    
    int id = getIntInput("Enter task ID: ");
    const Task* task = todoList.getTaskById(id);
    if (task) {
        todoList.displayTask(*task);
    } else {
        std::cout << "Task with ID " << id << " not found!" << std::endl;
    }
}

void editTask(TodoList& todoList) {
    if (todoList.isEmpty()) {
        std::cout << "No tasks to edit." << std::endl;
        return;
    }
    
    int id = getIntInput("Enter task ID to edit: ");
    std::string title = getInput("Enter new title: ");
    if (title.empty()) {
        std::cout << "Title cannot be empty!" << std::endl;
        return;
    }
    
    std::string description = getInput("Enter new description: ");
    todoList.editTask(id, title, description);
}

void deleteTask(TodoList& todoList) {
    if (todoList.isEmpty()) {
        std::cout << "No tasks to delete." << std::endl;
        return;
    }
    
    int id = getIntInput("Enter task ID to delete: ");
    todoList.deleteTask(id);
}

void toggleTask(TodoList& todoList) {
    if (todoList.isEmpty()) {
        std::cout << "No tasks to toggle." << std::endl;
        return;
    }
    
    int id = getIntInput("Enter task ID to toggle: ");
    todoList.toggleTask(id);
}

void markTaskCompleted(TodoList& todoList) {
    if (todoList.isEmpty()) {
        std::cout << "No tasks to mark." << std::endl;
        return;
    }
    
    int id = getIntInput("Enter task ID to mark as completed: ");
    todoList.markTaskCompleted(id, true);
}

void markTaskPending(TodoList& todoList) {
    if (todoList.isEmpty()) {
        std::cout << "No tasks to mark." << std::endl;
        return;
    }
    
    int id = getIntInput("Enter task ID to mark as pending: ");
    todoList.markTaskCompleted(id, false);
}

void viewCompletedTasks(const TodoList& todoList) {
    std::vector<Task> completed = todoList.getCompletedTasks();
    if (completed.empty()) {
        std::cout << "No completed tasks found." << std::endl;
        return;
    }
    
    std::cout << "\n=== COMPLETED TASKS ===" << std::endl;
    std::cout << std::setw(5) << "ID" << " | " 
              << std::setw(20) << "Title" << " | " 
              << std::setw(20) << "Completed" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& task : completed) {
        std::cout << std::setw(5) << task.getId() << " | " 
                  << std::setw(20) << (task.getTitle().length() > 18 ? 
                                      task.getTitle().substr(0, 15) + "..." : task.getTitle()) << " | " 
                  << std::setw(20) << task.getUpdatedAtString() << std::endl;
    }
}

void viewPendingTasks(const TodoList& todoList) {
    std::vector<Task> pending = todoList.getPendingTasks();
    if (pending.empty()) {
        std::cout << "No pending tasks found." << std::endl;
        return;
    }
    
    std::cout << "\n=== PENDING TASKS ===" << std::endl;
    std::cout << std::setw(5) << "ID" << " | " 
              << std::setw(20) << "Title" << " | " 
              << std::setw(20) << "Created" << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    for (const auto& task : pending) {
        std::cout << std::setw(5) << task.getId() << " | " 
                  << std::setw(20) << (task.getTitle().length() > 18 ? 
                                      task.getTitle().substr(0, 15) + "..." : task.getTitle()) << " | " 
                  << std::setw(20) << task.getCreatedAtString() << std::endl;
    }
}

void viewTaskSummary(const TodoList& todoList) {
    todoList.displayTaskSummary();
}

void saveTasks(TodoList& todoList) {
    std::string filename = getInput("Enter filename (or press Enter for default): ");
    todoList.saveToFile(filename);
}

void loadTasks(TodoList& todoList) {
    std::string filename = getInput("Enter filename (or press Enter for default): ");
    todoList.loadFromFile(filename);
}

void clearAllTasks(TodoList& todoList) {
    std::string confirm = getInput("Are you sure you want to clear all tasks? (yes/no): ");
    if (confirm == "yes" || confirm == "y" || confirm == "YES" || confirm == "Y") {
        todoList.clear();
    } else {
        std::cout << "Operation cancelled." << std::endl;
    }
}

int main() {
    TodoList todoList;
    
    // Try to load existing tasks
    todoList.loadFromFile();
    
    std::cout << "Welcome to the Todo List Application!" << std::endl;
    
    int choice;
    do {
        displayMenu();
        choice = getIntInput("");
        
        switch (choice) {
            case 1:
                addTask(todoList);
                break;
            case 2:
                viewAllTasks(todoList);
                break;
            case 3:
                viewTaskDetails(todoList);
                break;
            case 4:
                editTask(todoList);
                break;
            case 5:
                deleteTask(todoList);
                break;
            case 6:
                toggleTask(todoList);
                break;
            case 7:
                markTaskCompleted(todoList);
                break;
            case 8:
                markTaskPending(todoList);
                break;
            case 9:
                viewCompletedTasks(todoList);
                break;
            case 10:
                viewPendingTasks(todoList);
                break;
            case 11:
                viewTaskSummary(todoList);
                break;
            case 12:
                saveTasks(todoList);
                break;
            case 13:
                loadTasks(todoList);
                break;
            case 14:
                clearAllTasks(todoList);
                break;
            case 0:
                std::cout << "Saving tasks before exit..." << std::endl;
                todoList.saveToFile();
                std::cout << "Goodbye!" << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
        }
        
        if (choice != 0) {
            std::cout << "\nPress Enter to continue...";
            std::cin.get();
        }
        
    } while (choice != 0);
    
    return 0;
} 