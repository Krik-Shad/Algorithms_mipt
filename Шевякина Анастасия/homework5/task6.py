massive = [int(i) for i in input().split()]


def count(a):
    compressed_coords = {}
    b = sorted(a)
    ans = 0
    j = 0
    for i in range(len(a)):
        if b[i] not in compressed_coords:
            compressed_coords[b[i]] = j
            j += 1
    cnt = [0]*len(compressed_coords)
    for i in range(len(a)):
        ans += sum(cnt[compressed_coords[a[i]]+1:])
        cnt[compressed_coords[a[i]]] += 1
    return ans


print(count(massive))
