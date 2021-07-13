# https://www.acmicpc.net/problem/2407 #
def combination(n, r):
    dp = [[0 for _ in range(101)] for __ in range(101)]
    for i in range(1, n + 1):
        for j in range(0, r + 1):
            if (i == j) or (j == 0):
                dp[i][j] = 1
            else:
                dp[i][j] = dp[i - 1][j - 1] + dp[i - 1][j]
    return dp[n][r]

n, m = map(int, input().split())
print(combination(n, m))