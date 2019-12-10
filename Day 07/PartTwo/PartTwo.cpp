#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
	std::cout.precision(13);
	std::vector<double> inputBase = { 3,8,1001,8,10,8,105,1,0,0,21,42,67,88,105,114,195,276,357,438,99999,3,9,101,4,9,9,102,3,9,9,1001,9,2,9,102,4,9,9,4,9,99,3,9,1001,9,4,9,102,4,9,9,101,2,9,9,1002,9,5,9,1001,9,2,9,4,9,99,3,9,1001,9,4,9,1002,9,4,9,101,2,9,9,1002,9,2,9,4,9,99,3,9,101,4,9,9,102,3,9,9,1001,9,5,9,4,9,99,3,9,102,5,9,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,1,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,99,3,9,102,2,9,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,101,2,9,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,2,9,4,9,3,9,1001,9,1,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,102,2,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,2,9,4,9,99,3,9,1002,9,2,9,4,9,3,9,101,1,9,9,4,9,3,9,1002,9,2,9,4,9,3,9,102,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,3,9,1001,9,1,9,4,9,3,9,101,2,9,9,4,9,3,9,1001,9,1,9,4,9,3,9,1002,9,2,9,4,9,99 };
	std::vector<double> permutation = { 5,6,7,8,9 };
	std::vector<double> finalOutput = {};

	for (int permNumber = 0; permNumber < 5 * 4 * 3 * 2; permNumber++) // to try all permutations
	{
		std::vector<double> memory[] = { inputBase, inputBase, inputBase, inputBase, inputBase }; // load default input into all amps
		int pointers[5] = { 0,0,0,0,0 }; // set pointers to 0 for all amps
		int tapeIndex = 0;
		std::vector<double> tape = { permutation[0], 0, permutation[1], 0, permutation[2], 0, permutation[3], 0, permutation[4],0,0,0 };
		bool finished = 0; // flag for breaking loop
		bool isFirstIteration = 0;
		std::vector<double> outputAmpl = { 0,0,0,0,0 }; // outputs of amps
		std::vector<double> output = {};

		while (!finished) // until opcode 99 occurs
		{
			for (int ampl = 0; ampl < 5; ampl++) // for each amplifyer
			{
				std::vector<double> input = memory[ampl]; // set input
				int i = pointers[ampl]; // set index
				bool amplPrinted = 0; // flag for breaking loop

				while (true)
				{
					if (amplPrinted) // if opcode 4 occured
					{
						memory[ampl] = input; // save input
						pointers[ampl] = i; // save index
						break;
					}

					int opCode = fmod(input[i], 100);
					if (opCode == 99)
					{
						finished = 1;
						break;
					}

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
						if (!isFirstIteration)
						{
							input[input[i + 1]] = tape[tapeIndex]; // input from tape
							tapeIndex++;
						}
						else
							input[input[i + 1]] = outputAmpl[(!ampl ? 4 : (ampl - 1) % 5)]; // input for previous amp
						i += 2;
						break;
					case 4:
						amplPrinted = 1; // set print flag
						outputAmpl[ampl] = input[input[i + 1]]; //save to amp output table
						if (ampl == 4) // if last amp in loop
						{
							output.push_back(input[input[i + 1]]); // push to temp output vector
							isFirstIteration = 1; // set iteration flag
						}
						if (!isFirstIteration)
							tape[tapeIndex + 1] = input[input[i + 1]]; //save to tape
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
		}

		finalOutput.push_back((output.back()));
		std::next_permutation(permutation.begin(), permutation.end()); // push output of amp loop to output vector
	}

	std::cout << "MAX - > " << *std::max_element(std::begin(finalOutput), std::end(finalOutput)); // max of output vector
}