#include <iostream>
#include <ctime>

using namespace std;

time_t toSeconds(const char* date) {
	struct tm storage = {0,0,0,0,0,0,0,0,0};
	char* p = NULL;
	time_t result = 0;

	p = (char*)strptime(date, "%Y/%m/%d", &storage);
	result = mktime(&storage);

	return result;
};

class LicenseValidator {
	public:
		bool validate() {
			unsigned long data = 0x12'34'56'78;
			Blowfish* blowfish = new Blowfish(data);

			string encodedString = readLicenseFile();
			char* decodedChars = blowfish->decode(encodedString);

			time_t expirationDate = toSeconds(decodedChars);

			time_t now = time(0);
			char nowChars[20];
			strftime(nowChars, 20, "%Y/%m/%d", localtime(&now));
			time_t currentDate = toSeconds(nowChars);

			bool flag = false;
			if( currentDate <= expirationDate ) {
				flag = true;
			} else {
				flag = false;
			};
			return flag;
		};
};

