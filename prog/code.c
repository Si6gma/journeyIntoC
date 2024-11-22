/*
AirFi Box Re-enactment:
Movie player + ordering terminal + connected to other boxes + downloading uploading

Different states:

Main Box State:
OFFLINE, DOWNLOADING, IDLE, ACTIVE

Offline - Box is turned off
Downloading - Box is downloading data from server to box
Idle - Box is on, but doing nothing
Active - Box is being used by users

User States:
OFFLINE, Idle, ACTIVE

Offline - User is not connected to the box
Online - User is connected to the box but doing nothing
Active - User is using the box

User Active Sub-States:
    - Entertainment Services
    - Shopping
    - Watching Map
*/

typedef enum
{
    OFF,
    READY,
    ACTIVE
} boxState;

typedef enum
{
    DISCONNECTED,
    CONNECTED,
    ACTIVE
} userState;

typedef enum
{
    NONE,
    ENTERTAINMENT,
    SHOPPING,
    MAP
} userActivityState;

typedef enum
{
    NONE,
    PLAYING,
    PAUSE,
    FORWARD,
    REVERSE
} userEntertainmentState;

typedef enum
{
    NONE,
    SEARCHING,
    CART,
    PURCHASING
} userShoppingState;

typedef struct
{
    boxState state;
    int connectedUsers;
} box;

typedef struct
{
    int id;
    userState state;
    userActivityState activity;
    userEntertainmentState entertainment;
    userShoppingState shopping;
} User;
