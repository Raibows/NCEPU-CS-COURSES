def statistic(s):
    up = 0
    low = 0
    digit = 0
    other = 0
    for i in s:
        if i.isupper():
            up += 1
        elif i.islower():
            low += 1
        elif i.isdigit():
            digit += 1
        else:
            other += 1
    return (up, low, digit, other)
print(statistic('sadxcSDxcasdSD54*8S21XZCxcc'))