# main.py
from knapsack import knapsack
from .utils import knapsack_dynamic

def pair_contains(pairs, value):
    for pair in pairs:
        if pair[0] <= value <= pair[1]:
            return True
    return False


def solve(a, b, B, f):
    f_max = max(item[1] for item in f)
    a_last = a[len(a) - 1]
    a_first = a[0]

    # first case
    if f_max <= a_first:
        return knapsack(b, a).solve(B)

    # second case
    if f_max >= a_last:
        fs = range(0, len(b) * a_last)
        fs_filtered = (i for i in fs if not pair_contains(f, i))
        f_best = 0
        items_best = []
        for f_current in fs_filtered:
            [f_, items_] = knapsack_dynamic(a, b, B, f_current)
            if f_ > f_best:
                f_best = f_
                items_best = items_

        return [f_best, items_best]

    # third case
    t = len(a) - 1
    for i, a_i in enumerate(a):
        if a_i > f_max:
            t = i
            break

    [f_best, items_best] = knapsack(b, a).solve(B)

    item_greater = False
    for item in items_best:
        if item > t:
            item_greater = True

    if item_greater:
        return [f_best, items_best]
    else:
        fs = range(0, t * a_last)
        fs_filtered = (i for i in fs if not pair_contains(f, i))
        f_best = 0
        items_best = []
        for f_current in fs_filtered:
            [f_, items_] = knapsack_dynamic(a, b, B, f_current)
            if f_ > f_best:
                f_best = f_
                items_best = items_

        return [f_best, items_best]

size = [9, 11, 15, 21, 25, 34, 41, 52]
weight = [10, 12, 16, 22, 26, 35, 42, 53]

f = [[1, 2], [10, 20], [21, 25]]
capacity = 100

print(solve(weight, size, capacity, f))
