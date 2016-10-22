#include <stdio.h>
#include <stdlib.h>

// function prototype declaration
void printPath (FILE*, int**, int, int);
void calculateViaNode (int**, int**, int, int*, int*);
int findShortestPath (int**, int, int*, int*);


int main() {
	int matrixSize;
	int** fuelMatrix;
	int** viaMatrix;
	int i, j, k;
	int resultStart, resultEnd;
	int result;

	/**
	 * file open
	 */
	FILE* inputFile = fopen("1.inp", "r");
	FILE* outputFile = fopen("eleccar.out", "w");

	/**
	 * set lists and get input
	 */
	fscanf(inputFile, "%d", &matrixSize);
	fuelMatrix = (int**)malloc(sizeof(int*) * matrixSize);
	fuelMatrix[0] = (int*)malloc(sizeof(int) * matrixSize * matrixSize);
	viaMatrix = (int**)malloc(sizeof(int*) * matrixSize + 1);
	viaMatrix[0] = (int*)malloc(sizeof(int) * (matrixSize + 1) * (matrixSize + 1));
	// get input 
	for (j = 0; j < matrixSize; j++) {
		fscanf(inputFile, "%d", fuelMatrix[0] + j);
	}
	for (i = 1; i < matrixSize + 1; i++) {
		// set lists for viaMatrix and fuelMatrix
		viaMatrix[i] = viaMatrix[i - 1] + matrixSize + 1;
		if (i == matrixSize) {
			break;
		} 
		fuelMatrix[i] = fuelMatrix[i - 1] + matrixSize;

		// get input
		for (j = 0; j < matrixSize; j++) {
			fscanf(inputFile, "%d", fuelMatrix[i] + j);
		}
	}

	/**
	 * calculate via nodes and find shortest path
	 */
	calculateViaNode (fuelMatrix, viaMatrix, matrixSize, &resultStart, &resultEnd);
    result = findShortestPath(fuelMatrix, matrixSize, &resultStart, &resultEnd);
 

 	/**
 	 * set works by cases of result
 	 */
    if (result == 99999) {
    	fprintf (outputFile, "99999\n");
    } else if (result == -1) {
    	fprintf (outputFile, "nega-cycle");
    } else {
    	fprintf (outputFile, "%d\n", result);
    	fprintf (outputFile, "%d ", resultStart);
    	printPath (outputFile, viaMatrix, resultStart, resultEnd);
    	fprintf (outputFile, "%d\n", resultEnd);
    }
		
  

	/**
	 * file close
	 */
	fclose(inputFile);
	fclose(outputFile);

	/**
     * free allocation
     */
    free(fuelMatrix[0]);
	free(fuelMatrix);
	free(viaMatrix[0]);
	free(viaMatrix);

	return 0;
}

/**
 * calculte via node
 */
void calculateViaNode (int** fuelMatrix, int** viaMatrix, int matrixSizeforCalc, int* resultStart, int* resultEnd) {
	int i, j, k;

	for (k = 0; k < matrixSizeforCalc; k++) {		// 경유하는 지점

        for (i = 0; i < matrixSizeforCalc; i++) {	
            for (j = 0; j < matrixSizeforCalc; j++) {
                if (fuelMatrix[i][k] + fuelMatrix[k][j] < fuelMatrix[i][j]) {
                    viaMatrix[i + 1][j + 1] = k + 1;        
                    fuelMatrix[i][j] = fuelMatrix[i][k] + fuelMatrix[k][j];
                }
            }
        }  
    }

}

/**
 * finding shortest path
 */
int findShortestPath (int** fuelMatrix, int matrixSizeForFind, int* resultStart, int* resultEnd) {
	int max = 0;
	int i, j, k;

	for (i = 0; i < matrixSizeForFind; i++) {
		for (j = 0; j < matrixSizeForFind; j++) {

			if (i == j && fuelMatrix[i][j] < 0) {	// 음수 사이클이 존재하면
				return -1;
			}
			if (fuelMatrix[i][j] >= 99999) {		// 도달할 수 없는 정점이 존재하면
				return 99999;
			}
			if (fuelMatrix[i][j] > max) {			// 현재 max보다 더 큰 fuelMatrix가 있으면
				max = fuelMatrix[i][j];
				*resultStart = i + 1;
				*resultEnd = j + 1;
			}
		}
	}

	return max;
}


/**
 * print path on output file (using via matrix)
 */
void printPath (FILE* outputFileInFunc, int** viaMatrixForPrint, int start, int end) {
	if (viaMatrixForPrint[start][end] != 0) {
		printPath (outputFileInFunc, viaMatrixForPrint, start, viaMatrixForPrint[start][end]);
		fprintf (outputFileInFunc, "%d ", viaMatrixForPrint[start][end]);
		printPath (outputFileInFunc, viaMatrixForPrint, viaMatrixForPrint[start][end], end);
	}
}

