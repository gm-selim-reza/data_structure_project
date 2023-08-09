#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node
{
    char word[100];
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node *createNode(char word[])
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->word, word);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a word into the tree
struct Node *insertWord(struct Node *root, char word[])
{
    if (root == NULL)
    {
        return createNode(word);
    }

    int cmp = strcmp(word, root->word);
    if (cmp < 0)
    {
        root->left = insertWord(root->left, word);
    }
    else if (cmp > 0)
    {
        root->right = insertWord(root->right, word);
    }

    return root;
}

// Function to search for a word in the tree
int isSpelledCorrectly(struct Node *root, char word[])
{
    if (root == NULL)
    {
        return 0; // Word not found in the dictionary
    }

    int cmp = strcmp(word, root->word);
    if (cmp == 0)
    {
        return 1; // Word found in the dictionary
    }
    else if (cmp < 0)
    {
        return isSpelledCorrectly(root->left, word);
    }
    else
    {
        return isSpelledCorrectly(root->right, word);
    }
}

int main()
{
    struct Node *root = NULL;

    // Build your dictionary by inserting words into the tree
    char wordList[][100] = {"apple", "banana", "orange", "university", "teacher", "student", "is", "are", "input", "output"};
    for (int i = 0; i < sizeof(wordList)/ sizeof(wordList[0]); i++)
    {
        root = insertWord(root, wordList[i]);
    }

    char word[100];
    int n;
    while (1)
    {
        printf("Enter 1 for check word\n");
        printf("Enter 2 for add word\n");
        printf("Enter 0 for exit\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            printf("Enter a word to check: ");
            scanf("%s", word);

            if (isSpelledCorrectly(root, word))
            {
                printf("The word is spelled correctly!\n");
            }
            else
            {
                printf("The word is misspelled.\n");
            }
            printf("\n");
            break;
        case 2:
            printf("Enter a word to add: ");
            scanf("%s", word);
            root = insertWord(root, word);
            printf("Word added in dictionary");
            break;
        case 0:
            exit(0);
            break;
        }
    }

    return 0;
}
