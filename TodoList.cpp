#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>

TodoList::TodoList() : filename("tasks.json") {}

TodoList::TodoList(const std::string& filename) : filename(filename) {}

void TodoList::addTask(const std::string& title, const std::string& description) {
    Task task(title, description);
    tasks.push_back(task);
    std::cout << "Task added successfully! ID: " << task.getId() << std::endl;
}

bool TodoList::editTask(int id, const std::string& title, const std::string& description) {
    Task* task = getTaskById(id);
    if (task) {
        task->setTitle(title);
        task->setDescription(description);
        std::cout << "Task updated successfully!" << std::endl;
        return true;
    }
    std::cout << "Task with ID " << id << " not found!" << std::endl;
    return false;
}

bool TodoList::deleteTask(int id) {
    auto it = std::find_if(tasks.begin(), tasks.end(),
                          [id](const Task& task) { return task.getId() == id; });
    if (it != tasks.end()) {
        tasks.erase(it);
        std::cout << "Task deleted successfully!" << std::endl;
        return true;
    }
    std::cout << "Task with ID " << id << " not found!" << std::endl;
    return false;
}

bool TodoList::toggleTask(int id) {
    Task* task = getTaskById(id);
    if (task) {
        task->toggleCompleted();
        std::cout << "Task status toggled successfully!" << std::endl;
        return true;
    }
    std::cout << "Task with ID " << id << " not found!" << std::endl;
    return false;
}

bool TodoList::markTaskCompleted(int id, bool completed) {
    Task* task = getTaskById(id);
    if (task) {
        task->setCompleted(completed);
        std::cout << "Task marked as " << (completed ? "completed" : "pending") << "!" << std::endl;
        return true;
    }
    std::cout << "Task with ID " << id << " not found!" << std::endl;
    return false;
}

std::vector<Task> TodoList::getAllTasks() const {
    return tasks;
}

std::vector<Task> TodoList::getCompletedTasks() const {
    std::vector<Task> completed;
    for (const auto& task : tasks) {
        if (task.isCompleted()) {
            completed.push_back(task);
        }
    }
    return completed;
}

std::vector<Task> TodoList::getPendingTasks() const {
    std::vector<Task> pending;
    for (const auto& task : tasks) {
        if (!task.isCompleted()) {
            pending.push_back(task);
        }
    }
    return pending;
}

Task* TodoList::getTaskById(int id) {
    for (auto& task : tasks) {
        if (task.getId() == id) {
            return &task;
        }
    }
    return nullptr;
}

const Task* TodoList::getTaskById(int id) const {
    for (const auto& task : tasks) {
        if (task.getId() == id) {
            return &task;
        }
    }
    return nullptr;
}

int TodoList::getTaskCount() const {
    return tasks.size();
}

int TodoList::getCompletedTaskCount() const {
    return getCompletedTasks().size();
}

int TodoList::getPendingTaskCount() const {
    return getPendingTasks().size();
}

void TodoList::displayAllTasks() const {
    if (tasks.empty()) {
        std::cout << "No tasks found." << std::endl;
        return;
    }

    std::cout << "\n=== ALL TASKS ===" << std::endl;
    std::cout << std::setw(5) << "ID" << " | " 
              << std::setw(20) << "Title" << " | " 
              << std::setw(15) << "Status" << " | " 
              << std::setw(20) << "Created" << std::endl;
    std::cout << std::string(70, '-') << std::endl;

    for (const auto& task : tasks) {
        std::cout << std::setw(5) << task.getId() << " | " 
                  << std::setw(20) << (task.getTitle().length() > 18 ? 
                                      task.getTitle().substr(0, 15) + "..." : task.getTitle()) << " | " 
                  << std::setw(15) << task.getStatusString() << " | " 
                  << std::setw(20) << task.getCreatedAtString() << std::endl;
    }
}

void TodoList::displayTask(const Task& task) const {
    std::cout << "\n=== TASK DETAILS ===" << std::endl;
    std::cout << "ID: " << task.getId() << std::endl;
    std::cout << "Title: " << task.getTitle() << std::endl;
    std::cout << "Description: " << task.getDescription() << std::endl;
    std::cout << "Status: " << task.getStatusString() << std::endl;
    std::cout << "Created: " << task.getCreatedAtString() << std::endl;
    std::cout << "Updated: " << task.getUpdatedAtString() << std::endl;
}

void TodoList::displayTaskSummary() const {
    std::cout << "\n=== TASK SUMMARY ===" << std::endl;
    std::cout << "Total tasks: " << getTaskCount() << std::endl;
    std::cout << "Completed: " << getCompletedTaskCount() << std::endl;
    std::cout << "Pending: " << getPendingTaskCount() << std::endl;
    
    if (!tasks.empty()) {
        double completionRate = (double)getCompletedTaskCount() / getTaskCount() * 100;
        std::cout << "Completion rate: " << std::fixed << std::setprecision(1) 
                  << completionRate << "%" << std::endl;
    }
}

bool TodoList::saveToFile(const std::string& filename) {
    std::string file = filename.empty() ? this->filename : filename;
    
    try {
        nlohmann::json json;
        json["tasks"] = nlohmann::json::array();
        
        for (const auto& task : tasks) {
            json["tasks"].push_back(task.toJson());
        }
        
        std::ofstream file_stream(file);
        if (file_stream.is_open()) {
            file_stream << json.dump(4);
            file_stream.close();
            std::cout << "Tasks saved to " << file << std::endl;
            return true;
        } else {
            std::cout << "Error: Could not open file " << file << " for writing!" << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Error saving tasks: " << e.what() << std::endl;
        return false;
    }
}

bool TodoList::loadFromFile(const std::string& filename) {
    std::string file = filename.empty() ? this->filename : filename;
    
    try {
        std::ifstream file_stream(file);
        if (!file_stream.is_open()) {
            std::cout << "File " << file << " not found. Starting with empty task list." << std::endl;
            return false;
        }
        
        nlohmann::json json;
        file_stream >> json;
        file_stream.close();
        
        tasks.clear();
        
        if (json.contains("tasks") && json["tasks"].is_array()) {
            for (const auto& task_json : json["tasks"]) {
                Task task = Task::fromJson(task_json);
                tasks.push_back(task);
            }
            std::cout << "Loaded " << tasks.size() << " tasks from " << file << std::endl;
            return true;
        } else {
            std::cout << "Invalid file format!" << std::endl;
            return false;
        }
    } catch (const std::exception& e) {
        std::cout << "Error loading tasks: " << e.what() << std::endl;
        return false;
    }
}

void TodoList::setFilename(const std::string& filename) {
    this->filename = filename;
}

std::string TodoList::getFilename() const {
    return filename;
}

void TodoList::clear() {
    tasks.clear();
    std::cout << "All tasks cleared!" << std::endl;
}

bool TodoList::isEmpty() const {
    return tasks.empty();
} 