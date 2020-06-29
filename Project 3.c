/*  Date: 12/05/2018
	Description: Project 3 - Hash Table
	Version 3.0
	*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define N 17
#define SIZE 43680
#define hashSIZE 87211
#define transactions 1000000

const char digits[15] = "0123456789ABCD", fillString[N] = "AVAILABLE";
char hashTable[hashSIZE][N];
int numbers[SIZE] = { 0 }, countCollisions = 0, prices[hashSIZE] = { 0 }, agores[hashSIZE] = { 0 };

void initializeHashTable(char arr[hashSIZE][N]) {
	for (int i = 0; i < hashSIZE; i++) strcpy_s(arr[i], N, fillString);
	return;
}

void createRandomCode(char array[N]) {
	int i, randomDigit, randomDigitIndex, randomPosition;
	// Add random digits
	for (i = 0; i < N - 1; i++) {
		randomDigitIndex = rand() % 10;
		randomDigit = digits[randomDigitIndex]; // choose a random digit from digits[]
		array[i] = randomDigit;
	}

	//Add 4 random Letters
	for (i = 0; i < 4; i++) {
		randomPosition = rand() % (N - 1);
		randomDigitIndex = rand() % 4;
		randomDigitIndex += 10;
		randomDigit = digits[randomDigitIndex];
		array[randomPosition] = randomDigit;
	}
	array[N - 1] = '\0'; /* finalize string of randomCode*/
	return;
}

unsigned int moduloDivision(char str[N]) {
	int letter, i;
	long int hashVal = 0;
	for (i = 0; i < N - 1; i++) {
		letter = str[i];
		hashVal += letter;
	}
	return (hashVal % hashSIZE);
}

void linearProbing(char hashTable[hashSIZE][N], char randomCode[N], unsigned int hashIndex) {
	//int temp2 = hashIndex;
	hashIndex++; // increase index by 1
	while (hashIndex < hashSIZE) {
		//if AVAILABLE
		if (strcmp(hashTable[hashIndex], fillString) == 0) {
			strcpy_s(hashTable[hashIndex], N, randomCode);
			prices[hashIndex] = 10 + rand() % 990;
			agores[hashIndex]++;
			//printf("Found next FREE position at Index:%5d. Put %11s\t\t", hashIndex, hashTable[hashIndex]);
			//printf("Skipped %5d positions\n", hashIndex - temp2);
			break;
		}
		//if the same
		else if (strcmp(hashTable[hashIndex], randomCode) == 0) {
			agores[hashIndex]++;
			prices[hashIndex] += 10 + rand() % 990;
			break;
		}
		else {
			hashIndex++; // check next free index
			if (hashIndex > hashSIZE) hashIndex = 0; // dont get out of array limits	
		}
	}
	return;
}

int putCustomerToTable(unsigned int hashIndex, char randomCode[N]) {
	//if AVAILABLE
	if (strcmp(hashTable[hashIndex], fillString) == 0) {
		strcpy_s(hashTable[hashIndex], N, randomCode);
		prices[hashIndex] = 10 + rand() % 990;
		agores[hashIndex]++;
		//printf("Place in %6d�-> %11s\n", hashIndex, hashTable[hashIndex]);
	}
	//if the same
	else if (strcmp(hashTable[hashIndex], randomCode) == 0) {
		agores[hashIndex]++;
		prices[hashIndex] += 10 + rand() % 990;
	}
	else {
		//printf("Found in %6d�-> %11s\n", hashIndex, hashTable[hashIndex]);
		//printf("\n-> Collision at index %6d ", hashIndex);
		countCollisions++;
		linearProbing(hashTable, randomCode, hashIndex); // Manage Collision
	}
}

void mostUsedCard() {
	unsigned int i, maxagores = agores[0], card = 0;
	for (i = 1; i < hashSIZE; i++) {
		if (agores[i] > maxagores) {
			maxagores = agores[i];
			card = i;
		}
	}
	printf("\nMost used card: %s with %u transactions\n", hashTable[card], maxagores);
	return;
}

void BestCustomer() {
	unsigned int i, maxcust = agores[0], card = 0;
	for (i = 1; i < hashSIZE; i++) {
		if (prices[i] > maxcust) {
			maxcust = prices[i];
			card = i;
		}
	}
	if (strcmp(hashTable[card], fillString) == 0) return;
	printf("\nBest customer: %s with %u euros spent\n", hashTable[card], maxcust);
	return;
}


int main() {
	char randomCode[N], customers[SIZE][N];
	unsigned int i, hashIndex, no;
	srand(1047028);
	initializeHashTable(hashTable);
	puts("Hash Table initialized");

	for (i = 0; i < SIZE; i++) {
		createRandomCode(randomCode);
		strcpy_s(customers[i], N, randomCode);
	}

	for (i = 0; i < transactions; i++) {
		no = rand() % SIZE;
		hashIndex = moduloDivision(customers[no]);
		putCustomerToTable(hashIndex, customers[no]);
		if ((i == 250000) || (i == 500000) || (i == 750000)) printf("This may take a while... %d transactions, %d collisions\n", i, countCollisions);
	}

	printf("Collisions: %d\n", countCollisions);
	mostUsedCard();
	BestCustomer();
	system("PAUSE");
	return 0;
}