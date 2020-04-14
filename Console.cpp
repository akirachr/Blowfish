#include <iostream>
#include <vector>
#include <unistd.h>
#include <termios.h>
#include "./lib/Blowfish.h"
#include "./lib/FileLibrary.h"
#include "LicenseValidator.h"

using namespace std;

enum CommandName {GenerateLicenseKey, ReadLicenseKey, ValidateLicenseKey};

class Command {
	public:
		Command(){};
		virtual void execute() = 0;
};

class GenerateLicenseKeyCommand:public Command {
	public:
		GenerateLicenseKeyCommand(){};
		void execute() {
			long data = 0x12'34'56'78;
			Blowfish* blowfish = new Blowfish(data);

			cout << " " << endl;
			cout << "Please enter the expiration date (YYYY/mm/dd) below." << endl;
			cout << "Ex) 2020/03/05 when it is Mar. 5, 2020" << endl;
	
			string s;
			cin >> s;

			bool flag = validateDateString(s);

			if( flag ) {
				string encodedString =  blowfish->encode(s);
				createLicenseFile(encodedString);
				cout << " " << endl;
			} else {
				cout << "Try again." << endl;
				cout << " " << endl;
			};
		};
};

class ReadLicenseKeyCommand:public Command {
	public:
		ReadLicenseKeyCommand(){};
		void execute() {
			long data = 0x12'34'56'78;
			Blowfish* blowfish = new Blowfish(data);

			string encodedString = readLicenseFile();
			char* decodedChars = blowfish->decode(encodedString);
			cout << " " << endl;
			cout << "The license expiration date is as follows." << endl;
			printf("%s\n", decodedChars);
			cout << " " << endl;
		};
};

class ValidateLicenseKeyCommand:public Command {
	public:
		ValidateLicenseKeyCommand(){};
		void execute() {
			LicenseValidator* licenseValidator = new LicenseValidator();
			bool flag = licenseValidator->validate();
			string result;
			if( flag ) {
				result = "The expiration date has not yet come.";
			} else {
				result = "The expiration date passed.";
			};
			cout << " " << endl;
			cout << flag << endl;
			cout << result << endl;
			cout << " " << endl;
		};
};

class MenuProvider {
	private:
		static MenuProvider* instance;

		char** menu = new char*[256];

		Command* commands[];
	
		MenuProvider() {
			menu[0] = convertStringToChars("g - Generate License Key");
			menu[1] = convertStringToChars("r - Read License Key");
			menu[2] = convertStringToChars("v - Validate Key");
			menu[3] = convertStringToChars("q - Quit");
			
			commands[0] = new GenerateLicenseKeyCommand();
			commands[1] = new ReadLicenseKeyCommand();
			commands[2] = new ValidateLicenseKeyCommand();
		};
	public:
		static MenuProvider* getInstance() {
			if (instance == nullptr) {
				instance = new MenuProvider();
			};
			return instance;
		};
	
		char** getOptions() {
			return this->menu;
		};
	
		Command* getCommand(CommandName commandName) {
			return this->commands[commandName];
		};
};

MenuProvider* MenuProvider::instance = nullptr;

char getChoice(MenuProvider* menuProvider, FILE* in, FILE* out) {
	char** options = menuProvider->getOptions();
	
	bool selected = false;
	char selectedC = '\0';
	
	struct termios initialSettings, newSettings;
	
	while(*options) {
		fprintf(out, "%s\n", *options);
		options++;
	};

	do {
		options = menuProvider->getOptions();
		
		tcgetattr(fileno(in), &initialSettings);
		newSettings = initialSettings;
//		newSettings.c_lflag &= ~ICANON;
//		newSettings.c_lflag &= ~ECHO;
		newSettings.c_lflag &= ~ISIG;
//		newSettings.c_cc[VMIN] = 1;
//		newSettings.c_cc[VTIME] = 0;
		tcsetattr(fileno(in), TCSANOW, &newSettings);
		
		int selectedI = fgetc(stdin);
		
		tcsetattr(fileno(in), TCSANOW, &initialSettings);
		
		selectedC = (char)selectedI;
		while(*options) {
			if( selectedC == **options ) {
				selected = true;
				break;
			};
			options++;
		};
		if( selected ) {
			if( selectedC == 'g' ) {
				Command* command = menuProvider->getCommand(GenerateLicenseKey);
				command->execute();
			} else if( selectedC == 'r' ) {
				Command* command = menuProvider->getCommand(ReadLicenseKey);
				command->execute();
			} else if( selectedC == 'v' ) {
				Command* command = menuProvider->getCommand(ValidateLicenseKey);
				command->execute();
			}
		} else if( selectedC != '\n' ) {
			fprintf(out, "Try again.\n");
			options = menuProvider->getOptions();
			while(*options) {
				fprintf(out, "%s\n", *options);
				options++;
			};
		};
	} while( !selected || ( selectedC == '\n' ) );
	
	return selectedC;
};

int main() {
	
	MenuProvider* menuProvider = menuProvider->getInstance();
	
	char choice = '\0';
	
	if( !isatty(fileno(stdout)) ) {
		fprintf(stderr, "Not a terminal.\n");
	};
	
	FILE* input = fopen("/dev/tty", "r");
	FILE* output = fopen("/dev/tty", "w");
	
	if( !input || !output ) {
		fprintf(stderr, "Unable to open /dev/tty.\n");
		return 0;
	};
	
	do {
		choice = getChoice(menuProvider, input, output);
	} while( choice != 'q' );
	
	return 0;
}
