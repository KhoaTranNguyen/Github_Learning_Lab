arr = [2, 1, 1, 3, 5, 7, 9, 9, 1]

count_dict = {}
highest_occurs = 0
result = None

for num in arr:
    if num in count_dict:
        count_dict[num] += 1
    else:
        count_dict[num] = 1
    if count_dict[num] > highest_occurs:
        highest_occurs = count_dict[num]
        result = num

print(result)