#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define DATA_BITS    8
#define PARITY_BITS  4
#define CHAR_LIMIT   100




// Given a brokenSequence of bits representing a corrupted 12-bit (i.e., DATA_BITS + PARITY_BITS)
// hamming code sequence, determine which bit had been flipped and then flip it back and store
// the repaired sequence in fixedSequence.    Note that both bit sequences may be very large,
// but this function should only examine the first 12 bits of the sequence (i.e., the first
// 12 characters in the incoming and outgoing char array).
void fix(char brokenSequence[], char fixedSequence[]) {
//creates an array to contain a bitstring without paritybits
int bits[8];
//counter to find corrupted bit
int bit =0;
//sets all values to 0 before filling array
for (int i = 0;i<8;i++){
	bits[i]=0;
}
//fills bits array
bits[0]=brokenSequence[2];
for (int i = 1; i <4;i++){
	bits[i] = brokenSequence[i+3];
}
for (int i = 4; i <8;i++){
	bits[i] = brokenSequence[i+4];
}

//goes through parity bits to see which are wrong and adds the position if they are
if ((bits[0]+bits[1]+bits[3]+bits[4]+bits[6])%2==0){
	if (brokenSequence[0] != '0'){
		bit++;
	}
}else{
	if (brokenSequence[0] != '1'){
		bit++;
	}
}

if ((bits[0]+bits[2]+bits[3]+bits[5]+bits[6])%2==0){
	if (brokenSequence[1] != '0'){
		bit+=2;
	}
}else{
	if (brokenSequence[1] != '1'){
		bit+=2;
	};
}

if ((bits[1]+bits[2]+bits[3]+bits[7])%2==0){
	if (brokenSequence[3] != '0'){
		bit+=4;
	}
}else{
	if (brokenSequence[3] != '1'){
		bit+=4;
	}
}

if ((bits[4]+bits[5]+bits[6]+bits[7])%2==0){
	if (brokenSequence[7] != '0'){
		bit+=8;
	}
}else{
	if (brokenSequence[7] != '1'){
		bit+=8;
	}
}

//fixes the bit
if (brokenSequence[bit-1] == '1'){
	brokenSequence[bit-1] ='0';
} else{
	brokenSequence[bit-1] = '1';
}

  for (int i=0; i<DATA_BITS+PARITY_BITS; i++) 
    fixedSequence[i] = brokenSequence[i];
}






// This program takes in a corrupted 12-bit hamming code sequence from the user and then
// attempts to correct the corrupted bits.   It is assumed that exactly one bit in each
// of the 12-bit sequences has been flipped.   The input is a large array of characters
// which are all 1's or 0's.   The incoming sequence MUST be a multiple of 12 characters.
// For example, if a data string was entered originally as "ABCD" ... then each character
// in the string would be encoded as 12-bits.  So we would need 48 bits to represent the
// input string.   These 48 bits would be coded as 48 characters consisiting of 1's or
// 0's.   So, the expected input to this program would be a large 48 character string of
// '1' and '0' chars.
int main() {
  unsigned char   brokenString[12*CHAR_LIMIT+1];
  unsigned char   fixedString[12*CHAR_LIMIT+1];
  int             charCount;

  // Get the string to decode
  char formatString[10];
  sprintf(formatString, "%%%ds", 12*CHAR_LIMIT);
  scanf(formatString, (char *)brokenString);
  charCount = strlen(brokenString);

  // Make sure that the string size is a multiple of 12 characters, otherwise something is wrong
  if (charCount%12 != 0) {
    printf("The entered bit sequence must have a multiple of 12 bits.\nThis sequence has %d bits left over.\n", charCount%12);
    exit(-1);
  }

  // Fix the bits in the brokenString by identifying the single flipped bit in each of
  // the sequential sets of 12 bits
  for (int i=0; i<charCount/12; i++)
    fix(&brokenString[i*12], &fixedString[i*12]);
  fixedString[12*(charCount/12)] = '\0';
  printf("%s\n", fixedString);  
}
