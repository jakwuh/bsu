__author__ = 'OlgaVorokh'

import numpy


INF = 1e9


def input_data(graph):
    with open("input.txt", 'r') as f:
        n = f.readline()
        n = int(n)
            
        for i, line in enumerate(f):
            graph.append(map(lambda x: int(x) if int(x) != -1 else INF, line.split()))
        
    return n


def floyd_warshall_algorithm(n, graph, parent): 
    for k in xrange(n): 
        for i in xrange(n):
            for j in xrange(n): 
                if graph[i][k] < INF and graph[k][j] < INF:
                    if graph[i][j] > graph[i][k] + graph[k][j]:
                        graph[i][j] = graph[i][k] + graph[k][j]
                        parent[i][j] = k


def find_path(left, right, graph, parent):
    if parent[left][right] == -1: 
        return [left]
    part1 = find_path(left, parent[left][right], graph, parent)
    part2 = find_path(parent[left][right], right, graph, parent)
    return part1 + part2 
    

def output_data(graph, parent, path):
    print "Distance:"
    print graph
    print


    print "Path from start vertex 1 to finish vertex 9"
    print numpy.array(path) + 1
    print


def main():
    graph = []
    n = input_data(graph)
    
    parent = []
    for index in xrange(n): 
        parent.append([-1] * n)

    floyd_warshall_algorithm(n, graph, parent)

    start_vertex = 0
    end_vertex = 8
    path = find_path(start_vertex, end_vertex, graph, parent)
    path += [end_vertex]

    output_data(graph, parent, path)


main()    

