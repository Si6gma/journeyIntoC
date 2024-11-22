#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum
{
    BOX_OFF,
    BOX_READY,
    BOX_ACTIVE
} boxState;

typedef enum
{
    USER_DISCONNECTED,
    USER_CONNECTED,
    USER_ACTIVE
} userState;

typedef enum
{
    USER_ACTIVITY_NONE,
    USER_ACTIVITY_ENTERTAINMENT,
    USER_ACTIVITY_SHOPPING,
    USER_ACTIVITY_MAP
} userActivityState;

typedef enum
{
    USER_ENTERTAINMENT_NONE,
    USER_ENTERTAINMENT_PLAYING,
    USER_ENTERTAINMENT_PAUSE,
    USER_ENTERTAINMENT_FORWARD,
    USER_ENTERTAINMENT_REVERSE
} userEntertainmentState;

typedef enum
{
    USER_SHOPPING_NONE,
    USER_SHOPPING_SEARCHING,
    USER_SHOPPING_CART,
    USER_SHOPPING_PURCHASING
} userShoppingState;

typedef struct
{
    boxState state;
    int connectedUsers;
} Box;

typedef struct
{
    int id;
    userState state;
    userActivityState activity;
    userEntertainmentState entertainment;
    userShoppingState shopping;
} User;

void clearScreen();
void pauseScreen();
void displayBoxInfo(Box *box);
void displayUserInfo(User *user);
void mainMenu(Box *box, User *user);
void userMenu(Box *box, User *user);
void entertainmentMenu(Box *box, User *user);
void shoppingMenu(Box *box, User *user);
void handleUserActivity(Box *box, User *user);

int main()
{
    Box box = {BOX_READY, 0};
    User user = {1,
                 USER_DISCONNECTED,
                 USER_ACTIVITY_NONE,
                 USER_ENTERTAINMENT_NONE,
                 USER_SHOPPING_NONE};

    while (1)
    {
        clearScreen();
        mainMenu(&box, &user);
    }

    return 0;
}

void clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen()
{
    printf("\nPress Enter to continue...");
    getchar();
}

void displayBoxInfo(Box *box)
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

void displayUserInfo(User *user)
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

void mainMenu(Box *box, User *user)
{
    int choice;
    printf("==== Main Menu ====\n");
    displayBoxInfo(box);
    printf("\n1. User Menu\n");
    printf("2. Exit\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1)
    {
        userMenu(box, user);
    }
    else if (choice == 2)
    {
        exit(0);
    }
    else
    {
        printf("Invalid choice! Try again.\n");
        pauseScreen();
    }
}

void userMenu(Box *box, User *user)
{
    int choice;
    do
    {
        clearScreen();
        printf("==== User Menu ====\n");
        displayUserInfo(user);
        printf("\n1. Start Activity\n");
        printf("2. Stop Activity\n");
        printf("3. Return to Main Menu\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            if (user->activity != USER_ACTIVITY_NONE)
            {
                printf("You must stop the current activity before starting a new one.\n");
                pauseScreen();
            }
            else
            {
                user->state = USER_ACTIVE;
                printf("Choose an activity:\n1. Entertainment\n2. Shopping\n3. Map\n");
                int activity;
                scanf("%d", &activity);
                getchar();
                if (activity == 1)
                {
                    user->activity = USER_ACTIVITY_ENTERTAINMENT;
                    user->entertainment = USER_ENTERTAINMENT_PLAYING;
                    entertainmentMenu(box, user);
                }
                else if (activity == 2)
                {
                    user->activity = USER_ACTIVITY_SHOPPING;
                    user->shopping = USER_SHOPPING_SEARCHING;
                    shoppingMenu(box, user);
                }
                else if (activity == 3)
                {
                    user->activity = USER_ACTIVITY_MAP;
                    printf("Map activity selected.\n");
                    pauseScreen();
                }
                else
                {
                    printf("Invalid choice! Try again.\n");
                    pauseScreen();
                }
            }
        }
        else if (choice == 2)
        {
            user->state = USER_CONNECTED;
            user->activity = USER_ACTIVITY_NONE;
            user->entertainment = USER_ENTERTAINMENT_NONE;
            user->shopping = USER_SHOPPING_NONE;
            printf("User activity stopped.\n");
            pauseScreen();
        }
        else if (choice == 3)
        {
            return;
        }
        else
        {
            printf("Invalid choice! Try again.\n");
            pauseScreen();
        }

    } while (1);
}

void entertainmentMenu(Box *box, User *user)
{
    int choice;
    do
    {
        clearScreen();
        printf("==== Entertainment Menu ====\n");
        displayUserInfo(user);
        printf("\n1. Play\n2. Pause\n3. Forward\n4. Reverse\n5. Stop Entertainment\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1 && user->entertainment == USER_ENTERTAINMENT_PLAYING)
        {
            printf("You are already playing.\n");
        }
        else if (choice == 1)
        {
            user->entertainment = USER_ENTERTAINMENT_PLAYING;
            printf("Playing entertainment...\n");
        }
        else if (choice == 2 && user->entertainment == USER_ENTERTAINMENT_PAUSE)
        {
            printf("You are already paused.\n");
        }
        else if (choice == 2)
        {
            user->entertainment = USER_ENTERTAINMENT_PAUSE;
            printf("Entertainment paused.\n");
        }
        else if (choice == 3 && user->entertainment == USER_ENTERTAINMENT_FORWARD)
        {
            printf("You are already forwarding.\n");
        }
        else if (choice == 3)
        {
            user->entertainment = USER_ENTERTAINMENT_FORWARD;
            printf("Forwarding entertainment...\n");
        }
        else if (choice == 4 && user->entertainment == USER_ENTERTAINMENT_REVERSE)
        {
            printf("You are already reversing.\n");
        }
        else if (choice == 4)
        {
            user->entertainment = USER_ENTERTAINMENT_REVERSE;
            printf("Reversing entertainment...\n");
        }
        else if (choice == 5)
        {
            user->entertainment = USER_ENTERTAINMENT_NONE;
            user->activity = USER_ACTIVITY_NONE;
            printf("Stopping entertainment.\n");
        }

        pauseScreen();
    } while (user->entertainment != USER_ENTERTAINMENT_NONE);
}

void shoppingMenu(Box *box, User *user)
{
    int choice;
    do
    {
        clearScreen();
        printf("==== Shopping Menu ====\n");
        displayUserInfo(user);
        printf("\n1. Search Items\n2. View Shopping Cart\n3. Purchase Items\n4. Stop Shopping\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        getchar();

        if (choice == 1)
        {
            printf("Searching for items...\n");
            user->shopping = USER_SHOPPING_SEARCHING;
            pauseScreen();
        }
        else if (choice == 2)
        {
            printf("Viewing shopping cart...\n");
            user->shopping = USER_SHOPPING_CART;
            pauseScreen();
        }
        else if (choice == 3)
        {
            printf("Purchasing items...\n");
            user->shopping = USER_SHOPPING_PURCHASING;
            pauseScreen();
        }
        else if (choice == 4)
        {
            user->shopping = USER_SHOPPING_NONE;
            user->activity = USER_ACTIVITY_NONE;
            printf("Stopping shopping.\n");
            pauseScreen();
        }

    } while (user->shopping != USER_SHOPPING_NONE);
}
