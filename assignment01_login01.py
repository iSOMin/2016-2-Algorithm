inputFile = open("login.inp", "r")
outputFile = open("login.out", "w")

matrixSize = inputFile.readline().split()
userInfoMatrix = []


for x in range(int(matrixSize[0])):
	userInfoMatrix.append(inputFile.readline().split())

questionNumber = int(inputFile.readline())

for x in range(questionNumber):

	i, j, p, q = inputFile.readline().split()
	userNumberOfTargetRange = 0
	
	for timeRange in range(int(q)-int(p)+1):
		for dayRange in range(int(j)-int(i)+1):
			userNumberOfTargetRange += int(userInfoMatrix[int(p)+timeRange-1][int(i)+dayRange-1])

	print >> outputFile, userNumberOfTargetRange


inputFile.close()
outputFile.close()
