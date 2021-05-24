#include <stdio.h>

void memory_move(void *dest, void *src, size_t n, int type_size)
{
    n *= type_size;
    char *bdest = (char *)dest;
    char *bsrc = (char *)src;
    char *temp = new char[n];
    for (size_t i = 0; i < n; ++i)
        temp[i] = bsrc[i];
    for (size_t i = 0; i < n; ++i)
        bdest[i] = temp[i];
    delete[] temp;
}

struct stack
{
    int _size;
    int _top;
    int *_arr;

    stack(int size = 1)
    {
        this->_size = size;
        this->_top = 0;
        this->_arr = new int[size];
    }

    ~stack()
    {
        delete[] this->_arr;
        this->_arr = nullptr;
        this->_size = 0;
        this->_top = 0;
    }

    void push(int val)
    {
        if (this->_size == this->_top)
        {
            int *temp = new int[this->_size * 2];
            memory_move(temp, this->_arr, this->_size, sizeof(int));
            delete[] this->_arr;
            this->_arr = temp;
            this->_size *= 2;
        }
        this->_arr[this->_top++] = val;
    }

    int top()
    {
        if (this->_top <= 0)
            throw "Segmentation fault";
        return this->_arr[this->_top - 1];
    }

    void pop()
    {
        if (!this->is_empty())
            --this->_top;
        else
            throw "Segmentation fault";
    }

    bool is_empty()
    {
        return this->_top <= 0;
    }

    int size()
    {
        // not capacity but number of elements
        return this->_top;
    }

    int capacity()
    {
        return this->_size;
    }
};

int main(int argc, char *argv[])
{
    stack test(3);
    printf("%d\n", test.is_empty());
    for (int i = 0; i < 100; ++i)
    {
        test.push(i);
        printf("size %d capacity %d top_val %d\n", test.size(), test.capacity(), test.top());
        if (test.top() % 3 == 0)
            test.pop();
    }
    while (1)
    {
        if (test.is_empty())
            break;
        printf("top_val is %d\n", test.top());
        test.pop();
    }

    return 0;
}