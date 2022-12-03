#include <iostream>
#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

int main() {
	
	std::ifstream infile("./input.txt");

	if (!infile) {
		std::cout << "Error: text filename \"input.txt\" --> No such file or directory.\n";
		return EXIT_FAILURE;
	}

	struct Choices {
		char shape_;
		size_t score_;
		char winsAgainst_;
		char losesAgainst_;
		constexpr Choices(char shape = ' ', size_t score = 0, char winningShape = ' ', char losingShape = ' ') : shape_(shape), score_(score), winsAgainst_(winningShape), losesAgainst_(losingShape) {	}
	};

	std::unordered_map<char, Choices> rpsChoices;
	rpsChoices['X'] = Choices('X', 1, 'C', 'B');
	rpsChoices['Y'] = Choices('Y', 2, 'A', 'C');
	rpsChoices['Z'] = Choices('Z', 3, 'B', 'A');


	std::string line; 
	char elfChoice;
	char myChoice;
	size_t total = 0;
	while (std::getline(infile, line)) { //each line is a hand of RPS
		std::stringstream hand(std::move(line));
		hand >> elfChoice;
		hand >> myChoice;

		char winingChoice = rpsChoices.at(myChoice).winsAgainst_;
		char losingChoice = rpsChoices.at(myChoice).losesAgainst_;
		size_t shapeScore = rpsChoices.at(myChoice).score_;

		if (winingChoice == elfChoice) {
			total += shapeScore + 6;
		}
		else if (losingChoice == elfChoice) {
			total += shapeScore + 0;
		}
		else {
			total += shapeScore + 3;
		}
	}
	std::cout << "your total with this strategy guide was: " << total << std::endl;
	return EXIT_SUCCESS;
}
