#pragma once
#include<vector>
#include<string>
#include"stdafx.h"
using namespace std;
class Encryption
{
private:
	vector<int> S, T;
protected:
	vector<int> keyToInt(string key);
	void initialization(vector<int> arrKey, string key);
	string keyGeneration(int length);
	string toHexaDecimal(string text);
	void swap(int* a, int* b);
public:
	Encryption();
	string Encrypt(string input, string key);
	~Encryption();
};

