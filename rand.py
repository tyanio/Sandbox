import random

rand_data_1 = [str(random.randint(0, 3)) for i in range(10000)]
rand_data_2 = [str(random.randint(0, 3)) for i in range(10000)]
# rand_data = ["s", "a"]
# print(rand_data)
# print(type(rand_data[0]))

with open('rand.txt', 'w') as f:
    f.write(",".join(rand_data_1))
    f.write("\n")
    f.write(",".join(rand_data_2))

