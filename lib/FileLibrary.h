#include <iostream>
#include <vector>

using namespace std;

void createLicenseFile(string s) {
	vector<char> v(s.begin(), s.end());
	int length = v.size();
	char* chars = new char[length];
	for( int i = 0; i < length; i++ ) {
		chars[i] = v[i];
	};

	FILE* file = fopen("license.txt", "w");
	if( file == NULL ) {
		perror("Cannot open the license.txt.");
	};
	fputs(chars, file);
	if( ferror(file) ) {
		printf("Cannot write data to the license.txt.");
	};
	fclose(file);
	
	cout << " " << endl;
	cout << "Successfully created license.txt in the same directory." << endl;
	cout << "Please hand it over to the client." << endl;
};

string readLicenseFile() {
	FILE* file;
	char* chars = new char[5];
	file = fopen("license.txt", "r");
	if( file == NULL ) {
		perror("Cannot open the license.txt.");
	};
	string result = "";
	while( fgets(chars, 5, file) != NULL ) {
		result.append(string(chars));
	};
	if( ferror(file) ) {
		printf("Cannot retrieve data from the license.txt.");
	};
	fclose(file);

	return result;
};
