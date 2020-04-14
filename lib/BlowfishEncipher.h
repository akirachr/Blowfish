#include <iostream>

using namespace std;

class BlowfishEncipher {
	public:
		static long* encrypt(long* original, long* P, long** S) {
			long* encoded = new long[2];
			long Xl = original[0];
			long Xr = original[1];
			long temp = 0;

			for( int i = 0; i < N + 2; i++ ) {
				Xl = Xl ^ P[i];
				Xr = F::encode(Xl, S) ^ Xr;
				
				temp = Xl;
				Xl = Xr;
				Xr = temp;
			}

			encoded[0] = Xl;
			encoded[1] = Xr;
			
			return encoded;
		};
};
