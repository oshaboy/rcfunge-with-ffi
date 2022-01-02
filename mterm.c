/*
 *******************************************************************
 *** This software is copyright 1998-2008 by Michael H Riley     ***
 *** You have permission to use, modify, copy, and distribute    ***
 *** this software so long as this copyright notice is retained. ***
 *** This software may not be used in commercial applications    ***
 *** without express written permission from the author.         ***
 *******************************************************************
*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>

void Output(char* Buffer)
{
  printf("%s",Buffer);
}

void Input(char* Buffer)
{
  Buffer[0]='\0';
  gets(Buffer);
}

void ClrScr()
{
  Output("\E[H\E[2J");
}

void ClrEos()
{
  Output("\E[J");
}

void ClrEol()
{
  Output("\E[K");
}

void Delay(int sec)
{
  sleep(sec);
}

void GotoXY(int x,int y)
{
  char XBuffer[10];
  char YBuffer[10];
  char Buffer[20];
  sprintf(XBuffer,"%d",x+1);
  sprintf(YBuffer,"%d",y+1);
  strcpy(Buffer,"\E["); strcat(Buffer,YBuffer); strcat(Buffer,";");
  strcat(Buffer,XBuffer); strcat(Buffer,"H");
  Output(Buffer);
}

void CursorDown(int num)
{
  int i;
  for (i=0;i<num;i++) Output("\E[B");
}

void CursorUp(int num)
{
  int i;
  for (i=0;i<num;i++) Output("\E[A");
}
