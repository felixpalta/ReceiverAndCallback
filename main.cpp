#include <iostream>
#include <string>
#include <exception>
#include "IReceiver.h"

using namespace std;
int main()
try
{
	IReceiver* r = createReceiver();

	string input;
	while (cin >> input)
		{
			
			r->receive(input.c_str(),input.size());
	}

	destroyReceiver(r);

}

catch (exception& e){
	cerr << e.what() << endl;
}