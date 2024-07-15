#include <stdio.h>
#include <string.h>

// Function to swap numbers
void swapNumbers(int num1, int num2)
{
    printf("Before swap: Num1 = %d Num2 = %d", num1, num2);
    num1 = num1 + num2;
    num2 = num1 - num2;
    num1 = num1 - num2;
    printf("\nAfter swap: Num1 = %d Num2 = %d", num1, num2);
}

// Function to check if a number is prime
void isPrime(int num)
{
    int isPrime = 1;
    for (int i = 2; i < num; ++i)
    {
        if (num % i == 0)
        {
            printf("%d is not a prime", num);
            isPrime = 0;
            break;
        }
    }
    if (isPrime == 1)
    {
        printf("%d is a prime", num);
    }
}

// Function to perform array operations
void arrOps(int arr[], int size)
{
    int sum = 0;
    printf("Array elements: ");
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", arr[i]);
        sum += arr[i];
    }
    printf("\nSum of array elements: %d", sum);
}

// Function to check if a number is positive, negative, or zero
void checkNumber(int num)
{
    if (num > 0)
    {
        printf("%d is positive", num);
    }
    else if (num < 0)
    {
        printf("%d is negative", num);
    }
    else
    {
        printf("%d is zero", num);
    }
}

// Function to print alphabets from A to Z
void printAlphabets()
{
    printf("Alphabets from A to Z: ");
    for (char ch = 'A'; ch <= 'Z'; ++ch)
    {
        printf("%c ", ch);
    }
}

// Function to print Fibonacci series
void printFibonacci(int n)
{
    int t1 = 0, t2 = 1, nextTerm;
    printf("Fibonacci Series: %d %d ", t1, t2);
    for (int i = 3; i <= n; ++i)
    {
        nextTerm = t1 + t2;
        printf("%d ", nextTerm);
        t1 = t2;
        t2 = nextTerm;
    }
}

// Function to print full diamond shape pyramid
void printDiamond(int n)
{
    int space = n - 1;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= space; j++)
            printf(" ");
        space--;
        for (int j = 1; j <= 2 * i - 1; j++)
            printf("*");
        printf("\n");
    }
    space = 1;
    for (int i = 1; i <= n - 1; i++)
    {
        for (int j = 1; j <= space; j++)
            printf(" ");
        space++;
        for (int j = 1; j <= 2 * (n - i) - 1; j++)
            printf("*");
        printf("\n");
    }
}

// Function to print a 2D array
void print2DArray(int rows, int cols, int arr[rows][cols])
{
    printf("2D Array elements:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            printf("%d ", arr[i][j]);
        }
        printf("\n");
    }
}

// Function to perform binary search
int binarySearch(int arr[], int size, int key)
{
    int low = 0, high = size - 1;
    while (low <= high)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == key)
            return mid;
        if (arr[mid] < key)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return -1;
}

// Function to concatenate two strings
void concatenateStrings(char str1[], char str2[])
{
    strcat(str1, str2);
    printf("Concatenated string: %s", str1);
}

// Function to reverse an array
void reverseArray(int arr[], int size)
{
    printf("Reversed array: ");
    for (int i = size - 1; i >= 0; --i)
    {
        printf("%d ", arr[i]);
    }
}

// Function to reverse a string
void reverseString(char str[])
{
    int n = strlen(str);
    printf("Reversed string: ");
    for (int i = n - 1; i >= 0; --i)
    {
        printf("%c", str[i]);
    }
}

// Function to reverse a string using recursion
void reverseStringRec(char str[], int index, int size)
{
    if (index >= size)
        return;
    reverseStringRec(str, index + 1, size);
    printf("%c", str[index]);
}

// Function to sort a string
void sortString(char str[])
{
    int n = strlen(str);
    for (int i = 0; i < n - 1; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            if (str[i] > str[j])
            {
                char temp = str[i];
                str[i] = str[j];
                str[j] = temp;
            }
        }
    }
    printf("Sorted string: %s", str);
}

// Function to check for pangram string
void checkPangram(char str[])
{
    int alphabet[26] = {0};
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] >= 'A' && str[i] <= 'Z')
            alphabet[str[i] - 'A'] = 1;
        else if (str[i] >= 'a' && str[i] <= 'z')
            alphabet[str[i] - 'a'] = 1;
    }
    int isPangram = 1;
    for (int i = 0; i < 26; ++i)
    {
        if (alphabet[i] == 0)
        {
            isPangram = 0;
            break;
        }
    }
    if (isPangram)
        printf("The string is a pangram");
    else
        printf("The string is not a pangram");
}

// Function to print the first letter of each word
void printFirstLetter(char str[])
{
    printf("First letters of each word: ");
    int isNewWord = 1;
    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] == ' ')
        {
            isNewWord = 1;
        }
        else if (isNewWord)
        {
            printf("%c ", str[i]);
            isNewWord = 0;
        }
    }
}

int main()
{
    printf("\n");

    // swapNumbers(5, 4);
    // isPrime(1123);

    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    arrOps(arr, size);

    printf("\n");
    checkNumber(-5);
    printf("\n");
    printAlphabets();
    printf("\n");
    printFibonacci(10);
    printf("\n");
    printDiamond(5);

    int arr2D[2][3] = {{1, 2, 3}, {4, 5, 6}};
    printf("\n");
    print2DArray(2, 3, arr2D);

    int sortedArr[] = {1, 2, 3, 4, 5};
    int key = 3;
    int index = binarySearch(sortedArr, 5, key);
    if (index != -1)
        printf("\nElement found at index: %d", index);
    else
        printf("\nElement not found");

    char str1[100] = "Hello";
    char str2[] = " World";
    printf("\n");
    concatenateStrings(str1, str2);

    int arrToReverse[] = {1, 2, 3, 4, 5};
    printf("\n");
    reverseArray(arrToReverse, 5);

    char strToReverse[] = "Hello";
    printf("\n");
    reverseString(strToReverse);

    char strToReverseRec[] = "Hello";
    printf("\n");
    reverseStringRec(strToReverseRec, 0, strlen(strToReverseRec));

    char strToSort[] = "dcba";
    printf("\n");
    sortString(strToSort);

    char pangramStr[] = "The quick brown fox jumps over the lazy dog";
    printf("\n");
    checkPangram(pangramStr);

    char firstLetterStr[] = "Hello World";
    printf("\n");
    printFirstLetter(firstLetterStr);

    printf("\n\n");
}
