import time
from tqdm import tqdm
import matplotlib.pyplot as plt
from random import randrange
from subprocess import PIPE, run

ELE_MAX = 1000000000
ELE_RNG = 10000


def gen_testcase(amount):

    elements = []
    used = []

    for _ in tqdm(range(ELE_RNG)):
        tmp = str(randrange(ELE_MAX))
        while tmp in elements:
            tmp = str(randrange(ELE_MAX))
        elements.append(tmp)

    tc_str = "{}\n".format(ELE_RNG)
    tc_str += " ".join(elements)
    tc_str += "\n{}\n".format(amount)

    for _ in tqdm(range(amount)):
        operation = randrange(2)
        if operation:
            tmp = str(randrange(ELE_MAX))
            while tmp in elements or tmp in used:
                tmp = str(randrange(ELE_MAX))
            tc_str += "{} {}\n".format(1, tmp)
            used.append(tmp)
        else:
            tc_str += "0\n"

    print("Testcases generated.")
    return tc_str


def _execute(target, amount, testcase):
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
    plt.plot(x, y, label=target)
    print("{} drawed".format(target))

    ay = [sum(y) / float(len(y))] * int(amount / 100)
    plt.plot(x, ay, label="{} average".format(target), linestyle="--")


def execute(testcase, op_amount):
    _execute("Bheap", op_amount, testcase)
    _execute("Leftist", op_amount, testcase)

    print("dsadas")
    plt.title("Bheap vs Leftist")
    plt.xlabel("Number of operations")
    plt.ylabel("Spend time")
    plt.legend()
    plt.show()


if __name__ == "__main__":
    testcase = gen_testcase(5000)
    execute(testcase, 5000)
