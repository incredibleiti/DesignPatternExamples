#include <iostream>
#include <memory>

class BurgerBuilder; // Forward declaration

class Burger {
private:
    int size_;
    bool cheese_;
    bool pepperoni_;
    bool lettuce_;
    bool tomato_;

public:
    Burger(const BurgerBuilder& builder);

    void print() const {
        std::cout << "Burger size: " << size_ << "\n"
                  << "Cheese: " << (cheese_ ? "Yes" : "No") << "\n"
                  << "Pepperoni: " << (pepperoni_ ? "Yes" : "No") << "\n"
                  << "Lettuce: " << (lettuce_ ? "Yes" : "No") << "\n"
                  << "Tomato: " << (tomato_ ? "Yes" : "No") << "\n";
    }
};

class BurgerBuilder {
public:
    int size_;
    bool cheese_ = false;
    bool pepperoni_ = false;
    bool lettuce_ = false;
    bool tomato_ = false;

    explicit BurgerBuilder(int size) : size_(size) {}

    BurgerBuilder& addCheese() {
        cheese_ = true;
        return *this;
    }

    BurgerBuilder& addPepperoni() {
        pepperoni_ = true;
        return *this;
    }

    BurgerBuilder& addLettuce() {
        lettuce_ = true;
        return *this;
    }

    BurgerBuilder& addTomato() {
        tomato_ = true;
        return *this;
    }

    Burger build() {
        return Burger(*this);
    }

    friend class Burger;
};

// Define the Burger constructor using the builder
Burger::Burger(const BurgerBuilder& builder)
    : size_(builder.size_),
      cheese_(builder.cheese_),
      pepperoni_(builder.pepperoni_),
      lettuce_(builder.lettuce_),
      tomato_(builder.tomato_) {}

int main() {
    Burger myBurger = BurgerBuilder(14)
                        .addPepperoni()
                        .addLettuce()
                        .addTomato()
                        .build();

    myBurger.print();

    return 0;
}
