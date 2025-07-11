#include "Task.h"
#include <iomanip>
#include <sstream>
#include <ctime>

// Static counter for generating unique IDs
static int nextId = 1;

Task::Task() : id(0), title(""), description(""), completed(false) {
    created_at = std::chrono::system_clock::now();
    updated_at = created_at;
}

Task::Task(const std::string& title, const std::string& description)
    : id(nextId++), title(title), description(description), completed(false) {
    created_at = std::chrono::system_clock::now();
    updated_at = created_at;
}

Task::Task(int id, const std::string& title, const std::string& description, bool completed,
           const std::chrono::system_clock::time_point& created_at,
           const std::chrono::system_clock::time_point& updated_at)
    : id(id), title(title), description(description), completed(completed),
      created_at(created_at), updated_at(updated_at) {
    if (id >= nextId) {
        nextId = id + 1;
    }
}

int Task::getId() const {
    return id;
}

std::string Task::getTitle() const {
    return title;
}

std::string Task::getDescription() const {
    return description;
}

bool Task::isCompleted() const {
    return completed;
}

std::chrono::system_clock::time_point Task::getCreatedAt() const {
    return created_at;
}

std::chrono::system_clock::time_point Task::getUpdatedAt() const {
    return updated_at;
}

void Task::setTitle(const std::string& title) {
    this->title = title;
    updated_at = std::chrono::system_clock::now();
}

void Task::setDescription(const std::string& description) {
    this->description = description;
    updated_at = std::chrono::system_clock::now();
}

void Task::setCompleted(bool completed) {
    this->completed = completed;
    updated_at = std::chrono::system_clock::now();
}

void Task::toggleCompleted() {
    completed = !completed;
    updated_at = std::chrono::system_clock::now();
}

std::string Task::getStatusString() const {
    return completed ? "✓ Completed" : "○ Pending";
}

std::string Task::getCreatedAtString() const {
    auto time_t = std::chrono::system_clock::to_time_t(created_at);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

std::string Task::getUpdatedAtString() const {
    auto time_t = std::chrono::system_clock::to_time_t(updated_at);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

nlohmann::json Task::toJson() const {
    nlohmann::json json;
    json["id"] = id;
    json["title"] = title;
    json["description"] = description;
    json["completed"] = completed;
    json["created_at"] = std::chrono::duration_cast<std::chrono::seconds>(
        created_at.time_since_epoch()).count();
    json["updated_at"] = std::chrono::duration_cast<std::chrono::seconds>(
        updated_at.time_since_epoch()).count();
    return json;
}

Task Task::fromJson(const nlohmann::json& json) {
    int id = json["id"];
    std::string title = json["title"];
    std::string description = json["description"];
    bool completed = json["completed"];
    
    auto created_at = std::chrono::system_clock::from_time_t(json["created_at"]);
    auto updated_at = std::chrono::system_clock::from_time_t(json["updated_at"]);
    
    return Task(id, title, description, completed, created_at, updated_at);
} 