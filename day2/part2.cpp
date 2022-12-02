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

	struct Choices { // each choice knows what it wins against and what it loses against
		char shape_;
		size_t score_;
		Choices* winsAgainst_;
		Choices* losesAgainst_;
		constexpr Choices(char shape = ' ', size_t score = 0, Choices* winningShape = nullptr, Choices* losingShape = nullptr) : shape_(shape), score_(score), winsAgainst_(winningShape), losesAgainst_(losingShape) {	}
	};
	
	Choices A('A', 1);
	Choices B('B', 2);
	Choices C('C', 3);
	
	std::unordered_map<char, Choices> rpsChoices;
	rpsChoices['A'] = Choices('A', 1, &C, &B);
	rpsChoices['B'] = Choices('B', 2, &A, &C);
	rpsChoices['C'] = Choices('C', 3, &B, &A);
	
	std::string line; 
	char elfChoice;
	char desiredOutcome;
	size_t total = 0;

	while (std::getline(infile, line)) { //each line is a hand of Rock Paper Scissors
		std::stringstream hand(std::move(line));
		hand >> elfChoice;
		hand >> desiredOutcome;

		switch (desiredOutcome) {
		case 'X':// we lose
			total += rpsChoices[elfChoice].winsAgainst_->score_; //pick whatever the elf wins against
			break;
		case 'Y':// we draw
			total += rpsChoices[elfChoice].score_ + 3; //pick whatever the elf picks
			break;
		case 'Z':// win
			total += rpsChoices[elfChoice].losesAgainst_->score_ + 6; //pick whatever the elf loses against
			break;
		}
	}
	std::cout << "your total with this strategy guide was: " << total << std::endl;
}
