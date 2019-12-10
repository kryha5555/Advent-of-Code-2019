#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::cout.precision(8);
	std::vector<double> inputBase = { 3,8,1001,8,10,8,105,1,0,0,21,42,67,88,105,114,195,276,357,438,99999,3,9,101,4,9,9,102,3,9,9,1001,9,2,9,102,4,9,9,4,9,99,3,9,1001,9,4,9,102,4,9,9,101,2,9,9,1002,9,5,9,1001,9,2,9,4,9,99,3,9,1001,9,4,9,1002,9,4,9,101,2,9,9,1002,9,2,9,4,9,99,3,9,101,4,9,9,102,3,9,9,1001,9,5,9,4,9,99,3,9,102,5,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,99 };
	std::vector<double> permutation = { 0,1,2,3,4 };
	std::vector<double> output = {};

	for (int permNumber = 0; permNumber < 5 * 4 * 3 * 2; permNumber++) // to try all permutations
	{
		int tapeIndex = 0;
		std::vector<double> tape = { permutation[0], 0, permutation[1], 0, permutation[2], 0, permutation[3], 0, permutation[4],0,0,0 };

		for (int ampl = 0; ampl < 5; ampl++) // for each amplifyer
		{
			std::vector<double> input = inputBase; // reset input
			int i = 0; // index

			while (true) // loop until opcode 99
			{
				int opCode = fmod(input[i], 100);
				if (opCode == 99)
					break;

				bool mode_1 = fmod(floor(input[i] / 100), 10);
				bool mode_2 = fmod(floor(input[i] / 1000), 10);
				bool mode_3 = fmod(floor(input[i] / 10000), 10);

				switch (opCode)
				{
				case 1:
					input[input[i + 3]] = input[mode_1 ? i + 1 : input[i + 1]] + input[mode_2 ? i + 2 : input[i + 2]];
					i += 4;
					break;
				case 2:
					input[input[i + 3]] = input[mode_1 ? i + 1 : input[i + 1]] * input[mode_2 ? i + 2 : input[i + 2]];
					i += 4;
					break;
				case 3:
					input[input[i + 1]] = tape[tapeIndex]; // input from tape
					tapeIndex++; // move tape pointer
					i += 2;
					break;
				case 4:
					tape[tapeIndex + 1] = input[input[i + 1]]; // output to tape in right place
					i += 2;
					break;
				case 5:
					if (input[mode_1 ? i + 1 : input[i + 1]] != 0)
						i = input[mode_2 ? i + 2 : input[i + 2]];
					else
						i += 3;
					break;
				case 6:
					if (input[mode_1 ? i + 1 : input[i + 1]] == 0)
						i = input[mode_2 ? i + 2 : input[i + 2]];
					else
						i += 3;
					break;
				case 7:
					input[input[i + 3]] = (input[mode_1 ? i + 1 : input[i + 1]] < input[mode_2 ? i + 2 : input[i + 2]]);
					i += 4;
					break;
				case 8:
					input[input[i + 3]] = (input[mode_1 ? i + 1 : input[i + 1]] == input[mode_2 ? i + 2 : input[i + 2]]);
					i += 4;
					break;
				}
			}
		}

		output.push_back(tape[11]); // push output of 4th amp to output vector
		std::next_permutation(permutation.begin(), permutation.end());
	}

	std::cout << "MAX - > " << *std::max_element(std::begin(output), std::end(output)); // max of output vector
}