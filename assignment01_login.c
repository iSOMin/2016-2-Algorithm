#include <stdio.h>
#include <stdlib.h>

int main() {
	FILE* inputFlie = fopen("login.inp", "r");
	FILE* outputFile = fopen("login.out", "w");

	int numberOfTimeSection = 5;
	int numberOfDaySection = 5;
	int questionNumber = 3;
	int dayRange[2] = {1, 1};
	int timeRange[2] = {1, 1};
	int blockSum;

	int questionIndex, dayIndex, timeIndex;

	int **infoMatrix;



	fscanf(inputFlie, "%d %d", &numberOfTimeSection, &numberOfDaySection);

	infoMatrix = (int **)malloc(sizeof(int*) * numberOfTimeSection);
	infoMatrix[0] = (int *)malloc(sizeof(int) * numberOfDaySection * numberOfTimeSection);
	for (timeIndex = 0; timeIndex < numberOfTimeSection; timeIndex++) {
		if(timeIndex != 0) {
	    	infoMatrix[timeIndex] = infoMatrix[timeIndex - 1] + numberOfDaySection;
	    }
	    for (dayIndex = 0; dayIndex < numberOfDaySection; dayIndex++) {
			fscanf(inputFlie, "%d", &infoMatrix[timeIndex][dayIndex]);
		}
	}

	fscanf(inputFlie, "%d", &questionNumber);

	for (questionIndex = 0; questionIndex < questionNumber; questionIndex++) {
		blockSum = 0;
		fscanf(inputFlie, "%d %d %d %d", &dayRange[0], &dayRange[1], &timeRange[0], &timeRange[1]);

		for (dayIndex = dayRange[0] - 1; dayIndex < dayRange[1]; dayIndex++) {
			for (timeIndex = timeRange[0] - 1; timeIndex < timeRange[1]; timeIndex++) {
				blockSum += infoMatrix[timeIndex][dayIndex];
			}
		}
		fprintf(outputFile, "%d\n", blockSum);
	}


	free(infoMatrix[0]);
	free(infoMatrix);

	fclose(inputFlie);
	fclose(outputFile);

	return 0;
}
