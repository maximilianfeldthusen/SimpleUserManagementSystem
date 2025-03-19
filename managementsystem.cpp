#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>

class User {
public:
    User(const std::string& name, int age) : name(name), age(age) {
        if (age < 0) {
            throw std::invalid_argument("Age cannot be negative");
        }
    }

    void display() const {
        std::cout << "User: " << name << ", Age: " << age << std::endl;
    }

private:
    std::string name;
    int age;
};

class UserManager {
public:
    void addUser(const std::string& name, int age) {
        // Validate input
        if (name.empty() || name.length() > 50) {
            throw std::invalid_argument("Name must be between 1 and 50 characters");
        }
        users.emplace_back(std::make_unique<User>(name, age));
    }

    void displayUsers() const {
        for (const auto& user : users) {
            user->display();
        }
    }

private:
    std::vector<std::unique_ptr<User>> users; // Use smart pointers for memory management
};

int main() {
    UserManager userManager;

    // Try to add users
    try {
        userManager.addUser("Alice", 30);
        userManager.addUser("Bob", 25);
    } catch (const std::exception& e) {
        std::cerr << "Error adding user: " << e.what() << std::endl;
    }

    // Attempt to add a user with invalid age
    try {
        userManager.addUser("Charlie", -5); // This will throw an exception
    } catch (const std::exception& e) {
        std::cerr << "Error adding user: " << e.what() << std::endl; // Handle exceptions
    }

    // Display users
    userManager.displayUsers();

    return 0;
}

