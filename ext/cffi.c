/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#ifdef CFFI
#include <dlfcn.h>
#include <ffi.h>
#include <stdint.h>
#include <stdlib.h>
#include <alloca.h>
#include <stdio.h>
#include "funge.h"
#define LetterNum(x) ((x)-'A')

void ** pstack;
int stack_ptr;
void * popp(){
  register void * p = pstack[stack_ptr-1];
  stack_ptr--;
  pstack=realloc(pstack,stack_ptr*sizeof(void *));
  return p;

}
void pushp(void * p){
  stack_ptr++;
  pstack=realloc(pstack,stack_ptr*sizeof(void *));
  pstack[stack_ptr-1]=p;
  
}
void Load_CFFI(VM* vm,long int FingerPrint)
{
  INT  i;
  int cip;
  cip = vm->cip;
  vm->IPs[cip].NumOvers++;
  for (i=0;i<26;i++) vm->IPs[cip].Overloads[i][vm->IPs[cip].NumOvers]=0;
  vm->IPs[cip].OverFinger[vm->IPs[cip].NumOvers]=FingerPrint;
  Push(vm,FingerPrint); Push(vm,1);
  vm->IPs[cip].Overloads[LetterNum('B')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('B');
  vm->IPs[cip].Overloads[LetterNum('C')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('C');
  vm->IPs[cip].Overloads[LetterNum('D')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('D');
  vm->IPs[cip].Overloads[LetterNum('F')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('F');
  vm->IPs[cip].Overloads[LetterNum('G')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('G');
  vm->IPs[cip].Overloads[LetterNum('I')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('I');
  vm->IPs[cip].Overloads[LetterNum('L')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('L');
  vm->IPs[cip].Overloads[LetterNum('M')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('M');
  vm->IPs[cip].Overloads[LetterNum('O')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('O');
  vm->IPs[cip].Overloads[LetterNum('P')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('P');
  vm->IPs[cip].Overloads[LetterNum('S')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('S');
  vm->IPs[cip].Overloads[LetterNum('T')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('T');
  vm->IPs[cip].Overloads[LetterNum('U')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('U');
  vm->IPs[cip].Overloads[LetterNum('W')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('W');
  vm->IPs[cip].Overloads[LetterNum('Y')][vm->IPs[cip].NumOvers]=EX_CFFI+LetterNum('Y');
  
  pstack=malloc(sizeof(void*));
  *pstack=NULL;
  stack_ptr=1;

}

void Unload_CFFI(VM* vm) {
  Unload_Semantic(vm,LetterNum('B'));
  Unload_Semantic(vm,LetterNum('C'));
  Unload_Semantic(vm,LetterNum('D'));
  Unload_Semantic(vm,LetterNum('F'));
  Unload_Semantic(vm,LetterNum('G'));
  Unload_Semantic(vm,LetterNum('I'));
  Unload_Semantic(vm,LetterNum('L'));
  Unload_Semantic(vm,LetterNum('M'));
  Unload_Semantic(vm,LetterNum('O'));
  Unload_Semantic(vm,LetterNum('P'));
  Unload_Semantic(vm,LetterNum('S'));
  Unload_Semantic(vm,LetterNum('T'));
  Unload_Semantic(vm,LetterNum('U'));
  Unload_Semantic(vm,LetterNum('W'));
  Unload_Semantic(vm,LetterNum('Y'));
  free(pstack);
}
void ccall(VM * vm){
  /* Figure out Return Type */
  INT return_type_i=Pop(vm);
  ffi_type * return_type;
  switch(return_type_i){
    case 0:
      return_type=&ffi_type_uint32;
      break;
    case 1:
      return_type=&ffi_type_pointer;
    break;
    default:
      return_type=&ffi_type_void;
      break;
  }
  
  /* get the types (funge/pointer) of all the arguments */
  INT len=Pop(vm); /* Amount of arguments */
  ffi_type ** argtypes=alloca(len*sizeof(ffi_type*)); 
  {
  signed long long lensave=len;
  int count=0;
  /* set argument to pointer if pointer and uint32 if funge */
  while(lensave>0){	
    /* Get (part of if over 32 arguments) the bitmask for the arguments*/
    INT cur=Pop(vm); 
    for (int i=0; i<sizeof(INT)*8&&lensave>0; i++){
      if (cur&1){
        argtypes[count]=&ffi_type_pointer;
      } else {
        argtypes[count]=&ffi_type_uint32;
      }
      cur>>=1;
      count++;
     lensave--;
    }
    }
  }
  /* pop the arguments from the correct stack based on the bitmask */
  void ** arguments=alloca(len*sizeof(void *));
  {
    for (int i=0; i<len; i++){
      if(argtypes[i]==&ffi_type_uint32){
        INT * p=arguments[i]=alloca(sizeof(INT *));
        *p=Pop(vm);
      }else if(argtypes[i]==&ffi_type_pointer){
        void ** p=arguments[i]=alloca(sizeof(void *));
        *p=popp();
      } else {
        fprintf(stderr, "This isn't supposed to happen\n");
        exit(3);
      }
    }
  }
  /* Pop Function Pointer */
  void (*func)(void)=popp();
  ffi_cif cif;
  void * return_value=alloca(16); /* CFFI doesn't support raw structs the biggest data type would be 8 bytes, but I am allocating 16 for good measure */
  
  /* Call the function using libffi */
  ffi_prep_cif(&cif,FFI_DEFAULT_ABI, len, return_type, argtypes);
  ffi_call(&cif,func,return_value,arguments);

  /* Push the return value to the correct stack based on the return value */
  switch(return_type_i){
    case 0:
    //return_type=&ffi_type_uint32;
      Push(vm,*(INT*)return_value);
    break;
    case 1:
      //return_type=&ffi_type_pointer;
      pushp(*(void**)return_value);
    break;
  }
}
void Do_CFFI(VM* vm,int Cmd)
{
  int cip;
  cip = vm->cip;
  switch (Cmd) {
      case EX_CFFI+LetterNum('B'):
      {
        char * str=popp();
        INT index=Pop(vm);
        Push(vm,str[index]);
      }
      break;


      case EX_CFFI+LetterNum('C'):
      ccall(vm);
      break;
      case EX_CFFI+LetterNum('D'):
        pushp(pstack[stack_ptr-1]);
      break;
      case EX_CFFI+LetterNum('F'):
      free(popp());
      break;

      case EX_CFFI+LetterNum('G'):
      {
        uint64_t ptr=(uint64_t)popp();
        INT high=(INT)(ptr/(1L<<32));
        INT low=(INT)(ptr%(1L<<32));
        Push(vm, high); Push(vm,low);
      }
    
      break;
      case EX_CFFI+LetterNum('I'):
      popp();
      break;
      case EX_CFFI+LetterNum('L'):
      {
        char * libname=popp();
        void * library=dlopen(libname,RTLD_LAZY);
        if (!library){
          Reflect(vm);
        } else {
          pushp(library);
        }

      }
      break;
      case EX_CFFI+LetterNum('M'):
      {
        INT len=Pop(vm);
        INT * arr=malloc(sizeof(INT)*sizeof(len));
        for (int i=0; i<len; i++){
          arr[i]=Pop(vm);
        }
        pushp(arr);


      }
      break;
      case EX_CFFI+LetterNum('O'):
      {
      	for (int i=stack_ptr-1; i>=0; i--){
      	   if (pstack[i]){
      	   	printf("%d: %lx (First Word is %d)\n",i, pstack[i],*(INT *)(pstack[i]));
      	   } else {
      	   	printf("%d: NULL\n",i);
      	   }
      	}
      	printf("\n");
      }
      break;
      case EX_CFFI+LetterNum('P'):
      {
        INT low=Pop(vm);
        INT high=Pop(vm);
        uint64_t ptr=(((uint64_t)(uint32_t)high)<<32)|((uint32_t)low);
        pushp((void*)ptr);
      }
      break;
      case EX_CFFI+LetterNum('S'):
      {
        char * str=malloc(512*sizeof(char));
        int i=0;
        char c;
        do{

          c=(char)Pop(vm);
          str[i]=c;
          i++;
          if (i%512==0){
            str=realloc(str,(i+512)*sizeof(char));
          }
          

        } while(c);
        str=realloc(str, i+1);
        pushp(str);
        
        
      }
      break;

      case EX_CFFI+LetterNum('T'):
      {
        char * token_name=popp();
        void * library=popp();
        dlerror();
        void * token=dlsym(library,token_name);
        if (dlerror()){
          Reflect(vm);
        } else {
          pushp(token);
        }
      }
      break;

      case EX_CFFI+LetterNum('U'):
      if(dlclose(popp())){
        Reflect(vm);
      }
      break;
      case EX_CFFI+LetterNum('W'):
      {
        INT index=Pop(vm);
        INT * arr=popp();
        Push(vm,arr[index]);
      }
      break;
      case EX_CFFI+LetterNum('Y'):
      {
        void * ptr1=popp();
        void * ptr2=popp();
        pushp(ptr1);
        pushp(ptr2);
      }
      break;

  }
}
#endif



