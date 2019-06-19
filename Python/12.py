import os
x = os.getcwd()
print(x)

os.chdir('c:\\')

print(os.getcwd())

os.chdir(x)
print(os.getcwd())
