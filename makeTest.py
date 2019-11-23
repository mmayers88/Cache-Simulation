import os
import csv
from random import seed
from random import randint

os.remove("text.txt")
NumNums = 100000
seed(1)
with open("text.txt", "w+") as file:
	for i in range(NumNums):
		instruct = randint(0, 9)
		if instruct == 7:
			instruct = randint(0,2)
		address = randint(0, 4294967295)
		address = hex(address)
		address = str(address)
		address = address[2:]
		line = str(str(instruct) +' ' + address)
		file.write("%s" %line)
		file.write("\n")
