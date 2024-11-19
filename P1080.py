# https://www.acwing.com/solution/content/1062/
# 原理见上述链接
# 因为不想写高精度，所以用了python

if __name__ == "__main__":
    n = int(input())
    KingLeft, KingRight = map(int, input().split())
    data = []
    for i in range(n):
        a, b = map(int, input().split())
        data.append((a, b, a * b))
    # 根据a*b排序
    data.sort(key=lambda x: x[2])
    ans = 0
    mul = KingLeft
    for i in range(n):
        val = mul // data[i][1]
        mul *= data[i][0]
        ans = max(ans, val)
    print(ans)