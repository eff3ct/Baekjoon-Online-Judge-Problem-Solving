import sys, math
input = sys.stdin.readline

N = int(input())
S = list(map(int, input().split()))
sortS = sorted(S)

isPossible = 1
for i in range(N):
    if S[i] == sortS[i]:
        continue
    else:
        x = S[i] * sortS[i]
        s = math.isqrt(x)
        if s * s != x:
            isPossible = 0

if isPossible == 1:
    sys.stdout.write("YES")
else:
    sys.stdout.write("NO")