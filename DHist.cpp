#include <iostream>
#include <math.h>
#include <stdint.h>
#include <fstream>
#include <cassert>
#include <sys/stat.h>

using namespace std;

int main(int argc, char *argv[])
{
	char inFile[128];

//        cout << "Please input the filename of the text: ";
//        cin.getline(argv[1], 128);
	
	uint64_t Histogram[256];
	for(int i=0;i<256;i++)Histogram[i]=0;

        int n;
        struct stat results;
        n = stat(argv[1], &results);

        ifstream data(argv[1], ios::in);

	assert(data);
	
	uint8_t c=0;

	for(int i=0;i<results.st_size;i++)
	{
		data.read((char*)&c,1);
		Histogram[c]++;
	}

	int total = 0;
	for(int i=0;i<256;i++)
	{
//		cout << "HistBin[" << i << "] = " << Histogram[i] << endl;
		cout << Histogram[i] << "\n";
		total += Histogram[i];
	}

//        cout << "Original File had " << results.st_size << " bytes!\n";
//	cout << "Total Histogram Values = " << total << endl;

cout << endl << "*****" << endl;

return 0;
}
