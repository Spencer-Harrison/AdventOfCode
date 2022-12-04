#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <chrono>

int main() {
	std::ifstream infile("./input.txt");

	if (!infile) {
		std::cout << "Error: text filename \"input.txt\" --> No such file or directory.\n";
		return EXIT_FAILURE;
	}
	
	//plan this time is to read first two elves into the multisets. 
	//Then we will check which item the third elf has that is in both multisets.
	
	std::unordered_multiset<char> elfOne;
	std::unordered_multiset<char> elfTwo;
	std::string line;
	size_t total = 0;

	//map with chacters a-z and their priority 1-26 then the characters A-Z and their priority 27-52
	std::map<char, size_t> charPriority;
	for (size_t i = 0; i < 26; ++i) {
		charPriority['a' + i] = i + 1;
		charPriority['A' + i] = i + 27;
	}
	
	size_t lineCount = 0;
	while (std::getline(infile, line)) {
		switch (lineCount) {
		case 0:
			for (size_t i = 0; i < line.size(); ++i) {
				elfOne.insert(line[i]);
			}
			break;
		case 1:
			for (size_t i = 0; i < line.size(); ++i) {
				elfTwo.insert(line[i]);
			}
			break;
		case 2:
			for (size_t i = 0; i < line.size(); ++i) {
				if (elfOne.contains(line[i]) && elfTwo.contains(line[i])) {
					total += charPriority[line[i]];
					break;
				}
			}
			break;
		}
		++lineCount;
		if (lineCount == 3) {
			lineCount = 0;
			elfOne.clear();
			elfTwo.clear();
		}
	}
	
	std::cout << "Sum of priorities of all items that need to be rearranged was: " << total << std::endl;
	return EXIT_SUCCESS;
}
