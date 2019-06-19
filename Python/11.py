path = r'c:\users\raibows\desktop\emma.txt'

file = open(path, 'r')
s = file.readlines()
file.close()

r = [i.swapcase() for i in s]

file = open(path, 'w')
file.writelines(r)
file.close()



