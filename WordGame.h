/*

This class is a dictionary with games

*/

#pragma once

#include "EngVieDict.h"
class WordGame: public EngVieDict {
private:
	//                                          -------------- HIDING WORDS GAME ---------------
	
	//
	// read the list of words
	// return a pointer which has DynamicArray<Vocab*>* type
	// return null if the list is empty
	DynamicArray<Vocab*>* preparePractice(std::string fileName) {
		DynamicArray<Vocab*>* practiceWords = getPracticeWords("PracticeWords.txt");
		if (practiceWords->getSize() == 0) {
			delete practiceWords;
			return nullptr;
		}
		return practiceWords;
	}

	// dir (directions):
	// 1: left to right
	// 2: top to bottom
	// 3: top-left to bottom-right
	struct BoardGameAnswer {
		int row, col, dir;
		std::string word;
		BoardGameAnswer() {
			row = col = dir = 0;
		}
		BoardGameAnswer(int row, int col, int dir, std::string word) {
			this->row = row;
			this->col = col;
			this->dir = dir;
			this->word = word;
		}

		bool equals(BoardGameAnswer other) {
			if (row == other.row && col == other.col && dir == other.dir && (word.compare(other.word) == 0)) {
				return true;
			}
			return false;
		}

		bool onlyCompareWord(BoardGameAnswer other) {
			if (word.compare(other.word) == 0) return true;
			return false;
		}

	};

	// BECAREFUL, only take in valid arguments
	bool belongAnswerArea(BoardGameAnswer answer, int row, int col) {
		switch (answer.dir) {
		case 1:
			// left to right
			if (row != answer.row || !(col >= answer.col && col < answer.col + answer.word.length())) return false;
			break;
		case 2:
			// top to bottom
			if (col != answer.col || !(row >= answer.row && row < answer.row + answer.word.length())) return false;
			break;
		case 3:
			// top-left to bottom-right
			int i = answer.row;
			int j = answer.col;
			int l = answer.word.length();
			while (i < answer.row + l && j < answer.col + l) {
				if (i == row && j == col) return true;
				i++;
				j++;
			}
			return false;
		}
		return true;
	}

	// visual effects (print colors for words in ans array)
	void printBoard(char** board, int n, DynamicArray<BoardGameAnswer>* ans) {
		if (ans->getSize() == 0) {
			printBoard(board, n);
			return;
		}
		std::cout << "\t";
		for (int i = 0; i < n; i++) std::cout << i << "  ";
		std::cout << "\n\n\n";
		for (int i = 0; i < n; i++) {
			std::cout << i << "\t";
			for (int j = 0; j < n; j++) {
				bool havePrinted = false;
				for (int k = 0; k < ans->getSize(); k++) {
					if (belongAnswerArea(ans->getAt(k), i, j)) {
						std::string redText = "\x1b[91m";
						std::string greenText = "\x1b[92m";
						std::string defaultText = "\x1b[0m";
						if (i == ans->getAt(k).row && j == ans->getAt(k).col)
							std::cout << redText << board[i][j] << defaultText << "  ";
						else
							std::cout << greenText << board[i][j] << defaultText << "  ";

						havePrinted = true;
						break;
					}
				}
				if (!havePrinted) std::cout << board[i][j] << "  ";
			}
			std::cout << "\n\n";
		}
	}

	// white-black colors
	void printBoard(char** board, int n) {
		std::cout << "\t";
		for (int i = 0; i < n; i++) std::cout << i << "  ";
		std::cout << "\n\n\n";

		for (int i = 0; i < n; i++) {
			std::cout << i << "\t";
			for (int j = 0; j < n; j++) {
				std::cout << board[i][j] << "  ";
			}
			std::cout << "\n\n";
		}
	}

	// dir (directions):
	// 1: left to right
	// 2: top to bottom
	// 3: left-top to right-bottom
	// WARING: Input must be valid
	bool canPlaceWord(char** board, int n, int row, int col, int direction, std::string word) {
		if (row + word.length() >= n || col + word.length() >= n) return false;
		int i = row;
		int j = col;
		for (char letter : word) {
			// if the position hasn't been placed or has been placed but has the same letter 
			if (board[i][j] == '0' || board[i][j] == letter) {
				switch (direction) {
				case 1: j++; break;
				case 2: i++; break;
				case 3: i++; j++; break;
				}
			}
			else return false;
		}
		return true;

	}

	// WARING: Inputs must be VALID and CAN be placed in the board
	void placeWord(char** board, int n, int row, int col, int direction, std::string word) {
		int i = row;
		int j = col;
		for (char letter : word) {
			board[i][j] = letter - ' ';
			switch (direction) {
			case 1: j++; break;
			case 2: i++; break;
			case 3: i++; j++; break;
			}
		}
	}

	// WARING: Inputs must be VALID
	void putMissingLettersForTheBoard(char** board, int n) {
		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis('A', 'Z');
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (board[i][j] == '0') {
					board[i][j] = dis(ge);
				}
			}
		}
	}

	// WARNING: Might not work if n is too big or is allocated falsely
	// return a 2D-Array
	// n must suffice
	char** initialBoard(int n, char defValue = '0') {
		char** board = new char* [n];
		for (int i = 0; i < n; i++) board[i] = new char[n];

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				board[i][j] = defValue;
			}
		}

		return board;
	}

	void clearBoard(char** board, int n) {
		for (int i = 0; i < n; i++) delete[] board[i];
		delete[] board;
	}

	// return a 2D-Array, each cell of this array contains a letter
	// some rows, columns, or diagonals is arranged with meaning of words (is parameter) list
	// answers is will be allocated, its contents depend on words (is parameter) contents
	char** createWordLetterBoard(int n, DynamicArray<std::string>* words, DynamicArray<BoardGameAnswer>*& answers) {
		char** board = initialBoard(n, '0');
		answers = new DynamicArray<BoardGameAnswer>();

		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, n - 1);
		std::uniform_int_distribution<int> dis2(1, 3);

		for (int i = 0; i < words->getSize(); i++) {
			std::string word = words->getAt(i);
			int row = dis(ge);
			int col = dis(ge);
			int dir = dis2(ge);

			// warning, haven't fixed yet
			// can be an infinite loop if there's no available spot to place
			while (!canPlaceWord(board, n, row, col, dir, word)) {
				row = dis(ge);
				col = dis(ge);
				dir = dis2(ge);
			}

			placeWord(board, n, row, col, dir, word);
			answers->add(BoardGameAnswer(row, col, dir, word));
		}

		putMissingLettersForTheBoard(board, n);

		return board;
	}

	// only compare word-field
	int haveAnswerIn(DynamicArray<BoardGameAnswer>* answers, BoardGameAnswer aAnswer) {
		for (int i = 0; i < answers->getSize(); i++) {
			if (answers->getAt(i).onlyCompareWord(aAnswer)) return i;
		}
		return -1;
	}

	// play with board game nxn size and answers of the game
	void getStartedHidingWordGame(char** board, int n, DynamicArray<BoardGameAnswer>* answers) {
		DynamicArray<BoardGameAnswer>* userCorrectedAnswers = new DynamicArray<BoardGameAnswer>(0);

		while (userCorrectedAnswers->getSize() < answers->getSize()) {
			system("cls");
			printBoard(board, n, userCorrectedAnswers);
			ConsoleEffect::foregroundBlueB("- - - - - - - - - - - - - - - - - - - - - - -\n");
			std::cout << "You have found: " << userCorrectedAnswers->getSize() << "/" << answers->getSize() << " words\n";
			std::cout << "Press\n";
			std::cout << "ENTER -> answer\n";
			std::cout << "2 -> see answers\n";
			std::cout << "q -> quit\n";

			char userCommand;
			userCommand = _getch();

			BoardGameAnswer userAnswer;
			if (userCommand == 13) {
				std::cout << "The word you\'ve found is: ";
				std::getline(std::cin, userAnswer.word);
			}
			else if (userCommand == '2') {
				ConsoleEffect::foregroundBlueB("- - - - - - - - - - - - - - - - - - - - - - -\n");
				ConsoleEffect::foregroundYellowB("\t\tDirections\n");
				std::cout << "1: left to right\n";
				std::cout << "2: top to bottom\n";
				std::cout << "3: top-left to bottom-right\n";
				ConsoleEffect::foregroundYellowB("\t\tAnswers\n");
				for (int i = 0; i < answers->getSize(); i++) {
					std::cout << "(row:" << answers->getAt(i).row << ", col:" <<
						answers->getAt(i).col << ", dir:" << answers->getAt(i).dir << "): " <<
						answers->getAt(i).word << "\n";
				}
				ConsoleEffect::foregroundBlueB("- - - - - - - - - - - - - - - - - - - - - - -\n");
				system("pause");
			}
			else if (userCommand == 'q') {
				std::cout << "Do you really want to quit?(y): ";
				std::cin >> userCommand;
				std::cin.ignore();
				if (userCommand == 'y') break;
			}

			int indexRightAnswer = haveAnswerIn(answers, userAnswer);
			if (indexRightAnswer != -1) {
				userAnswer.row = answers->getAt(indexRightAnswer).row;
				userAnswer.col = answers->getAt(indexRightAnswer).col;
				userAnswer.dir = answers->getAt(indexRightAnswer).dir;
				userCorrectedAnswers->add(userAnswer);
			}

		}
		ConsoleEffect::foregroundBlueB("Your achievements!!!\n");
		std::cout << "You have found: " << userCorrectedAnswers->getSize() << "/" << answers->getSize() << " words\n";
		printBoard(board, n, userCorrectedAnswers);
	}


public:
	void playHidingWordsGame() {
		ConsoleEffect::foregroundYellowB("WELCOME TO HIDING LETTER GAME\n");

		// read the whole words from the file
		DynamicArray<Vocab*>* practiceWords = preparePractice("PracticeWords.txt");
		if (practiceWords == nullptr) {
			std::cout << "Have not any words in the practice list yet.\n";
			return;
		}

		// create a play list which contains words we wanna play
		std::cout << "Select the difficulty!\n";
		std::cout << "1 --> Easy, One Word\n";
		std::cout << "2 --> Normal, 5 Words\n";
		std::cout << "3 --> Hard, 10 Words\n";
		std::cout << "Chose one: ";
		std::string userCommand;
		std::getline(std::cin, userCommand);

		while (!(userCommand[0] >= '1' && userCommand[0] <= '3')) {
			std::cout << "chose from 1 to 3: ";
			std::getline(std::cin, userCommand);
		}

		DynamicArray<std::string>* playWordsList = new DynamicArray<std::string>();
		switch (userCommand[0]) {
		case '1':
			playWordsList = new DynamicArray<std::string>(1);
			break;
		case '2':
			playWordsList = new DynamicArray<std::string>(5);
			break;
		default:
			playWordsList = new DynamicArray<std::string>(10);
		}

		if (playWordsList->getSize() > practiceWords->getSize()) {
			std::cout << "Don\'t have enough words in the practice list to play.\n";
			return;
		}
		
		// get randomly the words from the main list we have read
		std::random_device rd;
		std::mt19937 ge(rd());
		std::uniform_int_distribution<int> dis(0, practiceWords->getSize()-1);
		
		// create a marked-array, haveTaken[i] is true if the postion i of the main list have been taken before
		bool* haveTaken = new bool[practiceWords->getSize()];
		// since all positions haven't been taken, so
		std::memset(haveTaken, false, practiceWords->getSize()*sizeof(bool));
		// start getting data for playing
		for (int i = 0; i < playWordsList->getSize(); i++) {
			int gettingPosition = dis(ge);
			while (haveTaken[gettingPosition]) gettingPosition = dis(ge);

			playWordsList->setAt(i, practiceWords->getAt(gettingPosition)->getEng());
			haveTaken[gettingPosition] = true;
		}
		// delete arrays we don't use anymore
		delete[] haveTaken;
		delete practiceWords;

		// max rows and columns of the table depends on the max length of the words
		// find the max length in playWordList
		int maxLengthPlayWords = playWordsList->getAt(0).length();
		for (int i = 1; i < playWordsList->getSize(); i++) {
			if (playWordsList->getAt(i).length() > maxLengthPlayWords) {
				maxLengthPlayWords = playWordsList->getAt(i).length();
			}
		}

		// create board game which is broader than 4 rows and 4 columns
		DynamicArray<BoardGameAnswer>* answers = new DynamicArray<BoardGameAnswer>();
		char** board = createWordLetterBoard(maxLengthPlayWords + 4, playWordsList, answers);
		delete playWordsList;
		getStartedHidingWordGame(board, maxLengthPlayWords + 4, answers);

		// clean and good bye
		clearBoard(board, maxLengthPlayWords + 4);
		delete answers;
		ConsoleEffect::foregroundYellowB("END HIDING LETTER GAME, HOPE TO SEE YOU AGAIN.\n");
		std::cout << "-------------------------------------------------------------\n";
	}

};
