import numpy as np


INPUT_FILENAME = 'input.txt'
OUTPUT_FILENAME = 'output.txt'

INF = 1e9
START_CITY = 0
RESULT_SCORE = 1e9
RESULT_PATH = []   


def input_data(filename): 
    with open(filename, 'r') as f: 
        cost = {}
        n = int(f.readline().strip())
        for index in xrange(n): 
            cost[index] = []

        index = 0
        for line in f: 
            values = line.strip().split()
            for val in values: 
                if int(val) == -1: 
                    cost[index].append(INF)
                else:
                    cost[index].append(int(val))
            index += 1
    return cost


def find_path(cost, current_city, used, current_path, current_score): 
    global RESULT_SCORE
    global RESULT_PATH
                    
    if current_score >= RESULT_SCORE: 
        return 
    if sum(used) == len(used): 
        if current_score + cost[current_city][START_CITY] < RESULT_SCORE: 
            RESULT_SCORE = current_score + cost[current_city][START_CITY]
            RESULT_PATH = current_path + [START_CITY]
        return
    for next_city in xrange(len(used)): 
        if not used[next_city]:
            used[next_city] = True
            find_path(cost, 
                      next_city,
                      used, 
                      current_path + [next_city], 
                      current_score + cost[current_city][next_city])
            used[next_city] = False 


def output_data(filename): 
    with open(filename, 'w') as f: 
        print >> f, RESULT_SCORE
        print >> f, np.array(RESULT_PATH) + 1     
    print RESULT_SCORE
    print np.array(RESULT_PATH) + 1


if __name__ == '__main__': 
    cost = input_data(INPUT_FILENAME)

    used = [False] * len(cost)
    used[START_CITY] = True
    find_path(cost, START_CITY, used, [START_CITY], 0)

    output_data(OUTPUT_FILENAME) 


