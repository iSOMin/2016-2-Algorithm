package laundry;

import java.io.*;

public class laundry {
	public static void main(String[] args) {
		try {
			BufferedReader input = new BufferedReader(new FileReader("2.inp"));
			BufferedWriter output = new BufferedWriter(new FileWriter("laundry.out"));
			
			String basisData = input.readLine();
			String[] dataTemp = basisData.split("\\s+");
			
			int numberOfHouse = Integer.parseInt(dataTemp[0]);
			int limitTime = Integer.parseInt(dataTemp[1]);
			
			House[] house = new House[numberOfHouse];
			int[][] distanceMatrix = new int[numberOfHouse][numberOfHouse];
			
			for(int i = 0; i < numberOfHouse; i++) {
				String locationData = input.readLine();
				dataTemp = locationData.split("\\s+");
				house[i] = new House(i + 1, Integer.parseInt(dataTemp[0]), Integer.parseInt(dataTemp[1]));
				for(int j = 0; j < i; j++) {
					distanceMatrix[j][i] = house[i].getDistanceFrom(house[j]);
					distanceMatrix[i][j] = distanceMatrix[j][i];
				}
			}
			
			BackTracker backTracker = new BackTracker(limitTime, numberOfHouse, distanceMatrix);
			int[] resultArr = backTracker.backtrack();
			
			if(resultArr[numberOfHouse - 1] == 0) {
				output.write("0");
			} else {
				for(int i = 0; i < resultArr.length - 1; i++) {
					output.write(resultArr[i] + " ");
				}
			}
			
			input.close();
			output.close();
			
		} catch (IOException e) {
			System.exit(1);
		}
	}	
}


class BackTracker {
	int limitTime;
	int nodeNumber;
	int[] nodeArr;
	int[][] distance;
	int[] answerArr;
	int[] leftArr;
	Permutation permutation;
	int n;
	
	BackTracker(int inputLimitTime, int inputNodeNumber, int[][] inputDistanceMatrix) {
		limitTime = inputLimitTime;
		nodeNumber = inputNodeNumber;
		nodeArr = new int[nodeNumber];
		answerArr = new int[nodeNumber + 1];
		answerArr[nodeNumber] = 0;
		distance = inputDistanceMatrix;
		n = nodeNumber;
	}
	
	int[] backtrack() {
		int range = factorial(nodeNumber - 1);
		permutation = new Permutation(nodeNumber);
		int[] newPerm;
		
		for (int i = 1; i < range; i++) {
			permutation.next();
			newPerm = permutation.getPermutation();
			getAnswer(newPerm);
		}
		
        return answerArr;
	}
	
	int factorial(int n) {
		if (n <= 1) {
			return n;
		} else {
			return factorial(n-1) * n;
		}
	}
	
	void getAnswer(int[] inputPermutation) {
		int[] caseArr = new int[inputPermutation.length + 1];
		for(int i = 0; i < inputPermutation.length; i++) {
			caseArr[i] = inputPermutation[i];
		}
		
		int previousNodeNumber = 0;
		int distanceSum = 0;
		for(int i = 0; i < caseArr.length; i++) {
			if(i == caseArr.length - 1) {
				distanceSum += distance[0][caseArr[i - 1] - 1];
				caseArr[i] = distanceSum;
	
				if(answerArr[nodeNumber] < caseArr[i] && caseArr[i] <= limitTime) {
					answerArr = caseArr;
				} else {
					continue;
				}
			} else {
				if(i > 0) {
					distanceSum += distance[previousNodeNumber - 1][caseArr[i] - 1];
				} 
				
				if(distanceSum > limitTime) {
					break;
				}
				previousNodeNumber = caseArr[i];
				caseArr[i] = caseArr[i];
			}
		}
	}
}


class House {
	private int x;
	private int y;
	private int houseName;
	
	House(int inputName, int inputX, int inputY) {
		houseName = inputName;
		x = inputX;
		y = inputY;
	}
	
	int getHouseName() {
		return houseName;
	}
	
	int getX() {
		return x;
	}
	
	int getY() {
		return y;
	}
	
	int getDistanceFrom(House destination) {
		int distance = 0;
		distance = Math.abs(x - destination.getX()) + Math.abs(y - destination.getY());
		
		return distance;
	}
}

class Permutation {
	private int n;
	private int[] permArray;

	Permutation(int num) {
		n = num;
		permArray = new int[n];
		assign();
	}
	
	void assign() {
		int i;
		for (i = 0; i < n; ++i) {
			permArray[i] = i + 1;
		}
	}

	boolean next() {
		int k, j, r, s;
		k = n - 2;
		
		while (permArray[k] > permArray[k + 1]) {
			if (k == 0)
				return false;
			k--;
		}

		j = n - 1;

		while (permArray[k] > permArray[j]) 
			j--;
		swap(j, k);

		r = n - 1;
		s = k + 1;

		while (r > s)
			swap(r--, s++);
		return true;
	}
	
	int[] getPermutation() {
		int[] copiedArray = permArray;
		return copiedArray;
	}

	
	private void swap(int i, int j) {
		int temp = permArray[i];
		permArray[i] = permArray[j];
		permArray[j] = temp;
	}
};
