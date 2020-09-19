#include <iostream>
using namespace std;


void build_tree(int arr[], int tree[], int root, int start, int end) {
    if (start == end)
    {
        tree[root] = arr[start];
        return;
    }
    int left = 2 * root + 1;
    int right = left + 1;
    int mid = (start + end) / 2;
    build_tree(arr, tree, left, start, mid);
    build_tree(arr, tree, right, mid+1, end);
    tree[root] = tree[left] + tree[right];
}

int query_sum(int tree[], int root, int start, int end, int L, int R) {
    if (L > end || R < start)
    {
        return 0;
    }
    if (start == end)
    {
        return tree[root];
    }
    if (L <= start && end <= R) // L start end R
    {
        return tree[root];
    }
    int mid = (start + end) / 2;
    int left = 2 * root + 1;
    int right = left + 1;
    int left_sum = query_sum(tree, left, start, mid, L, R);
    int right_sum = query_sum(tree, right, mid+1, end, L, R);
    return left_sum + right_sum;
}

void update(int arr[], int tree[], int root, int start, int end, int index, int value) {
    if (start == end)
    {
        arr[index] = value;
        tree[root] = value;
        return;
    }
    int mid = (start + end) / 2;
    int left = root * 2 + 1;
    int right = left + 1;
    if (index <= mid)
    {
        update(arr, tree, left, start, mid, index, value);
    }
    else
    {
        update(arr, tree, right, mid+1, end, index, value);
    }
    tree[root] = tree[left] + tree[right];
}


void show(int tree[]) {
    for (int i=0; i<15; ++i)
    {
        // if (tree[i] == 0)
        // {
        //     break;
        // }
        cout << tree[i] << endl;
    }
    cout << endl;
}

int main() {
    int arr[6] = {1, 3, 5, 7, 9, 11};
    int tree[1000] = {0};
    build_tree(arr, tree, 0, 0, 5);
    show(tree);
    update(arr, tree, 0, 0, 5, 3, 6);
    show(tree);
    cout << query_sum(tree, 0, 0, 5, 2, 4);
    return 0;
}