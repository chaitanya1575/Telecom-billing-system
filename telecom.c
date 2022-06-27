#include<stdio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>
struct subscriber
{
char phonenumber[20];
char name[50];
float amount;
}s;
void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();
void searchrecords();
void payment(); char
get; int main()
{
int phonenumber;
char choice;
while (1)
{
system("cls");
printf("\n **********************************************"); printf("\n
**** TELEPHONE BILLING MANAGEMENT SYSTEM ****"); printf("\n
***********************************************");
printf("\n"); printf("\n\t A : Adding new records.\n \t L : Listing of
records"); printf("\n\t M : Modifying records.\n \t P : Payments");
printf("\n\t S : Searching records."); printf("\n\t D : Deleting
records.\n\t E : Exit Program\n"); printf("\n");
printf("\n\t PLEASE SELECT THE LETTERS ONLY " );
choice=getche();
choice=toupper(choice);
switch(choice)
{
case 'P':
payment();break;
case 'A' :
addrecords();break;
case 'L' :
listrecords();break;
case 'M':
modifyrecords();break;
case 'S' :
searchrecords();break; case
'D': deleterecords();break;
case 'E':
system("cls"); printf("\n\n\t\t\t\tTHANK YOU");
printf("\n\n\n\n\n:\n\tFOR USING OUR
SERVICE"); Sleep(2000); exit(0); break;
default:
system("cls"); printf("Incorrect
Input"); printf("\nAny key to
continue"); getch();
}
}
}
void addrecords()
{
FILE *f;
char test;
f=fopen("data.dat","ab+");
if(f==0)
{ f=fopen("data.dat","wb+"); system("cls"); printf("please wait
while we configure your computer"); printf("/npress any
key to continue");
getch();
}
while(1)
{
system("cls");
printf("\n Enter phone number:");
scanf("%s",&s.phonenumber);
printf("\n Enter name:");
fflush(stdin);
scanf("%[^\n]",&s.name); printf("\n
Enter amount:");
scanf("%f",&s.amount);
fwrite(&s,sizeof(s),1,f); fflush(stdin);
system("cls"); printf("1 record
successfully added"); printf("\n Press
esc key to exit, any other key to add
other record:"); test=getche();
if(test==27)
break;
}
fclose(f);
}
void listrecords()
{
FILE *f;
int i;
if((f=fopen("data.dat","rb"))==NULL)
exit(0); system("cls"); printf("Phone
Number\t\tUser Name\t\t\tAmount\n");
for(i=0;i<79;i++)
printf("-");
while(fread(&s,sizeof(s),1,f)==1)
{
printf("\n%-10s\t\t%-20s\t\t $. %.2f /-",s.phonenumber,s.name,s.amount);
}
printf("\n");
for(i=0;i<79;i++)
printf("-");
fclose(f); getch();
}
void deleterecords()
{
FILE *f,*t; int
i=1;
char phonenumber[20];
if((t=fopen("temp.dat","w+"))==NULL)
exit(0);
if((f=fopen("data.dat","rb"))==NULL)
exit(0);
system("cls");
printf("Enter the phone number to be deleted from the
Database"); fflush(stdin); scanf("%[^\n]",phonenumber);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{ i=0;
continue;
}
else
fwrite(&s,sizeof(s),1,t);
}
if(i==1)
{ system("cls");
printf("Phone number %s not
found",phonenumber); remove("data.dat");
rename("temp.dat","data.dat"); getch(); fclose(f);
fclose(t); main();
}
remove("data.dat"); rename("temp.dat","file.dat");
system("cls"); printf("The Number %s Successfully
Deleted!!!!",phonenumber);
fclose(f);
fclose(t);
getch();
}
void searchrecords()
{
FILE *f;
char phonenumber[20];
int flag=1;
f=fopen("data.dat","rb+");
if(f==0)
exit(0);
fflush(stdin); system("cls"); printf("Enter Phone Number
to search in our database"); scanf("%s", phonenumber);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{ system("cls");
printf(" Record Found ");
printf("\n\nPhonenumber: %s\nName: %s\nAmount: $
%0.2f\n",s.phonenumber,s.name,s.amount);
flag=0; break;
}
else if(flag==1)
{ system("cls");
printf("Requested Phone Number Not found in our database");
}
}
getch(); fclose(f);
}
void modifyrecords()
{
FILE *f;
char phonenumber[20];
long int size=sizeof(s);
if((f=fopen("data.dat","rb+"))==NULL)
exit(0);
system("cls");
printf("Enter phone number of the subscriber to modify:");
scanf("%[^\n]",phonenumber);
fflush(stdin);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{
system("cls");
printf("\n Enter phone number:");
scanf("%s",&s.phonenumber);
printf("\n Enter name: ");
fflush(stdin);
scanf("%[^\n]",&s.name);
printf("\n Enter amount: ");
scanf("%f",&s.amount); fseek(f,-
size,SEEK_CUR);
fwrite(&s,sizeof(s),1,f); break;
}
}
fclose(f);
}
void payment()
{
FILE *f;
char phonenumber[20];
long int size=sizeof(s); float
amt;
int i;
if((f=fopen("data.dat","rb+"))==NULL) exit(0); system("cls");
printf("Enter phone number of the subscriber for
payment"); scanf("%[^\n]",phonenumber);
fflush(stdin);
while(fread(&s,sizeof(s),1,f)==1)
{
if(strcmp(s.phonenumber,phonenumber)==0)
{
system("cls");
printf("\n Phone No.: %s",s.phonenumber);
printf("\n Name: %s",s.name); printf("\n
Current amount: %f",s.amount);
printf("\n");
for(i=0;i<79;i++)
printf("-");
printf("\n\nEnter amount of payment :");
fflush(stdin); scanf(" %f",&amt);
s.amount=(amt-s.amount);
fseek(f,-size,SEEK_CUR);
fwrite(&s,sizeof(s),1,f);
break;
}
}
system("cls");
printf("THANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
getch(); fclose(f);
}