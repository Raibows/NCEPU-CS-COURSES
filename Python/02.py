import random
count = dict()
for i  in range(1000):
    x = random.randint(0,100)
    count[x] = (count[x]+1) if x in count else 1


count = [({x:count[x]}) for x in sorted(count.keys())]
print(count)

x = []
for i in range(10):
    x.append(random.randint(0,100))


