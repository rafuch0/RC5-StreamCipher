#ifndef RC5_H
#define RC5_H

#include <iostream>
#include <math.h>
#include <stdint.h>
#include <fstream>

using namespace std;

#define P8 0xb7
#define Q8 0x9e

class rc5
{
	public:
		rc5(int argc, char *argv[]);
		~rc5();
	private:
		void rc5doit();			//Initiates Program
		void rc5userPrompt();		//Prompt
		void rc5init();			//Create MixKey matrices
		void rc5encrypt();		//Encrypt
		void rc5decrypt();		//Decrypt

		uint8_t ROTL(uint8_t x, uint8_t s);		//Template Class rotate left
		uint8_t ROTR(uint8_t x, uint8_t s);		//Right
		uint8_t MagicP();			//Get MagicP for wordsize
		uint8_t MagicQ();			//Get MagicQ for wordsize

		bool encryptBool;		//E/D?
		int w; //16 bits		//Word Size
		int r; //1-256			//Rounds
		int b; //1-256 bytes		//Key Length

		char tempKey[256];		//Input Key
		uint8_t *K;				//Key Matrix
		uint8_t *S;				//Secret Key Matrix
		uint8_t *L;				//MixKey Matrix
};

#include "rc5.cpp"

#endif
