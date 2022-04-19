#pragma comment(lib,"cryptlib.lib")
#include<iostream>
#include<fstream>
#include<sstream>
#include<iomanip>
#include<CryptoPP/sha.h>
#include<CryptoPP/cryptlib.h>
#include<CryptoPP/hex.h>
#include<CryptoPP/files.h>

using namespace std;
using namespace CryptoPP;

string sha_256(string mesg) {
	ostringstream output;
	//stringstream�OC++���U�����O �M������Ū���r��óB�z �ܦh�ɭԮ��Ӱ��r�ꪺ���� �άOint string�������ഫ
	HexEncoder encoder(new FileSink(output));

	string digest;
	
	SHA256 hash;
	hash.Update((const byte*)mesg.data(), mesg.size());
	digest.resize(hash.DigestSize());
	hash.Final((byte*)&digest[0]);

	StringSource(digest, true, new Redirector(encoder));
	//StringSource: a source for byte array, cstring ,string

	return output.str();
}

string hexstr_to_ascii(string hex) {
	string ascii = "";
	for (size_t i = 0; i < hex.length(); i += 2) {
		//size_t �A��p�q�O���餤�i�e�Ǫ���ƱM�׭Ӽƪ��d�Ÿ���ƫ��O
		string part = hex.substr(i, 2);
		char ch = stoul(part, nullptr, 16);
		//stoul �Nstring�নunsigned long int
		ascii += ch;
	}
	return ascii;
}

string int_to_hexstr(int i) {
	stringstream stream;
	stream << setfill('0') << setw(sizeof(i) * 2) << hex << i;
	string ans = stream.str();

	int toupper(int c);
	for_each(ans.begin(), ans.end(), [](char &c) {c = ::toupper(c); });

	return ans;
}
int main() {
	ofstream Output;
	Output.open("out.txt");

	string mesg = "Bitcoin";
	string prehash = sha_256(mesg);

	vector<int> nonce;
	bool if_nonce;

	int num_lead_zero = 0;
	int i = 0;
	while (num_lead_zero <= 8) {
		if_nonce = 1;
		string digest = prehash;
		digest.append(int_to_hexstr(i));
		digest = hexstr_to_ascii(digest);
		digest = sha_256(digest);
		for (int k = 0; k < num_lead_zero; k++) {
			if (digest[k] != '0') {
				if_nonce = 0;
				break;
				//k=num_lead_zero;
			}
		}
		if (if_nonce == 1) {
			vector<int>::iterator result = find(nonce.begin(), nonce.end(), i);
			if (result == nonce.end()) {
				nonce.push_back(i);
				Output << num_lead_zero << endl;
				cout << num_lead_zero << endl;
				Output << prehash << endl;
				cout << prehash << endl;
				Output << int_to_hexstr(i) << endl;
				cout << int_to_hexstr(i) << endl;
				Output << digest << endl;
				cout << digest << endl;
				prehash = digest;
				num_lead_zero++;
			}
		}
		if (i == 2147483647) {
			//�������˼�=2147483647 �ܶq�l�p����p��
			i = -1;
		}
		i++;
	}
	Output.close();
	return 0;
}
