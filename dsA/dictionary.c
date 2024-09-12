#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Alpha
{
    char letter;
    struct Alpha *next;
    struct AlphaList *head;
};

struct AlphaList
{
    char *word;
    struct AlphaList *next;
};

// Function Prototypes
struct Alpha *createAlpha(char letter);
struct AlphaList *createAlphaList(const char *word);
void initializeAlpha(struct Alpha **head, char letters[], int arraySize);
void initializeAlphaList(struct Alpha **alphaHead, const char *words[], int numOfWords);
void printAlpha(struct Alpha *head);
void deleteAlpha(struct Alpha **head);
void deleteAlphaList(struct AlphaList **head);
void sortAlphaList(struct AlphaList **head);
void sortAlpha(struct Alpha **head);

struct Alpha *createAlpha(char letter)
{
    struct Alpha *newNode = (struct Alpha *)malloc(sizeof(struct Alpha));

    if (newNode == NULL)
    { // Edge Case: Memory allocation failed
        printf("Memory allocation failed. Node creation aborted.\n");
        return NULL;
    }

    newNode->letter = letter;
    newNode->next = NULL;
    newNode->head = NULL;
    return newNode;
}

struct AlphaList *createAlphaList(const char *word)
{
    struct AlphaList *newNode = (struct AlphaList *)malloc(sizeof(struct AlphaList));

    if (newNode == NULL)
    { // Edge Case: Memory allocation failed
        printf("Memory allocation failed. Node creation aborted.\n");
        return NULL;
    }

    newNode->word = strdup(word);
    if (newNode->word == NULL)
    { // Edge Case: Memory allocation failed for word
        printf("Memory allocation failed for word duplication. Node creation aborted.\n");
        free(newNode);
        return NULL;
    }

    newNode->next = NULL;
    return newNode;
}

void initializeAlphaList(struct Alpha **alphaHead, const char *words[], int numOfWords)
{
    for (int i = 0; i < numOfWords; i++)
    {
        struct Alpha *current = *alphaHead;
        char firstLetter = words[i][0];

        // Find the Alpha node that corresponds to the first letter of the word
        while (current != NULL && current->letter != firstLetter)
        {
            current = current->next;
        }

        // If the corresponding Alpha node is found, add the word to its AlphaList
        if (current != NULL)
        {
            struct AlphaList *newWordNode = createAlphaList(words[i]);
            if (newWordNode == NULL)
            {
                printf("Failed to allocate memory for word '%s'.\n", words[i]);
                return;
            }

            // Insert the new word node into the list of words for the current letter
            if (current->head == NULL)
            {
                current->head = newWordNode;
            }
            else
            {
                struct AlphaList *temp = current->head;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newWordNode;
            }
        }
    }
}

void initializeAlpha(struct Alpha **head, char letters[], int arraySize)
{
    if (arraySize <= 0)
        return;

    struct Alpha *current = NULL;

    for (int i = 0; i < arraySize; i++)
    {
        struct Alpha *newNode = createAlpha(letters[i]);

        if (newNode == NULL)
        {
            printf("Memory allocation failed. Aborting initialization.\n");
            deleteAlpha(head); // Clean up any already allocated nodes
            return;
        }

        if (*head == NULL)
        {
            *head = newNode;
            current = newNode;
        }
        else
        {
            current->next = newNode;
            current = newNode;
        }
    }
}

void sortAlphaList(struct AlphaList **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    struct AlphaList *current;
    struct AlphaList *lastSorted = NULL;

    do
    {
        swapped = 0;
        current = *head;

        while (current->next != lastSorted)
        {
            if (strcmp(current->word, current->next->word) > 0)
            {
                char *tempWord = current->word;
                current->word = current->next->word;
                current->next->word = tempWord;
                swapped = 1;
            }
            else if (strcmp(current->word, current->next->word) == 0)
            {
                // If duplicate, remove the next node
                struct AlphaList *duplicateNode = current->next;
                current->next = current->next->next;
                free(duplicateNode->word);
                free(duplicateNode);
            }
            else
            {
                current = current->next;
            }
        }
        lastSorted = current;
    } while (swapped);
}

void sortAlpha(struct Alpha **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    struct Alpha *sorted = NULL;

    // Bubble sort for Alpha nodes
    struct Alpha *current = *head;
    while (current != NULL)
    {
        // Sort the AlphaList for this Alpha node
        sortAlphaList(&current->head);

        struct Alpha *next = current->next;

        // Insert current node into sorted list
        if (sorted == NULL || current->letter < sorted->letter)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            struct Alpha *temp = sorted;
            while (temp->next != NULL && temp->next->letter < current->letter)
            {
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }

        current = next;
    }

    *head = sorted;
}

void printAlpha(struct Alpha *head)
{
    if (head == NULL)
    {
        printf("List is empty.\n");
        return;
    }

    while (head != NULL)
    {
        printf("%c", head->letter);
        if (head->head != NULL)
        {
            struct AlphaList *currentList = head->head;
            printf(" -> ");
            while (currentList != NULL)
            {
                printf("%s", currentList->word);
                if (currentList->next != NULL)
                {
                    printf(", ");
                }
                currentList = currentList->next;
            }
        }
        printf("\n");
        head = head->next;
    }
}

void deleteAlphaList(struct AlphaList **head)
{
    struct AlphaList *temp;

    if (*head == NULL)
        return;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp->word);
        free(temp);
    }

    *head = NULL;
}

void deleteAlpha(struct Alpha **head)
{
    struct Alpha *temp;

    if (*head == NULL)
        return;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;

        // Free the associated AlphaList before deleting the Alpha node
        deleteAlphaList(&temp->head);
        free(temp);
    }

    *head = NULL;
}

int main()
{
    char alphabet[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
        'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T',
        'U', 'V', 'W', 'X', 'Y', 'Z'};
    int numOfAlphabet = sizeof(alphabet) / sizeof(alphabet[0]);

    const char *words[] = {
        "Tree", "Whale", "Pineapple", "Xylophone", "Ocean",
        "Rabbit", "Waterfall", "Ant", "Glass", "Eagle",
        "Jungle", "Moon", "Vase", "Bridge", "Yacht",
        "Door", "Car", "Zebra", "King", "Quilt",
        "Flag", "Lamp", "Garden", "Island", "Nest",
        "Dog", "Flower", "Echo", "Zero", "Xerox",
        "Wind", "Boat", "Insect", "Kangaroo", "Orange",
        "Helicopter", "Candle", "Igloo", "Rose", "Victory",
        "Star", "Yard", "Wagon", "Tiger", "Quill",
        "Axe", "Wizard", "Village", "Unicorn", "Zoo",
        "Gold", "Mountain", "Giraffe", "Clock", "Astronaut",
        "Stone", "Cloud", "Pond", "Wave", "Leaf",
        "Dragon", "Sailboat", "Heart", "Jar", "Net",
        "Arrow", "Sun", "Map", "Fire", "Umbrella",
        "Butterfly", "Juice", "Kitchen", "Xylitol", "Yam",
        "Egg", "Dream", "Violin", "Forest", "Water",
        "Rabbit", "Night", "Horse", "Lion", "Octopus",
        "Rain", "Tunnel", "Key", "Bamboo", "Quartz",
        "Bottle", "Dolphin", "Question", "Stone", "Apple",
        "Road", "Echo", "Ink", "Journey", "Queen"};
    int numOfWords = sizeof(words) / sizeof(words[0]);

    struct Alpha *alphaHead = NULL;
    initializeAlpha(&alphaHead, alphabet, numOfAlphabet);
    initializeAlphaList(&alphaHead, words, numOfWords);

    sortAlpha(&alphaHead);
    printf("\nArray: \n\n");
    for (int i = 0; i < numOfWords; i++)
        printf("%s, ", words[i]);

    printf("\n\nList: \n\n");
    printAlpha(alphaHead);
    deleteAlpha(&alphaHead);

    return 0;
}
