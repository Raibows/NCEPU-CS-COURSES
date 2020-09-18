import os
import os.path

def dfs_showdir(path, depth):
    if depth == 0:
        print("root:[" + path + "]")

    no_show_list = ['.vscode', 'venv', 'book-cover', '.idea', 'cache']
    for i in no_show_list:
        if i in path:
            return

    for item in os.listdir(path):
        if '.git' not in item:
            print("|      " * depth + "+--" + item)

            newitem = path +'/'+ item
            if os.path.isdir(newitem):
                dfs_showdir(newitem, depth +1)

if __name__ == '__main__':
    dfs_showdir('./', 0)
