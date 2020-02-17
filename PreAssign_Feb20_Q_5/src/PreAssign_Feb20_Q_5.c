/*
 ============================================================================
 Name        : PreAssign_Feb20_Q_5.c
 Author      : Shivam Palaskar
 Version     :
 Copyright   : Open source
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void getProbPeriod(int,int,int);
int getMonthDays(int,int);
int isLeapYr(int);
void getCurrentDate(int *,int *,int *);
int getExp(int,int,int,int,int,int);
int getAge(int,int,int,int,int,int);
int getDiffInMonths(int ,int ,int ,int ,int ,int);

int main(void) {
	setvbuf(stdout,NULL,_IONBF,0);
	struct Employee{
		int empid,salary;
		char name[20],address[20];
		int bday_d,bday_m,bday_y;
		int jday_d,jday_m,jday_y;
	};
	struct Employee employee;

	printf("Enter Name of Employee: ");
	scanf("%[^\n]s",employee.name);
	fflush(stdin);
	printf("Enter Address : ");
	scanf("%s",employee.address);
	printf("Enter Salary : ");
	scanf("%d",&employee.salary);
	printf("Enter birth date dd/mm/yyyy : ");
	scanf("%d / %d / %d",&employee.bday_d,&employee.bday_m,&employee.bday_y);
	printf("Enter Date of joining dd/mm/yyyy : ");
	scanf("%d/%d/%d",&employee.jday_d,&employee.jday_m,&employee.jday_y);

	int age =  getAge(employee.bday_d,employee.bday_m,employee.bday_y,employee.jday_d,employee.jday_m,employee.jday_y);
	printf("\nAge : %d Years",age);


	int cday_d,cday_m,cday_y;
	getCurrentDate(&cday_d,&cday_m,&cday_y);
	int exp = getExp(employee.jday_d,employee.jday_m,employee.jday_y,cday_d,cday_m,cday_y);
	printf("\nExperience : %d Months",exp);

	getProbPeriod(employee.jday_d,employee.jday_m,employee.jday_y);

	return EXIT_SUCCESS;
}

void getCurrentDate(int *cday_d, int *cday_m, int *cday_y) {
	time_t now; // time_t : long int
	time(&now);
	struct tm *local = localtime(&now);
	*cday_d = local->tm_mday;        	// get day of month (1 to 31)
	*cday_m = local->tm_mon + 1;   	// get month of year (0 to 11)
	*cday_y = local->tm_year + 1900;
}

int getAge(int bday_d, int bday_m, int bday_y,int jday_d,int jday_m,int jday_y) {
	int months = getDiffInMonths(bday_d,bday_m,bday_y,jday_d,jday_m,jday_y);
	return (months/12);
}

int getDiffInMonths(int jday_d,int jday_m,int jday_y,int cday_d,int cday_m,int cday_y){
	if(cday_d<jday_d){
		cday_d+=getMonthDays(cday_m,cday_y);
		cday_m--;
		if(cday_m==0){
			cday_m=12;
			cday_y--;
		}
	}else if(cday_m<jday_m){
		cday_m+=12;
		cday_y--;
	}
	//int eday_d = cday_d-jday_d;
	int eday_m = cday_m-jday_m;
	int eday_y = cday_y-jday_y;
	//printf("\nPeriod : %d days %d months %d Years",eday_d,eday_m,eday_y);
	return (eday_y*12)+eday_m;
}

int getExp(int jday_d, int jday_m, int jday_y, int cday_d, int cday_m, int cday_y) {
	int months = getDiffInMonths(jday_d, jday_m, jday_y, cday_d, cday_m,cday_y);
	return  months;
}


int getMonthDays(int m,int y){
	if(m==2 && isLeapYr(y))
		return 29;
	else if(m==2 && !(isLeapYr(y)))
		return 28;
	if(m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)
		return 31;
	else
		return 30;
}

void getProbPeriod(int jday_d,int jday_m,int jday_y){
	int period = 90;
	while(period){
		if (period >= getMonthDays(jday_m, jday_y) - jday_d + 1) {
			if (period == 90){
				period -= (getMonthDays(jday_m, jday_y) - jday_d + 1);
				jday_d=1;
			}
			else
				period -= getMonthDays(jday_m, jday_y);

			jday_m++;
			if (jday_m == 13) {
				jday_m = 1;
				jday_y++;
			}
		}
		else {
			jday_d += (period-1);
			period = 0;
		}
	}
	printf("\nProbation Period End Date : %d/%d/%d",jday_d,jday_m,jday_y);
}

int isLeapYr(int jday_y){
	if((jday_y % 100)==0){
		if((jday_y % 400)==0){
			return 1;
		}else
			return 0;
	}
	else if((jday_y%4)==0)
		return 1;
	else
		return 0;
}
