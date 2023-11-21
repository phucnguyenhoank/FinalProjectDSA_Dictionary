#include "WordGame.h"

int main() {
	WordGame* wg = new WordGame();
	std::string userCommand = "h";

	while (userCommand.compare("q")) {
		if (userCommand.compare("1") == 0) {
			wg->lookUp();
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("2") == 0) {
			system("cls");
			int res = wg->addToPracticeList("PracticeWords.txt");
			if (res == 1) ConsoleEffect::foregroundYellowB("Word added.\n");
			else if (res == 2) ConsoleEffect::foregroundYellowB("Word already added.\n");
			else if (res == 3) ConsoleEffect::foregroundYellowB("Sorry, that word isn\'t in your practice list.\n");
			else ConsoleEffect::foregroundRed("Adding word failed.\n");
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("3") == 0) {
			system("cls");
			int res = wg->removeFromPracticeList("PracticeWords.txt");
			if (res == 1) ConsoleEffect::foregroundYellowB("Word removed.\n");
			else if (res == 2) ConsoleEffect::foregroundYellowB("Sorry, that word isn\'t in your practice list.\n");
			else if (res == 0) ConsoleEffect::foregroundYellowB("Practice list is empty.\n");
			else ConsoleEffect::foregroundRed("Removing word failed.\n");
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("4") == 0) {
			system("cls");
			int res = wg->addWord();
			if (res == 1) ConsoleEffect::foregroundYellowB("Word added.\n");
			else if (res == 2) ConsoleEffect::foregroundYellowB("The word already exists.\n");
			else ConsoleEffect::foregroundRed("Adding word failed.\n");
		}
		else if (userCommand.compare("5") == 0) {
			system("cls");
			int res = wg->removeWord();
			if (res == 1) ConsoleEffect::foregroundYellowB("Word removed.\n");
			else if (res == 2) ConsoleEffect::foregroundYellowB("Sorry, that word isn\'t in our dictionary.\n");
			else ConsoleEffect::foregroundRed("Removing word failed.\n");
		}
		else if (userCommand.compare("6") == 0) {
			system("cls");
			wg->playHidingWordsGame();
		}
		else if (userCommand.compare("h") == 0 || userCommand.compare("?") == 0) {
			ConsoleEffect::foregroundYellowB("    1\t\t"); std::cout << "-> Look Up a Word\n";
			ConsoleEffect::foregroundYellowB("    2\t\t"); std::cout << "-> Add words for Practice\n";
			ConsoleEffect::foregroundYellowB("    3\t\t"); std::cout << "-> Remove words from Practice List\n";
			ConsoleEffect::foregroundYellowB("    4\t\t"); std::cout << "-> Add words for the Dictionary\n";
			ConsoleEffect::foregroundYellowB("    5\t\t"); std::cout << "-> Remove words from the Dictionary\n";
			ConsoleEffect::foregroundYellowB("    6\t\t"); std::cout << "-> Play Hiding Words Game\n";
			ConsoleEffect::foregroundYellowB("    q\t\t"); std::cout << "-> Quit and Save changes\n";
			ConsoleEffect::foregroundYellowB("    f\t\t"); std::cout << "-> Flush the Screen\n";
			ConsoleEffect::foregroundYellowB("    h"); std::cout << " or "; ConsoleEffect::foregroundYellowB("?\t"); std::cout << "-> See the instruction\n";
			std::cout << "-------------------------------------------------------------\n";
		}
		else if (userCommand.compare("f") == 0) {
			system("cls");
		}
		else {
			ConsoleEffect::foregroundRed("invalid command\n");
			ConsoleEffect::foregroundYellowB("\'h\'");
			std::cout << " or ";
			ConsoleEffect::foregroundYellowB("\'?\'");
			std::cout << " for help\n";
		}
		ConsoleEffect::foregroundGreenB("\\main_run> ");
		std::getline(std::cin, userCommand);
	}

	std::cout << " \n\n~-~ -~- ~-~ -~- ~-~ -~-\n";
	std::cout << "    SEE YA (^-^)=b\n";
	std::cout << "~-~ -~- ~-~ -~- ~-~ -~-\n";

	// save to file
	wg->writeToFile("words.txt");

	return 0;
}
