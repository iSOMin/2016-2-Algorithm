
inputFile = open("board.inp", "r")
outputFile = open("board.out", "w")

board = []
result = []
temp = []

for x in range(3):
	board.append(map(int, inputFile.readline().split()))


print board

result = [[[0 for x in range(board[2][0] + 1)] for y in range(board[1][0] + 1)] for z in range(board[0][0] + 1)]

for x in range(1, board[0][0] + 1):
	for y in range(1, board[1][0] + 1):
		for z in range(1, board[2][0] + 1):
			result[x][y][z] = max(result[x - 1][y][z], max(result[x][y - 1][z], max(result[x][y][z - 1], result[x - 1][y - 1][z - 1] + board[0][x] * board[1][y] * board[2][z])))


print >> outputFile, result[x][y][z]


inputFile.close()
outputFile.close()