#include"stdafx.h"
#include "Encryption.h"
#include<vector>
#include<string>
#include<sstream>
#include<bitset>
Encryption::Encryption()
{
	this->T.resize(256);
	this->S.resize(256);
}
void Encryption::swap(int* a, int* b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}
vector<int>Encryption::keyToInt(string key)
{
	vector<int> ret;
	for (int i = 0; i < (int)key.size(); i++)
		ret.push_back((int)key[i]);
	return ret;
}
void Encryption::initialization(vector<int> arrKey, string key)
{
	// Key Generation
	for (int i = 0; i < 256; i++)
	{
		S[i] = i;
		T[i] = arrKey[i % (int)key.size()]; // repeat the key till the length of 256
	}
	int j = 0;
	// permutes by KSA Function
	for (int i = 0; i < 256; i++)
	{
		j = (j + S[i] + T[i]) % 256;
		swap(&S[i], &S[j]); 
	}
}
string Encryption::keyGeneration(int length)
{
	string key = "";
	int i = 0, j = 0;

	for (int idx = 0; idx < length; idx++)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;

		swap(&S[i], &S[j]); // permutes by PRGA
		int t = (S[i] + S[j]) % 256;
		int k = S[t];
		key += k;
	}
	return key;
}
string Encryption::toHexaDecimal(string text)
{
	stringstream ss;
	for (int i = 0; i < (int)text.size(); i++)
		ss << hex << (int)text[i];
	return ss.str();
}
string Encryption::Encrypt(string input, string key)
{
	string output = "";
	int length = (int)input.size();
	vector<int> key_int = keyToInt(key);
	initialization(key_int, key);
	string myKey = keyGeneration(length);
	// apply the RC4 algorithm
	for (int i = 0; i < (int)input.length(); i++)
		output.push_back((char)(input[i] ^ myKey[i]));
	output = toHexaDecimal(output);
	return output;
}

Encryption::~Encryption()
{
}