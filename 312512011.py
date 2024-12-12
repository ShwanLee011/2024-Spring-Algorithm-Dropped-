def distance(a, b):
    return float((a[0]-b[0])**2 + (a[1]-b[1])**2)**0.5

def bf(rests, n_rests):
    min_dist = distance((-10000, -10000), (10000, 10000))
    for i in range(n_rests):
        for j in range(i + 1, n_rests):
            if distance(rests[i], rests[j]) < min_dist:
                min_dist = distance(rests[i], rests[j])
    return min_dist

def stripclose(temp, n, d):

    min_d = d
    temp = sorted(temp, key=lambda x: x[1])
    i = 0
    while i < n:
        j = i + 1
        while j < n:
            if (temp[j][1] - temp[i][1]) >= min_d:
                break
            if (distance(temp[i], temp[j])) < min_d:
                min_d = distance(temp[i], temp[j])
            j += 1
        i += 1
    return min_d
def min(x, y):
    return x if x < y else y
def endcondition(rests, n):
    if n <= 3:
        return bf(rests, n)
    mid = n // 2
    midp = rests[mid]
    l = endcondition(rests[:mid], mid)
    r = endcondition(rests[mid:], n - mid)
    d = min(l, r)
    temp = []
    ix = 0
    while ix < n:
        if abs(rests[ix][0] - midp[0]) < d:
            temp.append(rests[ix])
        ix += 1
    return min(d, stripclose(temp, len(temp), d))

def closestpoints(rests, n_rests):
    rests = sorted(rests, key=lambda x: x[0])
    return endcondition(rests, n_rests)

def main():
    n_case = int(input())
    for _ in range(n_case):
        n_rests = int(input())
        rests = [tuple(map(float, input().split())) for _ in range(n_rests)]
        dist = float(closestpoints(rests, n_rests) )
        print("{:.6f}".format(dist))

if __name__ == "__main__":
    main()