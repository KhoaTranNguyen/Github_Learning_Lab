arr = [37, -1, -7, -11, -1, -3, -3]

maxx = arr[0]
cursum = 0

for i in range(0,len(arr)):
    if cursum + arr[i] >= 0:
        maxx = max(maxx, cursum + arr[i])
        cursum += arr[i]
    else:
        cursum = 0
    maxx = max(maxx, arr[i])

print(maxx)