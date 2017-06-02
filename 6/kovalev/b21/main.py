INF = 1e9
def get_root(parent, x):
    if parent[x] == x:
        return x
    parent[x] = get_root(parent, parent[x])
    return parent[x]

def union(parent, a, b):
    parent[get_root(parent, a)] = get_root(parent, b)

graph = []
with open("input.txt") as f:
    for line in f:
        graph.append(map(lambda x: INF if int(x) == -1 else int(x), line.split()))

parent = {}
for i in range(len(graph)):
    parent[i] = i
    
remaining_edges = len(graph) - 1

weight = 0
james = 0
while remaining_edges > 0:
    for i in range(len(graph)):
        for j in range(len(graph)):
            if graph[i][j] == weight:
                if get_root(parent, i) != get_root(parent, j):
                    print [i + 1, j + 1]
                    james += weight
                    union(parent, i, j)
                    remaining_edges -= 1
    weight += 1

print james
