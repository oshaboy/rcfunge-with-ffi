#include "funge.h"

INT FP_Load_File(VM* vm,char *FName)
{
  INT x,y,z;
  int count;
  char lineEnd;
  int InFile;
  char *Ptr;
  char Buffer[1000];
  lineEnd = 0;
  x=0; y=0; z=0;
  vm->LargestX=0; vm->LargestY=0; vm->LargestZ=0;
  InFile=open(FName,O_RDONLY);
  if (InFile != -1) {
    while ((count=read(InFile,Buffer,1000)) > 0) {
      Ptr=Buffer;
      while (count > 0) {
        if (*Ptr == 12) {
          z++;
          x = 0;
          y = 0;
          }
        else if (*Ptr == 10 || *Ptr == 13) {
          if (lineEnd == 0) lineEnd = *Ptr;
          if (*Ptr == lineEnd && lineEnd != 0) {
            y++;
            x = 0;
            }
          }
        else {
          if (x>vm->LargestX) vm->LargestX=x;
          if (y>vm->LargestY) vm->LargestY=y;
          if (z>vm->LargestZ) vm->LargestZ=z;
          if (*Ptr != ' ') Put_Funge(vm,x++,y,z,*Ptr);
            else x++;
          }
        Ptr++;
        count--;
        }
      }
    vm->LargestX=vm->LargestX-0+1;
    vm->LargestY=vm->LargestY-0+1;
    vm->LargestZ=vm->LargestZ-0+1;
    return 1;
    }
  else return 0;
}

