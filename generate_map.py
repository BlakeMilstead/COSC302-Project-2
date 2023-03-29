import random

file = open("map10", "x")

file.write("6\n")
file.write("f 3\n")
file.write("g 1\n")
file.write("G 2\n")
file.write("h 4\n")
file.write("m 7\n")
file.write("r 5\n")

tile_list = ['g','G','h','m','r']

file.write("10 10\n")

for i in range(10):
    for j in range(10):
        file.write(random.choice(tile_list))
        file.write(' ')
    file.write('\n')
    
file.write("0 0\n")
file.write("9 9")