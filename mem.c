/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "funge.h"

/* ************************************************************************* */
/* ***** Function to find limits of non-space cells, used by y command ***** */
/* ************************************************************************* */
/* FIXME - This routine is a hack, it works but there should be a faster way */
void Find_Limits(VM* vm,INT* minX,INT* minY,INT* maxX,INT* maxY) {
  int i,j;
  *minX = 99999;
  *minY = 99999;
  *maxX = -99999;
  *maxY = -99999;
  for (i=0; i<vm->NumRows; i++)
    for (j=0; j<vm->dFspace[i].NumCells; j++)
      if (vm->dFspace[i].Cells[j].v != 32) {
        if (vm->dFspace[i].Row < *minY) *minY = vm->dFspace[i].Row;
        if (vm->dFspace[i].Row > *maxY) *maxY = vm->dFspace[i].Row;
        if (vm->dFspace[i].Cells[j].x < *minX) *minX = vm->dFspace[i].Cells[j].x;
        if (vm->dFspace[i].Cells[j].x > *maxX) *maxX = vm->dFspace[i].Cells[j].x;
        }
  }

/* *********************************************** */
/* ***** Searches for a row in dynamic model ***** */
/* *********************************************** */
INT Find_Row(VM* vm,INT y,INT z)
{
  int st,en,cr;
  if (vm->NumRows == 0) return -1;
  st = 0;
  en = vm->NumRows - 1;
  cr = st+((en-st)/2);
  while ((en-st)>1) {
    if (vm->dFspace[cr].Row==y && vm->dFspace[cr].z==z) {
       return cr;
       }
    if (vm->dFspace[cr].z < z || 
        (vm->dFspace[cr].z==z && vm->dFspace[cr].Row<y)) {
      st = cr;
      cr = st+((en-st)/2);
      }
    else {
      en = cr;
      cr = st+((en-st)/2);
      }
    }
  if (vm->dFspace[st].Row==y && vm->dFspace[st].z==z) return st;
  if (vm->dFspace[en].Row==y && vm->dFspace[en].z==z) return en;
  return -1;
}

/* ****************************************** */
/* ***** Add new row into dynamic model ***** */
/* ****************************************** */
INT Add_Row(VM* vm,INT y,INT z) {
  INT i,j;
  i=0;
  while (i<vm->NumRows && (vm->dFspace[i].z<z || (vm->dFspace[i].z==z && vm->dFspace[i].Row<y)))
    i++;
  vm->NumRows++;
  if (vm->NumRows == 1) vm->dFspace=(ROWS*)malloc(sizeof(ROWS));
    else vm->dFspace=(ROWS*)realloc(vm->dFspace,sizeof(ROWS)*vm->NumRows);
  if (vm->dFspace == NULL) {
    printf("Could not increase cells in dFspace\n");
    exit(1);
    }
  for (j=vm->NumRows-1;j>i;j--) vm->dFspace[j]=vm->dFspace[j-1];
  vm->dFspace[i].Row=y;
  vm->dFspace[i].z=z;
  vm->dFspace[i].Min=0;
  vm->dFspace[i].Max=0;
  vm->dFspace[i].Cells = NULL;
  vm->dFspace[i].NumCells = 0;
  return i;
}

/* *************************************** */
/* ***** Function to add cell to row ***** */
/* *************************************** */
INT Add_Cell(VM* vm,INT row,INT x,INT y,INT z)
{
  INT i;
  long int addr;
  if (x<vm->dFspace[row].Min) vm->dFspace[row].Min=x;
  if (x>vm->dFspace[row].Max) vm->dFspace[row].Max=x;
  addr=0;
  while (addr<vm->dFspace[row].NumCells && vm->dFspace[row].Cells[addr].x<x)
     addr++;
  vm->dFspace[row].NumCells++;
  if (vm->dFspace[row].NumCells == 1)
    vm->dFspace[row].Cells=(CELL*)malloc(sizeof(CELL));
  else
    vm->dFspace[row].Cells=(CELL*)realloc(vm->dFspace[row].Cells,
      sizeof(CELL)*vm->dFspace[row].NumCells);
  if (vm->dFspace[row].Cells == NULL) {
    printf("Could not allocate memory for additional cells\n");
    exit(-1);
    }
  for (i=vm->dFspace[row].NumCells-1;i>addr;i--)
    vm->dFspace[row].Cells[i] = vm->dFspace[row].Cells[i-1];
  vm->dFspace[row].Cells[addr].x=x;
  return addr;
}

/* ************************************* */
/* ***** Get value from fungespace ***** */
/* ************************************* */
INT Get_Funge(VM* vm,INT x,INT y,INT z)
{
  INT i;
  long int addr;
  int st,en,cr;
  x += vm->IPs[vm->cip].OffsetX;
  y += vm->IPs[vm->cip].OffsetY;
  z += vm->IPs[vm->cip].OffsetZ;
  if (vm->MapScreen==1 && x>=0 && x<80 && y>=0 && y<25) {
    GotoXY(x+1,y+1);
    }
  i=Find_Row(vm,y,z);
  if (i==-1) return 32;
    st = 0;
    en = vm->dFspace[i].NumCells - 1;
    cr = st+((en-st)/2);
    while ((en-st)>1) {
      if (vm->dFspace[i].Cells[cr].x==x) return vm->dFspace[i].Cells[cr].v;
      if (vm->dFspace[i].Cells[cr].x < x) {
        st = cr;
        cr = st+((en-st)/2);
        }
      else {
        en = cr;
        cr = st+((en-st)/2);
        }
      }
    if (vm->dFspace[i].Cells[st].x==x) return vm->dFspace[i].Cells[st].v;
    if (vm->dFspace[i].Cells[en].x==x) return vm->dFspace[i].Cells[en].v;
    return 32;
}

/* ************************************** */
/* ***** Put value into Funge-Space ***** */
/* ************************************** */
void Put_Funge(VM* vm,INT x,INT y,INT z,INT value) {
  INT i;
  long int addr;
  if (vm->cip >=0) {
    x += vm->IPs[vm->cip].OffsetX;
    y += vm->IPs[vm->cip].OffsetY;
    z += vm->IPs[vm->cip].OffsetZ;
    }
  if (vm->MapScreen==1 && x>=0 && x<80 && y>=0 && y<25 && value>31 && value<127) {
    GotoXY(x+1,y+1); printf("%c",(char)value);
    }
    if (x>vm->XDim) vm->XDim=x;
    if (x<vm->XMin) vm->XMin=x;
    if (y>vm->YDim) vm->YDim=y;
    if (y<vm->YMin) vm->YMin=y;
    if (z>vm->ZDim) vm->ZDim=z;
    if (z<vm->ZMin) vm->ZMin=z;
    i=Find_Row(vm,y,z);
    if (i==-1) {
      i=Add_Row(vm,y,z);
      addr=Add_Cell(vm,i,x,y,z);
      vm->dFspace[i].Cells[addr].v = value;
      }

    addr = 0;
    while (addr < vm->dFspace[i].NumCells) {
      if (x==vm->dFspace[i].Cells[addr].x) {
        vm->dFspace[i].Cells[addr].v = value;
        return;
        }
      addr++;
      }
    addr=Add_Cell(vm,i,x,y,z);
    vm->dFspace[i].Cells[addr].v = value;
}

void Reset_VM(VM* vm) {
  int InFile;
  int i;
    if (vm->dFspace != NULL) {
      for (i=0; i<vm->NumRows; i++) {
        if (vm->dFspace[i].Cells != NULL) free(vm->dFspace[i].Cells);
        }
      if (vm->dFspace != NULL) free(vm->dFspace);
      vm->dFspace = NULL;
      vm->NumRows = 0;
      }
    if (vm->isDynamic == 'Y') {
      if ((InFile=open(vm->ProgName,O_RDONLY))!=-1) {
        Load_Fingerprint_File(vm,InFile,NULL,0);
        } else printf("Could not reload fingerprint %s\n",vm->ProgName);
      }
    else {
      Load_File(vm,vm->ProgName,0,0,0);
      }
  }

void Clear_Fs(VM* vm)
{
    vm->dFspace = NULL;
    vm->NumRows = 0;
}


/* ***************************************************** */
/* ***** Get cell where the current IP is pointing ***** */
/* ***************************************************** */
INT Get_Cell(VM* vm)
{
  INT v;
  v=Get_Funge(vm,vm->IPs[vm->cip].x-vm->IPs[vm->cip].OffsetX,
                 vm->IPs[vm->cip].y-vm->IPs[vm->cip].OffsetY,
                 vm->IPs[vm->cip].z-vm->IPs[vm->cip].OffsetZ);
  return v;
}


/* *************************************************** */
/* ***** Check to see if ip needs to wrap around ***** */
/* *************************************************** */
void Check_Wrap(VM* vm,int dir) {
  int cip;
  cip = vm->cip;
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  /* +++++ See if ip went beyond defined fungespace +++++ */
  /* ++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  if (vm->IPs[cip].x>vm->XDim ||
      vm->IPs[cip].x<vm->XMin ||
      vm->IPs[cip].y>vm->YDim ||
      vm->IPs[cip].y<vm->YMin ||
      vm->IPs[cip].z>vm->ZDim ||
      vm->IPs[cip].z<vm->ZMin) {
    /* +++++++++++++++++++++++++++++++++++++++++ */
    /* +++++ Back IP back into funge-space +++++ */
    /* +++++++++++++++++++++++++++++++++++++++++ */
    while (vm->IPs[cip].x>vm->XDim || vm->IPs[cip].x<vm->XMin ||
           vm->IPs[cip].y>vm->YDim || vm->IPs[cip].y<vm->YMin ||
           vm->IPs[cip].z>vm->ZDim || vm->IPs[cip].z<vm->ZMin) {
      vm->IPs[cip].x -= vm->IPs[cip].DeltaX*dir;
      vm->IPs[cip].y -= vm->IPs[cip].DeltaY*dir;
      vm->IPs[cip].z -= vm->IPs[cip].DeltaZ*dir;
      }
    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    /* +++++ Now back through funge-space til other side +++++ */
    /* +++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    while (vm->IPs[cip].x<=vm->XDim && vm->IPs[cip].x>=vm->XMin &&
           vm->IPs[cip].y<=vm->YDim && vm->IPs[cip].y>=vm->YMin &&
           vm->IPs[cip].z<=vm->ZDim && vm->IPs[cip].z>=vm->ZMin) {
      vm->IPs[cip].x -= vm->IPs[cip].DeltaX*dir;
      vm->IPs[cip].y -= vm->IPs[cip].DeltaY*dir;
      vm->IPs[cip].z -= vm->IPs[cip].DeltaZ*dir;
      }
    vm->IPs[cip].x += vm->IPs[cip].DeltaX*dir;
    vm->IPs[cip].y += vm->IPs[cip].DeltaY*dir;
    vm->IPs[cip].z += vm->IPs[cip].DeltaZ*dir;
    }
  }
