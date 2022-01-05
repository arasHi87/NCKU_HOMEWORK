import random
import time
from subprocess import PIPE, run

import matplotlib.pyplot as plt
from tqdm import trange


class Generator:
    def __init__(self, amount):
        self.amount = amount

    def get_test_case(self, type):
        if type == 1:
            return self._quick()
        if type == 4:
            return self._heap()
        return self._universal(type)

    def _universal(self, type):
        test_case = "{}\n".format(type)
        for i in range(self.amount, 0, -1):
            test_case += "{} ".format(i)
        test_case += "\n"
        return test_case

    def _quick(self):
        test_case = "1\n"
        for _ in range(self.amount):
            test_case += "{} ".format(1)
        test_case += "\n"
        return test_case

    def _heap(self):
        test_case = "3\n"
        elements = [i for i in range(self.amount)]
        random.shuffle(elements)
        for i in elements:
            test_case += "{} ".format(i)
        test_case += "\n"
        return test_case


if __name__ == "__main__":
    name = [
        "Insertion sort",
        "Quick sort",
        "Recursive Merge sort",
        "Iterative Merge sort",
        "Heap sort",
    ]
    for type in range(5):
        x, y = [], []
        tmp = 0
        for amount in [1000, 2000, 3000, 4000, 5000, 6000]:
            print("Running {} with amount of {}".format(name[type], amount))
            test_case = Generator(amount).get_test_case(type)
            for _ in trange(20):
                st = time.time()
                run(
                    args="./a.out",
                    encoding="utf-8",
                    input=test_case,
                    shell=True,
                    text=True,
                    stdout=PIPE,
                )
                tmp += time.time() - st
            x.append(amount)
            y.append(tmp / 20)
        plt.plot(x, y, label=name[type])

    plt.title("Each sort measure")
    plt.xlabel("Amount")
    plt.ylabel("Spend time")
    plt.legend()
    plt.show()
