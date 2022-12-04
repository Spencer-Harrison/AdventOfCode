#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <unordered_set>
#include <chrono>
#include <sstream>

int main() {

	//start timer
	auto startTimer = std::chrono::high_resolution_clock::now();

	std::ifstream infile("./input.txt");

	if (!infile) {
		std::cout << "Error: text filename \"input.txt\" --> No such file or directory.\n";
		return EXIT_FAILURE;
	}

	//going to read in comma separated ranges in the format of 1-3,2-9\n3-6,4-5\n etc.
	//Each comma separated pair will be read as a string. 
	// We will then convert the start and end of each range and subtract the end from the start to get the length of the range.
	// then compare two two ranges per line to find the larger range
	// then check if the smaller range is within the larger range.
	
	std::string line;
	std::string start;
	std::string end;
	int startInt1 = 0;
	int endInt1 = 0;
	int startInt2 = 0;
	int endInt2= 0;
	int length1 = 0;
	int length2 = 0;
	size_t rangeCount = 0;
	size_t rangePairCount = 0;
	while (getline(infile, line)) {
		std::stringstream ss(line);
		//split string by comma
		std::string range;
		while (getline(ss, range, ',')) {

			//split string by dash
			std::stringstream ss2(range);
			switch (rangeCount) {
			case 0:
				getline(ss2, start, '-');
				getline(ss2, end, '-');
				//convert start and end to ints
				startInt1 = std::stoi(start);
				endInt1 = std::stoi(end);
				length1 = endInt1 - startInt1;
				break;
			case 1:
				getline(ss2, start, '-');
				getline(ss2, end, '-');
				//convert start and end to ints
				startInt2 = std::stoi(start);
				endInt2 = std::stoi(end);
				length2 = endInt2 - startInt2;//subtract end from start to get length of range
				break;
			};
			++rangeCount;
			if (rangeCount == 2)
				rangeCount = 0;
		}
		//compare two ranges per line to find the larger range
		if (length1 >= length2 && (startInt1 <= startInt2 && endInt1 >= endInt2)) {//then check if the smaller range is within the larger range.
			++rangePairCount;
		}
		else if (length2 >= length1 && (startInt2 <= startInt1 && endInt2 >= endInt1)) {//then check if the smaller range is within the larger range.
			++rangePairCount;
		}
	}
	
	std::cout << "Number of pairs of elves whose sections completely overlap" << rangePairCount << std::endl;
		
	//print timer
	auto endTimer = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTimer - startTimer);
	std::cout << "Time taken: " << duration.count() << " milliseconds\n";
}
