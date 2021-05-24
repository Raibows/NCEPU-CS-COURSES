#include <stdio.h>

void memory_move(void *dest, void *src, size_t n, int type_size)
{
    n *= type_size;
    char *temp = new char[n];
    char *bdest = (char *)dest;
    char *bsrc = (char *)src;
    for (int i = 0; i < n; ++i)
        temp[i] = bsrc[i];
    for (int i = 0; i < n; ++i)
        bdest[i] = temp[i];
}

struct queue
{
    /*
    * circular queue
    * _rear points to the last
    * _front points to the first
    * first in first out
    */
    int _rear;
    int _front;
    int _size;
    int *_arr;

    queue(int size = 1)
    {
        this->_size = size;
        this->_rear = -1;
        this->_front = -1;
        this->_arr = new int[size];
    }

    ~queue()
    {
        delete[] this->_arr;
        this->_arr = nullptr;
        this->_size = 0;
        this->_rear = -1;
        this->_front = -1;
    }

    bool empty()
    {
        return this->_front == -1;
    }

    void put(int val)
    {
        if (this->_front == 0 && this->_rear == this->_size - 1)
        {
            // full
            int *temp = new int[this->_size * 2];
            memory_move(temp, this->_arr, this->_size, sizeof(int));
            delete[] this->_arr;
            this->_arr = temp;
            this->_size *= 2;
        }
        else if (this->_front == this->_rear + 1)
        {
            // full
            int *temp = new int[this->_size * 2];
            int j = 0;
            for (int i = this->_front; i < this->_size; ++i)
                temp[j++] = this->_arr[i];
            for (int i = 0; i <= this->_rear; ++i)
                temp[j++] = this->_arr[i];
            this->_front = 0;
            this->_rear = this->_size - 1;
            delete[] this->_arr;
            this->_arr = temp;
            this->_size *= 2;
        }
        if (this->_front == -1)
        {
            this->_front = 0;
            this->_rear = 0;
        }
        if (this->_rear == this->_size - 1)
            this->_rear = 0;
        else
            ++this->_rear;
        this->_arr[this->_rear] = val;
    }

    int get()
    {
        if (this->empty())
            throw "Segmentation fault";
    }
};
