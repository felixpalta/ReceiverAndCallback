#include <iostream>
#include "IReceiver.h"

using namespace std;
int main(){
	IReceiver* r = createReceiver();
	r->receive()
	cout << "wat" << endl;
}