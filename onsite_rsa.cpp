#pragma comment(lib,"cryptlib.lib")

#include<iostream>
#include<fstream>
#include "CryptoPP/rsa.h"
#include "CryptoPP/osrng.h"

using namespace std;
using namespace CryptoPP;

int main() {
	RSA::PrivateKey prvkey;
	AutoSeededRandomPool rng;
	
	Integer e("65537"), n("253963006250652707627402859040685100389"),d("42772482296155483517134936268603049473");
	prvkey.Initialize(n, e, d);
	Integer cipher("31639169974475525248366103533531939340");
	for (int i = 0; i < 10; i++) {
		string mesg;
		Integer M = prvkey.CalculateInverse(rng, cipher);
		mesg.resize(M.MinEncodedSize());
		M.Encode((byte*)mesg.data(), mesg.size());
		vector<int> DigMesg;
		for (int i = 0; i < mesg.size(); i++) {
			DigMesg.push_back((int)(mesg[i]));
		}
		Integer sum=0;
		for (int i = 0; i < DigMesg.size(); i++) {
			sum += DigMesg[i];
		}
		if (sum % 10 == 9) {
			Integer Plain((const byte*)mesg.data(), mesg.size());
			cout << Plain << endl;
			
		}
		cipher++;
	}
	return 0;
}