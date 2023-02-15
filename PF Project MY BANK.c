#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>
int i;
int AccNo;
char Password[12];
struct CreateAcc
{
	char Name[20];
	char FName[20];
	char CNIC[20];
	char Number[20];
	char Date[15];
	char Type[20];
	char Purpose[100];
	char Tenure[10];
	float  ReqAmount;
	float  Min;
	int  AccNo;
	char Password[12];
}C;
char Choice;
int Size=sizeof(C);
void CreAcc(void)
{
	srand(time(0));
	FILE *fptr;
	fptr=fopen("MyAccount.txt","a+");
	if(fptr==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
	printf("\t\t\t\tCREATING ACCOUNT\n");
	printf("Dear Customer\nPlease Enter Your Details\n");
	printf("Name: ");
	gets(C.Name);
	printf("FatherName: ");
	gets(C.FName);
	fflush(stdin);
	for(int i=0;i<15;i++)
	{
	printf("CNIC Number(XXXXX-XXXXXXX-X): ");
	scanf("%s",C.CNIC);
	fflush(stdin);
    i=strlen(C.CNIC);
    if(i<15||i>15)
    {
    	printf("Invalid CNIC Number\n");
    	printf("Please Enter CNIC Number\n");
    	i=0;
	}
    }
    for(int j=0;j<12;j++)
    {
	printf("Phone Number(XXXX-XXXXXXX): ");
	scanf("%s",C.Number);
	fflush(stdin);
	j=strlen(C.Number);
	if(j<12||j>12)
	{
		printf("InValid Number\n");
		printf("Please Enter Correct Phone Number\n");
		j=0;
	}
    }
    printf("Date Of Birth(D-M-Y): ");
	gets(C.Date);
	fflush(stdin);
	printf("AccountType: ");
	gets(C.Type);
	fflush(stdin);
	printf("Please Enter The Mininum Ammount You Want To keep In You Account\n");
	do
	{
	i=0;
	printf("Minimum Amount(>1000): ");
	scanf("%f",&C.Min);
	fflush(stdin);
	i++;
	if(C.Min<1000)
	{
		printf("This Amount Does Not Meet The Minimum Requirement\n");
		i=0;
	}
	}while(i==0);
	printf("Please Enter Your Password of Atleast 8 Characters By Which You Can Access Your Account\n");
	for(int k=0;k<8;k++)
{
	  printf("Password: ");
	  gets(C.Password);
	  fflush(stdin);
	  k=strlen(C.Password);
	if(k<8)
	{
		printf("Invalid Password\n");
		printf("Please Enter Password of 8 Characters\n");
		k=0;
	}
}
    printf("Do You Want To Continue(Y/N)\n");
    scanf("%c",&Choice);
    fflush(stdin);
    if(Choice=='N'||Choice=='n')
    {
    	main();
	}
	C.AccNo=100+rand();
	printf("Dear Customer Your Account Has Sucessfully Been Created\n");
	printf("Account Number: %d",C.AccNo);
	fwrite(&C,sizeof(C),1,fptr);
	fclose(fptr);
	printf("\n");
	getch();
}

void Dpst(void)
{
	AccDet();
	i=1;
	FILE *fptr;
	fptr=fopen("MyAccount.txt","r+");
	if(fptr==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
while(fread(&C,sizeof(C),1,fptr))
    {
        i=strcmp(C.Password,Password);
        if(AccNo==C.AccNo && i==0)
        {
        	float Bal=0.00;
        	printf("\n\t\t\tDEPOSIT\n");
			printf("Deposit Account:\n");
			scanf("%f",&Bal);
			fflush(stdin);
			printf("Do You Want To Continue(Y/N)\n");
            scanf("%c",&Choice);
            fflush(stdin);
            if(Choice=='N'||Choice=='n')
            {
    	        main();
	        }
	        else
	        {
	        C.Min=C.Min+Bal;
			fseek(fptr,-(Size),SEEK_CUR);
			fwrite(&C,sizeof(C),1,fptr);
			printf("Amount Deposited Sucessfully\n");
			break;
		    }
    }
}
       if(i!=0)
	   {
	       printf("No Such Record Found!");	
	   } 
	   fclose(fptr);
        getch();
}
void Wid(void)
{
	AccDet();
	FILE *fptr;
	fptr=fopen("MyAccount.txt","r+");
	if(fptr==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
while(fread(&C,sizeof(C),1,fptr))
    {
        i=strcmp(C.Password,Password);
        if(AccNo == C.AccNo && i==0)
        {
          	float Bal=0;
            printf("\n\t\t\tWITHDRAW\n");
	    do    
	    {
			printf("Account\n");
			scanf("%f",&Bal);
			fflush(stdin);
			if(Bal>C.Min || C.Min-Bal<15)
			{
				printf("Amount Exceeds Current Balance\n");
				i=1;
			}
			else
			{
			   i=0;
			   printf("Do You Want To Continue(Y/N)\n");
               scanf("%c",&Choice);
               fflush(stdin);
               if(Choice=='N'||Choice=='n')
               {
    	            main();
	           }
	           else
	           {
			   C.Min=C.Min-Bal;
			   fseek(fptr,-(Size),SEEK_CUR);
			   fwrite(&C,sizeof(C),1,fptr);
			   printf("Amonut Sucessfully Withdrawn");
			   fclose(fptr);
               }
            }
        }while(i!=0);
    }
}       if(i!=0)
        {
        	printf("No Such Record Found\n");
		}   
        getch();
}
void ModAcc(void)
{
	AccDet();
	char Ch;
	i=1;
	FILE *fptr;
    fptr=fopen("MyAccount.txt","r+");
    if(fptr==NULL)
    {
        printf("Unable To Open File");
        exit(1);
	}
while(fread(&C,sizeof(C),1,fptr))
{
   i=strcmp(C.Password,Password);
  if(C.AccNo==AccNo && i==0)
  {	
    printf("\n\t\t\tNEW DETAILS\n"); 
    printf("Do You want To Change Your Name[Y/N]\n");
    scanf("%c",&Ch);
    fflush(stdin);
    if(Ch=='Y'||Ch=='y')
    {
    	printf("New Name: ");
	    gets(C.Name);
	}
    printf("Do You want To Change Your Phone Number[Y/N]\n");
    scanf("%c",&Ch);
    fflush(stdin);
    if(Ch=='Y'||Ch=='y')
    {
	   for(int j=0;j<=12;j++)
       {
	     printf("New Phone Number(XXXX-XXXXXXX): ");
	     scanf("%s",C.Number);
	     fflush(stdin);
	     j=strlen(C.Number);
	    if(j<12)
	     {
		   printf("InValid Number\n");
		   printf("Please Enter Correct Phone Number\n");
	       j=0;
	     }
       }
	}
    printf("Do You want To Change Your Password[Y/N]\n");
    scanf("%c",&Ch);
    fflush(stdin);
    if(Ch=='Y'||Ch=='y')
    {
        printf("Please Enter Your Password of 8 Characters By Which You Can Access Your Account\n");
	    for(int k=0;k<8;k++)
       {
	      printf("New Password: ");
	      gets(C.Password);
	      fflush(stdin);
	      k=strlen(C.Password);
	      if(k<8)
	       {
		      printf("Invalid Password\n");
		      printf("Please Enter Password of 8 Characters\n");
		       k=0;
	       }
        }	
     }
          printf("Do You want To Change Your Date Of Birth[Y/N]\n");
          scanf("%c",&Ch);
          fflush(stdin);
          if(Ch=='Y'||Ch=='y')
           {
		     printf("Date Of Birth: ");
	         gets(C.Date);
	       }
	        printf("Do You Want To Continue(Y/N)\n");
            scanf("%c",&Choice);
            if(Choice=='N'||Choice=='n')
            {
    	        main();
	        }
	        else
	       {
	       fseek(fptr,-Size,SEEK_CUR);
		   fwrite(&C,sizeof(C),1,fptr);
		   printf("Record Sucessfully Updated\n");
		   break; 
           }
       }
   }
        if(i!=0)
        {
        	printf("No Such Record Found\n");
		}
        fclose(fptr);    
	    getch();
}
void Del()
{
	FILE *fptr,*ft;
	int i=1;
	fptr=fopen("MyAccount.txt","r");
	if(fptr==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
	ft=fopen("Temperory.txt","w");
	if(ft==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
	printf("\t\t\tDELETING RECORD\n");
	printf("Accont Number:");
	scanf("%d",&AccNo);
	fflush(stdin);
	printf("Password:");
	scanf("%s",Password);
	fflush(stdin);
	while(fread(&C,sizeof(C),1,fptr))
	{
		i=strcmp(Password,C.Password);
		if(AccNo!=C.AccNo && i!=0)
		{
			fwrite(&C,sizeof(C),1,ft);
		}
	}
	fclose(fptr);
	fclose(ft);
	printf("Do You Want To Continue(Y/N)\n");
    scanf("%c",&Choice);
    if(Choice=='N'||Choice=='n')
    {
        main();
	}
	printf("Account Sucessfully Deleted\n");
	remove("MyAccount.txt");
	rename("Temperory.txt","MyAccount.txt");
	getch();	
	
}
void AccDet(void)
{
    i=0; 
	FILE *fptr;
	fptr=fopen("MyAccount.txt","r");
	if(fptr==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
	printf("\t\t\t\tLOGIN ACCOUNT\n");
	printf("Account Number: ");
	scanf("%d",&AccNo);
	fflush(stdin);
	printf("Password:");
    gets(Password);
	fflush(stdin);
while(fread(&C,sizeof(C),1,fptr))
{
	i=strcmp(C.Password,Password);
	if(AccNo==C.AccNo && i==0)
  {
    system("cls");
	printf("\t\t\tACCOUNT DETAILS\n");
	printf("Name: %s\n",C.Name);
	printf("Father Name: %s\n",C.FName);
	printf("CNIC Number: %s\n",C.CNIC);
	printf("Phone Number: %s\n",C.Number);
	printf("Date Of Birth: %s\n",C.Date);
	printf("Account Type= %s\n",C.Type);
	printf("Balance: %f\n",C.Min);
	printf("Password: %s",C.Password);
	break;
  }
}
  	  fclose(fptr);
  	  if(i!=0)
 	  printf("No Such Record Found!");
 	  printf("\n");
 	  getch();
}
void AccLst()
{
	FILE *fptr;
	fptr=fopen("MyAccount.txt","r");
    printf("\t\t\tACCOUNT HOLDERS LIST\n");
	printf("Name's\t\tAccontNumbers\n");	
	while(fread(&C,sizeof(C),1,fptr))
	{
		printf("%s\t\t%d\n",C.Name,C.AccNo);
	}
	fclose(fptr);
	getch();
}
int loan()
{
	FILE *fp;
	fp=fopen("MyAccount.txt","r+");
	if(fp==NULL)
	{
		printf("Unable To Open File");
		exit(1);
	}
	printf("\t\t\t\tLOGIN ACCOUNT\n");
	printf("Account Number: ");
	scanf("%d",&AccNo);
	fflush(stdin);
	printf("Password: ");
	gets(Password);
	fflush(stdin);
while(fread(&C,sizeof(C),1,fp))
{
	i=strcmp(C.Password,Password);
	if(AccNo==C.AccNo && i==0)
	{
	printf("\t\t\t\t\tLOAN REQUEST\n");
	printf("Required Amount: ");
	scanf("%f",&C.ReqAmount);
	fflush(stdin);
	printf("Tenure(Immediate/Short/long):");
	gets(C.Tenure);
	fflush(stdin);
	printf("Purpose: ");
	scanf("%s",C.Purpose);
	fflush(stdin);
	i=strcmp(C.Tenure,"Immediate");
	if(i==0)
	{
		printf("Dear Customer!\nYour Request For Lone Has Been Aproved\nYou Will Recieve Your Lone Within In An Hour.\nIt Is To Inform You That You Will Have Return This lone Within 6 Months\n");
		C.Min=C.Min+C.ReqAmount;
		fseek(fp,-(Size),SEEK_CUR);
		fwrite(&C,sizeof(C),1,fp);
		fclose(fp);
		printf("Thanks For Taking Lone!");
		break;
	}
	else
	{
		i=strcmp(C.Tenure,"Short");
		if(i==0)
		{
			printf("Dear Customer\nYour Request For Lone Will be Aproved Within (24-48) Hours After Verifying Your Details\nIt Is To Inform You That You Will Have Return This Lone Within 1 Year\n");
		    printf("Thanks For Taking Lone");
		    C.Min=C.Min+C.ReqAmount;
		    fseek(fp,-(Size),SEEK_CUR);
		    fwrite(&C,sizeof(C),1,fp);
		    fclose(fp);
		    break;
		}
		else
		{
			printf("Dear Customer\nYour Request For Lone Will be Aproved Within (24-48) Hours After Verifying Your Details\nIt Is To Inform You That You Will Have Return This Lone Within 1 Year\n");
			printf("Thanks For Taking Lone");
			C.Min=C.Min+C.ReqAmount;
			fseek(fp,-(Size),SEEK_CUR);
		    fwrite(&C,sizeof(C),1,fp);
		    fclose(fp);
		    break;
		}
	}
}
           if(i!=0)
		    {
	            printf("No Such Record Found!");	   	
		    }
}
            getch();
}
int main(void)
{
int Choice;
while(1)
{		
    system("cls");
	printf("\n\t\t\t\t\t\tWelcome To MRS Bank\n\n");
    printf("\t\t\t\t1.CREATE ACCOUNT\n\n");
	printf("\t\t\t\t2.MODIFY ACCOUNT\n\n");
	printf("\t\t\t\t3.DEPOSIT\n\n");
	printf("\t\t\t\t4.WITHDRAWL\n\n");
	printf("\t\t\t\t5.DELETE ACCOUNT\n\n");
	printf("\t\t\t\t6.ACCOUNT DETAILS\n\n");
	printf("\t\t\t\t7.LOAN REQUEST\n\n");
	printf("\t\t\t\t8.ACCOUNT HOLDER'S LIST\n\n");
	printf("\t\t\t\t9.Exit\n\n");
	printf("\t\t\t\tPlease Enter Your Choice ");
	scanf("%d",&Choice);
	system("cls");
	fflush(stdin);
switch(Choice)
 {
   case 1:
        {
            CreAcc();
		    break;
		}
	case 2:
	    {
            ModAcc();
            break;
        }
	case 3:
	    {
            Dpst();
    		break;			
		}
	case 4:
		{
            Wid();
			break; 				
		}	
	case 5:
	    {
	    	Del();
	    	break;
		}	
	case 6:
	    {
	    	AccDet();
	    	break;
		}
	case 7:
	    {
	    	loan();
	    	break;
		}			
	case 8:
	    {
	   	    AccLst();
	   		break;
		}
	case 9:
	    {
	    	printf("Thanks For Coming!");
	    	exit(0);
		}	
	default :
	    {
	    	printf("No Such Choice Found!");
	    }		  				     		
	}	
}
}
