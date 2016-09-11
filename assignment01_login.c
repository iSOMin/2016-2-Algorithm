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

	int questionIndex, dayIndex, timeIndex;
	int **infoMatrix;



	fscanf(inputFlie, "%d %d", &numberOfTimeSection, &numberOfDaySection);
	numberOfTimeSection++;
	numberOfDaySection++;

	infoMatrix = (int **)malloc(sizeof(int*) * (numberOfTimeSection));
	infoMatrix[0] = (int *)malloc(sizeof(int) * (numberOfDaySection) * (numberOfTimeSection));
	for (timeIndex = 1; timeIndex < numberOfTimeSection; timeIndex++) {
	    	infoMatrix[timeIndex] = infoMatrix[timeIndex - 1] + numberOfDaySection;
	    for (dayIndex = 1; dayIndex < numberOfDaySection; dayIndex++) {
			fscanf(inputFlie, "%d", &infoMatrix[timeIndex][dayIndex]);
			infoMatrix[timeIndex][dayIndex] = infoMatrix[timeIndex][dayIndex]
												+ infoMatrix[timeIndex - 1][dayIndex]
												+ infoMatrix[timeIndex][dayIndex - 1]
												- infoMatrix[timeIndex - 1][dayIndex - 1];
		}
	}

	fscanf(inputFlie, "%d", &questionNumber);

	for (questionIndex = 0; questionIndex < questionNumber; questionIndex++) {
		fscanf(inputFlie, "%d %d %d %d", &dayRange[0], &dayRange[1], &timeRange[0], &timeRange[1]);
		fprintf(outputFile, "%d\n", infoMatrix[timeRange[1]][dayRange[1]]
										- infoMatrix[timeRange[1]][dayRange[0] - 1]
										- infoMatrix[timeRange[0] - 1][dayRange[1]]
										+ infoMatrix[timeRange[0] - 1][dayRange[0] - 1]);
	}

	free(infoMatrix[0]);
	free(infoMatrix);

	fclose(inputFlie);
	fclose(outputFile);

	return 0;
}
