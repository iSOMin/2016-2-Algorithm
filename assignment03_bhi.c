// before find BHI function

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

typedef struct {
	int x;
	int y;
} STAR;

int findMinimumBHI (STAR*, int, int);
int distanceOf (STAR, STAR);
void quickStarSort (STAR*, int, int);
void swapStar (STAR*, STAR*);
STAR getShorterStar (STAR, STAR);
int isSame (STAR, STAR);


int main() {
	int starArraySize;
	STAR* starArray;
	int minBHI = 150000;
	int i;

	// file open
	FILE* inputFlie = fopen("2.inp", "r");
	FILE* outputFile = fopen("bhi.out", "w");

	// get input
	fscanf(inputFlie, "%d", &starArraySize);
	starArray = (STAR*)malloc(sizeof(STAR) * starArraySize);
	for(i = 0; i < starArraySize; i++) {
		fscanf(inputFlie, "%d %d", &starArray[i].x, &starArray[i].y);
	}

	// calculate minimum BHI
	quickStarSort(starArray, 0, starArraySize);

	//for(i = 0; i < starArraySize; i++) {
	//	printf("%d %d\n", starArray[i].x, starArray[i].y);
	//}

	minBHI = findMinimumBHI(starArray, 0, starArraySize);
	fprintf(outputFile, "%d\n", minBHI);

	// file close
	fclose(inputFlie);
	fclose(outputFile);

	return 0;
}


int findMinimumBHI (STAR* starArray, int start, int starArraySize) {
	int i, j, k;
	int baseDistance;
	int minBHI = 150000;

	for (i = 0; i < starArraySize - 2; i++) {
		for (j = i + 1; j < starArraySize - 1; j++) {
			baseDistance = distanceOf(starArray[i], starArray[j]);

			if (minBHI < baseDistance) 
				continue;
			
			for (k = 0; k < starArraySize; k++) {
				if (k == i || k == j) 
					continue;

				if (distanceOf(starArray[i], starArray[k]) > baseDistance) 
					continue;

				if (distanceOf(starArray[j], starArray[k]) > baseDistance)
					continue;
				
				if (minBHI > baseDistance) {
					printf("%d %d %d: %d\n", i, j, k, baseDistance);
					minBHI = baseDistance;
					break;
				}
			}
		}
	}
	return minBHI;
}

int distanceOf (STAR star1, STAR star2) {
	return sqrt(pow((double)(star1.x - star2.x), 2.0) + 
				pow((double)(star1.y - star2.y), 2.0));
}

void quickStarSort(STAR* array, int start, int end){
	int i = start;
	int j = end;
	STAR pivot = array[(start + end) / 2];

	do {
		while (isSame(getShorterStar(array[i], pivot), array[i]))
			i++;
		while (isSame(getShorterStar(array[j], pivot), pivot))
			j--;

		if (i <= j) {
			swapStar (&array[i], &array[j]);
			i++;
			j--;
		}
	} while (i <= j);

	if (start < j)
		quickStarSort (array, start, j);
	if (i < end)
		quickStarSort (array, i, end);
}

void swapStar (STAR* a, STAR* b) {
	STAR tmp;
	int i;
	for (i = 0; i < 3; i++) {
		tmp = *a;
		*a = *b;
		*b = tmp;
	} 
}

STAR getShorterStar (STAR a, STAR b) {
	return (a.x < b.x)? a : (a.x > b.x)? b : (a.y < b.y)? a : b;
}

int isSame (STAR a, STAR b) {
	if (a.x == b.x && a.y == b.y) {
		return 0;
	} else {
		return 1;
	}
}