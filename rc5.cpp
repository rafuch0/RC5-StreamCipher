#ifndef RC5_CPP
#define RC5_CPP

#include <iostream>
#include <math.h>
#include <stdint.h>
#include <fstream>
#include <cassert>
#include <sys/stat.h>
#include <sys/time.h>
#include <string.h>

#define P8 0xb7
#define Q8 0x9e

using namespace std;

uint8_t rc5::MagicP()
{
	return (uint8_t) P8;
}

uint8_t rc5::MagicQ()
{
        return (uint8_t) Q8;
}

uint8_t rc5::ROTL(uint8_t x, uint8_t s)
{
	return (uint8_t) (((x)<<(s&(w-1))) | ((x)>>(w-(s&(w-1)))));
}

uint8_t rc5::ROTR(uint8_t x, uint8_t s)
{
	return (uint8_t) (((x)>>(s&(w-1))) | ((x)<<(w-(s&(w-1)))));
}

rc5::rc5(int argc, char *argv[])
{
	encryptBool = true;
	if(argc == 3)
	{
		if((*argv[1]) == 'e')
		{
			encryptBool = true;
			cerr << "Encrypting" << endl;
		}
		else if((*argv[1]) == 'd')
		{
			encryptBool = false;
			cerr << "Decrypting" << endl;
		}

		strcpy(tempKey, argv[2]);
		b = 25;
		w = 8;
		r = 64;

		rc5init();			//Init
		rc5doit();			//Do Encrypt or Decrypt
	}
	else cerr << "USAGE: cat blah | ./a.out e <key>" << endl;
}

void rc5::rc5doit()
{
	if(encryptBool) rc5encrypt();	//Encrypt
	else rc5decrypt();		//Else Decrypt
}

void rc5::rc5init()
{
        int u = w/8;
        int c = (int)ceil((float)max(b,1)/(float)u);
        int t = 2*(r+1);

        int i;
        int j;

        K = new uint8_t[b];   //make sure key size is 1-256
        L = new uint8_t[c];
        S = new uint8_t[t];

	for(int z=0;z<b;z++)
	{
		K[z] = tempKey[z];
	}

	for(int z=0;z<c;z++)
	{
		L[z] = 0;
	}

        uint8_t A=0;
        uint8_t B=0;

        for(i=b-1,L[c-1]=0;i!=-1;i--)
        {
                L[i/u] = (L[i/u]<<8) + K[i];
        }

        for(i=1,S[0]=MagicP();i<t;i++)
        {
                S[i] = S[i-1]+MagicQ();
        }

        for(int z=0,A=B=i=j=0;z<3*max(t,c);z++,i=(i+1)%t,j=(j+1)%c)
        {
                A = S[i] = ROTL((S[i] + A + B),3);
                B = L[j] = ROTL((L[j] + A + B),(A + B));
        }
}

rc5::~rc5()
{
	delete[] K;		//Destructors
	delete[] S;
	delete[] L;
}

void rc5::rc5encrypt()
{
	uint8_t A = 0;
	uint8_t B = 0;

	uint8_t buffer[64];

	int j=0;
	int i=0;
	while(!cin.eof())
	{
		cin.read((char*)&buffer,sizeof(A)*64);
		//cerr << "Read = " << cin.gcount() << endl;
		for(j=0;j<64;j+=2)
		{
	        A = buffer[j];
			B = buffer[j+1];
			if(cin.gcount() < 64)
			{
				if(j == cin.gcount()) break;
				else if(j+1 == cin.gcount()) B = cin.gcount();
			}
	
			A = A + S[0];
			B = B + S[1];
			for(i=1;i<=r;i++)
			{
				A = ROTL((A^B),B) + S[2*i];
				B = ROTL((B^A),A) + S[2*i+1];
			}

			cout << A;
			cout << B;
			if(j+1 == cin.gcount()) break;
		}
	}
}

void rc5::rc5decrypt()
{
        uint8_t A = 0;
        uint8_t B = 0;

	uint8_t buffer[64];

	int i=0;
	int j=0;

	while(!cin.eof())
	{
		cin.read((char*)&buffer,sizeof(A)*64);

		//cerr << "Read = " << cin.gcount() << endl;
		for(j=0;j<64;j+=2)
		{
			A = buffer[j];
	        B = buffer[j+1];

            for(i=r;i>0;i--)
	        {
    			B = ROTR((B - S[2*i+1]),A)^A;
       	        A = ROTR((A - S[2*i]),B)^B;
      	   	}

       	    B = B - S[1];
        	A = A - S[0];

			if(cin.gcount() < 64)
			{
				if(j == cin.gcount()) break;
				cout << A;
				if((j + 2 == cin.gcount()) && (B == cin.gcount()-1)) break;
				cout << B;
			}
			else
			{
				cout << A;
				cout << B;
			}
		}
        }
}

#endif
