from scipy.optimize import basinhopping
from function import func


def f(a):
    return func(a[0], a[1])


# the bounds and answer
x_min, x_max = -50, 60
y_min, y_max = -50, 50
bounds = [(x_min, x_max), (y_min, y_max)]

x0 = [0.0, 0.0]
minimizer_kwargs = dict(method="L-BFGS-B", bounds=bounds)
res = basinhopping(f, x0, niter=10000, minimizer_kwargs=minimizer_kwargs)

print(res)
