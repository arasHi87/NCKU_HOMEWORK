from math import sqrt
from function import func


def __lt__(self, other):
    print(self)
    return self.intAttribute < other.intAttribute


def brute_force(bounds):
    ans = (10000000000.0, 0.0, 0.0)
    precision = 1
    for x in range(bounds[0][0] * precision, bounds[0][1] * precision):
        for y in range(bounds[1][0] * precision, bounds[1][1] * precision):
            tx, ty = x / precision, y / precision
            temp = func(tx, ty)
            if temp < ans[0]:
                ans = (temp, tx, ty)
    return ans


class LocalBeamSearch:
    def __init__(self, bounds, width=10000):
        self.width = width
        # the bounds should be like [(x_min, x_max), (y_min, y_max)]
        self.x_bnd, self.y_bnd = bounds
        # the start and end point for x and y
        self.sx, self.ex = self.x_bnd
        self.sy, self.ey = self.y_bnd
        self.storage = []  # use to save the top width best ans
        self.result = (func(0, 0), 0, 0)  # use to save the best result
        self.d = [(1.0, -1.0), (1.0, 0.0), (1.0, 1.0), (0.0, -1.0),
                  (0.0, 1.0), (-1.0, -1.0), (-1.0, 0.0), (-1.0, 1.0)]
        self.block = sqrt(width)
        self.base = 1  # use to control precision

    def get_ans(self):
        # run first time to get rough answer
        self._runLBS()

        # improve the accuracy of the top sqrt(width) best answers to reduce deviation and re-run
        self.storage = self.storage[:int(self.block)]
        self.d = [tuple(y / self.width for y in x) for x in self.d]
        self._coreLBS()

        return self.result

    def _runLBS(self):
        # handle the interval of x and y
        x_blk = abs((self.sx - self.ex) / self.block)
        y_blk = abs((self.sy - self.ey) / self.block)

        # init start points
        for i in range(int(self.block)):
            for j in range(int(self.block)):
                x = self.sx + x_blk * i
                y = self.sy + y_blk * j
                self.storage.append((func(x, y), x, y))

        # run algorithm core
        self._coreLBS()

    def _coreLBS(self):
        # find the answer
        for i in range(len(self.storage)):
            while True:
                # save this step best ans and coordinate
                # now ans, x and y, use to save the found minimum temporarily
                [nans, nx, ny] = self.storage[i]

                # find the smallest value in the eight directions
                for j in range(len(self.d)):
                    dx, dy = nx+self.d[j][0], ny+self.d[j][1]
                    dans = func(dx, dy)
                    if dans < nans:
                        nans, nx, ny = dans, dx, dy

                # check if found value diff with origin, if so then change value and keep find
                if nans < self.storage[i][0]:
                    self.storage[i] = (nans, nx, ny)
                else:
                    break

        # sort storage and get the best ans
        self.storage.sort()
        self.result = self.storage[0]


if __name__ == "__main__":
    bounds = []
    ans = []
    atype = ["BF", "LBS"]
    with open("input.txt", "r") as fp:
        for line in fp.read().split():
            bounds.append(tuple(map(int, line.split(","))))
    ans.extend(list(brute_force(bounds)))
    ans.extend(list(LocalBeamSearch(bounds).get_ans()))

    # round ans
    for i in range(len(ans)):
        ans[i] = str(round(ans[i], 3 if i % 3 == 0 else None))

    # convert all int to string to format print length
    size = len(max(ans, key=len))
    for i in range(2):
        print("%s → Result X of %s" % (ans[3*i+1].ljust(size), atype[i]))
        print("%s → Result Y of %s" % (ans[3*i+2].ljust(size), atype[i]))
        print("%s → Result Z of %s" % (ans[3*i+0].ljust(size), atype[i]))
