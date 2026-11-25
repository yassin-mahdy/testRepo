#include <iostream>
using namespace std;

class MyArray
{
private:
    int *arr;
    int size;

public:
    // Parameterized constructor
    MyArray(int s = 0)
        : size{s}
    {
        if (size == 0)
            arr = nullptr;
        else
            arr = new int[size];

        // Initialize to 0
        for (int i = 0; i < size; i++)
            arr[i] = 0;
    }

    // Copy constructor (deep copy)
    MyArray(const MyArray &other)
        : size(other.size)
    {
        if (size == 0)
            arr = nullptr;
        else
            arr = new int[size];

        for (int i = 0; i < size; i++)
            arr[i] = other.arr[i];
    }

    // Destructor
    ~MyArray()
    {
        delete[] arr;
    }

    // set element with bounds checking
    void setElemAt(int num, int index)
    {
        if (index < 0 || index >= size)
        {
            cout << "Error: invalid index.\n";
            exit(1);
        }
        arr[index] = num;
    }

    // display array
    void display() const
    {
        cout << "Here is the array: ";
        for (int i = 0; i < size; ++i)
        {
            cout << arr[i];
            if (i < size - 1)
                cout << " ";
        }
        cout << endl;
    }

    // operator+
    MyArray operator+(const MyArray &right) const
    {
        if (size != right.size)
        {
            cout << "Error: Can't add arrays of different sizes.\n";
            exit(1);
        }

        MyArray temp(size);
        for (int i = 0; i < size; ++i)
            temp.arr[i] = arr[i] + right.arr[i];

        return temp;
    }

    // BONUS: ResizeMe → return a matrix (int**)
    int **ResizeMe(int resizeFactor)
    {
        int **matrix = new int *[resizeFactor]; // rows

        for (int i = 0; i < resizeFactor; ++i)
        {
            matrix[i] = new int[size]; // allocate each row

            for (int j = 0; j < size; ++j)
            {
                if (i == 0)
                    matrix[0][j] = arr[j]; // first row = original array
                else
                    matrix[i][j] = 0; // other rows = zeros
            }
        }

        return matrix;
    }
};

int main()
{
    cout << "--- Testing MyArray ---\n";

    // Create two arrays
    MyArray a1(5);
    MyArray a2(5);

    // Set elements
    for (int i = 0; i < 5; i++)
    {
        a1.setElemAt(i + 1, i);        // 1 2 3 4 5
        a2.setElemAt((i + 1) * 10, i); // 10 20 30 40 50
    }

    // Display arrays
    a1.display();
    a2.display();

    // Add arrays
    MyArray sum = a1 + a2;
    cout << "Sum of arrays: ";
    sum.display();

    // Test copy constructor
    MyArray copy = a1;
    cout << "Copy of a1: ";
    copy.display();

    // Test ResizeMe
    int resizeFactor = 3;
    int **matrix = a1.ResizeMe(resizeFactor);

    cout << "\nMatrix (" << resizeFactor << " x " << 5 << "):\n";
    for (int i = 0; i < resizeFactor; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Clean matrix memory (responsibility of main)
    for (int i = 0; i < resizeFactor; i++)
        delete[] matrix[i];
    delete[] matrix;

    return 0;
}
