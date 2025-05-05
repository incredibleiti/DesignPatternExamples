#include <iostream>

// Interface
class Door {
public:
    virtual float getWidth() const = 0;
    virtual float getHeight() const = 0;
    virtual ~Door() = default;
};

// Concrete class
class WoodenDoor : public Door {
private:
    float width;
    float height;

public:
    WoodenDoor(float width, float height)
        : width(width), height(height) {}

    float getWidth() const override {
        return width;
    }

    float getHeight() const override {
        return height;
    }
};

// Example usage
int main() {
    WoodenDoor door(35.5f, 80.0f);
    std::cout << "Width: " << door.getWidth() << ", Height: " << door.getHeight() << std::endl;
    return 0;
}
