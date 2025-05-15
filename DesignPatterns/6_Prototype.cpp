#include <iostream>
#include <string>
#include <memory>

// Base class for cloning
class Sheep {
private:
    std::string name;
    std::string category;

public:
    Sheep(const std::string& name, const std::string& category = "Mountain Sheep")
        : name(name), category(category) {}

    // Copy constructor (used for cloning)
    Sheep(const Sheep& other)
        : name(other.name), category(other.category) {}

    // Clone method using polymorphism
    std::unique_ptr<Sheep> clone() const {
        return std::make_unique<Sheep>(*this); // calls copy constructor
    }

    // Setters
    void setName(const std::string& newName) {
        name = newName;
    }

    void setCategory(const std::string& newCategory) {
        category = newCategory;
    }

    // Getters
    std::string getName() const {
        return name;
    }

    std::string getCategory() const {
        return category;
    }
};

int main() {
    // Original sheep
    Sheep original("Jolly");
    std::cout << "Original Name: " << original.getName() << std::endl;
    std::cout << "Original Category: " << original.getCategory() << std::endl;

    // Clone and modify
    std::unique_ptr<Sheep> cloned = original.clone();
    cloned->setName("Dolly");

    std::cout << "Cloned Name: " << cloned->getName() << std::endl;
    std::cout << "Cloned Category: " << cloned->getCategory() << std::endl;

    return 0;
}
