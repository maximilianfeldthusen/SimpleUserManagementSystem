
## Documentation

### SimpleUserManagementSystem

This C++ code implements a simple user management system using classes, exception handling, and smart pointers for memory management. Let's break down the code step-by-step:

### 1. Includes and Namespace
```cpp
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <stdexcept>
```
These include directives allow the program to use various standard library features:
- `<iostream>` for input and output (using `std::cout` and `std::cerr`).
- `<string>` for using the `std::string` class.
- `<vector>` for using the `std::vector` container.
- `<memory>` for smart pointers (specifically `std::unique_ptr`).
- `<stdexcept>` for standard exception classes like `std::invalid_argument`.

### 2. User Class
```cpp
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
```
- **Constructor**: Takes a `name` and `age` as parameters. If the `age` is negative, it throws an `std::invalid_argument` exception.
- **display()**: A member function that prints out the user's name and age.
- **Private Members**: `name` and `age` are private, ensuring they can only be accessed through the class's public methods.

### 3. UserManager Class
```cpp
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
```
- **addUser()**: This method takes a `name` and `age` and validates them. If the name is empty or longer than 50 characters, it throws an exception. If the input is valid, it creates a new `User` object using `std::make_unique` (which returns a `std::unique_ptr` to handle dynamic memory safely) and adds it to the `users` vector.
- **displayUsers()**: This method iterates through the `users` vector and calls the `display()` method of each `User` object to output their information.
- **Private Member**: `users` is a vector of `std::unique_ptr<User>`, ensuring that the memory for `User` objects is managed automatically (no need to manually delete them).

### 4. Main Function
```cpp
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
```
- **Creating UserManager**: An instance of `UserManager` is created.
- **Adding Users**: The program tries to add two users, "Alice" and "Bob". If any exceptions occur during this process, they are caught, and an error message is printed to the standard error stream.
- **Invalid User Attempt**: The program attempts to add a user "Charlie" with a negative age, which will cause an exception to be thrown and caught, with an error message printed.
- **Displaying Users**: Finally, the program calls `displayUsers()` to print the details of all valid users that were added.

### Summary
The code demonstrates:
- Class design and encapsulation by organizing user-related functionality into `User` and `UserManager` classes.
- Exception handling to manage invalid inputs gracefully.
- Usage of smart pointers for automatic memory management, preventing memory leaks.
- Basic input validation to ensure data integrity. 


