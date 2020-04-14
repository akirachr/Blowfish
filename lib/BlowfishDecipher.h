#include <iostream>

using namespace std;

class BlowfishDecipher {
	public:
		static long* decrypt(long* original, long* P, long** S) {
			long* decoded = new long[2];
			long Xl = original[0];
			long Xr = original[1];
			long temp = 0;

			for( int i = N + 1; i >= 0; i-- ) {
				temp = Xl;
				Xl = Xr;
				Xr = temp;
				
				Xr = F::encode(Xl, S) ^ Xr;
				Xl = Xl ^ P[i];
			}

			decoded[0] = Xl;
			decoded[1] = Xr;
			
			return decoded;
		};
};
