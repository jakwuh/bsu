import sys

from scipy.optimize import linprog
from numpy.random import random_sample

# What is x vector:
# x = {x_11, x_12, x_21, x_22}


mode = raw_input("Enter d to use defaults, c to input variables\n")
if mode == "d":
    print "Defaults:"

    print "A1 oil cost:\t 5"
    print "A2 oil cost:\t 4"
    print "A1-B1 cost:\t 2"
    print "A1-B2 cost:\t 3"
    print "A2-B1 cost:\t 2"
    print "A2-B2 cost:\t 3\n"
    c = [7, 8, 7, 8]

    print "B1 from 1 A1 produces:\t 3"
    print "B1 from 1 A2 produces:\t 5"
    print "B2 from 1 A1 produces:\t 4"
    print "B2 from 1 A2 produces:\t 3\n"
    A_ub = [[-3, 0, -5, 0], [0, -4, 0, -3], [0, 1, 1, 0]]

    print "B1 must produce:\t 5000"
    print "B2 must produce:\t 5200\n"

    print "A1/B2 <-> A2/B1 capacity:\t 10000\n"
    b_ub = [-5000,
            -5200,
            10000]

    z = 1./3. * random_sample() + 1./3.
    print "Z: {}\n".format(z)

    A_eq = [[0, 1, -z, 0]]
    b_eq = [0]

elif mode == "c":

    print "Input variables:"

    a1_prod = float(raw_input("A1 oil cost:\t "))
    a2_prod = float(raw_input("A2 oil cost:\t "))
    a1b1_transfer = float(raw_input("A1-B1 cost:\t "))
    a1b2_transfer = float(raw_input("A1-B2 cost:\t "))
    a2b1_transfer = float(raw_input("A2-B1 cost:\t "))
    a2b2_transfer = float(raw_input("A2-B2 cost:\t "))
    c = [a1_prod + a1b1_transfer,
        a1_prod + a1b2_transfer,
        a2_prod + a2b1_transfer,
        a2_prod + a2b2_transfer]

    prod_b1a1 = float(raw_input("B1 from 1 A1 produces:\t "))
    prod_b1a2 = float(raw_input("B1 from 1 A2 produces:\t "))
    prod_b2a1 = float(raw_input("B2 from 1 A1 produces:\t "))
    prod_b2a2 = float(raw_input("B2 from 1 A2 produces:\t "))
    A_ub = [[-prod_b1a1, 0, -prod_b1a2, 0],
            [0, -prod_b2a1, 0, -prod_b2a2],
            [0, 1, 1, 0]]

    produce_b1 = float(raw_input("B1 must produce:\t "))
    produce_b2 = float(raw_input("B2 must produce:\t "))

    cap = float(raw_input("A1-B2 <-> A2-B1 capacity:\t "))
    b_ub = [-produce_b1,
            -produce_b2,
            cap]

    a = 1. / 3.
    b = 2. / 3.
    z = (b - a) * random_sample() + a

    print "Z: {}\n".format(z)

    A_eq = [[0, 1, -z, 0]]
    b_eq = [0]

else:
    print("Bad input.")
    sys.exit()

res = linprog(c, A_ub, b_ub, A_eq, b_eq)


print "\nResult:"
print res.message

if res.success:
    print "\nMinimum cost:"
    print res.fun
    print "\nOptimal plan:"
    print res.x
