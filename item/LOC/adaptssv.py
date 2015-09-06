import sys
import csv


out_file = open(sys.argv[2], "w")
trainingSet = open(sys.argv[1])

for row in trainingSet:
	line = row.rstrip('\n')
	t = line.rstrip(',')
	t = t + '\n'
	out_file.write(t)

out_file.close()

