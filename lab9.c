#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
	struct RecordType* item;
	struct HashType* next;
};

// Compute the hash function
int hash(int x)
{
	return x % 23;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		// if index is occupied with any records, print all

		
		
        struct HashType *tmp = &pHashArray[i];

		if(tmp->item == NULL){
			continue;
		}

		printf("%d -> ", i);
        while (tmp != NULL)
        {
            if (tmp->item != NULL)
                printf("%d, %c, %d -> ", tmp->item->id, tmp->item->name, tmp->item->order);
            tmp = tmp->next;
        }
        printf("NULL\n");
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);



	// Your hash implementation

	int hashSz = 23; // assuming hash table size is 23
    struct HashType *hashArray = (struct HashType *)malloc(sizeof(struct HashType) * hashSz);



    for (int i = 0; i < hashSz; i++)
    {
        hashArray[i].item = NULL;
        hashArray[i].next = NULL;
    }


    for (int i = 0; i < recordSz; i++)
    {

		struct HashType *newNode = (struct HashType *)malloc(sizeof(struct HashType));
		newNode->item = (struct RecordType *)malloc(sizeof(struct RecordType));
		newNode->item->id = pRecords[i].id;
		newNode->item->name = pRecords[i].name;
		newNode->item->order = pRecords[i].order;
		newNode->next = NULL;

		int hashValue = hash(pRecords[i].id);
		struct HashType *tmp = &hashArray[hashValue];

		if (tmp->item == NULL) {
			tmp->item = newNode->item;
			tmp->next = NULL;
		} else {
			struct HashType *oldHead = tmp->next;
			tmp->next = newNode;
			newNode->next = oldHead;
		}

    }

	
    displayRecordsInHash(hashArray, hashSz);


}