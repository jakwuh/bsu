#!/usr/bin/env python

import sys

for line in sys.stdin:
    line = line.strip()

    type, a_or_b, b_or_c = line.split()

    if type == '1':
        print '%s\t%s\t%s' % (b_or_c, 'a', a_or_b)
    elif type == '2':
        print '%s\t%s\t%s' % (a_or_b, 'c', b_or_c)

# import sys
# import os

# for line in sys.stdin:
#     try:
#         line = line.rstrip(os.linesep)
#         tokens = line.split('\t')

#         print '%s\t%s' % (tokens[0], tokens[1])
#     except Exception:
#         continue

# import sys
#
# for line in sys.stdin:
#     try:
#         line = line.strip()
#         words = line.split()
#         for word in words:
#             num = int(word)
#             print '%s\t%s' % (1, '1U' + str(num))
#     except Exception:
#         continue

# import sys

# for line in sys.stdin:
#     line = line.strip()
#     words = line.split()
#     for word in words:
#         print '%s\t%s' % (word, 1)
