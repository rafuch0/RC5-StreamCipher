#include <iostream>
#include <stdint.h>
#include "rc5.H"

int main(int argc, char *argv[])
{
	rc5 *myRC58;
	myRC58 = new rc5(argc, argv);
	delete myRC58;
}
