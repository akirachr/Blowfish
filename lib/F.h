#include <iostream>

using namespace std;

class F {
	public:
		static long encode(long x, long** S) {
			unsigned short a;
			unsigned short b;
			unsigned short c;
			unsigned short d;
			long y = 0;
			
			d = (unsigned short)(x & 0x000000FF);
			x >>= 8;
			c = (unsigned short)(x & 0x000000FF);
			x >>= 8;
			b = (unsigned short)(x & 0x000000FF);
			x >>= 8;
			a = (unsigned short)(x & 0x000000FF);

			y = S[0][a] + S[1][b];
			y = y ^ S[2][c];
			y = y + S[3][d];
			
			return y;
		};
};
