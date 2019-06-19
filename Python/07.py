def judge(num):
    if num < 2:
        print('wrong input')
    else:
        for i in range(2,int(num/2)):
            if num % i == 0:
                print('no')
                return
        print('yes')

while True:
    x = eval(input())
    judge(x)