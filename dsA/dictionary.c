#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Alpha
{
    char letter;
    struct Alpha *next;
    struct AlphaList *head;
} Alpha;

typedef struct AlphaList
{
    char *word;
    struct AlphaList *next;
} AlphaList;

// Function Prototypes
Alpha *createAlpha(char letter);
AlphaList *createAlphaList(const char *word);
void initializeAlpha(Alpha **head, char letters[], int arraySize);
void initializeAlphaList(Alpha **alphaHead, const char *words[], int numOfWords);
void printAlpha(Alpha *head);
void deleteAlpha(Alpha **head);
void deleteAlphaList(AlphaList **head);
void sortAlphaList(AlphaList **head);
void sortAlpha(Alpha **head);

Alpha *createAlpha(char letter)
{
    Alpha *newNode = (Alpha *)malloc(sizeof(Alpha));

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

AlphaList *createAlphaList(const char *word)
{
    AlphaList *newNode = (AlphaList *)malloc(sizeof(AlphaList));

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

void initializeAlphaList(Alpha **alphaHead, const char *words[], int numOfWords)
{
    for (int i = 0; i < numOfWords; i++)
    {
        Alpha *current = *alphaHead;
        char firstLetter = words[i][0];

        // Find the Alpha node that corresponds to the first letter of the word
        while (current != NULL && current->letter != firstLetter)
        {
            current = current->next;
        }

        // If the corresponding Alpha node is found, add the word to its AlphaList
        if (current != NULL)
        {
            AlphaList *newWordNode = createAlphaList(words[i]);
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
                AlphaList *temp = current->head;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = newWordNode;
            }
        }
    }
}

void initializeAlpha(Alpha **head, char letters[], int arraySize)
{
    if (arraySize <= 0)
        return;

    Alpha *current = NULL;

    for (int i = 0; i < arraySize; i++)
    {
        Alpha *newNode = createAlpha(letters[i]);

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

void sortAlphaList(AlphaList **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    int swapped;
    AlphaList *current;
    AlphaList *lastSorted = NULL;

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
                AlphaList *duplicateNode = current->next;
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

void sortAlpha(Alpha **head)
{
    if (*head == NULL || (*head)->next == NULL)
        return;

    Alpha *sorted = NULL;

    // Bubble sort for Alpha nodes
    Alpha *current = *head;
    while (current != NULL)
    {
        // Sort the AlphaList for this Alpha node
        sortAlphaList(&current->head);

        Alpha *next = current->next;

        // Insert current node into sorted list
        if (sorted == NULL || current->letter < sorted->letter)
        {
            current->next = sorted;
            sorted = current;
        }
        else
        {
            Alpha *temp = sorted;
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

void printAlpha(Alpha *head)
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
            AlphaList *currentList = head->head;
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

void deleteAlphaList(AlphaList **head)
{
    AlphaList *temp;

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

void deleteAlpha(Alpha **head)
{
    Alpha *temp;

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

    Alpha *alphaHead = NULL;

    initializeAlpha(&alphaHead, alphabet, numOfAlphabet);
    initializeAlphaList(&alphaHead, words, numOfWords);

    sortAlpha(&alphaHead);

    printAlpha(alphaHead);

    deleteAlpha(&alphaHead);

    return 0;
}
