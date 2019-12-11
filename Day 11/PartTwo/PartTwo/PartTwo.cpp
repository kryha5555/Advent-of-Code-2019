#include <iostream>
#include <vector>
#include <fstream>
#define GRIDX 43
#define GRIDY 6
#define POSX 0
#define POSY 0

int main()
{
	std::vector<double> input = { 3,8,1005,8,318,1106,0,11,0,0,0,104,1,104,0,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,1,10,4,10,101,0,8,29,1,107,12,10,2,1003,8,10,3,8,102,-1,8,10,1001,10,1,10,4,10,1008,8,0,10,4,10,1002,8,1,59,1,108,18,10,2,6,7,10,2,1006,3,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,1008,8,1,10,4,10,1002,8,1,93,1,1102,11,10,3,8,102,-1,8,10,1001,10,1,10,4,10,108,1,8,10,4,10,101,0,8,118,2,1102,10,10,3,8,102,-1,8,10,101,1,10,10,4,10,1008,8,0,10,4,10,101,0,8,145,1006,0,17,1006,0,67,3,8,1002,8,-1,10,101,1,10,10,4,10,1008,8,0,10,4,10,101,0,8,173,2,1109,4,10,1006,0,20,3,8,102,-1,8,10,1001,10,1,10,4,10,108,0,8,10,4,10,102,1,8,201,3,8,1002,8,-1,10,1001,10,1,10,4,10,1008,8,0,10,4,10,1002,8,1,224,1006,0,6,1,1008,17,10,2,101,5,10,3,8,1002,8,-1,10,1001,10,1,10,4,10,108,1,8,10,4,10,1001,8,0,256,2,1107,7,10,1,2,4,10,2,2,12,10,1006,0,82,3,8,1002,8,-1,10,1001,10,1,10,4,10,1008,8,1,10,4,10,1002,8,1,294,2,1107,2,10,101,1,9,9,1007,9,988,10,1005,10,15,99,109,640,104,0,104,1,21102,1,837548352256,1,21102,335,1,0,1105,1,439,21102,1,47677543180,1,21102,346,1,0,1106,0,439,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,3,10,104,0,104,1,3,10,104,0,104,0,3,10,104,0,104,1,21102,1,235190374592,1,21101,393,0,0,1105,1,439,21102,3451060455,1,1,21102,404,1,0,1105,1,439,3,10,104,0,104,0,3,10,104,0,104,0,21102,837896909668,1,1,21102,1,427,0,1105,1,439,21102,1,709580555020,1,21102,438,1,0,1105,1,439,99,109,2,21201,-1,0,1,21102,1,40,2,21102,1,470,3,21102,460,1,0,1106,0,503,109,-2,2105,1,0,0,1,0,0,1,109,2,3,10,204,-1,1001,465,466,481,4,0,1001,465,1,465,108,4,465,10,1006,10,497,1101,0,0,465,109,-2,2105,1,0,0,109,4,1201,-1,0,502,1207,-3,0,10,1006,10,520,21101,0,0,-3,21202,-3,1,1,22101,0,-2,2,21101,1,0,3,21101,0,539,0,1106,0,544,109,-4,2105,1,0,109,5,1207,-3,1,10,1006,10,567,2207,-4,-2,10,1006,10,567,21202,-4,1,-4,1105,1,635,22101,0,-4,1,21201,-3,-1,2,21202,-2,2,3,21101,0,586,0,1105,1,544,22102,1,1,-4,21102,1,1,-1,2207,-4,-2,10,1006,10,605,21102,1,0,-1,22202,-2,-1,-2,2107,0,-3,10,1006,10,627,21202,-1,1,1,21101,627,0,0,105,1,502,21202,-2,-1,-2,22201,-4,-2,-4,109,-5,2105,1,0 };
	input.insert(input.end(), 470, 0);
	std::vector<double> output = {};

	bool grid[GRIDX][GRIDY] = {};
	bool mask[GRIDX][GRIDY] = {};
	int posX = POSX;
	int posY = POSY;
	enum direction { UP, RIGHT, DOWN, LEFT };
	int dir = UP;
	grid[posX][posY] = 1;

	int step = 0;
	int relativeBase = 0;
	int i = 0;

	while (true)
	{
		int opCode = fmod(input[i], 100);
		if (opCode == 99)
			break;

		int mode_1 = fmod(floor(input[i] / 100), 10);
		int mode_2 = fmod(floor(input[i] / 1000), 10);
		int mode_3 = fmod(floor(input[i] / 10000), 10);

		switch (opCode)
		{
		case 1:
			input[mode_3 == 1 ? i + 3 : (mode_3 == 2 ? relativeBase + input[i + 3] : input[i + 3])] = input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] + input[mode_2 == 1 ? i + 2 : (mode_2 == 2 ? relativeBase + input[i + 2] : input[i + 2])];
			i += 4;
			break;
		case 2:
			input[mode_3 == 1 ? i + 3 : (mode_3 == 2 ? relativeBase + input[i + 3] : input[i + 3])] = input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] * input[mode_2 == 1 ? i + 2 : (mode_2 == 2 ? relativeBase + input[i + 2] : input[i + 2])];
			i += 4;
			break;
		case 3:
			input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] = grid[posX][posY];
			i += 2;
			break;
		case 4:
			output.push_back(input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])]);
			i += 2;
			step++;
			break;
		case 5:
			if (input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] != 0)
				i = input[mode_2 == 1 ? i + 2 : (mode_2 == 2 ? relativeBase + input[i + 2] : input[i + 2])];
			else
				i += 3;
			break;
		case 6:
			if (input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] == 0)
				i = input[mode_2 == 1 ? i + 2 : (mode_2 == 2 ? relativeBase + input[i + 2] : input[i + 2])];
			else
				i += 3;
			break;
		case 7:
			input[mode_3 == 1 ? i + 3 : (mode_3 == 2 ? relativeBase + input[i + 3] : input[i + 3])] = (input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] < input[mode_2 == 1 ? i + 2 : (mode_2 == 2 ? relativeBase + input[i + 2] : input[i + 2])]);
			i += 4;
			break;
		case 8:
			input[mode_3 == 1 ? i + 3 : (mode_3 == 2 ? relativeBase + input[i + 3] : input[i + 3])] = (input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])] == input[mode_2 == 1 ? i + 2 : (mode_2 == 2 ? relativeBase + input[i + 2] : input[i + 2])]);
			i += 4;
			break;
		case 9:
			relativeBase += input[mode_1 == 1 ? i + 1 : (mode_1 == 2 ? relativeBase + input[i + 1] : input[i + 1])];
			i += 2;
			break;
		}

		if (step == 2)
		{
			mask[posX][posY] = 1;
			grid[posX][posY] = output[output.size() - 2];

			output[output.size() - 1] ? dir = (dir + 1) % 4 : (!dir ? dir = 3 : dir = (dir - 1) % 4);

			switch (dir)
			{
			case UP:
				posY--;
				break;
			case RIGHT:
				posX++;
				break;
			case DOWN:
				posY++;
				break;
			case LEFT:
				posX--;
				break;

			}

			step = 0;
		}
	}

	std::fstream outputFile;
	outputFile.open("output.txt", std::fstream::out);

	for (auto i = 0; i < GRIDX; i++)
	{
		for (auto j = 0; j < GRIDY; j++)
			outputFile << grid[i][j] << ' ';
		outputFile << std::endl;
	}
}