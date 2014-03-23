#include <iostream>
#include <string>
#include <exception>
#include <fstream>
#include "IReceiver.h"



using namespace std;
int main()
try
{

	const int inputChunkSize = 5;

	IReceiver* r = createReceiver();

	string input;
	char c;
	int i = 0;
	while (cin >> c){
		if (i < inputChunkSize) {
			input += c;
			++i;
		}
		else
		{
			cin.putback(c);
			r->receive(input.c_str(),input.size());
			input = "";
			i = 0;
		}
	}
	destroyReceiver(r);

}

catch (exception& e){
	cerr << e.what() << endl;
}