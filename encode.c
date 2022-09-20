#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DATA_BITS    8
#define PARITY_BITS  4
#define CHAR_LIMIT   100


// Encode the given character c into a bitSequence of size (DATA_BITS + PARITY_BITS).
// Each character in bitSequence must be a '1' or '0' character corresponding to one of the
// proper hamming code data bits or parity bits.  For example, if c='A', then the
// resulting string "100010010001" should be stored in bitSequence.
void encode(unsigned char c, char bitSequence[]) {
//creates an array for the  
int bits[8];
//makes bitsequence all zeros 
  for (int i=0; i<PARITY_BITS + DATA_BITS; i++)
    bitSequence[i] = '0';
  bitSequence[12] = '\0';
  
//gets ascii value
int value = (int)c;
int count = 7;
//makes all values in bits 0
for (int i = 0;i<8;i++){
	bits[i]=0;
}
//fills bits
while(value>0){
if (value%2==0){
	bits[count]=0;
}else{
bits[count] = 1;
}
count--;
value = value/2;
}

//fills parity bits
if ((bits[0]+bits[1]+bits[3]+bits[4]+bits[6])%2==0){
bitSequence[0] = '0';
}else{
bitSequence[0]='1';
}

if ((bits[0]+bits[2]+bits[3]+bits[5]+bits[6])%2==0){
bitSequence[1] = '0';
}else{
bitSequence[1]='1';
}

if ((bits[1]+bits[2]+bits[3]+bits[7])%2==0){
bitSequence[3] = '0';
}else{
bitSequence[3]='1';
}

if ((bits[4]+bits[5]+bits[6]+bits[7])%2==0){
bitSequence[7] = '0';
}else{
bitSequence[7]='1';
}

//fills rest of bitsequence
bitSequence[2] = bits[0]+48;
for (int i = 1; i <4;i++){
	bitSequence[i+3] = bits[i]+48;
}
for (int i = 4; i <8;i++){
	bitSequence[i+4] = bits[i]+48;
}



}


// This program gets a string of ASCII characters from the user and then encodes each character
// using a 12-bit hamming code scheme, which uses 4 parity bits.  The output is displayed as a single
// string that represents a sequence of bits which has length of 12 times the number of characters
// entered.  The resulting string output consists solely of '1' and '0' characters.
int main() {
  unsigned char   transmitString[CHAR_LIMIT+1];
  unsigned char   encodedCharacters[(12+1)*(CHAR_LIMIT+1)];
  int             charCount;

  // Get the string to encode
  char formatString[10];
  sprintf(formatString, "%%%ds", CHAR_LIMIT);
  scanf(formatString, (char *)transmitString);
  charCount = strlen(transmitString);

  // Encode each character in the string by using a 12-bit hamming code
  for (int i=0; i<charCount; i++) {
    encode(transmitString[i], &encodedCharacters[13*i]);
    printf("%s", &encodedCharacters[13*i]);
  }
  printf("\n");  
}
