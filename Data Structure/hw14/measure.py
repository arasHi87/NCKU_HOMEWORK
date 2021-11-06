import time
import random
from tqdm import trange
from subprocess import PIPE, run
from matplotlib import pyplot as plt

ELE_RNG = 10000
OPS_RNG = 10000


def gen_testcase(ops_rng):
    tc_str = ""
    elements = [x for x in range(ELE_RNG)]

    for _ in range(ops_rng):
        tc_str += "0 {} {}\n".format(random.choice(elements),
                                     random.choice(elements))

    for i in range(ELE_RNG):
        tc_str += "1 {}\n".format(i)

    return tc_str


def _execute(target):
    x, y = [[], []], [[], []]
    for i in trange(OPS_RNG):
        testcase = gen_testcase(i)
        for j in [0, 1]:
            st = time.time()
            run(args='./{}'.format(target[j]), encoding='utf-8', input=testcase,
                shell=True, text=True, stdout=PIPE)
            ct = time.time() - st
            if i % 100 == 0:
                x[j].append(i)
                y[j].append(ct)
    for i in [0, 1]:
        plt.plot(x[i], y[i], label=target[i])
        print("{} drawed".format(target[i]))

        ay = [sum(y[i]) / float(len(y[i]))] * int(OPS_RNG / 100)
        plt.plot(x[i], ay, label="{} average".format(
            target[i]), linestyle="--")


def execute():
    _execute(["hdsu", "wdsu"])

    plt.title("Height vs Weight unoin in disjoinset")
    plt.xlabel("Number of operations")
    plt.ylabel("Spend time")
    plt.legend()
    plt.show()


if __name__ == '__main__':
    execute()
