#include <iostream>
#include "FanoAlgorithm.h"

int main()
{
	string str = "If A is success in life, then A = x + y + z. Work is x, play is y and z is keeping your mouth shut.";
	FanoAlgorithm* f = new FanoAlgorithm(str);
	cout << "Initial string: " << str << endl;
	f->printCharsEncoding();
	cout << "Encoded string: " << f->getEncodedStr() << endl;
	cout << "Initial string memory: " << f->initStrSizeInBites() << " bites" << endl;
	cout << "Encoded string memory: " << f->encodedStrSizeInBites() << " bites" << endl;
	cout << "Compression ratio: " << f->compressionRatio() << endl;
	cout << "Decoded string: " << f->getDecodedStr() << endl;
	return 0;
}
