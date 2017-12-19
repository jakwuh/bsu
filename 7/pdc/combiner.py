#!/usr/bin/env python

# import sys

# def median(mylist):
#     sorts = sorted(mylist)
#     length = len(sorts)
#     if not length % 2:
#         return (sorts[length / 2] + sorts[length / 2 - 1]) / 2.0
#     return sorts[length / 2]

# count = 0
# cur_list = []

# for line in sys.stdin:
#     try:
#         line = line.rstrip(os.linesep)
#         tokens = line.split('\t')

#         if count < 15:
#             count += 1
#             cur_list.append(tokens[0])

#         # print '%s\t%s' % (tokens[0], tokens[1])
#     except Exception:
#         continue
