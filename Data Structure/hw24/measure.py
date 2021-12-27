import time
from tqdm import tqdm
import matplotlib.pyplot as plt
from random import randrange, shuffle
from subprocess import PIPE, run

ELE_MAX = 1000000000
ELE_RNG = 10000


# def gen_testcase(amount):

#     elements = []
#     used = []

#     for _ in tqdm(range(ELE_RNG)):
#         tmp = str(randrange(ELE_MAX))
#         while tmp in elements:
#             tmp = str(randrange(ELE_MAX))
#         elements.append(tmp)

#     tc_str = "{}\n".format(ELE_RNG)
#     tc_str += " ".join(elements)
#     tc_str += "\n{}\n".format(amount)

#     for _ in tqdm(range(amount)):
#         operation = randrange(3)
#         if operation == 1:
#             tmp = str(randrange(ELE_MAX))
#             while tmp in elements or tmp in used:
#                 tmp = str(randrange(ELE_MAX))
#             tc_str += "{} {}\n".format(1, tmp)
#             used.append(tmp)
#         else:
#             tc_str += "0\n"

#     print("Testcases generated.")
#     return tc_str


def gen_base(amount):
    tc_str = "{}\n".format(amount)
    elements = [x for x in range(1, amount)]
    shuffle(elements)

    for x in elements:
        tc_str += "0 {}\n".format(x)

    return tc_str


def gen_testcase(limit, amount):
    tc_str = "{}\n".format(amount)
    for m in range(amount):
        op = randrange(1, 5)
        if op == 1:
            tc_str += "0 {}\n".format(randrange(1, limit))
        if op == 2:
            tc_str += "1 {}\n".format(randrange(1, limit))
        if op == 3 or op == 4:
            tc_str += "2 {}\n".format(randrange(1, limit))

    return tc_str


def _execute(target, amount, testcase, row, col):
    x, y = [], []
    for i in tqdm(range(amount)):
        st = time.time()
        run(
            args="./{}".format(target),
            encoding="utf-8",
            input=testcase,
            shell=True,
            text=True,
            stdout=PIPE,
        )

        if i % 100 == 0:
            x.append(i)
            y.append(time.time() - st)
    print((row - 1) * 3 + col)
    plt.subplot(1, 3, (row - 1) * 3 + col)
    plt.plot(x, y, label=target)
    # plt.title("AVL vs RBT")
    plt.xlabel("Number of operations")
    plt.ylabel("Spend time")
    print("{} drawed".format(target))

    ay = [sum(y) / float(len(y))] * int(amount / 100)
    plt.plot(x, ay, label="{} average".format(target), linestyle="--")


def execute(testcase, op_amount, row, col):
    _execute("rbt", op_amount, testcase, row, col)
    _execute("avl", op_amount, testcase, row, col)


if __name__ == "__main__":
    # testcase = gen_testcase(5000)
    # execute(testcase, 5000)
    # amounts = [10000]
    amounts = [100000]
    row, col = 1, 1
    for n in amounts:
        testcase = gen_base(n)
        col = 1
        for m in [n, 2 * n, 4 * n]:
            # print(row, col)
            tc = testcase + gen_testcase(n, m)
            execute(testcase, 1000, row, col)
            col = col + 1
        row = row + 1

    plt.legend()
    plt.show()
