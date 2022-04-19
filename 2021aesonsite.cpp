#pragma comment(lib,"cryptlib.lib")  
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "cryptopp/cryptlib.h"
#include "cryptopp/hex.h"
#include "cryptopp/filters.h"
#include "cryptopp/aes.h"
#include "cryptopp/modes.h"

#include <iostream>
#include <string>

using namespace CryptoPP;
using namespace std;
int main(int argc, char* argv[]) {

	byte key[] = "0000000000000000";
	byte cipher[] = "ac45d78068c2bd87c3f50dec9f898260";
	const byte iv[] = "0000000000000000";
	string k;

	HexDecoder decoder;
	decoder.Attach(new StringSink(k));
	decoder.Put(cipher, sizeof(cipher));
	decoder.MessageEnd();

	string output;

	for (char i = '0'; i <= '9'; i++) {
		for (char j = '0'; j <= '9'; j++) {
			key[0] = i;
			key[1] = j;
			CBC_Mode<AES>::Decryption cbc(key, 16, iv);
			StreamTransformationFilter CBC(cbc, new StringSink(output), StreamTransformationFilter::PKCS_PADDING);
			CBC.Put(reinterpret_cast<const unsigned char*>(k.c_str()), k.length());
			try { CBC.MessageEnd(); }
			catch (...) {}
			if (output.size())
				cout << key << "\n" << output << "\n";
			output.clear();
		}
	}
	return 0;
}