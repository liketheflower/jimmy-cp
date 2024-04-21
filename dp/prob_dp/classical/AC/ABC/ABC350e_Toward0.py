# https://atcoder.jp/contests/abc350/tasks/abc350_e
from functools import cache

N, A, X, Y = map(int, input().split())


@cache
def f(n):
    if n <= 0:
        return 0
    # choos A
    new_n = n // A
    cost_A = f(new_n) + X
    # choose 1 to 6
    """
    f(n) = (f(n) + Y)/6  when i = 1 and (sum(f(n//i) + Y))/6 when i = 2 to 6
    (5/6)f(n) = Y / 6 + sum(f(n//i)i + Y)/6
    5f(n) = Y + sum(f(n//i) + Y)
    """
    cost_B_exp = Y

    for i in range(2, 7):
        new_n = n // i
        cost_B_exp += f(new_n) + Y
    cost_B_exp /= 5
    return min(cost_A, cost_B_exp)


ret = f(N)
print(f"{ret:.7f}")
