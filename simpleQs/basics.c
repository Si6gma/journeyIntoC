#include <stdio.h>

int main()
{
    // Student data
    int studentID = 15;
    int studentAge = 23;
    float studentFee = 75.25;
    char studentGrade = 'B';

    // Print variables
    printf("\nStudent id and age are: %d %d\n", studentID, studentAge);
    printf("Student age: %d\n", studentAge);
    printf("Student fee: %f\n", studentFee);
    printf("Student grade: %c\n\n", studentGrade);

    float f1 = 35e3;
    double d1 = 12E4;

    printf("%f\n", f1);
    printf("%lf\n\n", d1);

    // Create variables of different data types
    int items = 50;
    float cost_per_item = 9.99;
    float total_cost = items * cost_per_item;
    char currency = '$';

    // Print variables
    printf("Number of items: %d\n", items);
    printf("Cost per item: %.2f %c\n", cost_per_item, currency);
    printf("Total cost = %.2f %c\n\n", total_cost, currency);

    int num1 = 5;
    int num2 = 2;
    float sum = (float)num1 / num2;

    printf("%.1f\n\n", sum); // 2.500000

    // Set the maximum possible score in the game to 500
    int maxScore = 500;

    // The actual score of the user
    int userScore = 423;

    /* Calculate the percantage of the user's score in relation to the maximum available score.
    Convert userScore to float to make sure that the division is accurate */
    float percentage = (float)userScore / maxScore * 100.0;
    // GET FATHES HELP
    // Print the percentage
    printf("User's percentage is %.2f\n\n", percentage);

    char greetings1[] = "Hello World!";
    printf("%c\n\n", greetings1[0]);

    char greetings[] = "Hello World!";
    greetings[0] = 'J';
    printf("%s\n\n", greetings);

    return 0;
}