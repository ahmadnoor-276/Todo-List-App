#ifndef TASK_H
#define TASK_H

#include <string>
#include <chrono>
#include <nlohmann/json.hpp>

class Task {
private:
    int id;
    std::string title;
    std::string description;
    bool completed;
    std::chrono::system_clock::time_point created_at;
    std::chrono::system_clock::time_point updated_at;

public:
    // Constructors
    Task();
    Task(const std::string& title, const std::string& description = "");
    Task(int id, const std::string& title, const std::string& description, bool completed,
         const std::chrono::system_clock::time_point& created_at,
         const std::chrono::system_clock::time_point& updated_at);

    // Getters
    int getId() const;
    std::string getTitle() const;
    std::string getDescription() const;
    bool isCompleted() const;
    std::chrono::system_clock::time_point getCreatedAt() const;
    std::chrono::system_clock::time_point getUpdatedAt() const;

    // Setters
    void setTitle(const std::string& title);
    void setDescription(const std::string& description);
    void setCompleted(bool completed);
    void toggleCompleted();

    // Utility methods
    std::string getStatusString() const;
    std::string getCreatedAtString() const;
    std::string getUpdatedAtString() const;
    
    // JSON serialization
    nlohmann::json toJson() const;
    static Task fromJson(const nlohmann::json& json);
};

#endif // TASK_H 