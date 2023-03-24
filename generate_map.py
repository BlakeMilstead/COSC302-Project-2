import random

file = open("map1000", "x")

file.write("6\n")
file.write("f 3\n")
file.write("g 1\n")
file.write("G 2\n")
file.write("h 4\n")
file.write("m 7\n")
file.write("r 5\n")

tile_list = ['g','G','h','m','r']

file.write("1000 1000\n")

for i in range(1000):
    for j in range(1000):
        file.write(random.choice(tile_list))
        file.write(' ')
    file.write('\n')
    
file.write("0 0\n")
file.write("999 999")