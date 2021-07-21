# https://www.acmicpc.net/problem/17362 #
# UCPC 2019 Qualifier A #
n = int(input())
n %= 8
if n == 0:
    n = 2
elif n == 7:
    n = 3
elif n == 6:
    n = 4
print(n)