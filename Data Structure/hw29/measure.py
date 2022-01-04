import random
import string
from subprocess import PIPE, run

import matplotlib.pyplot as plt

M = 100000
N = 10000


def get_random_str():
    return "".join(random.choices(string.ascii_lowercase + string.digits, k=20))


if __name__ == "__main__":
    # generate test case
    string_used = [get_random_str() for _ in range(N)]
    string_unused = [get_random_str() for _ in range(N // 2)]
    string_test = []
    test_case = ""
    for i in range(N):
        test_case += string_used[i] + "\n"
    for _ in range(N // 2):
        _str = string_used[random.randint(0, N // 2 - 1)]
        string_test.append(_str)
        test_case += _str + "\n"
    for _ in range(N // 2):
        _str = string_unused[random.randint(0, N // 2 - 1)]
        string_test.append(_str)
        test_case += _str + "\n"

    # run process
    x, y, = (
        [],
        [],
    )
    for _h in range(1, 11):
        cnt = 0
        tc = "{} {} {}\n{}".format(N, M, _h, test_case)
        result = run(
            args="./a.out",
            encoding="utf-8",
            input=tc,
            shell=True,
            text=True,
            stdout=PIPE,
        )
        result = result.stdout.split("\n")

        # count false positive
        for i in range(len(result)):
            if result[i] == "1" and string_test[i] not in string_used:
                cnt += 1
        print(_h, cnt)
        x.append(_h)
        y.append(cnt / N)

    plt.plot(x, y, label="False Positive")
    plt.title("Bloom Filter FP probability")
    plt.xlabel("h")
    plt.ylabel("FP")
    plt.legend()
    plt.show()
