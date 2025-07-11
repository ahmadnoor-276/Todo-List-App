#ifndef TODOLIST_H
#define TODOLIST_H

#include "Task.h"
#include <vector>
#include <string>
#include <nlohmann/json.hpp>

class TodoList {
private:
    std::vector<Task> tasks;
    std::string filename;

public:
    // Constructors
    TodoList();
    TodoList(const std::string& filename);

    // Task management
    void addTask(const std::string& title, const std::string& description = "");
    bool editTask(int id, const std::string& title, const std::string& description);
    bool deleteTask(int id);
    bool toggleTask(int id);
    bool markTaskCompleted(int id, bool completed = true);
    
    // Getters
    std::vector<Task> getAllTasks() const;
    std::vector<Task> getCompletedTasks() const;
    std::vector<Task> getPendingTasks() const;
    Task* getTaskById(int id);
    const Task* getTaskById(int id) const;
    int getTaskCount() const;
    int getCompletedTaskCount() const;
    int getPendingTaskCount() const;

    // Display methods
    void displayAllTasks() const;
    void displayTask(const Task& task) const;
    void displayTaskSummary() const;

    // File operations
    bool saveToFile(const std::string& filename = "");
    bool loadFromFile(const std::string& filename = "");
    void setFilename(const std::string& filename);
    std::string getFilename() const;

    // Utility methods
    void clear();
    bool isEmpty() const;
};

#endif // TODOLIST_H 