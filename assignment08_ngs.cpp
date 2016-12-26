#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

class Ngs {
private:
	string ngsInfo;
	int length;
public:
	Ngs(string newNgsInfo): ngsInfo(newNgsInfo), length(ngsInfo.length()) {};

	void print() {
		cout << ngsInfo << endl;
	}
	int getLength() {
		return length;
	}
	string getNgsInfo() {
		return ngsInfo;
	}
};

void printNgsArray(vector<Ngs> array) {
	int i;
	for (i = 0; i < array.size(); i++) {
		array[i].print();
	}
}

int findLongestStringLength(vector<Ngs> array){
  
	int i;
	int longestStringLength = 1;
	int currentLength = 0;
	int size = array.size();

	for(i = 0; i < size; i++){
		currentLength = array[i].getLength();
		if(currentLength > longestStringLength) {
			longestStringLength = currentLength;
		}
	}

	return longestStringLength;
}

string radixSort(vector<Ngs>& array){
	int i;
	int newIndex;
	int size = array.size();
	int count = 0;
	int longestLength = findLongestStringLength(array);
	vector<Ngs> tempArray = array;
	int sameCount = 1;
	int maxCount = 1;
	string maxNgs;
	array.clear();

	vector<Ngs> a;
	vector<Ngs> g;
	vector<Ngs> t;
	vector<Ngs> c;

	while (longestLength > count - 1){
		for (i = 0; i < tempArray.size(); i++) {
			newIndex = tempArray[i].getLength() - 1 - count;
			if (newIndex == -1) {
				if((array.size() > 0) && (array[array.size() - 1].getNgsInfo() == tempArray[i].getNgsInfo())) {
					sameCount++;
					if(sameCount > maxCount) {
						maxCount = sameCount;
						maxNgs = tempArray[i].getNgsInfo();
					} else {
						continue;
					}
				} else {
					sameCount = 1;
				}
				array.push_back(tempArray[i]);
				continue;
			} else if (newIndex < -1) {
				continue;
			}
			char currentChar = tempArray[i].getNgsInfo()[newIndex];
			if (currentChar == 'a') {
				a.push_back(tempArray[i]);
			} else if (currentChar == 'c') {
				c.push_back(tempArray[i]);
			} else if (currentChar == 'g') {
				g.push_back(tempArray[i]);
			} else if (currentChar == 't') {
				t.push_back(tempArray[i]);
			} else {
				continue;
			}
		}

		tempArray.clear();

		for(int i = 0; i < a.size(); i++) {
			tempArray.push_back(a[i]);
		}
		a.clear();

		for(int i = 0; i < c.size(); i++) {
			tempArray.push_back(c[i]);
		}
		c.clear();

		for(int i = 0; i < g.size(); i++) {
			tempArray.push_back(g[i]);
		}
		g.clear();

		for(int i = 0; i < t.size(); i++) {
			tempArray.push_back(t[i]);
		}
		t.clear();

		count++;
	}
	return maxNgs;
}

int main(){
	ifstream inFile;
	inFile.open("ngs.inp");
	ofstream outFile("ngs.out");

	vector<Ngs> ngs;
	string max;
	string tempString;

	if(inFile.is_open()) {
		while(getline(inFile, tempString)) {
			ngs.push_back(tempString);
		}
	}
  
	max = radixSort(ngs);

	outFile << max;

	inFile.close();
	outFile.close();

	return 0;
}
