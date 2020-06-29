/*  Date: 24/05/2018
	Description: Project 4 - Compare search algorithms
	Version 5.3
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 50000
#define hashSIZE 100003

void createFirstMatrix();
void createSecondMatrix();
int linearsearch(int firstMatrix[N], int secondMatrix[N]);
int sortbinary(int firstMatrix[N], int secondMatrix[N]);
int bubblesort(int *array);
int binarysearch(int array[], int search);
int openAddressing(int firstMatrix[N], int secondMatrix[N]);
void fillHashTable(int *table, int num, int index);
int searchHash(int *table, int num, int index);

int firstMatrix[N], secondMatrix[N];
struct hash *hashTable = NULL;

struct node {
	int key;
	struct node *next;
};

struct hash {
	struct node *head;
	int count;
};

struct node * createNode(int key);

void insertToHash(int key);
int searchInHash(int key);
void chaining();
/////////////////////////////////////////////////////////////////////

 int main(){
	 if (hashSIZE < N) {
		 puts("HashSIZE < N");
		 system("PAUSE");
		 return -5;
	}
	printf_s("N = %d,  Hash Size = %d\n", N, hashSIZE);
	srand(1047028);
    createFirstMatrix();
    createSecondMatrix();
    if (linearsearch(firstMatrix, secondMatrix)) return -1;
    if (sortbinary(firstMatrix, secondMatrix)) return -2;
	if (openAddressing(firstMatrix, secondMatrix)) return -3;
	chaining();
	system("PAUSE");
    return 0;
 }

 void createFirstMatrix() {
	 unsigned int i;
	 srand(1047028);
	 for (i = 0; i<N; i++) {
		 firstMatrix[i] = rand() % (10 * N);
	 }
	 return;
 }

 void createSecondMatrix() {
	 unsigned int i, num1, num2;
	 for (i = 0; i < N; i++) secondMatrix[i] = -1.0;
	 for (i = 0; i < N / 2; i++) {
		 num1 = rand() % N;
		 num2 = rand() % N;
		 secondMatrix[num1] = firstMatrix[num2];
	 }
	 for (i = 0; i < N; i++) {
		 if (secondMatrix[i] == -1) secondMatrix[i] = rand() % (10 * N);
	 }
	 return;
 }
 /////////////////////////////////////////////////////////////////////

 int linearsearch(int firstMatrix[N], int secondMatrix[N]) {
	 unsigned int i, j, counter = 0;
	 clock_t start = clock();
	 for (i = 0; i < N; i++) {
		 for (j = 0; j < N; j++) {
			 if (firstMatrix[i] == secondMatrix[j]) {
				 counter++;
				 break;
			 }
		 }
	 }
	 clock_t end = clock();
	 puts("1: Linear Search:");
	 printf_s("   Common numbers: %d, Time: %f\n", counter, (float)(end - start) / CLOCKS_PER_SEC);
	 return 0;
 }
 /////////////////////////////////////////////////////////////////////

 int sortbinary(int firstMatrix[N], int secondMatrix[N]) {
	 unsigned int i, counter = 0;
	 bubblesort(secondMatrix);
	 clock_t start = clock();
	 for (i = 0; i < N; i++) {
		 if (binarysearch(secondMatrix, firstMatrix[i]) == 1) counter++;
	 }
	 clock_t end = clock();
	 puts("2: Sort and Binary Search:");
	 printf_s("   Common numbers: %d, Time: %f\n", counter, (float)(end - start) / CLOCKS_PER_SEC);
	 return 0;
 }

 int bubblesort(int *array) {
	 int swap;
	 for (int i = 0; i < N - 1; i++){
		 for (int j = 0; j < N - i - 1; j++){
			 if (array[j] > array[j + 1]){
				 swap = array[j];
				 array[j] = array[j + 1];
				 array[j + 1] = swap;
			 }
		 }
	 }
	 return;
 }

 int binarysearch(int array[], int search) {
	 int first = 0, last = N - 1, middle = (first + last) / 2;
	 while (first <= last) {
		 if (array[middle] < search)
			 first = middle + 1;
		 else if (array[middle] == search) {
			 return 1;
		 }
		 else
			 last = middle - 1;
		 middle = (first + last) / 2;
	 }
	 if (first > last) return 0;
 }
 /////////////////////////////////////////////////////////////////////

 int openAddressing(int firstMatrix[N], int secondMatrix[N]) {
	 unsigned int i, counter = 0, hashIndex;
	 int hashTable[hashSIZE];
	 for (i = 0; i < hashSIZE; i++) hashTable[i] = -1.0;
	 for (i = 0; i < N; i++) {
		 hashIndex = (secondMatrix[i] % hashSIZE);
		 fillHashTable(hashTable, secondMatrix[i], hashIndex);
	 }

	 clock_t start = clock();
	 for (i = 0; i < N; i++) {
		 hashIndex = (firstMatrix[i] % hashSIZE);
		 if (searchHash(hashTable, firstMatrix[i], hashIndex) == 1) counter++;
	 }
	 clock_t end = clock();
	 puts("3: Open Addressing Search:");
	 printf_s("   Common numbers: %d, Time: %f\n", counter, (float)(end - start) / CLOCKS_PER_SEC);
	 return 0;
 }

 void fillHashTable(int *table, int num, int index) {
	 if (table[index] == -1 || table[index] == num) table[index] = num;
	 else {
		 index++;
		 while (index < hashSIZE) {
			 if (table[index] == -1 || table[index] == num) {
				 table[index] = num;
				 break;
			 }
			 else {
				 index++;
				 if (index > hashSIZE) index = 0; // dont get out of array limits	
			 }
		 }
	 }
 }

 int searchHash(int *table, int num, int index) {
	 while (1) {
		 if (table[index] == num) return 1;
		 else if (table[index] == -1) return 0;
		 else {
			 index++;
			 if (index > hashSIZE) index = 0;
		 }
	 }
 }
 /////////////////////////////////////////////////////////////////////

 void chaining() {
	 unsigned int i, counter = 0;
	 hashTable = (struct hash *)calloc(N, sizeof(struct hash));
	 for (i = 0; i < N; i++) {
		 insertToHash(secondMatrix[i]);
	 }
	 clock_t start = clock();
	 for (i = 0; i < N; i++) {
		 if (searchInHash(firstMatrix[i]) == 1) counter++;
	 }
	 clock_t end = clock();
	 puts("4: Chaining Search:");
	 printf_s("   Common numbers: %d, Time: %f\n", counter, (float)(end - start) / CLOCKS_PER_SEC);
 }

 struct node * createNode(int key) {
	 struct node *newnode;
	 newnode = (struct node *)malloc(sizeof(struct node));
	 newnode->key = key;
	 newnode->next = NULL;
	 return newnode;
 }

 void insertToHash(int key) {
	 int hashIndex = key % N;
	 struct node *newnode = createNode(key);
	 /* head of list for the bucket with index "hashIndex" */
	 if (!hashTable[hashIndex].head) {
		 hashTable[hashIndex].head = newnode;
		 hashTable[hashIndex].count = 1;
		 return;
	 }
	 /* adding new node to the list */
	 newnode->next = (hashTable[hashIndex].head);
	 /*
	 * update the head of the list and no of
	 * nodes in the current bucket
	 */
	 hashTable[hashIndex].head = newnode;
	 hashTable[hashIndex].count++;
	 return;
 }

 int searchInHash(int key) {
	 int hashIndex = key % N, flag = 0;
	 struct node *myNode;
	 myNode = hashTable[hashIndex].head;
	 if (!myNode) return 0;//Search element unavailable in hash table
	 while (myNode != NULL) {
		 if (myNode->key == key) {
			 flag = 1;
			 return 1;///////////////////
			 break;
		 }
		 myNode = myNode->next;
	 }
	 if (!flag) return 0;//Search element unavailable in hash table
	 
 }