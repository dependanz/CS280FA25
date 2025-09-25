#include <string>
#include "dog.h"

using namespace std;

std::string Dog::getName() const {
    return name;
}

std::string Dog::getBreed() const {
    return breed;
}

int Dog::getAge() const {
    return age;
}

void Dog::setName(const std::string &newName) {
    name = newName;
}

void Dog::setBreed(const std::string &newBreed) {
    breed = newBreed;
}

void Dog::setAge(int newAge) {
    age = newAge;
}

bool Dog::operator==(const Dog &other) const {
    return name == other.name && breed == other.breed && age == other.age;
}

bool Dog::operator!=(const Dog &other) const {
    return !(*this == other);
}

bool Dog::operator<(const Dog &other) const {
    return age < other.age;
}

bool Dog::operator>(const Dog &other) const {
    return age > other.age;
}

Dog Dog::operator*(Dog other) const {
    // Breeding logic
    return Dog(
        name + "-" + other.name,
        breed + "-" + other.breed,
        0
    );
}

Dog Dog::operator+(int ageIncrease) {
    return Dog(
        name,
        breed,
        age + ageIncrease
    );
}

Dog operator+(int ageIncrease, const Dog &dog) {
    return Dog(dog.name, dog.breed, dog.age + ageIncrease);
}