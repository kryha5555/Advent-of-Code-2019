#include <iostream>
#include <fstream>
#include <vector>
#include <regex> 
#include <unordered_map>
#define SIZEY 65 
#define SIZEX 13

void addNeed(std::unordered_map<std::string, double> &needs, std::unordered_map<std::string, double> &haves, std::string key, double value);
void removeNeed(std::unordered_map<std::string, double> &needs, std::unordered_map<std::string, double> &haves, std::string key, double value);
void setNeed(std::unordered_map<std::string, double> &needs, std::unordered_map<std::string, double> &haves, std::string key, double value);
void printMap(std::unordered_map<std::string, double> &mymap);

int main()
{
	/* FILE INPUT AND REGEX*/

	std::ifstream inputFile;
	std::string temp, temp2;

	std::regex digit("\\d+");
	std::regex label("[A-Z]+");

	int digits[SIZEY][SIZEX] = {};
	std::string labels[SIZEY][SIZEX] = {};

	inputFile.open("../input.txt", std::fstream::in);

	int receipe = 0;
	while (std::getline(inputFile, temp))
	{
		std::smatch	digitMatch;
		std::smatch labelMatch;
		int swapInt = 0;
		std::string swapString = {};
		temp2 = temp;

		int position = 0;
		while (std::regex_search(temp, digitMatch, digit))
		{
			digits[receipe][position] = std::stoi(digitMatch[0]);
			position++;
			temp = digitMatch.suffix();
		}

		swapInt = digits[receipe][0];
		digits[receipe][0] = digits[receipe][position - 1];
		digits[receipe][position - 1] = swapInt;

		position = 0;
		while (std::regex_search(temp2, labelMatch, label))
		{
			labels[receipe][position] = labelMatch[0];
			position++;
			temp2 = labelMatch.suffix();
		}

		swapString = labels[receipe][0];
		labels[receipe][0] = labels[receipe][position - 1];
		labels[receipe][position - 1] = swapString;
		receipe++;
	}
	inputFile.close();

	/* CREATE MAPS AND ADD NEED FOR ONE FUEL */

	std::unordered_map<std::string, double> needs;
	std::unordered_map<std::string, double> haves;

	addNeed(needs, haves, "FUEL", 1);

	/* RESOLVE ALL NEEDS */

	while (!needs.empty() && !(needs.find("ORE") != needs.end() && needs.size() == 1))
	{
		std::vector<std::string> keys;
		for (auto const& element : needs)
			keys.push_back(element.first);

		std::vector<double> values;
		for (auto const& element : needs)
			values.push_back(element.second);

		int howLong = needs.size();

		for (int i = 0; i < howLong; i++)
			if (keys[i] != "ORE")
			{
				for (int rec = 0; rec < SIZEY; rec++)
					if (labels[rec][0] == keys[i])
					{
						receipe = rec;
						break;
					}

				removeNeed(needs, haves, labels[receipe][0], digits[receipe][0]);

				int positionOfNull = -1;
				for (int pos = 0; pos < SIZEX; pos++)
					if (labels[receipe][pos] == "")
					{
						positionOfNull = pos;
						break;
					}

				if (positionOfNull == -1)
					positionOfNull = SIZEX;

				std::vector<std::string> ingredientsLabels;
				for (int pos = 1; pos < positionOfNull; pos++)
					ingredientsLabels.push_back(labels[receipe][pos]);

				std::vector<double> ingredientsDigits;
				for (int pos = 1; pos < positionOfNull; pos++)
					ingredientsDigits.push_back(digits[receipe][pos]);

				for (int j = 0; j < ingredientsDigits.size(); j++)
					addNeed(needs, haves, ingredientsLabels[j], ingredientsDigits[j]);
			}
	}

	printMap(needs);
}

void addNeed(std::unordered_map<std::string, double> &needs, std::unordered_map<std::string, double> &haves, std::string key, double value)
{
	setNeed(needs, haves, key, haves[key] - needs[key] - value);
}

void removeNeed(std::unordered_map<std::string, double>& needs, std::unordered_map<std::string, double>& haves, std::string key, double value)
{
	setNeed(needs, haves, key, haves[key] - needs[key] + value);
}

void setNeed(std::unordered_map<std::string, double>& needs, std::unordered_map<std::string, double>& haves, std::string key, double value)
{
	if (value > 0)
	{
		needs.erase(key);
		haves[key] = value;
	}
	else if (value < 0)
	{
		haves.erase(key);
		needs[key] = -value;
	}
	else //if value == 0
	{
		haves.erase(key);
		needs.erase(key);
	}
}

void printMap(std::unordered_map<std::string, double>& mymap)
{
	for (auto it = mymap.begin(); it != mymap.end(); ++it)
		std::cout << it->first << " : " << it->second;
	std::cout << std::endl;
}