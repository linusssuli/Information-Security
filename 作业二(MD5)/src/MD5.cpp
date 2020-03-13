#include <iostream> 
#include <iomanip>
#include <cstdio>
#include <cstring>
#include <string>
#include <cstdlib>
#include "MD5.h"

using namespace std;

void HMD5(void *buffer){
	
	unsigned int A, B, C, D, Temp;
	const unsigned int *X = static_cast<unsigned int*>(buffer);

	A = MD[0];
	B = MD[1];
	C = MD[2];
	D = MD[3];
	
	for(int i = 0;i < 64;i++){

		switch(i/16){ 
			case 0:{
				Temp = F(B, C, D);
				break;
			}	
			case 1:{
				Temp = G(B, C, D);
				break;
			}
			case 2:{
				Temp = H(B, C, D);
				break;
			}
			case 3:{
				Temp = I(B, C, D);
				break;
			}
			default:
				break;
		}
		Temp += X[Order_Table[i]] + T[i] + A;
		A = LS(Temp,S[i]) + B;
		
		Temp = D;
		D = C;
		C = B;
		B = A;
		A = Temp;
	}
	MD[0] = A;
	MD[1] = B;
	MD[2] = C;
	MD[3] = D;
}

void Init(const char *msg){
	unsigned int K = strlen(msg);
	unsigned int P = 0;
	if(K*8%512==448){ 
		P = 512;
	} else{
		P = 448 - (K*8)%512;
	}
	P /= 8; 
	unsigned int msgLen = K + P + 8;
	unsigned char* buffer = new unsigned char[msgLen];
	for(int i = 0;i < K;i++){
		buffer[i] = msg[i];
	}
	for(int i = K+1;i < msgLen;i++){
		buffer[i] = 0x00;
	}
	buffer[K] = 0x80;//10000000
	buffer[msgLen-5] = (K*8&0xFF000000)>>24;
	buffer[msgLen-6] = (K*8&0x00FF0000)>>16;
	buffer[msgLen-7] = (K*8&0x0000FF00)>>8;
	buffer[msgLen-8] = K*8&0x000000FF;
	
	unsigned int L = msgLen/64;
	unsigned int A, B, C, D;
	for (int i = 0;i < L;i++){
		A = MD[0];
		B = MD[1];
		C = MD[2];
		D = MD[3];
		
		HMD5(&buffer[i*64]);
		
		MD[0] += A;
		MD[1] += B;
		MD[2] += C;
		MD[3] += D;
	}
		
}
int main(){
	char msg[56];
	printf("Welcome to MD5 Encrption! Please enter the number you want to encrypt.......\n");
	scanf("%s", msg);
	printf("\nYour PlainText is: %s", msg);
	Init(msg);
	
	printf("\n\n\n---------------Encrypting, wait for a minute--------------------\n\n\n");
	unsigned char a, b, c, d;
	printf("Your CipherText is: ");
	for(int i = 0;i < 4;i++){
		a = (MD[i]&0xFF000000)>>24;
		b = (MD[i]&0x00FF0000)>>16;
		c = (MD[i]&0x0000FF00)>>8;
		d = MD[i]&0x000000FF;
		printf("%x%x%x%x", d,c,b,a);
		
	}
	printf("\n\n");
	return 0;
	system("PAUSE");
} 
