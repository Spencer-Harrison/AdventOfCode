#include <fstream>
#include <iostream>
#include <string>
#include <set>


int main() {
	
	std::ifstream infile("./input.txt");

	if (!infile) {
		std::cout << "Error: text filename \"input.txt\" --> No such file or directory.\n";
		infile.close();
		return EXIT_FAILURE;	
	}

	//alternate idea fill up a set with each elf's total calories. Then print off the final 3 values. 
	std::multiset<size_t> elfCalorieList;

	std::string line;
	size_t calories = 0;
	size_t lineCount = 0;
	while (std::getline(infile, line)) {
		try {
			if (line.compare("") == 0) {
				elfCalorieList.insert(calories);
				calories = 0;
			}
			else {
				calories += std::stoi(line);
			}
		}
		catch (std::invalid_argument e) {
			std::cout << "Not an int at line : " << lineCount << std::endl;
		}
		++lineCount;
	}
	std::cout << "Elf number " << elfCalorieList.size() << " has the most calories with: " << *elfCalorieList.rbegin() << std::endl;
	//second highest elf
	std::cout << "Elf number " << elfCalorieList.size() - 1 << " has the second most calories with: " << *std::next(elfCalorieList.rbegin()) << std::endl;
	//third highest elf
	std::cout << "Elf number " << elfCalorieList.size() - 2 << " has the third most calories with: " << *std::next(elfCalorieList.rbegin(), 2) << std::endl;
	
	
	size_t total = *elfCalorieList.rbegin() + *std::next(elfCalorieList.rbegin()) + *std::next(elfCalorieList.rbegin(), 2);
	std::cout << "Total calories of top 3: " << total << std::endl;
	
	infile.close();
	return EXIT_SUCCESS;
}
