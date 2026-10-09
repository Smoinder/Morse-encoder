#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node { //Creating a node for binary tree(for decoding)
    char character;
    struct Node* dot;  // for . in binary tree
    struct Node* dash; // for - in binary tree
} Node;

// Creating a new node
Node* createNode(char character);

// Inserting a node into root
void insert(Node* root, char* str, char character);

// Decoding
char* decode(Node* root, char* code);

// Deleting the memory for dynamically allocated root
void freeTree(Node* root);

//Creating a root for Morse code
void insertMorse(Node* root);

//Adding an element to array
char* add_char(char* initial, int elements);

//Coding a string to Morse
char* code(char* str);

int main()
{
    int choose;
    printf("\t\t\tMorse code\n");
    while (1) //An infinite loop for menu
    {
        printf("What you would like to choose?\n");
        printf("1.To code Latin to Morse\n");
        printf("2.To decode from Morse to Latin\n");
        printf("3.To see the table of Latin - Morse\n");
        printf("4.Exit\n");
        scanf("%d", &choose);
        if (choose == 1) //Case coding
        {
            printf("Would you like to\n");
            printf("1.Read a text from file\n");
            printf("2.Read a text from console\n");
            scanf("%d", &choose);
            if (choose == 1) //Case file
            {
                FILE* file;
                char file_root[100], text[100], * coded, killer;
                printf("Write the root of your file: ");
                scanf("%c", &killer); //Killing last '\n' in the buffer
                fgets(file_root, 100, stdin);
                file_root[strlen(file_root) - 1] = '\0'; //Replacing '\n' with '\0'
                file = fopen(file_root, "r");
                if (file == NULL)
                {
                    printf("Error whith opening the file\n");
                    continue;
                }
                fgets(text, 100, file);
                coded = code(text);
                printf("%s = %s in Morse\n", text, coded);
                free(coded);
                fclose(file);
            }
            else if (choose == 2) //Case console
            {
                char text[100], * coded, killer;
                printf("Write the text you want to code: ");
                scanf("%c", &killer); //Killing last '\n' in the buffer
                fgets(text, 100, stdin);
                text[strlen(text) - 1] = '\0';//Replacing '\n' with '\0'
                coded = code(text);
                printf("%s = %s in Morse\n", text, coded);
                free(coded);
            }
        }
        else if (choose == 2) //Case decoding
        {
            printf("Would you like to\n");
            printf("1.Read a coded text from file\n");
            printf("2.Read a coded text from console\n");
            scanf("%d", &choose);
            if (choose == 1) //Case file
            {
                FILE* file;
                char file_root[100], text[100], * decoded, killer;
                printf("Write the root of your file: ");
                scanf("%c", &killer); //Killing last '\n' in the buffer
                fgets(file_root, 100, stdin);
                file_root[strlen(file_root) - 1] = '\0'; //Replacing '\n' with '\0'
                file = fopen(file_root, "r");
                if (file == NULL)
                {
                    printf("Error whith opening the file\n");
                    continue;
                }
                fgets(text, 100, file);
                Node* root = createNode('\0'); //Creating a binary tree
                insertMorse(root); //Insertin all of the characters there
                decoded = decode(root, text); //Decoding the text
                printf("%s = %s in Latin\n", text, decoded);
                free(decoded);
                freeTree(root);
            }
            else if (choose == 2) //Case console
            {
                char text[100], * decoded, killer;
                printf("Write the text you want to decode: ");
                scanf("%c", &killer); //Killing last '\n' in the buffer
                fgets(text, 100, stdin);
                text[strlen(text) - 1] = '\0';//Replacing '\n' with '\0'
                Node* root = createNode('\0'); //Creating a binary tree
                insertMorse(root); //Inserting all of the characters there
                decoded = decode(root, text); //Decoding the text
                printf("%s = %s in Latin\n", text, decoded);
                free(decoded);
                freeTree(root);
            }
        }
        else if (choose == 3) //Case table
        {
            char* symb = (char*)malloc(2 * sizeof(char)), * morse; //Creating two dinamically allocated strings, symb is allocated dinamically for function code() working properly
            if (symb == NULL)
            {
                printf("Error whith allocating the memory\n");
                continue;
            }
            symb[0] = 'A';
            symb[1] = '\0';
            while (symb[0] <= 'Z') //coding each symbol from 'A' to 'Z' to morse
            {
                morse = code(symb);
                printf("%s = %s\n", symb, morse);
                symb[0]++;
                free(morse);
            }
            free(symb);
        }
        else if (choose == 4)
        {
            break;
        }
        else
        {
            printf("Incorrect input, try again\n");
        }
    }
    return 0;
}

Node* createNode(char character)
{
    Node* newNode = (Node*)malloc(sizeof(Node)); //allocating memory dinamically, for pointer not to be deleted after function finishes
    if (newNode == NULL)
    {
        return NULL;
    }
    newNode->character = character;
    newNode->dot = NULL; //initiliazing to zero pointer both dash and dot
    newNode->dash = NULL;
    return newNode;
}

void insert(Node* root, char* str, char character)
{
    Node* current = root;
    int i = 0;
    while (str[i] != '\0') //while inserted string isn't finished
    { 
        if (str[i] == '.')
        {
            if (current->dot == NULL)
            {
                current->dot = createNode('\0'); //creating a new branch in the tree if it doesn't exist yet
            }
            current = current->dot; //going there
        }
        else if (str[i] == '-') 
        {
            if (current->dash == NULL) 
            {
                current->dash = createNode('\0'); //creating a new branch in the tree if it doesn't exist yet
            }
            current = current->dash; //going there
        }
        i++;
    }
    current->character = character; //inserting the intersted value into the tree
}

char* decode(Node* root, char* code)
{
    Node* current = root;
    int i = 0, j = 0;
    char* res = (char*)malloc((1) * sizeof(char)); //allocating memory for result dynamically for it not being deleted after function finishes
    if (res == NULL)
    {
        return NULL;
    }
    res[0] = '\0';
    while (code[i] != '\0') //till we reach the end of the inserted string
    { 
        if (code[i] == '.')
        {
            current = current->dot; //going to coresponding branch
        }
        else if (code[i] == '-')
        {
            current = current->dash; //going to coresponding branch
        }
        else if (code[i] == ' ')// Space between characters => The end of the letter
        { 
            if (current != NULL && current->character != '\0')
            {
                res = add_char(res, 1);
                res[j] = current->character;
                j++;
                if (code[i + 1] == ' ') // Two spaces = new word
                {
                    res = add_char(res, 1);
                    res[j] = ' ';
                    j++;
                }
            }
            current = root; // Returning to the root for next letter
        }
        i++;
    }
    if (current != NULL && current->character != '\0') 
    {
        res = add_char(res, 1);
        res[j] = current->character; // For last letter, because there is no space after it
        j++;
    }
    res[j] = '\0'; //Putting the end of the resulting string
    return res;
}

void freeTree(Node* root)
{
    if (root != NULL) {
        freeTree(root->dot); //delete the whole dot branch
        freeTree(root->dash); //delete the whole dash branch
        free(root); //delete the root after all
    }
}

void insertMorse(Node* root)
{
    insert(root, ".-", 'A');
    insert(root, "-...", 'B');
    insert(root, "-.-.", 'C');
    insert(root, "-..", 'D');
    insert(root, ".", 'E');
    insert(root, "..-.", 'F');
    insert(root, "--.", 'G');
    insert(root, "....", 'H');
    insert(root, "..", 'I');
    insert(root, ".---", 'J');
    insert(root, "-.-", 'K');
    insert(root, ".-..", 'L');
    insert(root, "--", 'M');
    insert(root, "-.", 'N');
    insert(root, "---", 'O');
    insert(root, ".--.", 'P');
    insert(root, "--.-", 'Q');
    insert(root, ".-.", 'R');
    insert(root, "...", 'S');
    insert(root, "-", 'T');
    insert(root, "..-", 'U');
    insert(root, "...-", 'V');
    insert(root, ".--", 'W');
    insert(root, "-..-", 'X');
    insert(root, "-.--", 'Y');
    insert(root, "--..", 'Z');
    insert(root, "-----", '0');
    insert(root, ".----", '1');
    insert(root, "..---", '2');
    insert(root, "...--", '3');
    insert(root, "....-", '4');
    insert(root, ".....", '5');
    insert(root, "-....", '6');
    insert(root, "--...", '7');
    insert(root, "---..", '8');
    insert(root, "----.", '9');
}

char* add_char(char* initial, int elements)
{
    int len = strlen(initial);
    char* res = (char*)malloc((len + 1 + elements) * sizeof(char)); //Creating a new array which is 1 element bigger
    if (res == NULL)
    {
        return NULL;
    }
    for (int i = 0; i < len; i++)
    {
        res[i] = initial[i]; //copying initial array to final
    }
    res[len + elements] = '\0'; //Adding the end of string
    free(initial); //deleting previous string
    return res;
}

char* code(char* str)
{
    char* morse_codes[] = {
    ".-",   // A
    "-...", // B
    "-.-.", // C
    "-..",  // D
    ".",    // E
    "..-.", // F
    "--.",  // G
    "....", // H
    "..",   // I
    ".---", // J
    "-.-",  // K
    ".-..", // L
    "--",   // M
    "-.",   // N
    "---",  // O
    ".--.", // P
    "--.-", // Q
    ".-.",  // R
    "...",  // S
    "-",    // T
    "..-",  // U
    "...-", // V
    ".--",  // W
    "-..-", // X
    "-.--", // Y
    "--..", // Z
    "-----", // 0
    ".----", // 1
    "..---", // 2
    "...--", // 3
    "....-", // 4
    ".....", // 5
    "-....", // 6
    "--...", // 7
    "---..", // 8
    "----."  // 9
    };
    int j = 0;
    char* res = (char*)malloc(1 * sizeof(char)); //allocating memory for result dinamically for it not being deleted after the function finishes
    if (res == NULL)
    {
        return NULL;
    }
    res[0] = '\0';
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (toupper(str[i]) >= 'A' && toupper(str[i]) <= 'Z') //Checking whether it's a letter
        {
            int serial = toupper(str[i]) - 'A'; // Serial number of character
            res = add_char(res, strlen(morse_codes[serial])); //Adding coresponding number of characters to result
            for (int k = 0; morse_codes[serial][k] != '\0'; k++, j++)
            {
                res[j] = morse_codes[serial][k]; //Copying the Morse code
            }
            res = add_char(res, 1); //Adding a space after each character
            res[j] = ' ';
            j++;
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            int serial = ('Z' - 'A') + (str[i] - '0') + 1; // Serial number of character
            res = add_char(res, strlen(morse_codes[serial])); //Adding coresponding number of characters to result
            for (int k = 0; morse_codes[serial][k] != '\0'; k++, j++)
            {
                res[j] = morse_codes[serial][k]; //Copying the Morse code
            }
            res = add_char(res, 1); //Adding a space after each character
            res[j] = ' ';
            j++;
        }
        else if (str[i] == ' ') //Adding two spaces after each word
        {
            res = add_char(res, 2);
            res[j] = str[i];
            res[j + 1] = str[i];
            j += 2;
        }
    }
    res[j] = '\0';
    return res;
}