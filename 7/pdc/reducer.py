#!/usr/bin/env python

import sys

last_b = None
a_values = []
c_values = []

for line in sys.stdin:
    line = line.strip()

    try:
        b, type, a_or_c  = line.split('\t')

        if b == last_b:
            if type == 'a':
                a_values.append(a_or_c)
            else:
                c_values.append(a_or_c)

        else:
            if last_b:
                for a in a_values:
                    for c in c_values:
                        print '%s\t%s\t%s' % (a, last_b, c)

            a_values = [a_or_c] if type == 'a' else []
            c_values = [a_or_c] if type == 'c' else []

        last_b = b
    except:
        continue

if last_b:
    for a in a_values:
        for c in c_values:
            print '%s\t%s\t%s' % (a, last_b, c)

# data_dict = defaultdict(list)

# def mean(data_list):
#     return sum(data_list)/float(len(data_list)) if len(data_list) else 0
# def median(mylist):
#     sorts = sorted(mylist)
#     length = len(sorts)
#     if not length % 2:
#         return (sorts[length / 2] + sorts[length / 2 - 1]) / 2.0
#     return sorts[length / 2]


# for line in sys.stdin:
#     try:
#         line = line.rstrip(os.linesep)
#         serial_id, duration = line.split("\t")
#         data_dict[serial_id].append(float(duration))
#     except Exception:
#         pass
# for k,v in data_dict.items():
#     print "%s\t%s\t%s" %(k, mean(v), median(v))

# from operator import itemgetter
# import sys
#
# current_count = 0
# current_sum = 0
#
# for line in sys.stdin:
#     try:
#         line = line.strip()
#
#         # try:
#         word, count_and_sum = line.split('\t')
#         local_count, local_sum = count_and_sum.split('U');
#
#         current_count += int(local_count)
#         current_sum += int(local_sum)
#
#     except Exception:
#         continue
#
# print '%s\t%s' % (1, '{}U{}'.format(current_count, current_sum))

# from operator import itemgetter
# import sys

# current_word = None
# current_count = 0
# word = None

# for line in sys.stdin:
    # line = line.strip()

    # word, count = line.split('\t', 1)

    # try:
    #     count = int(count)
    # except ValueError:
    #     continue

    # if current_word == word:
    #     current_count += count
    # else:
    #     if current_word:
    #         print '%s\t%s' % (current_word, current_count)
    #     current_count = count
    #     current_word = word

# if current_word == word:
    # print '%s\t%s' % (current_word, current_count)
