import sys
import csv


out_file = open(sys.argv[2], "w")
trainingSet = open(sys.argv[1])

for row in trainingSet:
	if row.startswith( "#" ) or not row.strip():
		continue
	else:
		values = row.rstrip().split(',')
		del values[0]
		line = ' '.join(values)
		line = line + '\n'
		out_file.write(line)

out_file.close()

