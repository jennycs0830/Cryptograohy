#pragma comment(lib,"cryptlib.lib")

#include<iostream>
#include<fstream>
#include<CryptoPP/rsa.h>
#include<CryptoPP/osrng.h>

using namespace std;
using namespace CryptoPP;

int main() {
	AutoSeededRandomPool rng;
	
	InvertibleRSAFunction parameters;
	int key_length = 1024;
	parameters.GenerateRandomWithKeySize(rng, key_length);

	const Integer& n = parameters.GetModulus();
	string n1 = IntToString(n, 16);
	cout << "n=" << n1 << endl;
	const Integer& p = parameters.GetPrime1();
	string p1 = IntToString(p, 16);
	cout << "p=" << p1 << endl;
	const Integer& q = parameters.GetPrime2();
	string q1 = IntToString(q, 16);
	cout << "q=" << q1 << endl;
	const Integer& d = parameters.GetPrivateExponent();
	string d1 = IntToString(d, 16);
	cout << "d=" << d1 << endl;
	const Integer& e = parameters.GetPublicExponent();
	string e1 = IntToString(e, 16);
	cout << "e=" << e1 << endl;

	RSA::PublicKey pubkey;
	pubkey.Initialize(n, e);
	string mesg = "Paris prosecutors are investigating if short-circuit caused Notre Dame fire.";
	if (mesg.size() <= (key_length / 8)) {
		Integer M((const byte*)mesg.data(), mesg.size());
		Integer C = pubkey.ApplyFunction(M);
		string cipher = IntToString(C, 16);
		cout << "Ciphertext:" << hex << cipher << endl;
	}

	RSA::PrivateKey prvkey;
	//Integer C1;
	Integer M((const byte*)mesg.data(), mesg.size());
	prvkey.Initialize(n, e, d);
	//M = prvkey.CalculateInverse(rng, C1);
	string plain;
	plain.resize(M.MinEncodedSize());
	M.Encode((byte*)plain.data(), plain.size());
	cout << "Plain:" << plain << endl;

	return 0;
}
