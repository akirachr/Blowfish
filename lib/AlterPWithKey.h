#include <iostream>

using namespace std;

class AlterPWithKey {
	public:
		static long* alter(long* P, long data) {
			long* alteredP = new long[N + 2];
			for( int i = 0; i < N + 2; i++ ) {
				alteredP[i] = P[i] ^ data;
			};
			return alteredP;
		};
};
