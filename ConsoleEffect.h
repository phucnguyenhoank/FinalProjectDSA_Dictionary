#include <iostream>
#define ESC "\x1b"
#define CSI "\x1b["

class ConsoleEffect {
public:

	// save current cursor position to the memory
	static void saveCurrentCursor() {
		std::cout << ESC << "7";
	}

	// move the cursor to the position that 'saveCurrentCursor' has saved
	static void loadSavedCursor() {
		std::cout << ESC << "8";
	}

	// Returns all attributes to the default state prior to modification
	static void defaultTextFormatting() {
		std::cout << CSI << "0m";
	}

	// Applies only the foreground portion of the defaults
	static void foregroundDefault() {
		std::cout << CSI << "39m";
	}

	// Applies non-bold/bright red to foreground
	static void foregroundRed(std::string s) {
		std::cout << CSI << "31m" << s;
		foregroundDefault();
	}

	// Applies bold/bright red to foreground
	static void foregroundRedB(std::string s) {
		std::cout << CSI << "91m" << s;
		foregroundDefault();
	}

	// Applies bold/bright green to foreground
	static void foregroundGreenB(std::string s) {
		std::cout << CSI << "92m" << s;
		foregroundDefault();
	}

	// Applies bold/bright yellow to foreground
	static void foregroundYellowB(std::string s) {
		std::cout << CSI << "93m" << s;
		foregroundDefault();
	}

	// Applies bold/bright blue to foreground
	static void foregroundBlueB(std::string s) {
		std::cout << CSI << "94m" << s;
		foregroundDefault();
	}

	// Applies bold/bright white to foreground
	static void foregroundWhiteB(std::string s) {
		std::cout << CSI << "97m" << s;
		foregroundDefault();
	}

};