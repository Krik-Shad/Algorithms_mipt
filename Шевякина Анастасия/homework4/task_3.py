n_amount = int(input())
n_datalen = int(input())

priorities = [int(m) for m in input().split()]
data = []
for i in range(n_amount):
    l = input().split()
    data.append([l[0], [int(k) for k in l[1:]]])

def priority_one_sort(a, num_pri):
    new = sorted(a, key=lambda data: data[1][num_pri-1])
    return new

def prior_sort(a, priorities):
    # priorities = priorities[::-1]
    for priority in priorities:
        a = priority_one_sort(a, priority)
    for i in a:
        print(i[0])

prior_sort(data, priorities)

