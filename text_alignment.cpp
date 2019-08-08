#include <cstdlib> 
#include <string>
#include <fstream>
#include <vector>
#include <iostream> 

void writeOut(const std::vector<std::string> outputLines, char* fileOut) {
    std::ofstream out_str(fileOut);
    // Checking to make sure file was opened successfully
    if (!out_str.good()) {
    	std::cerr << "Failed to open " << fileOut << ".txt to write." << std::endl;
    	exit(1);
    }
	unsigned int o = 0;
	while (o < outputLines.size()) {
		out_str << outputLines[o] << std::endl;
		++o; 
	}
	out_str.close();	 
}

std::string singleWord(int width, const std::vector<std::string> words) {
    int wordLength = words[0].length();
    if (wordLength <= width) {
    	std::string horizontalBorder = std::string((width + 4), '-');
    	int numSpaces = width - wordLength; 
    	std::string coreLine = "| " + words[0] + std::string(numSpaces, ' ') + " |";
    	std::string textJustification = horizontalBorder + '\n' + coreLine + '\n' + horizontalBorder; 
    	return textJustification;
    }
    else {
    	std::cerr << "Word is longer than specified width." << std::endl;
    	exit(1);
    }
}

std::vector<std::string> flushLeft(unsigned int width, const std::vector<std::string> words) {
	std::string horizontalBorder = std::string((width + 4), '-');
	std::vector<std::string> leftJustification;
	leftJustification.push_back(horizontalBorder);
	std::string coreLine = "";
	unsigned int numSpaces = width;
	int i = 0;
	int vectorSize = words.size();
	while (i < vectorSize) {	
		bool lineStatus = false;
		bool ifActivate = false;
		if (words[i].length() < numSpaces) {
			coreLine += words[i] + ' ';
			numSpaces -= words[i].length() + 1;
			lineStatus = true;
			ifActivate = true;
		} 
		if (words[i].length() == numSpaces && !ifActivate) { 
			coreLine = "| " + coreLine + words[i] + " |";
			leftJustification.push_back(coreLine);
			numSpaces = width;
			coreLine = "";
			lineStatus = true;
		} 
		if (!lineStatus) {
 			coreLine = "| " + coreLine + std::string(numSpaces, ' ') + " |";
			leftJustification.push_back(coreLine);
			numSpaces = width;
			coreLine = "";
			coreLine += words[i] + ' ';
			numSpaces -= words[i].length() + 1;
		}
		++i;
	}
	// Adds final line and bottom border to vector 
	coreLine = "| " + coreLine + std::string(numSpaces, ' ') + " |";
	leftJustification.push_back(coreLine); 
	leftJustification.push_back(horizontalBorder);
	return leftJustification;	 
}

std::vector<std::string> flushRight(int width, const std::vector<std::string> words) {
	std::string horizontalBorder = std::string((width + 4), '-');
	std::vector<std::string> rightJustification;
	rightJustification.push_back(horizontalBorder);
	std::string coreLine = "";
	unsigned int numSpaces = width;
	int i = 0;
	int vectorSize = words.size();
	while (i < vectorSize) {
		bool lineStatus = false;
		bool ifActivate = false;
		if (words[i].length() < numSpaces) {
			coreLine += words[i] + ' ';
			numSpaces -= words[i].length() + 1;
			lineStatus = true; 
			ifActivate = true;
		}
		if (words[i].length() == numSpaces && !ifActivate) {
			coreLine = "| " + coreLine + words[i] + " |";
			rightJustification.push_back(coreLine);
			coreLine = "";
			numSpaces = width;
			lineStatus = true;
		}
		if (!lineStatus) {
			if (coreLine[coreLine.length()-1] == ' ') {
				coreLine = coreLine.erase(coreLine.length()-1, 1); // Erases an extra space if the words is at the end
			}
 			coreLine = "| " + std::string(numSpaces + 1, ' ') + coreLine + " |";
			rightJustification.push_back(coreLine);
			numSpaces = width;
			coreLine = "";
			coreLine += words[i] + ' ';
			numSpaces -= words[i].length() + 1;
		}
		++i;
	}	
	// Adds final line and bottom border to vector
	coreLine = "| " + std::string(numSpaces+1, ' ') + coreLine + "|";
	rightJustification.push_back(coreLine);
	rightJustification.push_back(horizontalBorder);
	return rightJustification;
}

std::vector<std::string> fullJustify(int width, const std::vector<std::string> words) { 
	std::string horizontalBorder = std::string((width + 4), '-');
	std::vector<std::string> fullJustification;
	fullJustification.push_back(horizontalBorder);
	std::vector<std::string> storedWords;
	std::string coreLine = "";
	unsigned int numSpaces = width;
	int i = 0;
	int vectorSize = words.size();
	while (i < vectorSize) {
		bool lineStatus = false;
		// Adds words, which are short enough, to a vector and keeps track of available spaces
		if (words[i].length() < (numSpaces - (storedWords.size() - 1))) {
			storedWords.push_back(words[i]);
			numSpaces -= words[i].length();
			lineStatus = true;
		} 
		if (words[i].length() >= width) { 
			// Left justifies a line containing a single word
			if (storedWords.size() == 1) { 
				coreLine = "| " + storedWords[0] + std::string(numSpaces, ' ') + " |";
				fullJustification.push_back(coreLine);
				storedWords.clear();
				numSpaces = width;
				coreLine = "";
			} // Creates a line with proper spacing which separates the words
			if (storedWords.size() > 1) {
				int spacing = numSpaces / (storedWords.size() - 1);
				int extraSpaces = numSpaces % (storedWords.size() - 1);
				std::string space;
				extraSpaces > 0 ? space = " " : space = "";
				for (int x = 0; x < (storedWords.size() - 1); ++x) {
					coreLine += storedWords[x] + std::string(spacing, ' ') + space;
					--extraSpaces;
					if (extraSpaces <= 0) {
						space = "";
					}
				}
				coreLine = "| " + coreLine + storedWords[storedWords.size()-1] + " |";
				fullJustification.push_back(coreLine);
				coreLine = "";
				numSpaces = width;
				storedWords.clear();
				
			} // Creates a line contaning a single word with same length as width
			if (words[i].length() == width) {
				coreLine = "| " + words[i] + " |";
				fullJustification.push_back(coreLine);
			} 
			int wordLength = words[i].length();
			int j = 0;
			std::string line;
			if (words[i].length() > width) {
				while (j < wordLength) { // Takes care of the remaining bits of the long word without hyphen
					if (words[i].substr(j, width).length() != width) {
						std::string line = words[i].substr(j, (words[i].length() - j));
						numSpaces = width - (line.length());
						storedWords.push_back(line);
					} // Splits the word by iterating at intervals and adds a hyphen
					std::string str1 = words[i].substr(j, (width-1)) + '-';
					std::string line = "| " + str1 + " |";
					if (str1.length() == width) {
						fullJustification.push_back(line);
					}
					j += width-1;
				}
			}
			lineStatus = true;
		}
		if (!lineStatus) { // If word length is less than width but more than amount of available spaces
			if (storedWords.size() == 1) { // Deals with word leftover in vector
				coreLine = "| " + storedWords[0] + std::string(numSpaces, ' ') + " |";
				fullJustification.push_back(coreLine);
				coreLine = "";
				storedWords.clear();
				storedWords.push_back(words[i]);
				numSpaces = width;
				numSpaces -= words[i].length();
			}
			if (storedWords.size() > 1) { // Deals with multiple words leftover by spacing them correctly
				int spacing = numSpaces / (storedWords.size() - 1);
				int extraSpaces = numSpaces % (storedWords.size() - 1);
				std::string space;
				extraSpaces > 0 ? space = " " : space = "";
				for (int x = 0; x < (storedWords.size() - 1); ++x) {
					coreLine += storedWords[x] + std::string(spacing, ' ') + space; 
					--extraSpaces;
					if (extraSpaces <= 0) {
						space = "";
					}
				} // Variables are recycled 
				coreLine = "| " + coreLine + storedWords[storedWords.size()-1] + " |";
				fullJustification.push_back(coreLine);
				coreLine = "";
				storedWords.clear();
				storedWords.push_back(words[i]);
				numSpaces = width;
				numSpaces -= words[i].length();				
			}
		}	
	++i;
	} // Adds final line and bottom border to vector 
	for (int y = 0; y < storedWords.size(); ++y) {
		coreLine += storedWords[y] + ' ';
	}
	numSpaces -= (storedWords.size());
	coreLine = "| " + coreLine + std::string(numSpaces, ' ') + " |";
	fullJustification.push_back(coreLine);
	fullJustification.push_back(horizontalBorder);
	return fullJustification;
} 

//-----------------------------------------------------------------------------------------//

int main(int argc, char* argv[]) {
    // Opening input file to read
    std::ifstream in_str(argv[1]);
    if (!in_str.good()) { 
    	std::cerr << "Failed to open " << argv[1] << ".txt to read." << std::endl;
    	exit(1);
    }  
    std::vector<std::string> wordsList;
    std::string words;
   	while (in_str >> words) {
       	wordsList.push_back(words);
   	}   
    // Coverting string containing width to an integer 
    std::string widthStr = argv[3];
    int width = atoi(widthStr.c_str());
    // Retrieving type of text justificaton from command line
    std::string justificationType = argv[4]; 
	// If the input text does not contain a single word 
	if (wordsList.size() == 0) {
		std::cerr << "No words to utilize for text justification." << std::endl; 
		exit(1);  
	} // If the input text only contains a single word
	if (wordsList.size() == 1) {
		std::cout << singleWord(width, wordsList) << std::endl;
	}  
    if (justificationType == "flush_left") {
    	std::vector<std::string> leftJustified = flushLeft(width, wordsList);
    	writeOut(leftJustified, argv[2]);
    }
    if (justificationType == "flush_right") {
    	std::vector<std::string> rightJustified = flushRight(width, wordsList);
    	writeOut(rightJustified, argv[2]);
    }    
    if (justificationType == "full_justify") {
    	std::vector<std::string> fullJustified = fullJustify(width, wordsList);
    	for (int x = 0; x < fullJustified.size(); ++x) {
    		std::cout << fullJustified[x] << std::endl;
    	}
    	writeOut(fullJustified, argv[2]);
    } // If an incorrect justification type is entered 
    return 0;
}
