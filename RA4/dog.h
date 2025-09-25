#ifndef dog_h
#define dog_h

#include <string>

class Dog {
private:
    std::string name;
    std::string breed;
    int age;

public:
    Dog(const std::string &name, const std::string &breed, int age)
        : name(name), breed(breed), age(age) {}

    std::string getName() const;
    std::string getBreed() const;
    int getAge() const;

    void setName(const std::string &newName);
    void setBreed(const std::string &newBreed);
    void setAge(int newAge);
    
    bool operator==(const Dog &other) const;
    bool operator!=(const Dog &other) const;

    // Comparing their ages.
    bool operator<(const Dog &other) const;
    bool operator>(const Dog &other) const;

    // "Breeding logic"
    Dog operator*(Dog other) const;

    // dog : Dog + ageIncrease : int
    Dog operator+(int ageIncrease);

    // ageIncrease : int + dog : Dog
    friend Dog operator+(int ageIncrease, const Dog &dog);
};

#endif