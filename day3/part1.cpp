#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <chrono>

int main() {
	
	//start timer
	auto start = std::chrono::high_resolution_clock::now();

	std::ifstream infile("./input.txt");

	if (!infile) {
		std::cout << "Error: text filename \"input.txt\" --> No such file or directory.\n";
		return EXIT_FAILURE;
	}
	
	//plan is to read in each line and add the first half of chars to a multiset.
	//then check if any of the remaining chars are in that set using c++20 contains. If so, add that chars priority to the total.
	
	std::unordered_multiset<char> charSet;
	std::string line;
	size_t total = 0;

	//map with chacters a-z and their priority 1-26 then the characters A-Z and their priority 27-52
	std::map<char, size_t> charPriority;
	for (size_t i = 0; i < 26; ++i) {
		charPriority['a' + i] = i + 1;
		charPriority['A' + i] = i + 27;
	}
	
	while (std::getline(infile, line)) {
		for (size_t i = 0; i < line.size() / 2; ++i) {
			charSet.insert(line[i]);
		}
		for (size_t i = line.size() / 2; i < line.size(); ++i) {
			if (charSet.contains(line[i])) {
				total += charPriority[line[i]];
				break;
			}
		}
		charSet.clear();
	}
	
	std::cout << "Sum of priorities of all items that need to be rearranged was: " << total << std::endl;
	return EXIT_SUCCESS;
}
