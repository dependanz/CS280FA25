/**
 * Driver program for the Dog class.
 */
#include <iostream>
#include "dog.h"

using namespace std;

int main() {
    Dog dog1("Buddy", "Golden Retriever", 3);
    Dog dog2("Max", "Beagle", 5);

    cout << "Dog 1: " << dog1.getName() << ", Breed: " << dog1.getBreed() << ", Age: " << dog1.getAge() << endl;
    cout << "Dog 2: " << dog2.getName() << ", Breed: " << dog2.getBreed() << ", Age: " << dog2.getAge() << endl;

    // Compare dogs
    if (dog1 == dog2) {
        cout << "Dog 1 is the same as Dog 2" << endl;
    } else {
        cout << "Dog 1 is different from Dog 2" << endl;
    }

    if (dog1 < dog2) {
        cout << "Dog 1 is younger than Dog 2" << endl;
    } else if (dog1 > dog2) {
        cout << "Dog 1 is older than Dog 2" << endl;
    } else {
        cout << "Dog 1 and Dog 2 are of the same age" << endl;
    }

    // Breed two dogs
    Dog puppy = dog1 * dog2;
    cout << "Puppy: " << puppy.getName() << ", Breed: " << puppy.getBreed() << ", Age: " << puppy.getAge() << endl;

    // Increase age of dog1 by 2 using friend function
    dog1 = 2 + dog1;
    cout << "After aging, Dog 1's new age: " << dog1.getAge() << endl;

    dog1 = dog1 + 2;
    cout << "After aging (again), Dog 1's new age: " << dog1.getAge() << endl;

    return 0;
}