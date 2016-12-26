#include <iostream>
#include <string>
#include <fstream>
using namespace std;


void setShortWay();
int getSolution();
int maximum(int, int);
int maximum(int, int, int);

int graphSize;	
int friendLocation[3];
int distanceArray[26][26];
int degreeArray[26];
char meetingPoint;
int nowLongest = 99999;

int main(){
	ifstream inFile;
	inFile.open("candle.inp");
	ofstream outFile("candle.out");
	int i, j, k;


	inFile >> graphSize;

	for(i = 0; i < 3; i++) {
		char tempLocation;
		inFile >> tempLocation;
		friendLocation[i] = (int)tempLocation - (int)'a';
	}

	for(i = 0; i < graphSize; i++) {
		for(j = 0; j < graphSize; j++) {
			distanceArray[i][j] = 99999;
		}
	}

	for(i = 0; i < graphSize; i++) {
		int startPoint;
		int endPoint;
		int distance;
		int degree;
		char tempPoint;

		inFile >> tempPoint >> degree;
		startPoint = (int)tempPoint - (int)'a';
		degreeArray[startPoint] = degree;

		for(j = 0; j < degree; j++) {
			inFile >> tempPoint >> distance;
			endPoint = (int)tempPoint - (int)'a';
			distanceArray[startPoint][endPoint] = distance;
		}
	}


	for (k = 0; k < graphSize; k++) {
		for (i = 0; i < graphSize; i++) {
			for (j = 0; j < graphSize; j++) {
				if (i == k || j == k) {
					if (distanceArray[i][j] > distanceArray[i][k] + distanceArray[k][j]) { 
						distanceArray[i][j] = distanceArray[i][k] + distanceArray[k][j];
					} else {
						continue;
					}
				} else if (distanceArray[i][j] > distanceArray[i][k] + distanceArray[k][j] + degreeArray[k]) { 
					distanceArray[i][j] = distanceArray[i][k] + distanceArray[k][j] + degreeArray[k];
				} else {
					continue;
				}
			}
		}
	}

	int result = getSolution();
	outFile << (char)meetingPoint << " " << result << endl;

  

	inFile.close();
	outFile.close();

	return 0;
}

void setShortWay() {

}

int getSolution() {
	int current;
	int fromFirst, fromSecond, fromThird;

	for (int i = 0; i < graphSize; i++) {
		fromFirst = distanceArray[friendLocation[0]][i];
		fromSecond = distanceArray[friendLocation[1]][i];
		fromThird = distanceArray[friendLocation[2]][i];

		current = maximum(fromFirst, fromSecond, fromThird);

		if(current < nowLongest) {
			nowLongest = current;	
			meetingPoint = char(i + (int)'a');
		}
	}
	return nowLongest;
}


int maximum( int a, int b ) { return a>b ? a : b ; }
int maximum( int a, int b, int c ) { return maximum( maximum(a,b), c ) ; }
