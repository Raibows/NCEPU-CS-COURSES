zidian = dict()
zidian['1'] = 1
zidian['2'] = 2

while True:
    temp = input()
    # if zidian.get(temp) == None:
    #     print('doesn\'t exit')
    # else:
    #     print(zidian[temp])
    print(zidian.get(temp)) if zidian.get(temp) != None else print('no')
