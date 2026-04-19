#include <iostream>

class President {
private:
    // Private constructor to prevent direct instantiation
    President() {
        std::cout << "President instance created.\n";
    }

    // Delete copy constructor and assignment operator to prevent copying
    President(const President&) = delete;
    President& operator=(const President&) = delete;

    // Delete move constructor and assignment operator
    President(President&&) = delete;
    President& operator=(President&&) = delete;

public:
    // Static method to access the single instance
    static President& getInstance() {
        static President instance; // Thread-safe in C++11 and beyond
        return instance;
    }

    void addressNation() const {
        std::cout << "My fellow citizens...\n";
    }
};

int main() {
    President& p1 = President::getInstance();
    p1.addressNation();

    // Uncommenting below lines will result in compilation errors
    // President p2 = p1;                    // Copy not allowed
    // President* p3 = new President();      // Constructor is private

    return 0;
}
