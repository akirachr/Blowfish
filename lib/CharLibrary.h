#include <iostream>
#include <vector>

using namespace std;

unsigned char* convertStringToUnsignedChars(string s) {
	vector<unsigned char> v(s.begin(), s.end());
	int length = v.size();
	unsigned char* chars = new unsigned char[length];
	for( int i = 0; i < length; i++ ) {
	        chars[i] = v[i];
	};
	
	return chars;
};

char* convertStringToChars(string s) {
	vector<char> v(s.begin(), s.end());
	int length = v.size();
	char* chars = new char[length + 1];
	for( int i = 0; i < length; i++ ) {
		chars[i] = v[i];
	};
	chars[length] = '\0';
	
	return chars;
};

long convertUnsignedCharsToLong(unsigned char* chars) {
        long a = (long)chars[0] << 24;
        long b = (long)chars[1] << 16;
        long c = (long)chars[2] << 8;
        long d = (long)chars[3];
        long result = a + b + c + d;

        return result;
};

char* convertLongToChars(long x) {
	char* chars = new char[4];
	chars[0] = (char)((x >> 24) & 0x000000FF);
	chars[1] = (char)((x >> 16) & 0x000000FF);
	chars[2] = (char)((x >> 8) & 0x000000FF);
	chars[3] = (char)(x & 0x000000FF);

	return chars;
};

unsigned char* createPaddingInformationChars(int paddingLength) {
	unsigned char* paddingInformationChars = new unsigned char[8];

	if( paddingLength == 0 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x30;
		};
	} else if( paddingLength == 1 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x31;
		};
	} else if( paddingLength == 2 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x32;
		};
	} else if( paddingLength == 3 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x33;
		};
	} else if( paddingLength == 4 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x34;
		};
	} else if( paddingLength == 5 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x35;
		};
	} else if( paddingLength == 6 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x36;
		};
	} else if( paddingLength == 7 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x37;
		};
	} else if( paddingLength == 8 ) {
		for( int i = 0; i < 8; i++ ) {
		        paddingInformationChars[i] = (unsigned char)0x38;
		};
	}

	return paddingInformationChars;
};

void arraycopy(unsigned char* source, int sourcePosition, unsigned char* destination, int destinationPosition, int length) {
	for( int i = 0; i < length; i++ ) {
		destination[destinationPosition + i] = source[sourcePosition + i];
	};
};

int charToInt(unsigned char c) {
	int s = 0;
	if( c == '0' ) {
		s = 0;
	} else if( c == '1' ) {
		s = 1;
	} else if( c == '2' ) {
		s = 2;
	} else if( c == '3' ) {
		s = 3;
	} else if( c == '4' ) {
		s = 4;
	} else if( c == '5' ) {
		s = 5;
	} else if( c == '6' ) {
		s = 6;
	} else if( c == '7' ) {
		s = 7;
	} else if( c == '8' ) {
		s = 8;
	} else if( c == '9' ) {
		s = 9;
	} else if( c == 'A' ) {
		s = 10;
	} else if( c == 'B' ) {
		s = 11;
	} else if( c == 'C' ) {
		s = 12;
	} else if( c == 'D' ) {
		s = 13;
	} else if( c == 'E' ) {
		s = 14;
	} else if( c == 'F' ) {
		s = 15;
	};
	
	return s;
};

unsigned char* convertEncodedStringHexToUnsignedChars(string encodedStringHex) {
	vector<unsigned char> v(encodedStringHex.begin(), encodedStringHex.end());
	int length = v.size();
	unsigned char* encodedChars = new unsigned char[length / 2];
	for( int i = 0; i < length; i += 2 ) {
		long upper = (long)(charToInt(v[i])*16);
		long lower = (long)charToInt(v[i + 1]);
		long x = upper + lower;
		encodedChars[i / 2] = (unsigned char)(x & 0x000000FF);
	};
	
	return encodedChars;
};

string convertIntToString(int i) {
	string s = "0";
	if( i == 0 ) {
		s = "0";
	} else if( i == 1 ) {
		s = "1";
	} else if( i == 2 ) {
		s = "2";
	} else if( i == 3 ) {
		s = "3";
	} else if( i == 4 ) {
		s = "4";
	} else if( i == 5 ) {
		s = "5";
	} else if( i == 6 ) {
		s = "6";
	} else if( i == 7 ) {
		s = "7";
	} else if( i == 8 ) {
		s = "8";
	} else if( i == 9 ) {
		s = "9";
	} else if( i == 10 ) {
		s = "A";
	} else if( i == 11 ) {
		s = "B";
	} else if( i == 12 ) {
		s = "C";
	} else if( i == 13 ) {
		s = "D";
	} else if( i == 14 ) {
		s = "E";
	} else if( i == 15 ) {
		s = "F";
	}
	
	return s;
};

string convertUnsignedCharToStringHex(unsigned char c) {
	string s = "";
	int x = (int)c;
	int upper = x / 16;
	int lower = x % 16;
	s.append(convertIntToString(upper));
	s.append(convertIntToString(lower));

	return s;
};

int unsignedStrLen(unsigned char* uchars) {
	int length = 0;
	int i = 0;
	while( uchars[i] != '\0' ) {
		i++;
	};
	length = i;

	return length;
};

string convertUnsignedCharsToStringHex(unsigned char* chars) {
	string s = "";
	int length = unsignedStrLen(chars);
	for( int i = 0; i < length; i++ ) {
		s.append(convertUnsignedCharToStringHex(chars[i]));
	};
	
	return s;
};

char* convertUnsignedCharsToChars(unsigned char* uchars) {
	int length = unsignedStrLen(uchars);
	char* chars = new char[length];
	for( int i = 0; i < length; i++ ) {
		chars[i] = (char)uchars[i];
	};
	
	return chars;
};

bool validateDateString(string date) {
	bool flag = false;
	int dateLength = date.size();
	if( dateLength == 10 ) {
		flag = true;
	} else {
		flag = false;
		return flag;
	};
	
	if( date.at(4) != '/' ) {
		flag = false;
		return flag;
	};
	
	if( date.at(7) != '/' ) {
		flag = false;
		return flag;
	};
	
	string year = date.substr(0, 4);
	int yearInt = 0;
	try {
		yearInt = stoi(year);
	} catch(invalid_argument const &e) {
		cout << "The value of year must be an integer." << endl;
		flag = false;
		return flag;
	};
	if( yearInt >= 2020 ) {
		flag = true;
	} else {
		cout << "The value of year must be over or equal to 2020. " << endl;
		flag = false;
		return flag;
	};
	
	int monthInt = 0;
	string month = date.substr(5, 2);
	try {
		monthInt = stoi(month);
	} catch(invalid_argument const &e) {
		cout << "The value of month must be an integer." << endl;
		flag = false;
		return flag;
	};
	if( (1 <= monthInt) & (monthInt <= 12) ) {
		flag = true;
	} else {
		cout << "The value of month must be in the range of 01 - 12. " << endl;
		flag = false;
		return flag;
	};
	
	int dayInt = 0;
	string day = date.substr(8, 2);
	try {
		dayInt = stoi(day);
	} catch(invalid_argument const &e) {
		cout << "The value of day must be an integer." << endl;
		flag = false;
		return flag;
	};
	if( (1 <= dayInt) & (dayInt <= 31) ) {
		flag = true;
	} else {
		cout << "The value of day must be in the range of 01 - 31. " << endl;
		flag = false;
		return flag;
	};
	
	return flag;
};
