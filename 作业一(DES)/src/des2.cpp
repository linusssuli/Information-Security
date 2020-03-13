#include <iostream>
#include <cstdio>
#include <cstdlib>
using namespace std; 

const static int IP_Table[64] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};


const static int E_Table[48] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

const static int P_Table[32] = {                                          
	16, 7, 20, 21, 29, 12, 28, 17, 1,  15, 23, 26, 5,  18, 31, 10,
	 2, 8, 24, 14, 32, 27, 3,  9,  19, 13, 30, 6,  22, 11, 4,  25 
};

const static int PC1_Table[56] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

const static int PC2_Table[48] = { 
    14, 17, 11, 24, 1, 5,
    3, 28, 15, 6, 21, 10,
    23, 19, 12, 4, 26, 8,
    16, 7, 27, 20, 13, 2,
    41, 52, 31, 37, 47, 55,
    30, 40, 51, 45, 33, 48,
    44, 49, 39, 56, 34, 53,
    46, 42, 50, 36, 29, 32
};

const static int IPInverse_Table[64] = {
    40,8,48,16,56,24,64,32,39,7,47,15,55,23,63,31, 
    38,6,46,14,54,22,62,30,37,5,45,13,53,21,61,29, 
    36,4,44,12,52,20,60,28,35,3,43,11,51,19,59,27, 
    34,2,42,10,50,18,58,26,33,1,41,9,49,17,57,25 
};



const static int S1_Box[4][16] = {
	14,  4, 13,  1,  2, 15, 11,  8,  3, 10,  6, 12,  5,  9,  0,  7,
	 0, 15,  7,  4, 15,  2, 13,  1, 10,  6, 12, 11,  9,  5,  3,  8,
	 4,  1, 14,  8, 13,  6,  2, 11, 15, 12,  9,  7,  3, 10,  5,  0,
	15, 12,  8,  2,  4,  9,  1,  7,  5, 11,  3, 14, 10,  0,  6, 13
};

const static int S2_Box[4][16] = {
	15,  1,  8, 14,  6, 11,  3,  4,  9,  7,  2, 13, 12,  0,  5, 10,
	 3, 13,  4,  7, 15,  2,  8, 14, 12,  0,  1, 10,  6,  9, 11,  5,
	 0, 14,  7, 11, 10,  4, 13,  1,  5,  8, 12,  6,  9,  3,  2, 15,
	13,  8, 10,  1,  3, 15,  4,  2, 11,  6,  7, 12,  0,  5, 14,  9
};

const static int S3_Box[4][16] = {
	10,  0,  9, 14,  6,  3, 15,  5,  1, 13, 12,  7, 11,  4,  2,  8,
	13,  7,  0,  9,  3,  4,  6, 10,  2,  8,  5, 14, 12, 11, 15,  1,
	13,  6,  4,  9,  8, 15,  3,  0, 11,  1,  2, 12,  5, 10, 14,  7,
	 1, 10, 13,  0,  6,  9,  8,  7,  4, 15, 14,  3, 11,  5,  2, 12
};

const static int S4_Box[4][16] = {
	 7, 13, 14,  3,  0,  6,  9, 10,  1,  2,  8,  5, 11, 12,  4, 15,
	12,  8, 11,  5,  6, 15,  0,  3,  4,  7,  2, 12,  1, 10, 14,  9,
	10,  6,  9,  0, 12, 11,  7, 13, 15,  1,  3, 14,  5,  2,  8,  4,
	 3, 15,  0,  6, 10,  1, 13,  8,  9,  4,  5, 11, 12,  7,  2, 14
};

const static int S5_Box[4][16] = {
	 2, 12,  4,  1,  7, 10, 11,  6,  8,  5,  3, 15, 13,  0, 14,  9,
	14, 11,  2, 12,  4,  7, 13,  1,  5,  0, 15, 10,  3,  9,  8,  6,
	 4,  2,  1, 11, 10, 13,  7,  8, 15,  9, 12,  5,  6,  3,  0, 14,
	11,  8, 12,  7,  1, 14,  2, 13,  6, 15,  0,  9, 10,  4,  5,  3
};

const static int S6_Box[4][16] = {
	12,  1, 10, 15,  9,  2,  6,  8,  0, 13,  3,  4, 14,  7,  5, 11,
	10, 15,  4,  2,  7, 12,  9,  5,  6,  1, 13, 14,  0, 11,  3,  8,
	9, 14, 15,  5,  2,  8, 12,  3,  7,  0,  4, 10,  1, 13, 11,  6,
	4,  3,  2, 12,  9,  5, 15, 10, 11, 14,  1,  7,  6,  0,  8, 13
};

const static int S7_Box[4][16] = {
	 4, 11,  2, 14, 15,  0,  8, 13,  3, 12,  9,  7,  5, 10,  6,  1,
	13,  0, 11,  7,  4,  9,  1, 10, 14,  3,  5, 12,  2, 15,  8,  6,
	 1,  4, 11, 13, 12,  3,  7, 14, 10, 15,  6,  8,  0,  5,  9,  2,
	 6, 11, 13,  8,  1,  4, 10,  7,  9,  5,  0, 15, 14,  2,  3, 12
};

const static int S8_Box[4][16] = {
	13,  2,  8,  4,  6, 15, 11,  1, 10,  9,  3, 14,  5,  0, 12,  7,
	 1, 15, 13,  8, 10,  3,  7,  4, 12,  5,  6, 11,  0, 14,  9,  2,
	 7, 11,  4,  1,  9, 12, 14,  2,  0,  6, 10, 13, 15,  3,  5,  8,
	 2,  1, 14,  7,  4, 10,  8, 13, 15, 12,  9,  0,  3,  5,  6, 11
};


void IP(const int input[64], int left[32], int right[32]) 
{
  int temp[64];
  for(int i = 0; i < 64; i++) 
  {
    temp[i] = input[IP_Table[i] - 1];
  }
   for(int i = 0; i < 64; i++)
    {
        if(i<32) 
        {
            left[i] = temp[i];
        }
        else
        {
            right[i-32] = temp[i]; 
        }
    }
}


void E(const int input[32], int output[48]) 
{
  for(int i = 0; i < 48; i++) 
  {
    output[i] = input[E_Table[i] - 1];
  }
}


void PC_1(const int input[64], int c[28], int d[28]) 
{
    int temp[56];
    for(int i = 0; i < 56; i++)
    {
        temp[i] = input[PC1_Table[i] - 1];
    }

    for(int i = 0; i < 56; i++)
    {
        if(i < 28)  
        {
            c[i] = temp[i];
        }
        else 
        {
            d[i-28] = temp[i];
        }
    }
}


void LeftShift(const int input[28], int output[28], int counter) 
{
	for(int i = 0; i < 28; i++) 
	{
		output[i] = input[(i + counter) % 28];
	}
}


void PC_2(const int c[28], const int d[28], int output[48]) 
{
	bool temp[56];
	for(int i = 0; i < 56; i++)
    {
		if(i < 28)
        {
			temp[i] = c[i];
		}
		else
        {
			temp[i] = d[i-28];
		}
	}
	
	for(int i = 0; i < 48; i++)
    {
		output[i] = temp[PC2_Table[i]-1];
	}
}


void XOR(const int *input1, const int *input2, int *output, int len)
{
    int i;
    for(i = 0; i < 32; i++)
    {
        output[i] = input1[i] ^ input2[i];
    }
}

void S(const int input[48], int output[32]) 
{
  int a1[6], a2[6], a3[6], a4[6], a5[6], a6[6], a7[6], a8[6];
  int b1[4], b2[4], b3[4], b4[4], b5[4], b6[4], b7[4], b8[4];
  for(int i = 0; i < 6; i++) 
  {
    a1[i] = input[i];
    a2[i] = input[i + 6];
    a3[i] = input[i + 2 * 6];
    a4[i] = input[i + 3 * 6];
    a5[i] = input[i + 4 * 6];
    a6[i] = input[i + 5 * 6];
    a7[i] = input[i + 6 * 6];
    a8[i] = input[i + 7 * 6];
  }
  int n, m;
  n = (a1[0] << 1) + a1[5];
  m = (a1[1] << 3) + (a1[2] << 2) + (a1[3] << 1) + a1[4];

  n = (a2[0] << 1) + a2[5];
  m = (a2[1] << 3) + (a2[2] << 2) + (a2[3] << 1) + a2[4];

  n = (a3[0] << 1) + a3[5];
  m = (a3[1] << 3) + (a3[2] << 2) + (a3[3] << 1) + a3[4];

  n = (a4[0] << 1)+ a4[5];
  m = (a4[1] << 3) + (a4[2] << 2) + (a4[3] << 1) + a4[4];

  n = (a5[0] << 1) + a5[5];
  m = (a5[1] << 3) + (a5[2] << 2) + (a5[3] << 1) + a5[4];

  n = (a6[0] << 1) + a6[5];
  m = (a6[1] << 3) + (a6[2] << 2) + (a6[3] << 1) + a6[4];

  n = (a7[0] << 1) + a7[5];
  m = (a7[1] << 3) + (a7[2] << 2) + (a7[3] << 1) + a7[4];

  n = (a8[0] << 1) + a8[5];
  m = (a8[1] << 3)+ (a8[2] << 2) + (a8[3] << 1) + a8[4];

  for (int i = 0; i < 4; i++) 
  {
	b1[3 - i] = (S1_Box[n][m] >> i) & 1;
    b2[3 - i] = (S2_Box[n][m] >> i) & 1;
    b3[3 - i] = (S3_Box[n][m] >> i) & 1;
    b4[3 - i] = (S4_Box[n][m] >> i) & 1;
    b5[3 - i] = (S5_Box[n][m] >> i) & 1;
    b6[3 - i] = (S6_Box[n][m] >> i) & 1;
    b7[3 - i] = (S7_Box[n][m] >> i) & 1;
    b8[3 - i] = (S8_Box[n][m] >> i) & 1;
	}

  for(int i = 0; i < 4; i++) 
  {
    output[i] = b1[i];
    output[i + 4] = b2[i];
    output[i + 2 * 4] = b3[i];
    output[i + 3 * 4] = b4[i];
    output[i + 4 * 4] = b5[i];
    output[i + 5 * 4] = b6[i];
    output[i + 6 * 4] = b7[i];
    output[i + 7 * 4] = b8[i];    
  }
}


void P(const int input[32], int output[32]) 
{
  int i;
  for(i = 0; i < 32; i++) 
  {
    output[i] = input[i];
  }
}

void subKey(const int input[64], int output[16][48]) 
{
  int leftCount = 0;
  int C[28] = {0}, D[28] = {0};
  int Ci[16][28] = {0}, Di[16][28] = {0};
  
  PC_1(input, C, D);
  for(int i = 1; i <= 16; i++) 
  {
    if(i == (1 || 2 || 9 || 16)) 
	{
      leftCount += 1;
    }
	else 
	{
      leftCount += 2; 
    }
    LeftShift(C, Ci[i - 1], leftCount);
    LeftShift(D, Di[i - 1], leftCount);
  }
  for(int i = 0; i < 16; i++) 
  {
    PC_2(Ci[i], Di[i], output[i]);
  }
}


void Feistel(const int input[32], const int subkey[48], int output[32]) 
{
  int temp[48] = {0}, temp2[48] = {0}, temp3[32] = {0};
  E(input, temp);
  XOR(temp, subkey, temp2, 48);
  S(temp2, temp3);
  P(temp3, output);
}


void IPInverse(const int input[64], int output[64]) 
{
	for (int i = 0; i < 64; i++) 
	{
		output[i] = input[IPInverse_Table[i] - 1];
	}
};


void CharToBit(const char input[8], int output[64]) 
{
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			output[7 * (i + 1) - j + i] = (input[i] >> j) & 1;
		}
	}
};


void BitToChar(const int input[64], char output[8]) 
{
	for (int i = 0; i < 8; i++) 
	{
		for (int j = 0; j < 8; j++) 
		{
			output[i] = output[i] * 2 + input[j + 8 * i];
		}
	}
};


void encryption(const char input[8], const char keyInput[8], int output[64]) 
{
	int PlainText[64] = {0};
    CharToBit(input, PlainText);
  
	int key[64] = {0};
  	CharToBit(keyInput, key);
	int subkeys[16][48];
  	subKey(key, subkeys);
  
  	int L[17][32] = {0}, R[17][32] = {0};
  	IP(PlainText, L[0], R[0]);

  	for(int i = 1; i <= 16; i++) 
	{
    	for(int j = 0; j < 32; j++) 
		{
      		L[i][j] = R[i - 1][j];
    	}
    	int temp[32] = {0};
    	Feistel(R[i - 1], subkeys[i - 1], temp);
		XOR(temp, L[i - 1], R[i], 32);
  	}
  	int temp[32] = {0};
  	for(int i = 0; i < 32; i++) 
	{
    	temp[i] = L[16][i];
    	L[16][i] = R[16][i];
    	R[16][i] = temp[i];
  	}

  	int output_1[64] = {0};
  	for(int i = 0; i < 32; i++) 
	{
    	output_1[i] = L[16][i];
    	output_1[i + 32] = R[16][i];
  	}

  IPInverse(output_1, output);
}

void Decryption(const int input[64], const char keyInput[8], char output[8]) 
{
	int key[64] = {0};
  	CharToBit(keyInput, key);
  	//×ÓÃÜÔ¿Éú³É
	int subkeys[16][48];
  	subKey(key, subkeys);
  
  	//³õÊ¼ÖÃ»»IP
  	int L[17][32] = {0}, R[17][32] = {0};
  	IP(input, L[0], R[0]);
  
  	//µü´ú
  	for(int i = 1; i <= 16; i++) 
	{
    	for(int j = 0; j < 32; j++) 
		{
      		L[i][j] = R[i - 1][j];
    	}
    	int temp[32] = {0};
    	Feistel(R[i - 1], subkeys[16 - i], temp); 
		XOR(temp, L[i - 1], R[i], 32);
  	}
  	int temp[32] = {0};
  	for(int i = 0; i < 32; i++) 
	{
    	temp[i] = L[16][i];
    	L[16][i] = R[16][i];
    	R[16][i] = temp[i];
  	}

  	//ÄæÖÃ»»IP^-1
  	int output_1[64] = {0};
  	int output_2[64] = {0};
  	for(int i = 0; i < 32; i++) 
	{
    	output_1[i] = L[16][i];
    	output_1[i + 32] = R[16][i];
  	}
  
  	IPInverse(output_1, output_2);
	BitToChar(output_2, output);
}

int main() 
{
	int CipherText[64] = {0};
	char PlainText[9] = {0};
	char key[9] = { 0 };
	
  	cout << "please enter your plaintext!£¨must be eight number or character!£©" << endl;
  	cout << "Plaintext: ";
  	cin >> PlainText;
	
  	cout << "please enter your secret_key!(must be eight number or character)" <<endl;
  	cout<< "SecretKey: ";
	cin >> key;
  	
  	cout<<endl;
  	cout<<"Encryption in progress"<<endl; 
  	cout<<"----------------------"<<endl;
	encryption(PlainText, key, CipherText);
	cout<<"your ciphertext is: "<<endl;
	for (int i = 0; i < 64; i++) 
	{
		cout<<CipherText[i];
		if ((i + 1) % 8 == 0)
		{
			cout<<endl;
		}
	}
	
	cout << endl << "Decryption in progress£º" <<endl; 
	cout<<"----------------------"<<endl;
	Decryption(CipherText, key, PlainText);
	cout<<"your plaintext is:"<<endl;
	for (int i = 0; i<8; i++) 
	{
		cout<<PlainText[i];
	}
	cout<<endl<<endl;
	return 0;
}
