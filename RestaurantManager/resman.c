#include <stdio.h>
#include <stdlib.h>
#include "../include/console.h"

// some constants almost redefined to optimize runtime
#define null NULL

// constants for app maximums and error values and other values
#define 	_max_NameLength	 250
	#define 	_max_LineLength	 75
		 #define 	_value_Uninitialized	 -1
			#define 	_max_load_foods_index		9000000
				#define _max_order_detailes		500
// constants for menu item selects
#define		_SELECTING_ADD_FOOD 	'F'
 	#define		_SELECTING_SORT_FOODS 	'S'
		#define		_SELECTING_ADD_ORDER	 'O'
			#define		_SELECTING_CLOSE	 '0'
				
// constants for file names	
#define 	_filename_foods	 "foods.dta"
#define		_filename_orders	"orders.dta"

// constants for string compares
#define		strings_equal	0
#define		strings_1st_smaller		1
#define		strings_2nd_smaller	2

// program structs
	//Food definition
typedef struct {
	long int price;
	char name[ _max_NameLength ];
} Food;
	// Date definition
typedef enum {	Sun = 1, Mon , Tue, Wed, Thur, Fri, Sat	} WeekDay;
	typedef enum { January = 1, February, March, April, May, June, July, August, September, Octobor, November, December} Month;
		typedef struct {
			WeekDay weekday ;
			Month month;
			short int day, year;
		} Date;
char *DAY_NAMES[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
char *MONTH_NAMES[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "Octobor", "November", "December"};

	// Order definition
typedef struct {	
	Food food;
	char name[ _max_NameLength ];
	char detailes[_max_order_detailes];
	Date date;
} Order;




// function prototypes
char getUserChoice();
	void addFood();	
		void sortFoods();
			void addOrder();
				void insertSeperatorLine();
					void showError(char *);
						void convertStringsToLowerCase(char *,char *);
							char compareStrings(char *, char *);
int main()
{
	char choice = NULL;
	while( (choice = getUserChoice()) != _SELECTING_CLOSE )
	{
		switch(choice)
		{
			case _SELECTING_ADD_FOOD:
				addFood();		break;
			
			case _SELECTING_SORT_FOODS:
				sortFoods();		break;
			
			case _SELECTING_ADD_ORDER:
				addOrder();		break;
				
		}
		
		getch();
		system(CLEAR_SCREEN);
	}
	
	//CLOSE
	printf("\n\n\t>> Goodbye! <<");
	getch();
	return 0;
}

void addFood()
{
 	FILE *fpFoods;
 	int scanf_result = EOF;
 	Food newFood;
	newFood.price = _value_Uninitialized;
	newFood.name[0] = null;
	printf("\n\t:: New Food Form ::\n");
	insertSeperatorLine();
	
	//food name input
	do //while the fodd name is not empty
	{
		printf("\n\t\tFood Name: ");
		scanf_result = scanf("%s",newFood.name);
	}while(scanf_result == EOF || newFood.name[0] == null);
	
	//food price get
	do{ //get the price until the value is corrct
		printf("\n\t\t  Price[R]: ");
		scanf_result = scanf("%ld", &newFood.price);
	} while( scanf_result == EOF || newFood.price <= _value_Uninitialized);
	
	insertSeperatorLine();
	
	// add new data to the file
	fpFoods = fopen(_filename_foods, "a");//open for appending new 
	if( !fpFoods ) // if the couldint open normally
	{
		showError("Program failed while saving the data in the file");
		return;
	}
	else // if everthing have been correctly then...
	{
		fprintf(fpFoods, "\n%s\n%ld", newFood.name, newFood.price);
		printf("\n\t# Successfully added to the menu #");
	}
	
	fclose(fpFoods);
}
 
void sortFoods()
{
	FILE *fpFoods;
	Food *allFoods;
	long int length = 0;
	long int i , j;
	
	allFoods = (Food*) malloc(sizeof(Food) * _max_load_foods_index); // creating a dynamic array because the static array can not be 90000 memeber long!
	
	fpFoods = fopen(_filename_foods, "r");
	if(!fpFoods) // if cannot load the foods.txt or it doesnt even exist!
	{
		showError("Program failed while reading the menu file");
		return;
	}
	
	
	fgetc(fpFoods); // skip the first \n character in the first of the file
	for(length = 0; !feof(fpFoods); length++)
	{
		fscanf(fpFoods, "%s", allFoods[length].name);
		fscanf(fpFoods, "%ld", &(allFoods[length].price));
	}
	fclose(fpFoods);
	//until here reading data from file completed , now we am going to sort the array and write that in the food.txt file again
	
	//sorting...
	for(i = 0;i < length;i++)
	{
		for(j = i + 1;j < length;j++)
		{
			if( allFoods[j].price < allFoods[i].price )
			{
				Food tempFood = allFoods[j];
				allFoods[j] = allFoods[i];
				allFoods[i] = tempFood;
			}
		}
	}
	
	//now we write new data from begging to the foods.txt
	fpFoods = fopen(_filename_foods, "w");
	if(!fpFoods) // if cannot load the foods.txt or it doesnt even exist!
	{
		showError("Program failed while updating the menu file");
		return;
	}
	
	system(CLEAR_SCREEN);
	printf("\n\n Row\t|\tName\t\t\t|\tPrice(rials)\n");
	insertSeperatorLine();
	for(i = 0; i < length ; i++)
	{
		fprintf(fpFoods, "\n%s\t%ld", allFoods[i].name, allFoods[i].price);
		printf( "%3d\t|%25s\t|\t%ld\n",i+1, allFoods[i].name, allFoods[i].price);
	}
	fclose(fpFoods);
	allFoods = null; // freeing the pointer array
	printf("\n\n\tResult:\n\t\t# Successfully sorted and updated the menu #");
}

void addOrder()
{
	Order neworder;
	FILE *fpFoods,*fpOrders;
 	int scanf_result = EOF;
	neworder.food.price = _value_Uninitialized;
	neworder.food.name[0] = null;
	
	printf("\n\t:: Order Form ::\n");
	insertSeperatorLine();

	//food name input
	do //while the food name is not empty
	{
		printf("\n\t\tFood Name: ");
		scanf_result = scanf("%s",neworder.food.name);
	}while(scanf_result == EOF || neworder.food.name[0] == null);
	
	// start searching for food price
	
	fpFoods = fopen(_filename_foods, "r");//open for reading data
	if( !fpFoods ) // if the couldint open normally
	{
		showError("Program failed while openning the food data file...Ordering failed...");
		return;
	}
	
	fgetc(fpFoods); // skip the first \n character in the first of the file
	while( !feof(fpFoods) )
	{
		char nextfood[_max_NameLength] = { null };
		long int foodprice = 0;
		fscanf(fpFoods, "%s", nextfood);
		fscanf(fpFoods, "%ld", &foodprice);
		if( compareStrings(neworder.food.name, nextfood) == strings_equal )
		{
			neworder.food.price = foodprice;
			break;
		}
	}
	fclose(fpFoods);
	if(neworder.food.price == _value_Uninitialized)
	{
		showError("No food found with this name...Please read the Food Listr again...");
		return;
	}
	
	printf("\n\t\tPrice[R]: %ld\n",neworder.food.price);
	
	insertSeperatorLine();
	
	printf("\n\t:: Customer Form ::\n");
	
	insertSeperatorLine();
	
	do //while the customer name is not empty
	{
		printf("\n\t\tYour Name: ");
		scanf_result = scanf("%s",neworder.name);
	}while(scanf_result == EOF || neworder.name[0] == null);
	
	do //while the customer food detail is not empty
	{
		printf("\n\t\tSpecific Food Detail: ");
		scanf_result = scanf("%s",neworder.detailes);
	}while(scanf_result == EOF || neworder.detailes[0] == null);
	
	do //while the customer food detail is not empty
	{
		printf("\n\t\tDate [day dd mm yyyy]: ");
		scanf_result = scanf("%d %d %d %d",&neworder.date.weekday, &neworder.date.day, &neworder.date.month, &neworder.date.year);
	} while(scanf_result == EOF);
	
	
	// now is time to save in the file!
	fpOrders = fopen(_filename_orders, "a");//open for reading data
	if( !fpOrders ) // if the couldint open normally
	{
		showError("Program failed while saving order data in the file...Failed taking the Order...");
		return;
	}
	// save into file all the data program got from the user
	fprintf(fpOrders, "\n%s\t%s\t%ld\t%s\t%d\t%d\t%d\t%d",neworder.name, neworder.food.name, neworder.food.price, neworder.detailes, neworder.date.weekday, 
			neworder.date.day, neworder.date.month, neworder.date.year);
	// display the succefful operation message
	printf("\n\tOrder took in: \t\t\t%s, %d, %s, %d\n", DAY_NAMES[ neworder.date.weekday - 1], neworder.date.day, MONTH_NAMES[ neworder.date.month - 1], neworder.date.year);
	
	fclose(fpOrders);

}



void insertSeperatorLine()
{
 	short int i;
 	
 	for(i = 0;i < _max_LineLength;i++)
 		printf("-");
 	printf("\n");
}

void showError(char *message)
{
	printf("\n\tXx %s xX",message);
	printf("\n\n    ...  Press any key to continue  ...");
}


char getUserChoice() 
{
	char choice = null;
	printf("|? Please select what do you want to do ?|\n\n\n\tF <- Add Food\n\n\t S <- Sort Foods\n\n\t  O <- Add Order\n\n\t   0 <- Close\n\n\t\t");
	while(choice != _SELECTING_CLOSE && choice != _SELECTING_ADD_FOOD && choice != _SELECTING_SORT_FOODS && choice != _SELECTING_ADD_ORDER)
	{
		choice = getch();
		//if the letter entered is lower case, the program turns it to upper case character; this is for simplifying the use of choice
		if(choice >= 'a' && choice <= 'z') // upper case letters boundry
			choice += 'A' - 'a'; // add the difference from 'A' to 'a' to turn the letter to upper case
			
	}
	return choice;
	
}

 void convertStringsToLowerCase(char *in, char *out)
 {
 	int i;
 	for(i = 0; in[i] ; i++)
 		out[i] = in[i] < 'A' || in[i] > 'Z' ? in[i] : in[i] + 'a' - 'A';
 	in[i] = null;
 }
 
 char compareStrings(char *s1, char *s2)
 {
 	int i;
 	char ltls1[_max_NameLength] = { null }, ltls2[_max_NameLength] = { null };
 	convertStringsToLowerCase(s1, ltls1);
 	convertStringsToLowerCase(s2, ltls2);

 	for(i = 0;	ltls1[i] && ltls2[i] ; i++)
 	{
 		if(ltls1[i] < ltls2[i])
 			return strings_1st_smaller;
 		if(ltls2[i] < ltls1[i])
		 	return strings_2nd_smaller;	
	}
	return strings_equal;
 }
 
