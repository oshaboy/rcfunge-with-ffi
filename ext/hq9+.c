/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef HQ9P
#include <time.h>
#include "funge.h"
#define LetterNum(x) ((x)-'A')

/* a0 b1 c2 d3 e4 f5 g6 h7 i8 j9 k10 l11 m12 n13 o14 p15 q16 r17 s18 t19
   u20 v21 w22 x23 y24 z25 */

static int accumulator;
void Load_HQ9P(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[LetterNum('H')][vm->IPs[cip].NumOvers]=EX_HQ9P+LetterNum('H');   /* H */
  vm->IPs[cip].Overloads[LetterNum('Q')][vm->IPs[cip].NumOvers]=EX_HQ9P+LetterNum('Q');  /* Q */
  vm->IPs[cip].Overloads[LetterNum('N')][vm->IPs[cip].NumOvers]=EX_HQ9P+LetterNum('N'); /* N */
  vm->IPs[cip].Overloads[LetterNum('P')][vm->IPs[cip].NumOvers]=EX_HQ9P+LetterNum('P');  /* P */
  accumulator=0;
}

void Unload_HQ9P(VM* vm) {
  Unload_Semantic(vm,LetterNum('H'));
  Unload_Semantic(vm,LetterNum('Q'));
  Unload_Semantic(vm,LetterNum('N'));
  Unload_Semantic(vm,LetterNum('P'));
}

void Do_HQ9P(VM* vm,int Cmd)
{
  int cip;
  cip = vm->cip;
  switch (Cmd) {
    case EX_HQ9P+LetterNum('H'):
    puts("Hello, World!");
    break;
    
    case EX_HQ9P+LetterNum('Q'):
    {
	INT x,y,z;
	INT cell;
	
	for (z=vm->ZMin; z<=vm->ZDim; z++){
		for (y=vm->YMin; y<=vm->YDim; y++){
			for (x=vm->XMin; x<=vm->XDim; x++){
				 cell = Get_Funge(vm,x,y,z);
				 putchar((int)cell);
			}
			printf("\n");
		}
		printf("\f");
	}
    }
    break;
    case EX_HQ9P+LetterNum('N'):
    {
    	int bottles=99;
	while (bottles>0){
		printf("%d Bottle%s of beer on the wall\n",bottles, bottles==1?"s":"");
		printf("%d Bottle%s of beer\n",bottles, bottles==1?"s":"");
		printf("Take one down, pass it around\n");
		bottles--;
		if (bottles==0){
			printf("There are no more bottles of beer on the wall\n\n");
		} else{
			printf("%d Bottle%s of beer on the wall\n\n",bottles, bottles==1?"":"s");
		}
	}
	printf("There are no more bottles of beer on the wall\n");
	printf("There are no more bottles of beer\n");
	printf("Go to the store, buy some more\n");
	printf("99 Bottles of beer on the wall\n\n");
    }
    break;
    case EX_HQ9P+LetterNum('P'):
    accumulator++;
    break;
    }
}
#endif

