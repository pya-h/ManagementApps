#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "console.h"

//define accepted values for place type
#define HOTEL '1'
#define RESTAURANT '2'

#define MAX_ARRAY_LENGTH 100
#define MAX_NUMBER_LENGTH 20

//define type bool for handling errors(it makes the code easier)
#define TRUE 1
#define FALSE 0
#define bool char

//define showing and sorting constants
#define JUST_DISTANCE 8
#define SHOW_ALL 9
#define PRICE 0
#define QUALITY 3
#define DISTANCE 4
#define ASCENDING '0'
#define DESCENDING '1'
#define NONE '-'
#define UNLIMITED -1.0

#define R 6371

//global variables and arrays
char list[MAX_ARRAY_LENGTH][5][MAX_NUMBER_LENGTH] = {'\0'}; //declare the main array and initial its each element with '\0' 
char type = '\0'; //variable wich shows the requested place type

//function prototypes
bool LoadFile();
bool IsNum(char);
void CalculateDistances(double,double);
void Sort(char,char);
void Show(char,double,int,short int);

int main()
{
	double x = 0.0,y = 0.0;
	while (type != HOTEL && type != RESTAURANT) //get the type of the place , skip the loop when the entered char is '1' or '2' (for ignoring unacceptable values)
	{
		system(CLEAR_SCREEN); // clear the screen , adopted from http://stackoverflow.com/questions/15102976/how-to-clear-screen-from-simple-c-program 
		printf("Type of the place ?\n1. Hotel\n2. Restaurant");
		type = getch();
	}
	system(CLEAR_SCREEN);
	printf("Enter the x cordinate of your location : \n");
	scanf("%lf",&x);
	printf("Enter the y cordinate of your location : \n");
	scanf("%lf",&y);
	if(!LoadFile()) // load the file into an array for making the calculations easy , if an error occured close the program with appropriate message
	{
		system(CLEAR_SCREEN);
		printf("An error occured while loading the \"Data_File.txt\" .\nAny key to exit ...");
		getch();
		return 1;
	}
	CalculateDistances(x,y); // calculate the distances between the person and places
	char part = '\0';
	while (part != '1' && part != '2' && part != '3') //ask wich part of the program must run, skip the loop when '1' or '2' or '3' is entered(for ignoring unacceptable values)
	{
		system(CLEAR_SCREEN);
		printf("Reporting Methods ? \n1) Show All \n2) Filter By Maximum Distance \n3) Custom Filter");
		part = getch();
	}
	system(CLEAR_SCREEN);
	if(part == '1')
		Show(JUST_DISTANCE,UNLIMITED,UNLIMITED,UNLIMITED);//1st part of program according to the project
	else if(part == '2')
	{
		//2nd part of program according to the project
		double maxDistance = 0.0;
		printf("Enter the max distance from you : ");
		scanf("%lf",&maxDistance);
		Sort(DISTANCE,ASCENDING); //sort the array by distance and in ascending order
		Show(JUST_DISTANCE,maxDistance,UNLIMITED,UNLIMITED);//show the table
	}
	else
	{
		//3rd part of program according to the project
		double maxDistance = 0.0,maxPrice = 0.0,minQuality = 0.0;
		printf("Enter the max distance from you : ");
		scanf("%lf",&maxDistance);
		printf("Enter the max price : ");
		scanf("%lf",&maxPrice);
		printf("Enter the min quality : ");
		scanf("%lf",&minQuality);
		char order = '\0';
		printf("\n\nchoose the order of sorting : 0)Ascending\t1)Descending ");
		while(order != ASCENDING && order != DESCENDING)
			order = getch();
		printf("\n\nchoose how to sort information : \n0)by Distance\t1)by Price\t2)by Quality ");
		char sortBy = '\0';
		while (sortBy != '0' && sortBy != '1' && sortBy != '2')
			sortBy = getch();
		switch(sortBy)
		{
			case '0':
				sortBy = DISTANCE;break;
			case '1':
				sortBy = PRICE;break;
			case '2':
				sortBy = QUALITY;break;
		}//modify the sortBy value for using the array easier
		Sort(sortBy,order); // sort the array as requested
		Show(SHOW_ALL,maxDistance,maxPrice,minQuality); //show the requested information
	}
	return 0;
}

bool IsNum(char ch)
{
	if((ch >= 48 && ch <= 57) || ch == '.' || ch == '-') //the ASCII code of numeric chars is between 48 and 57
		return TRUE;
	return FALSE; //if the chars are not numeric the return false
}

bool LoadFile()
{
	char fileName[100]; //file address
	FILE *in; //for opening the file
	int i = 0; //i is the row's counter
	system(CLEAR_SCREEN);
	printf("Enter the address of the \"Data_File.txt\" file ...\nIf the file is in the folder of the program , press \"h\" : ");
	scanf("%s",fileName);
	if(!(in = fopen(fileName[0] == 'h' ? "Data_File.txt" : fileName,"rt"))) // try opening the file with the address entered by user , if the address was 'h' , then replace the address with "Data_File.txt"
		return FALSE; // return false to the function if an error occured while opening the file , false means that the function can't do its job correctly
	while(!feof(in)) //continue until we're not arrived to file's end
	{
		char ch = getc(in); //get the current char in the file
		if((ch == 'H' && type == HOTEL) || (ch == 'R' && type == RESTAURANT)) //check whether the current place is the same with user's request
		{
			int j = 0;
			for(j = 0;j < 4;j++) //j is the column counter
			{
				int k = 0; //k is the number length counter
				while(!IsNum(ch) && !feof(in)) //skip chars that are not number or '.' or '-'
					ch = getc(in); 
				for(k = 0;ch != '\t' && ch != ' ' && ch != '\n' && !feof(in);k++) //get the current number and put it in the right column
				{
					list[i][j][k] = ch;
					ch = getc(in);
				}
			}
			i++;
		}
		else //if the current row is not about the user wanted type then skip it
			while(ch != '\n' && !feof(in)) //skip the row
				ch = getc(in);
	}
	system(CLEAR_SCREEN);
	printf("File has loaded successfully ...\nAny key to continue...");
	getch();
	fclose(in); // close the opened file
	return TRUE; // true means that the function has done its job correctly
}

void CalculateDistances(double x,double y)
{
	int i = 0;
	for(;list[i][0][0] != '\0';i++)
	{
		double placeX = 0.0,placeY = 0.0;
		sscanf(list[i][1],"%lf",&placeX);//convert the string X and Y to double for making the calculation much easier
		sscanf(list[i][2],"%lf",&placeY);//adopted from http://stackoverflow.com/questions/10075294/converting-string-to-a-double-variable-in-c
		const double a = sin((x-placeX)/2.0)*sin((x-placeX)/2.0) + cos(y)*cos(placeY) + sin((y-placeY)/2.0)*sin((y-placeY)/2.0);
		const double c = 2.0 * atan2(sqrt(a),sqrt(1.0-a));
		sprintf(&list[i][DISTANCE][0],"%f",R*c);//calculate the distance according to the formula and then convert the result into string to store it in the array
		//adbopted from http://stackoverflow.com/questions/7462349/convert-double-value-to-a-char-array-in-c
	}
	return;
}

void Sort(char sortBy,char order)
{
		int i = 0;
		for(;list[i][0][0] != '\0';i++) //check whether the it is the last row or not
		{
			int j = i+1;
			for(;list[j][0][0] != '\0';j++) //check whether the it is the last row or not
			{
				double d1 = 0.0,d2 = 0.0;
				sscanf(list[i][sortBy],"%lf",&d1);//convert the char* to double for making the calculations easier
				sscanf(list[j][sortBy],"%lf",&d2);
				if((order == ASCENDING && d1 > d2) || 
						( order == DESCENDING && d1 < d2))
				{
					char temp[MAX_NUMBER_LENGTH] = {'\0'};
					strcpy(temp,list[i][sortBy]); //copy the value (not address) of one string to another one via strcpy
					strcpy(list[i][sortBy],list[j][sortBy]);
					strcpy(list[j][sortBy],temp);
				} // sorting algorythm
			}
		}
		return;
}

void Show(char showType,double maxDistance,int maxPrice,short int minQuality)
{
	int i = 0;
	system(CLEAR_SCREEN);
	//start of creating a table
	printf("Type\t");
	if(type == RESTAURANT)
		printf("\t");
	printf("Distance\t");
	if(showType == SHOW_ALL)
		printf("Price\tQuality");
	printf("\n-------------------------------------------------------------------------\n");
	
	for(;list[i][0][0] != '\0';i++)
	{
		//start of filtering the infornation 
		if(maxDistance != UNLIMITED)
		{
			double distance = 0.0;
			sscanf(list[i][DISTANCE],"%lf",&distance);
			if(distance > maxDistance)
				continue; //skip this row if it is not in teh requested distance range
		}
		if(maxPrice != UNLIMITED)
		{
			double price = 0.0;
			sscanf(list[i][PRICE],"%lf",&price);
			if(price > maxPrice)
				continue;//skip this row if it is not in teh requested price range
		}
		if(minQuality != UNLIMITED)
		{
			double quality = 0.0;
			sscanf(list[i][QUALITY],"%lf",&quality);
			if(quality < minQuality)
				continue; //skip this row if it is not in teh requested quality range
		}
		//end of the filtering the information
		if(type == RESTAURANT)//print the type of place
			printf("Restaurant\t");
		else
			printf("Hotel\t");
		printf("%s\t",list[i][DISTANCE]);
		if(showType == SHOW_ALL)//print other informations if requested
		{
			printf("%s\t",list[i][PRICE]);
			printf("%s",list[i][QUALITY]);
		}
		printf("\n");//go to next line for printing
	}//end of creating the table
	return;
}
