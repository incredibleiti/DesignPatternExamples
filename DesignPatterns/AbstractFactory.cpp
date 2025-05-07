#include <iostream>
#include <memory>

// Door interface
class Door {
public:
    virtual void getDescription() const = 0;
    virtual ~Door() = default;
};

// Wooden Door
class WoodenDoor : public Door {
public:
    void getDescription() const override {
        std::cout << "I am a wooden door\n";
    }
};

// Iron Door
class IronDoor : public Door {
public:
    void getDescription() const override {
        std::cout << "I am an iron door\n";
    }
};

// Door Fitting Expert interface
class DoorFittingExpert {
public:
    virtual void getDescription() const = 0;
    virtual ~DoorFittingExpert() = default;
};

// Carpenter
class Carpenter : public DoorFittingExpert {
public:
    void getDescription() const override {
        std::cout << "I can only fit wooden doors\n";
    }
};

// Welder
class Welder : public DoorFittingExpert {
public:
    void getDescription() const override {
        std::cout << "I can only fit iron doors\n";
    }
};

// Abstract Factory Interface
class DoorFactory {
public:
    virtual std::unique_ptr<Door> makeDoor() const = 0;
    virtual std::unique_ptr<DoorFittingExpert> makeFittingExpert() const = 0;
    virtual ~DoorFactory() = default;
};

// Wooden Door Factory
class WoodenDoorFactory : public DoorFactory {
public:
    std::unique_ptr<Door> makeDoor() const override {
        return std::make_unique<WoodenDoor>();
    }

    std::unique_ptr<DoorFittingExpert> makeFittingExpert() const override {
        return std::make_unique<Carpenter>();
    }
};

// Iron Door Factory
class IronDoorFactory : public DoorFactory {
public:
    std::unique_ptr<Door> makeDoor() const override {
        return std::make_unique<IronDoor>();
    }

    std::unique_ptr<DoorFittingExpert> makeFittingExpert() const override {
        return std::make_unique<Welder>();
    }
};

// Main usage
int main() {
    // Wooden door + carpenter
    WoodenDoorFactory woodenFactory;
    auto woodenDoor = woodenFactory.makeDoor();
    auto carpenter = woodenFactory.makeFittingExpert();
    woodenDoor->getDescription();      // Output: I am a wooden door
    carpenter->getDescription();       // Output: I can only fit wooden doors

    // Iron door + welder
    IronDoorFactory ironFactory;
    auto ironDoor = ironFactory.makeDoor();
    auto welder = ironFactory.makeFittingExpert();
    ironDoor->getDescription();        // Output: I am an iron door
    welder->getDescription();          // Output: I can only fit iron doors

    return 0;
}
