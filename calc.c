// Benjamin Y.
// CSCI 304 ('24 01)
// March X 2024
// Section 1 (2-3.5)
// Synopsis: A mutation of project 1!



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "calc.h"



unsigned short get_binary_op(bin_str bin)
{
    unsigned short val = 0;
    unsigned short bore = 1;

    for (int i = 0; i < 19; i++){

      if (val != ' '){ // if 1, add pow. if not, be lazy

        for (int j = 15; j >= i; j--){ // budget pow(2, 15-i)
          bore *= 2;
        } 

        val += (((int)(bin[i])-48) * bore);
        }
    }

    return val;
}

void convert_to_binary(short val, bin_str bin){

    bin_str bval, inter, temp;
    // printf("%d = val\n", val);
    unsigned short uval = (unsigned short) val;
    for (int i = 0; i < 16; i++){ // repeated division algorithm

        temp[15-i] = (char)(uval % 2 + 48);
        // printf("%c", bin[i]);
        uval /= 2;
    }

    int j = 0;
    for (int i = 0; i < 19; i++){

      if ((i+1) % 5 != 0){ // not a multiple of 5 in {0,18}
        inter[i] = temp[i-j];
      }

      else{
        inter[i] = ' '; // spaces at multiples of 5
        j++;
      }
      bin[i] = inter[i];
      bin[19] = '\0'; // manual fix for stringness
    }

    uval = 0; // just in case there's some memory error between fcalls (paranoia)
}


void print_base(short val, char mode) // big thing
{
  
  short hex = 0;
  short dec = 0;
  short oct = 0;
  short cur = val;

  bin_str bval, inter, temp;
  convert_to_binary(cur, temp);

  // nice formatting

  int j = 0;
  for (int i = 0; i < 19; i++){
    bval[i] = temp[i];
  }
  bval[19] = '\0'; // just copying it over. A left over from 16 digit implementation

  printf("****************************************\n");

  printf("* Base Values:         Input Mode: ");

  switch(mode)
    {
      case 'B':
        printf("Bin");
        hex = val;
        oct = val;
        dec = val;
        break;
      case 'H':
        printf("Hex");
        hex = val;
        oct = val;
        dec = val;
        break;

      case 'O':
        printf("Oct");
        hex = val;
        oct = val;
        dec = val;
        break;

      case 'D':
        printf("Dec");
        hex = val;
        oct = val;
        dec = val;
        break;

      default:
        break;

    }

  printf(" *\n");
  printf("*   Binary  :  %s     *\n", bval);
  printf("*   Hex     :  %04hX                    *\n", hex);
  printf("*   Octal   :  %06ho                  *\n", oct);
  printf("*   Decimal :  %-10hi              *\n", dec);
  printf("****************************************\n\n");

}



char print_menu(void) // lots of prompts
{
  char key;
  int obvious = 0;

  while (!obvious){

    char resp[10]; //copy and pasted
    printf("Please select one of the following options: \n\n");
    printf("B  Binary Mode            &  AND with Value           +  Add to Value\n");
    printf("O  Octal Mode             |  OR  with Value           -  Subtract from Value\n");
    printf("H  Hexadecimal Mode       ^  XOR with Value           N  Negate Value\n");
    printf("D  Decimal Mode           ~  Complement Value\n\n");
    printf("C  Clear Value            <  Shift Value Left\n");
    printf("S  Set Value              >  Shift Value Right\n\n");
    printf("Q  Quit\n\n");
    printf("Option: ");
    scanf("%s", resp);

    if (strlen(resp) > 1){ // if it is long than one, so preventing weird memory errors

      for (int i = 0; i < strlen(resp); i++){
      printf("%c", resp[i]);
      }

      printf("\n");
      printf("\nInvalid option: %s\n\n", resp);
      continue;
      }

    else{
      printf("%s\n", resp);
    }

    key = toupper(resp[0]); /* just uppercase */

    
    switch(key)
    {
      case 'B':
      case 'Q':
      case 'O':
      case 'H':
      case 'D':
      case 'C':
      case 'S':

      case '&':
      case '|':
      case '^':
      case '~':

      case '+':
      case '-':
      case 'N':

      case '<':
      case '>':

        obvious = 1;
        break;

      default:
        printf("\nInvalid option: %s\n\n", resp);
        break;

    }

  }

  return key;

}



short get_operand(char option) /* tosses input */
{
  
  int f = 1;
  long temp = 0;
  bin_str bin;
  short val = 0;
  char input;
  
  switch(option)
    {
      case 'B':
        printf("Enter binary value: ");
        scanf("%s", bin);
        printf("%s", bin);

        f = 1;
        for (int i = 0; i < strlen(bin); i++){
          if (bin[strlen(bin)-1-i]=='1'){
            val += f;
          }
          f *= 2;
        }
    
        break;

      case 'H':
        printf("Enter hex value: ");
        scanf("%hX", &val);
        printf("%hX", val);

        break;

      case 'O':
        printf("Enter octal value: ");
        scanf("%ho", &val);
        printf("%ho", val);
        
        break;

      case 'D':
        printf("Enter decimal value: ");
        scanf("%hi", &val);
        printf("%hi", val);
        
        break;

      default:
        break;
    }

  return val;
}





void add (short *val, char mode){
    short cur = get_operand(mode);
    bin_str bcur, bval, temp;
    long langsam = *val + cur;
    *val += cur;

    if ( (labs(*val - langsam)) ){  // if short size caused overflow, != original value in long
      
      if ((cur > 0)){
        printf("\nPositive Overflow");
      }

      if ((cur < 0)){
        printf("\nNegative Overflow");
      }

    }

    convert_to_binary(*val, temp);
}

void subtract (short *val, char mode){
    short cur = get_operand(mode);
    bin_str bcur, bval, temp;
    long langsam = *val - cur;
    *val -= cur;

    if ( (labs(*val - langsam)) ){  // same logic as the add function
      
      if ((cur < 0)){ 
        printf("\nPositive Overflow");
      }
      if ((cur > 0)){
        printf("\nNegative Overflow");
      }
    }
    
    convert_to_binary(*val, temp);
}




int main ()
{
  short val = 0;
  short cur;
  short shift;
  int terminate = 0;
  char lastNumMode = 'D'; // so numerical mode holds even if input is not B,H,D, or O
  char mode;
  bin_str bin, ctemp, vtemp, result;

  printf("\n");

  while (!terminate){ // terminate called by 'Q' input

    print_base(val, lastNumMode);
    mode = print_menu ();
    
    switch(mode){
      case 'B':
        lastNumMode = 'B';
        printf("Mode: Binary");
        break;

      case 'H':
        lastNumMode = 'H';
        printf("Mode: Hexadecimal");
        break;

      case 'O':
        lastNumMode = 'O';
        printf("Mode: Octal");
        break;

      case 'D':
        lastNumMode = 'D';
        printf("Mode: Decimal");
        break;

      case 'S':
        val = get_operand (lastNumMode);
        break;

      case 'C':
        val = 0;
        printf("\n");
        break;

      case 'Q':
        terminate = 1;
        break;

      case '&':
      
        cur = get_operand (lastNumMode);
        val &= cur;
        break;
      
      case '|':

        cur = get_operand (lastNumMode);
        val |= cur;
        break;

      case '^':

        cur = get_operand (lastNumMode);
        val ^= cur;
        break;
        
      case '~':
        val = -val - 1;
        printf("\n");
        break;

      case '+':
        add (&val, lastNumMode);
        break;
      case '-':
        subtract (&val, lastNumMode);
        break;
      case 'N':
        val = -val;
        printf("\n");
        break;

      case '<':
        printf("Enter number of positions to left shift value: ");
        scanf("%hd", &shift);
        printf("%hd\n\n", shift);
        shift = (short) shift;
        val = val << shift;
        break;

      case '>':
        printf("Enter number of positions to right shift value: ");
        scanf("%hd", &shift);
        printf("%hd\n\n", shift);
        shift = (short) shift;
        val = val >> shift;
        break;

      default:
        break;
      }

      if ( (mode != 'C') && (mode != '~') && (mode != 'N') && (mode != '>') && (mode != '<') && (mode != 'Q') ){ //  special cases
      printf("\n\n");
      }
  }
  
  printf("\n");
  return EXIT_SUCCESS;
}