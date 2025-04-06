#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 50  

// Structure for storing words with frequency
typedef struct { 
    char word[MAX_LEN]; 
    int number, freq; 
} WordEntry;

// Huffman Tree Node
typedef struct Node { 
    char word[MAX_LEN]; 
    int freq; 
    struct Node *left, *right; 
} Node;

WordEntry *table = NULL; 
int count = 0, capacity = 10;  // Dynamic array with initial size

// Find word index in table
int findWord(char *word) {
    for (int i = 0; i < count; i++) if (!strcmp(word, table[i].word)) return i;
    return -1;
}

// Insert word or update frequency
void insertWord(char *word) {
    int idx = findWord(word);
    if (idx == -1) { 
        if (count == capacity) { capacity *= 2; table = realloc(table, capacity * sizeof(WordEntry)); }
        strcpy(table[count].word, word); 
        table[count].number = count + 1; 
        table[count].freq = 1; 
        count++; 
    } else table[idx].freq++;
}

// Build Huffman Tree
Node* buildHuffmanTree() {
    Node **nodes = malloc(count * sizeof(Node*)), *a, *b, *newNode;
    int size = count;
    for (int i = 0; i < count; i++) {
        nodes[i] = malloc(sizeof(Node));
        strcpy(nodes[i]->word, table[i].word);
        nodes[i]->freq = table[i].freq;
        nodes[i]->left = nodes[i]->right = NULL;
    }
    while (size > 1) {
        for (int i = 0; i < size - 1; i++) 
            if (nodes[i]->freq > nodes[i + 1]->freq) { Node* tmp = nodes[i]; nodes[i] = nodes[i + 1]; nodes[i + 1] = tmp; }
        a = nodes[0]; b = nodes[1];
        newNode = malloc(sizeof(Node)); newNode->freq = a->freq + b->freq;
        newNode->left = a; newNode->right = b; nodes[0] = newNode;
        memmove(&nodes[1], &nodes[2], (--size - 1) * sizeof(Node*));
    }
    Node *root = nodes[0]; free(nodes); return root;
}

// Print Huffman Codes
void printHuffman(Node *root, char *code, int depth) {
    if (!root) return;
    if (strlen(root->word) > 0) { code[depth] = '\0'; printf("Word: %-15s Code: %s\n", root->word, code); }
    code[depth] = '0'; printHuffman(root->left, code, depth + 1);
    code[depth] = '1'; printHuffman(root->right, code, depth + 1);
}

// Read file and process words
void processFile(const char *filename) {
    FILE *file = fopen(filename, "r"); char word[MAX_LEN];
    if (!file) { perror("Error opening file"); exit(1); }
    table = malloc(capacity * sizeof(WordEntry));
    while (fscanf(file, "%49s", word) != EOF) { for (int i = 0; word[i]; i++) word[i] = tolower(word[i]); insertWord(word); }
    fclose(file);
}

// Free Huffman Tree
void freeTree(Node *root) {
    if (!root) return;
    freeTree(root->left);
    freeTree(root->right);
    free(root);
}

// Main function
int main() {
    processFile("input.txt");

    printf("\nUnique Words with Numbers and Frequency:\n");
    for (int i = 0; i < count; i++) 
        printf("Word: %-15s Number: %-3d Frequency: %d\n", table[i].word, table[i].number, table[i].freq);

    Node *root = buildHuffmanTree();
    printf("\nHuffman Codes:\n");
    char code[20]; printHuffman(root, code, 0);

    freeTree(root);
    free(table);
    return 0;
}
