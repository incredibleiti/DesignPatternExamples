#include <iostream>
#include <memory>

// Interface
class Interviewer {
public:
    virtual void askQuestions() const = 0;
    virtual ~Interviewer() = default;
};

// Developer Implementation
class Developer : public Interviewer {
public:
    void askQuestions() const override {
        std::cout << "Asking about design patterns!" << std::endl;
    }
};

// CommunityExecutive Implementation
class CommunityExecutive : public Interviewer {
public:
    void askQuestions() const override {
        std::cout << "Asking about community building" << std::endl;
    }
};

// Abstract HiringManager
class HiringManager {
public:
    virtual ~HiringManager() = default;

    void takeInterview() const {
        std::unique_ptr<Interviewer> interviewer = makeInterviewer();
        interviewer->askQuestions();
    }

protected:
    virtual std::unique_ptr<Interviewer> makeInterviewer() const = 0;
};

// Concrete DevelopmentManager
class DevelopmentManager : public HiringManager {
protected:
    std::unique_ptr<Interviewer> makeInterviewer() const override {
        return std::make_unique<Developer>();
    }
};

// Concrete MarketingManager
class MarketingManager : public HiringManager {
protected:
    std::unique_ptr<Interviewer> makeInterviewer() const override {
        return std::make_unique<CommunityExecutive>();
    }
};

// Example usage
int main() {
    DevelopmentManager devManager;
    devManager.takeInterview();  // Output: Asking about design patterns!

    MarketingManager marketingManager;
    marketingManager.takeInterview();  // Output: Asking about community building.

    return 0;
}
