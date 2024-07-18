#include <stdio.h>

// Search in an array
int findElement(int arr[], int n, int key)
{
    int i;
    for (i = 0; i < n; i++)
        if (arr[i] == key)
            return i;

    // If the key is not found
    return -1;
}

void insertIntoArray(int arr[], int n, int insert)
{
    for (int i = 0; i < n; i++)
    {
        if (arr[i] == 0)
        {
            arr[i] = insert;
            return;
        }
    }
}

// Driver's Code
int main()
{
    int arr[20] = {12, 34, 10, 6, 40};
    int sizeOfArr = sizeof(arr) / sizeof(arr[0]);
    printf("Size of array: %d\n", sizeOfArr);

// findElement
#if 1
    int search = 40;
    int position = findElement(arr, sizeOfArr, search);
    printf("Position in Array: %d \n", position);
#endif

// insertIntoArray
#if 1
    int insert = 67;
    insertIntoArray(arr, sizeOfArr, insert);
    for (int i = 0; i < sizeOfArr; i++)
    {
        printf("%d \n", arr[i]);
    }
#endif

    printf("\n");
    return 0;
}
