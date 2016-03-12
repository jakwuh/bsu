#!/usr/bin/python

infile = open('in.txt', 'r')
outfile = open('out.txt', 'w')

n = int(infile.readline().split()[0]);
total = 0
left = [0] * 250002
right = [0] * 250002

for i in range(0, n):
	data = infile.readline().split()
	left[i] = int(data[0])
	right[i] = int(data[1])
	total += left[i] + right[i]

steps = [2E9] * 1500012
steps[0] = 0

minimum = 0; maximum = 0
for i in range(0, n):
	for j in range(maximum, minimum - 1, -1):
		if (steps[j] == 2E9):
			continue
		tmp = steps[j]
		steps[j] = 2E9
		if (tmp < steps[j + left[i]]): 
			steps[j + left[i]] = tmp;
		if (tmp + 1 < steps[j + right[i]]): 
			steps[j + right[i]] = tmp + 1;
	maximum += max(left[i], right[i]);
	minimum += min(left[i], right[i]);

k = 0;
middleLeft = total / 2;
middleRight = (total + 1) / 2;
while (steps[middleLeft - k] == 2E9 and steps[middleRight + k] == 2E9):
	++k;

outfile.write(str(min(steps[middleLeft - k], steps[middleRight + k])))