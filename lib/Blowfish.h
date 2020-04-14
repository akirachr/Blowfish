#include <iostream>
#include "Common.h"
#include "CharLibrary.h"
#include "KeyGenerator.h"
#include "AlterPWithKey.h"
#include "F.h"
#include "BlowfishEncipher.h"
#include "BlowfishDecipher.h"

using namespace std;

class Blowfish {
	private:
		long* P;
		long** S = new long*[256];
	public:
		Blowfish(long data) {
			FOR(i, 4) S[i] = new long[256];
			KeyGenerator* keyG = new KeyGenerator();
			P = keyG->getP();
			S = keyG->getS();
			P = AlterPWithKey::alter(P, data);
			long* original = new long[2];
			original[0] = 0x00'00'00'00;
			original[1] = 0x00'00'00'00;
			for( int i = 0; i < N + 2; i += 2 ) {
				original = BlowfishEncipher::encrypt(original, P, S);
				P[i] = original[0];
				P[i + 1] = original[1];
			};
			for( int i = 0; i < 4; i++ ) {
				for( int j = 0; j < 256; j += 2 ) {
					original = BlowfishEncipher::encrypt(original, P, S);
					S[i][j] = original[0];
					S[i][j + 1] = original[1];
				}
			}
		}
	
		long* encode(long xl, long xr) {
			long* encoded = new long[2];
			long* original = new long[2];
			original[0] = xl;
			original[1] = xr;
			encoded = BlowfishEncipher::encrypt(original, P, S);

			return encoded;
		};
	
		long* decode(long xl, long xr) {
			long* decoded = new long[2];
			long* original = new long[2];
			original[0] = xl;
			original[1] = xr;
			decoded = BlowfishDecipher::decrypt(original, P, S);

			return decoded;
		};
	
		unsigned char* encodeEightChars(unsigned char* originalChars) {
			long xl = ((long)originalChars[0]<<24) + ((long)originalChars[1]<<16) + ((long)originalChars[2]<<8) + (long)originalChars[3];
			long xr = ((long)originalChars[4]<<24) + ((long)originalChars[5]<<16) + ((long)originalChars[6]<<8) + (long)originalChars[7];

			long* encodedLong = encode(xl, xr);

			unsigned char* encodedChars = new unsigned char[8];
			encodedChars[3] = (unsigned char)(encodedLong[0] & 0x000000FF);
			encodedLong[0] >>= 8;
			encodedChars[2] = (unsigned char)(encodedLong[0] & 0x000000FF);
			encodedLong[0] >>= 8;
			encodedChars[1] = (unsigned char)(encodedLong[0] & 0x000000FF);
			encodedLong[0] >>= 8;
			encodedChars[0] = (unsigned char)(encodedLong[0] & 0x000000FF);

			encodedChars[7] = (unsigned char)(encodedLong[1] & 0x000000FF);
			encodedLong[1] >>= 8;
			encodedChars[6] = (unsigned char)(encodedLong[1] & 0x000000FF);
			encodedLong[1] >>= 8;
			encodedChars[5] = (unsigned char)(encodedLong[1] & 0x000000FF);
			encodedLong[1] >>= 8;
			encodedChars[4] = (unsigned char)(encodedLong[1] & 0x000000FF);

			return encodedChars;
		};
	
		unsigned char* decodeEightChars(unsigned char* originalChars) {
			long xl = ((long)originalChars[0]<<24) + ((long)originalChars[1]<<16) + ((long)originalChars[2]<<8) + (long)originalChars[3];
			long xr = ((long)originalChars[4]<<24) + ((long)originalChars[5]<<16) + ((long)originalChars[6]<<8) + (long)originalChars[7];

			long* decodedLong = decode(xl, xr);

			unsigned char* decodedChars = new unsigned char[8];
			decodedChars[3] = (unsigned char)(decodedLong[0] & 0x000000FF);
			decodedLong[0] >>= 8;
			decodedChars[2] = (unsigned char)(decodedLong[0] & 0x000000FF);
			decodedLong[0] >>= 8;
			decodedChars[1] = (unsigned char)(decodedLong[0] & 0x000000FF);
			decodedLong[0] >>= 8;
			decodedChars[0] = (unsigned char)(decodedLong[0] & 0x000000FF);

			decodedChars[7] = (unsigned char)(decodedLong[1] & 0x000000FF);
			decodedLong[1] >>= 8;
			decodedChars[6] = (unsigned char)(decodedLong[1] & 0x000000FF);
			decodedLong[1] >>= 8;
			decodedChars[5] = (unsigned char)(decodedLong[1] & 0x000000FF);
			decodedLong[1] >>= 8;
			decodedChars[4] = (unsigned char)(decodedLong[1] & 0x000000FF);

			return decodedChars;
		};
	
		string encode(string originalString) {
			vector<unsigned char> v(originalString.begin(), originalString.end());
			int originalCharLength = v.size();
			unsigned char* originalChars = new unsigned char[originalCharLength];
			for( int i = 0; i < originalCharLength; i++ ) {
				originalChars[i] = v[i];
			};

			int residue = originalCharLength % 8;
			int paddingLength = 0;
			if( residue != 0 ) {
				paddingLength = 8 - residue;
			};

			unsigned char* temporaryChars = new unsigned char[originalCharLength + paddingLength + 8];
			arraycopy(originalChars, 0, temporaryChars, 0, originalCharLength);
			for( int i = 0; i < paddingLength; i++ ) {
				temporaryChars[originalCharLength + i] = 0x1b;
			};
			arraycopy(createPaddingInformationChars(paddingLength), 0, temporaryChars, originalCharLength + paddingLength, 8);

			unsigned char* encodedChars = new unsigned char[originalCharLength + paddingLength + 8 + 1];

			unsigned char* eightChars = new unsigned char[8];
			unsigned char* encodedEightChars = new unsigned char[8];
			int repeat = (originalCharLength + paddingLength + 8) / 8;
			for( int i = 0; i < repeat; i++ ) {
				arraycopy(temporaryChars, i * 8, eightChars, 0, 8);
				encodedEightChars = encodeEightChars(eightChars);
				arraycopy(encodedEightChars, 0, encodedChars, i * 8, 8);
			};

			encodedChars[originalCharLength + paddingLength + 8] = '\0';

			return convertUnsignedCharsToStringHex(encodedChars);
		};

		char* decode(string encodedStringHex) {
			vector<unsigned char> v(encodedStringHex.begin(), encodedStringHex.end());
			int length = v.size();
			unsigned char* encodedChars = new unsigned char[length / 2];
			for( int i = 0; i < length; i += 2 ) {
				long upper = (long)(charToInt(v[i])*16);
				long lower = (long)charToInt(v[i + 1]);
				long x = upper + lower;
				encodedChars[i / 2] = (unsigned char)(x & 0x000000FF);
			};

			unsigned char* temporaryChars = new unsigned char[length / 2];

			unsigned char* eightChars = new unsigned char[8];
			unsigned char* decodedEightChars = new unsigned char[8];
			int repeat = length / 16;
			for( int i = 0; i < repeat; i++ ) {
				arraycopy(encodedChars, i * 8, eightChars, 0, 8);
				decodedEightChars = decodeEightChars(eightChars);
				arraycopy(decodedEightChars, 0, temporaryChars, i * 8, 8);
			};

			int paddingLength = charToInt(temporaryChars[length / 2 - 1]);

			unsigned char* decodedChars = new unsigned char[length / 2 - paddingLength - 8 + 1];

			arraycopy(temporaryChars, 0, decodedChars, 0, length / 2 - paddingLength - 8);

			decodedChars[length / 2 - paddingLength - 8] = '\0';

			char* result = new char[length / 2 - paddingLength - 8 + 1];
			result = convertUnsignedCharsToChars(decodedChars);
			
			result[length / 2 - paddingLength - 8] = '\0';

			return result;
		};
};
