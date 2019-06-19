import random
x = [random.randint(1,20) for i in range(20)]
x1 = sorted(x[:10])
x2 = sorted((x[10:20]), reverse=True)
print(x1+x2)