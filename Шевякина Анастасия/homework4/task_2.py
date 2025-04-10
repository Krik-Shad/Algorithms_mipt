n = int(input())
coordinates = []
for i in range(n):
    l = input().split()
    x = int(l[0])
    y = int(l[1])
    coordinates.append([x, y])

def merge(lhs, rhs):
    result = []
    i = j = 0

    while len(result) < len(rhs)+len(lhs) and i<len(lhs) and j<len(rhs):
        if (lhs[i][0] < rhs[j][0]):
            result.append(lhs[i])
            i+=1
        elif lhs[i][0] == rhs[j][0]:
            if lhs[i][1] < rhs[j][1]:
                result.append(lhs[i])
                i+=1
            else:
                result.append(rhs[j])
                j+=1
        else:
            result.append(rhs[j])
            j+=1
    if i < len(lhs):
        result += lhs[i:]
    if j < len(rhs):
        result += rhs[j:]
    return result

def merge_sort(a):
    if len(a)<=1:
        return a
    mid = len(a) // 2
    left = merge_sort(a[:mid])
    right = merge_sort(a[mid:])

    return merge(left, right)

def coordinates_sort(coords):
    new_coords = merge_sort(coords)
    return new_coords

coordinates = coordinates_sort(coordinates)

for i in coordinates:
    print(f"{i[0], i[1]}")

