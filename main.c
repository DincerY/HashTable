#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TABLE_SIZE 10

typedef struct Node{
    char * key;
    int value;
    struct Node * next;
} node;

typedef struct HastTable{
    node * table[TABLE_SIZE];
} hashTable;

unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash << 5) + *key++;
    }
    return hash % TABLE_SIZE;
}

node * createNode(const char * key, int value){
    node * newNode = (node*)malloc(sizeof(node));
    if(newNode){
        newNode->key = strdup(key);
        newNode->value = value;
        newNode->next = NULL;
    }
    return newNode;
}

void insert(hashTable * ht,const char* key,int value){
    unsigned int index = hashFunction(key);
    node * newNode = createNode(key,value);

    if(ht->table[index]){
        newNode->next = ht->table[index];
    }
    ht->table[index] = newNode;
}

int search(hashTable * ht, const char * key){
    unsigned int index = hashFunction(key);
    node * currentNode = ht->table[index];
    while (currentNode){
        if(strcmp(currentNode->key,key) == 0){
            return currentNode->value;
        }
        currentNode = currentNode->next;
    }
}

void printHashTable(hashTable * ht){
    for (int i = 0; i < TABLE_SIZE; i++) {
        node * cur = ht->table[i];
        printf("[%d]",i);

        while (cur){
            printf("(%s,%d)",cur->key,cur->value);
            cur = cur->next;
        }
        printf("\n");
    }
}

void freeHashTable(hashTable* ht){
    for (int i = 0; i < TABLE_SIZE; i++) {
        node* current = ht->table[i];
        while (current){
            node* next = current->next;
            free(current->key);
            free(current);
            current = next;
        }
    }
}

int main() {

    hashTable ht;
    memset(&ht, 0, sizeof(hashTable));


    insert(&ht, "John", 42);
    insert(&ht, "Jane", 28);
    insert(&ht, "Bob", 35);

    // Hash tablosunu yazdırma
    printf("Hash Table:\n");
    printHashTable(&ht);

    return 0;
}