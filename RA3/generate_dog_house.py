import random
import argparse
from math import floor

parser = argparse.ArgumentParser()
parser.add_argument(
    "--write_file",
    action="store_false",
)
args = parser.parse_args()

# List of one-word dog breed names
breeds = [
    "Beagle", "Poodle", "Bulldog", "Boxer", "Collie", "Dachshund", "Dalmatian",
    "Husky", "Labrador", "Mastiff", "Pointer", "Pug", "Retriever", "Rottweiler",
    "Shepherd", "Terrier", "Akita", "Chihuahua", "Corgi", "Basenji", "Doberman", "Weimaraner"
]

# Generate 10 lines; each line will have between 14 and 24 randomly chosen breed names
if not args.write_file:
    with open("dog_house.txt", "w") as f:
        for _ in range(100):
            count = random.randint(10, 100)
            dogs = [random.choice(breeds) for _ in range(count)]
            if random.random() < 0.01:
                cat_idx = floor(random.random() * len(dogs))
                dogs[cat_idx] = "\\cat"
            line = " ".join(dogs)
            f.write(line + "\n")
else:
    for _ in range(100):
        count = random.randint(10, 100)
        dogs = [random.choice(breeds) for _ in range(count)]
        if random.random() < 0.01:
            cat_idx = floor(random.random() * len(dogs))
            dogs[cat_idx] = "\\cat"
        line = " ".join(dogs)
        print(line)