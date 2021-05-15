#pragma once
#include <iostream>
#include <string>
#include <math.h>

using namespace std;

constexpr auto SIZE = 256;

class FanoAlgorithm
{
	string str;
	string encodedStr;
	string decodedStr;
	size_t charsFreq[SIZE] = { 0 };
	string charsCode[SIZE] = { "" };

	size_t getCharFreq(char c) {
		return this->charsFreq[(size_t)c];
	}

	string getCharCode(char c) {
		return this->charsCode[(size_t)c];
	}

	int getStrFreq(string str) {
		int freq = 0;

		for (size_t i = 0; i < str.length(); i++) {
			freq += getCharFreq(str[i]);
		}
		return freq;
	}

	void encodeCharsIteration(string str, string code) {
		if (str.length() > 1) {
			string leftStr = "";
			int leftFreq = 0;
			int strFreq = getStrFreq(str);
			size_t i;

			for (i = 0; i < str.length() - 1; i++) {
				int freq = getCharFreq(str[i]);
				int nextFreq = getCharFreq(str[i + 1]);
				leftFreq += freq;
				leftStr += str[i];
				if (abs(strFreq - 2 * leftFreq) < abs(strFreq - 2 * (leftFreq + nextFreq))) {
					break;
				}
			}

			encodeCharsIteration(leftStr, code + '1');
			encodeCharsIteration(str.substr(i + 1, str.length() - i), code + '0');
		}
		else {
			this->charsCode[(size_t)str[0]] = code;
		}
	}

	void sortByFreq(string& str) {
		for (size_t i = 0; i < str.length(); i++) {
			for (size_t j = i + 1; j < str.length(); j++) {
				if (this->getCharFreq(str[i]) < this->getCharFreq(str[j])) {
					char t = str[i];
					str[i] = str[j];
					str[j] = t;
				}
			}
		}
	}

	void encode() {
		string uniq = "";
		for (size_t i = 0; i < str.length(); i++) {
			if (getCharFreq(str[i]) == 0) {
				uniq += str[i];
			}
			this->charsFreq[(size_t)str[i]] += 1;
		}
		this->sortByFreq(uniq);
		encodeCharsIteration(uniq, "");
		for (size_t i = 0; i < this->str.length(); i++) {
			this->encodedStr += this->getCharCode(str[i]);
		}
	}

	void decode() {
		this->decodedStr = this->encodedStr;
		size_t length = this->decodedStr.length();
		for (size_t pos = 0; pos < length; pos++) {
			for (size_t i = 0; i < 256; i++) {
				char c = i;
				string code = this->getCharCode(c);
				if (!code.empty()) {
					size_t currPos = this->decodedStr.find(code, pos);
					if (currPos == pos) {
						string s = string(1, c);
						this->decodedStr.replace(pos, code.length(), s);
						length = this->decodedStr.length();
						break;
					}
				}
			}
		}
	}

public:
	FanoAlgorithm(string str) {
		this->str = str;
		this->encodedStr = "";
		this->decodedStr = "";
	}

	string getEncodedStr() {
		if (this->encodedStr.empty()) {
			this->encode();
		}
		return this->encodedStr;
	}

	string getDecodedStr() {
		if (this->encodedStr.empty()) {
			this->encode();
		}
		if (this->decodedStr.empty()) {
			this->decode();
		}
		return this->decodedStr;
	}

	void printCharsEncoding() {
		if (this->encodedStr.empty()) {
			this->encode();
		}
		cout << "Char\tFreq\tCode" << endl;
		for (size_t i = 0; i < 256; i++) {
			if (!this->charsCode[i].empty()) {
				char c = i;
				cout << c << '\t' << this->getCharFreq(c) << '\t' << this->getCharCode(c) << endl;
			}
		}
	}

	size_t initStrSizeInBites() {
		return this->str.length() * 8;
	}

	size_t encodedStrSizeInBites() {
		if (this->encodedStr.empty()) {
			this->encode();
		}
		size_t size = 0;
		for (size_t i = 0; i < this->str.length(); i++) {
			size += this->getCharCode(str[i]).length();
		}
		return size;
	}

	double compressionRatio() {
		if (this->encodedStr.empty()) {
			this->encode();
		}
		return  (double)this->initStrSizeInBites() / (double)this->encodedStrSizeInBites();
	}
};
