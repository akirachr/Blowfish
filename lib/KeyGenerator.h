#include <iostream>

using namespace std;

class KeyGenerator {
	private:
		long seed = 0xA1'A2'A3'A4;
		long* P = new long[N + 2];
		long** S = new long*[256];
	public:
		KeyGenerator() {
			FOR(i, 4) S[i] = new long[256];
			FOR(i, N + 2) P[i] = seed;
			FOR(i, 4) FOR(j, 256) S[i][j] = seed;
		};

		long* getP() {
			return P;
		};
	
		long** getS() {
			return S;
		};
};
