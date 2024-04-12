#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType {
    int id;
    char name;
    int order; 
};

// Node for Hash Chaining
struct HashNode {
    struct RecordType data;
    struct HashNode* next;
};

// Hash Table Structure
struct HashType {
    struct HashNode** buckets;
    int size;
};

// Compute the hash function
int hash(int x, int size) {
    return x % size;
}

// Initialize Hash Table
struct HashType* createHashTable(int size) {
    struct HashType* hashTable = (struct HashType*)malloc(sizeof(struct HashType));
    hashTable->size = size;
    hashTable->buckets = (struct HashNode**)malloc(sizeof(struct HashNode*) * size);
    
    for (int i = 0; i < size; ++i) {
        hashTable->buckets[i] = NULL;
    }

    return hashTable;
}

// Insert a record into the hash table
void insertHash(struct HashType* hashTable, struct RecordType record) {
    int index = hash(record.id, hashTable->size);
    struct HashNode* newNode = (struct HashNode*)malloc(sizeof(struct HashNode));
    newNode->data = record;
    newNode->next = hashTable->buckets[index];
    hashTable->buckets[index] = newNode;
}

// Display the hash table contents
void displayRecordsInHash(struct HashType* hashTable) {
    printf("Hash Table Contents:\n");
    for (int i = 0; i < hashTable->size; ++i) {
        struct HashNode* node = hashTable->buckets[i];
        if (node) {
            printf("Index %d -> ", i);
            while (node) {
                printf("id: %d, name: %c, order: %d -> ", node->data.id, node->data.name, node->data.order);
                node = node->next;
            }
            printf("NULL\n");
        }
    }
}

// Parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData) {
    FILE* inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, id, order;
    char name;
    struct RecordType* pRecord;
    *ppData = NULL;

    if (inFile) {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType*)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL) {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i) {
            pRecord = *ppData + i;
            fscanf(inFile, "%d %c %d\n", &id, &name, &order);
            pRecord->id = id;
            pRecord->name = name;
            pRecord->order = order;
        }
        fclose(inFile);
    }
    return dataSz;
}

// Prints the records
void printRecords(struct RecordType pData[], int dataSz) {
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i) {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}

int main(void) {
    struct RecordType* pRecords;
    int recordSz = 0;

    recordSz = parseData("input_lab_9.txt", &pRecords);
    printRecords(pRecords, recordSz);

    struct HashType* hashTable = createHashTable(31); // Assume 31 as a suitable size
    for (int i = 0; i < recordSz; i++) {
        insertHash(hashTable, pRecords[i]);
    }
    displayRecordsInHash(hashTable);

    return 0;
}
