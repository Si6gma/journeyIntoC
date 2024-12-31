#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Enum for the box states
typedef enum
{
    BOX_OFF,
    BOX_READY,
    BOX_ACTIVE
} BoxState;

// Enum for the user connection states
typedef enum
{
    USER_DISCONNECTED,
    USER_CONNECTED,
    USER_ACTIVE
} UserState;

// Enum for the types of user activities
typedef enum
{
    USER_ACTIVITY_NONE,
    USER_ACTIVITY_ENTERTAINMENT,
    USER_ACTIVITY_SHOPPING,
    USER_ACTIVITY_MAP
} UserActivityState;

// Enum for the types of entertainment activities
typedef enum
{
    USER_ENTERTAINMENT_NONE,
    USER_ENTERTAINMENT_PLAYING,
    USER_ENTERTAINMENT_PAUSE,
    USER_ENTERTAINMENT_FORWARD,
    USER_ENTERTAINMENT_REVERSE
} UserEntertainmentState;

// Enum for the types of shopping activites
typedef enum
{
    USER_SHOPPING_NONE,
    USER_SHOPPING_SEARCHING,
    USER_SHOPPING_CART,
    USER_SHOPPING_PURCHASING
} UserShoppingState;

// Structure for a Box
typedef struct
{
    BoxState state;
    int connectedUsers;
} Box;

// Structure representing a User
typedef struct
{
    int id;
    UserState state;
    UserActivityState activity;
    UserEntertainmentState entertainment;
    UserShoppingState shopping;
} User;

// Function prototypes
void clearScreen();
void pauseScreen();
void displayBoxInfo(const Box *box);
void displayUserInfo(const User *user);
void mainMenu(Box *box, User *user);
void userMenu(Box *box, User *user);
void entertainmentMenu(User *user);
void shoppingMenu(User *user);

// Main function to initialize and run the program
int main()
{
    Box box = {BOX_READY, 0};
    User user = {1, USER_DISCONNECTED, USER_ACTIVITY_NONE, USER_ENTERTAINMENT_NONE, USER_SHOPPING_NONE};

    while (1)
    {
        clearScreen();
        mainMenu(&box, &user);
    }
    return 0;
}

// Cross-platform clear screen function
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Pause screen function to wait for user input
void pauseScreen()
{
    printf("\nPress Enter to continue...");
    getchar();
}

// Display information about the box
void displayBoxInfo(const Box *box)
{
    printf("Box State: ");
    switch (box->state)
    {
    case BOX_OFF:
        printf("OFF\n");
        break;
    case BOX_READY:
        printf("READY\n");
        break;
    case BOX_ACTIVE:
        printf("ACTIVE\n");
        break;
    }
    printf("Connected Users: %d\n", box->connectedUsers);
}

// Display information about the user
void displayUserInfo(const User *user)
{
    printf("User ID: %d\n", user->id);
    printf("User State: ");
    switch (user->state)
    {
    case USER_DISCONNECTED:
        printf("DISCONNECTED\n");
        break;
    case USER_CONNECTED:
        printf("CONNECTED\n");
        break;
    case USER_ACTIVE:
        printf("ACTIVE\n");
        break;
    }
    printf("User Activity: ");
    switch (user->activity)
    {
    case USER_ACTIVITY_NONE:
        printf("NONE\n");
        break;
    case USER_ACTIVITY_ENTERTAINMENT:
        printf("ENTERTAINMENT\n");
        break;
    case USER_ACTIVITY_SHOPPING:
        printf("SHOPPING\n");
        break;
    case USER_ACTIVITY_MAP:
        printf("MAP\n");
        break;
    }
    printf("Entertainment State: ");
    switch (user->entertainment)
    {
    case USER_ENTERTAINMENT_NONE:
        printf("NONE\n");
        break;
    case USER_ENTERTAINMENT_PLAYING:
        printf("PLAYING\n");
        break;
    case USER_ENTERTAINMENT_PAUSE:
        printf("PAUSE\n");
        break;
    case USER_ENTERTAINMENT_FORWARD:
        printf("FORWARD\n");
        break;
    case USER_ENTERTAINMENT_REVERSE:
        printf("REVERSE\n");
        break;
    }
    printf("Shopping State: ");
    switch (user->shopping)
    {
    case USER_SHOPPING_NONE:
        printf("NONE\n");
        break;
    case USER_SHOPPING_SEARCHING:
        printf("SEARCHING\n");
        break;
    case USER_SHOPPING_CART:
        printf("CART\n");
        break;
    case USER_SHOPPING_PURCHASING:
        printf("PURCHASING\n");
        break;
    }
}

// Main menu for program interaction
void mainMenu(Box *box, User *user)
{
    int choice;
    printf("==== Main Menu ====\n");
    displayBoxInfo(box);

    printf("\n1. User Menu");
    printf("\n2. Exit");
    printf("\nEnter your choice: ");

    if (scanf("%d", &choice) != 1)
        choice = -1;
    getchar();

    switch (choice)
    {
    case 1:
        userMenu(box, user);
        break;
    case 2:
        exit(0);
    default:
        printf("Invalid choice! Try again.\n");
        pauseScreen();
        break;
    }
}

// User menu with activity choices
void userMenu(Box *box, User *user)
{
    int choice;
    do
    {
        clearScreen();
        printf("==== User Menu ====\n");
        displayUserInfo(user);
        printf("\n1. Start Activity\n2. Stop Activity\n3. Return to Main Menu\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
            choice = -1;
        getchar();

        switch (choice)
        {
        case 1:
            if (user->activity != USER_ACTIVITY_NONE)
            {
                printf("Stop current activity first.\n");
                pauseScreen();
            }
            else
            {
                user->state = USER_ACTIVE;
                printf("Select an activity:\n1. Entertainment\n2. Shopping\n3. Map\n");
                int activity;
                if (scanf("%d", &activity) != 1)
                    activity = -1;
                getchar();
                if (activity == 1)
                    entertainmentMenu(user);
                else if (activity == 2)
                    shoppingMenu(user);
                else if (activity == 3)
                    printf("Map selected.\n");
                else
                    printf("Invalid choice.\n");
            }
            break;
        case 2:
            user->state = USER_CONNECTED;
            user->activity = USER_ACTIVITY_NONE;
            printf("Activity stopped.\n");
            pauseScreen();
            break;
        case 3:
            return;
        default:
            printf("Invalid choice! Try again.\n");
            pauseScreen();
            break;
        }
    } while (1);
}

// Menu for entertainment-related options
void entertainmentMenu(User *user)
{
    int choice;
    do
    {
        clearScreen();
        printf("==== Entertainment Menu ====\n");
        displayUserInfo(user);
        printf("\n1. Play\n2. Pause\n3. Forward\n4. Reverse\n5. Stop Entertainment\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
            choice = -1;
        getchar();

        switch (choice)
        {
        case 1:
            user->entertainment = USER_ENTERTAINMENT_PLAYING;
            break;
        case 2:
            user->entertainment = USER_ENTERTAINMENT_PAUSE;
            break;
        case 3:
            user->entertainment = USER_ENTERTAINMENT_FORWARD;
            break;
        case 4:
            user->entertainment = USER_ENTERTAINMENT_REVERSE;
            break;
        case 5:
            user->entertainment = USER_ENTERTAINMENT_NONE;
            return;
        default:
            printf("Invalid choice! Try again.\n");
            break;
        }
        pauseScreen();
    } while (1);
}

// Menu for shopping-related options
void shoppingMenu(User *user)
{
    int choice;
    do
    {
        clearScreen();
        printf("==== Shopping Menu ====\n");
        displayUserInfo(user);
        printf("\n1. Search Items\n2. View Cart\n3. Purchase\n4. Stop Shopping\nEnter your choice: ");
        if (scanf("%d", &choice) != 1)
            choice = -1;
        getchar();

        switch (choice)
        {
        case 1:
            user->shopping = USER_SHOPPING_SEARCHING;
            break;
        case 2:
            user->shopping = USER_SHOPPING_CART;
            break;
        case 3:
            user->shopping = USER_SHOPPING_PURCHASING;
            break;
        case 4:
            user->shopping = USER_SHOPPING_NONE;
            return;
        default:
            printf("Invalid choice! Try again.\n");
            break;
        }
        pauseScreen();
    } while (1);
}
