arr = [1, 1, 1, 2, 3, 5, 7, 9, 9, 9]

max_count = 1
current_count = 1
result = arr[0]

for i in range(1, len(arr)):
    if arr[i] == arr[i-1]:
        current_count += 1
        if current_count > max_count:
            max_count = current_count
            result = arr[i]
    else:
        current_count = 1

print(result)