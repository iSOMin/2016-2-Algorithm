#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addFractionToOneArray (int*, int*, int*);
int compareFraction (int*, int*);
int funcLCM (int, int);
int funcGCD (int, int);
void quickFractionSort(int**, int, int);
void swapFraction (int*, int*);
int binaryFractionSearch(int**, int, int*);

int main() {

	time_t startTime = 0;
	time_t endTime = 0;
	startTime = clock();

	int listLength = 5;

	int i, j, k;
	int **dataList;
	//int **sortedList;
	int sumResult[2];
	int searchResult = 0;

	FILE* inputFlie = fopen("trio.inp", "r");
	FILE* outputFile = fopen("trio.out", "w");


	fscanf(inputFlie, "%d", &listLength);

	dataList = (int **)malloc(sizeof(int*) * (listLength + 1));
	dataList[0] = (int *)malloc(sizeof(int) * 3 * (listLength + 1));
	//sortedList = (int **)malloc(sizeof(int*) * (listLength + 1));
	//sortedList[0] = (int *)malloc(sizeof(int) * 3 * (listLength + 1));

	for (i = 1; i < (listLength + 1); i++) {
    	dataList[i] = dataList[i - 1] + 3;
    	//sortedList[i] = sortedList[i - 1] + 3;

	    for (j = 0; j < 2; j++) {
			fscanf(inputFlie, "%d", &dataList[i][j]);
			//sortedList[i][j] = dataList[i][j];
		}
		dataList[i][2] = i;
		//sortedList[i][2] = i;
	}

	//quickFractionSort (sortedList, 1, listLength);

	for (i = 1; i < (listLength + 1); i++) {
		for (j = 1; j < (listLength + 1); j++) {
			if (i == j || compareFraction(dataList[i], dataList[j]) > 0) {
				continue;
			}

			addFractionToOneArray (dataList[i], dataList[j], sumResult);
			
			for (k = 1; k < (listLength + 1); k++) {
				if (sumResult[0] * dataList[k][1] == sumResult[1] * dataList[k][0]) {
					fprintf(outputFile, "%d %d %d", i, j, k);
					goto finished;
				}
			}
			/*
			searchResult = binaryFractionSearch(sortedList, listLength, sumResult);

			if (searchResult != -1) {
				fprintf(outputFile, "%d %d %d", i, j, searchResult);
				goto finished;
			}
			*/
		}
	}


	fprintf(outputFile, "0 0 0");

	finished:


	free(dataList[0]);
	free(dataList);
	//free(sortedList[0]);
	//free(sortedList);

	fclose(inputFlie);
	fclose(outputFile);

	endTime = clock();
	printf ("%f\n", (float)((endTime - startTime)/CLOCKS_PER_SEC));

	return 0;
}

void addFractionToOneArray (int* firstNum, int* secondNum, int* sumResult) {
	int denom = funcLCM (firstNum[1], secondNum[1]);
	sumResult[0] = (denom / firstNum[1]) * firstNum[0] + (denom / secondNum[1]) * secondNum[0];
	sumResult[1] = denom;
	//int GCD = funcGCD(sumResult[0], sumResult[1]);
	//sumResult[0] /= GCD;
	//sumResult[1] /= GCD;
}

int compareFraction (int* firstNum, int* secondNum) {
	int denom = funcLCM (firstNum[1], secondNum[1]);
	if ((denom / firstNum[1]) * firstNum[0] - (denom / secondNum[1]) * secondNum[0] < 0) {
		return -1;
	} else if ((denom / firstNum[1]) * firstNum[0] - (denom / secondNum[1]) * secondNum[0] == 0){
		return 0;
	} else {
		return 1;
	}
}

int funcLCM (int firstNum, int secondNum) {
	return (secondNum * firstNum) / funcGCD(firstNum, secondNum);
}

int funcGCD (int firstNum, int secondNum) {
	if (secondNum == 0) return firstNum;
	return funcGCD(secondNum, firstNum % secondNum);
}

int binaryFractionSearch(int** dataArr, int size, int* findFraction) {
    int low = 1;
    int high = size;
    int mid;
 
    while (low <= high) {
        mid = (low + high) / 2;
        printf("%d , %d      =      %d , %d\n", dataArr[mid][0], dataArr[mid][1], findFraction[0], findFraction[1]);

        if (compareFraction(dataArr[mid], findFraction) > 0) {
        	high = mid - 1;
        } else if (compareFraction(dataArr[mid], findFraction) < 0) {
        	low = mid + 1;
        } else if (compareFraction(dataArr[mid], findFraction) == 0){
        	return dataArr[mid][2];
        }
    }

    return -1;
}

void quickFractionSort(int** array, int start, int end){
	int i = start;
	int j = end;
	int *tempFraction;
	int *pivot = array[(start + end) / 2];

	do {
		while (compareFraction(array[i], pivot) < 0)
			i++;
		while (compareFraction(array[j], pivot) > 0)
			j--;

		if (i <= j) {
			swapFraction (array[i], array[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (start < j)
		quickFractionSort (array, start, j);
	if (i < end)
		quickFractionSort (array, i, end);
}

void swapFraction (int* a, int* b) {
	int tmp;
	int i;
	for (i = 0; i < 3; i++) {
		tmp = a[i];
		a[i] = b[i];
		b[i] = tmp;
	} 
}
