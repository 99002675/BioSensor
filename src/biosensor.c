#include "biosensor.h"
#include <stdio.h>
#include <stdlib.h>
#include<stdio.h>
int TotalMem=60;        //Initial Memory
int wirelen=2;          //Wire length of product
void TempAlert(int TempInCel)        //Temperature Alert
{
    if(TempInCel>=40)
    {
    printf("High is Temperature= %d\n",TempInCel);
    }
    else
    {
    printf("low is Temperature= %d\n",TempInCel);
    }
}
void PulseAleart(int pulse){          //Pulse Alert to patient
    if(pulse>65)
        {
        printf("pulse is high %d\n ",pulse);
       }
       else
       {
        printf("pulse is low %d\n ",pulse);
       }
}
void BloodPressureAlert(int sis, int dis){      //Blood Pressure Alert to patient
if(sis>=130 || dis>=89){
    printf("Blood pressure is high sis=%d and dis=%d\n",sis,dis);
}
else
    {
   printf("Blood pressure is low sis=%d and dis=%d\n",sis,dis);
}
}
void BaudRateAlert(int baudrate)        //Baud rate identification
{
    if(baudrate<9600)
    {
    printf("Baudrate is less than 9600\n");
    }
else if(baudrate>9600)
{
  printf("Baudrate is Greater than 9600\n");
}
else if(baudrate<0)
{
  printf("Baudrate cannot be negative\n");
}
}
void LCDOutput(int pulse,int sis,int dia,int TempInFar, long int baudrate)
{
      printf(" pulse=%d\n sis=%d\n dia=%d\n TempInFar=%d\n baudrate=%ld\n",pulse,sis,dia,TempInFar,baudrate);
}
int TemperatureInFar(int TempInCel )
{
    if(TempInCel>=34 && TempInCel<=44)
    {
       int far=((TempInCel/5)*9)+32;
       return far;
    }
    else if(TempInCel<33 ||TempInCel>44 )
    {
        TempAlert(TempInCel);
        return 0;
    }
    else
        return 0;
}
void write()                                //Write data to the output
{
   char ch;
   FILE *source, *target;
   source = fopen("re.txt", "r");
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
   target = fopen("we.txt", "w");
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }

   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
   fclose(source);
   fclose(target);
}
void pulsecheck(int pulse)
{
if(pulse>=62 && pulse<=65){}
else
    PulseAleart(pulse);
}
void BloodPressureCheck(int sis,int dia)
{
if((sis<120 && sis >=60) &&(dia< 80 && dia>=45))
    {
    }
else if(sis >=120 || dia >=80)
 BloodPressureAlert(sis,dia);
}
int  biosensorMem()
{
if (TotalMem==60)
    return 60;
else
    return 0;
}
int  WireLength(){
if (wirelen==2)
    return 2;
else
    return 0;
}
int biosensor(int suply,int pulse,int sis,int dia,int TempInCel, long int baudrate )
{
 if(suply>=5 || suply<=16)
 {
  if(baudrate==9600)
  {
     int TemInFar=TemperatureInFar(TempInCel);
     pulsecheck(pulse);
     BloodPressureCheck(sis,dia);
     LCDOutput(pulse,sis,dia,TemInFar,baudrate);
     write();
     return 1;
   }
else if(baudrate<9600 )
{
      BaudRateAlert(baudrate);
      write();
      return 0;
}
else if(baudrate>9600 )
{
    BaudRateAlert(baudrate);
    return 0;
}
else if(baudrate<0)
{
    BaudRateAlert(baudrate);
}
}
else if(suply>16)
{
    printf("\nSupply voltage is very high");
    return 0;
}
else if(suply<5)
{
    printf("\nSupply voltage is very low");
    return 0;
}
else if(suply<0)
{
    printf("\nNegative Supply voltage ");
    return 0;
}
    return 0;
}
