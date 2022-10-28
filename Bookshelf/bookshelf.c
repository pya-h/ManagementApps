#include <stdio.h>
#include <stdlib.h>
#include "../include/console.h"
#include <string.h>

// some constants almost redefined to optimize runtime

// constants for app maximums and error values and other values
#define 	_max_NameLength	 250
    #define 	_max_LineLength	 75
         #define 	_value_Uninitialized	 -1
            #define 	_max_load_books_index		10000
                #define _max_order_detailes		500
// constants for menu item selects
#define		_SELECTING_ADD_BOOK 	'B'
    #define		_SELECTING_SORT_BOOKS 	'S'
        #define		_SELECTING_BOOKMARK	 'M'
            #define		_SELECTING_CLOSE	 '0'

// constants for file names
#define 	_filename_books	 "books.dta"
#define		_filename_bookmarks	"bookmarks.dta"

// constants for string compares
#define		strings_equal	0
#define		strings_1st_smaller		1
#define		strings_2nd_smaller	2

// program structs
    //Food definition
typedef struct {
    long int price;
    char name[ _max_NameLength ];
} Book;
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
    Book book;
    char name[ _max_NameLength ];
    short int page;
    Date lastMarkDate;
} Bookmark;




// function prototypes
char getUserChoice();
    void addBook();
        void sortBooks();
            void bookmarkBook();
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
            case _SELECTING_ADD_BOOK:
                addBook();		break;

            case _SELECTING_SORT_BOOKS:
                sortBooks();		break;

            case _SELECTING_BOOKMARK:
                bookmarkBook();		break;

        }
		printf("\n\nPress a key to return to the main menu...");
        getch();
        system(CLEAR_SCREEN);
    }

    //CLOSE
    printf("\n\n\t>> Goodbye! <<");
    getch();
    return 0;
}

void addBook()
{
    FILE *fpBooks;
    int scanf_result = EOF;
    Book newBook;
    newBook.price = _value_Uninitialized;
    newBook.name[0] = NULL;
    printf("\n\t:: New Book Form ::\n");
    insertSeperatorLine();

    //book name input
    do //while the book name is not empty
    {
        printf("\n\t\tBook Name: ");
        scanf_result = scanf("%s",newBook.name);
    }while(scanf_result == EOF || newBook.name[0] == NULL);

    //book price get
    do{ //get the price until the value is corrct
        printf("\n\t\t  Price[T]: ");
        scanf_result = scanf("%ld", &newBook.price);
    } while( scanf_result == EOF || newBook.price <= _value_Uninitialized);

    insertSeperatorLine();

    // add new data to the file
    fpBooks = fopen(_filename_books, "a");//open for appending new
    if( !fpBooks ) // if the couldint open normally
    {
        showError("Program failed while saving the data in the file");
        return;
    }
    else // if everthing have been correctly then...
    {
        fprintf(fpBooks, "\n%s\t%ld", newBook.name, newBook.price);
        printf("\n\t# Successfully added to the menu #");
    }

    fclose(fpBooks);
}

void sortBooks()
{
    FILE *fpBooks, *fpBookmarks;
    Book *allBooks;
	Bookmark *allBookmarks;
    long int booksLength = 0, bookmarksLength = 0, maxLength = 0;
    long int i , j;

    allBooks = (Book*) malloc(sizeof(Book) * _max_load_books_index); // creating a dynamic array because the static array can not be 90000 memeber long!
	allBookmarks = (Bookmark*) malloc(sizeof(Bookmark) * _max_load_books_index) ;
	
    fpBooks = fopen(_filename_books, "r");
    fpBookmarks = fopen(_filename_bookmarks, "r");
    
    if(!fpBooks) // if cannot load the books file or it doesnt even exist!
    {
        showError("Program failed while reading the books file");
        return;
    }
	if(!fpBookmarks) // if cannot load the books file or it doesnt even exist!
    {
        showError("Program failed while reading the bookmarks file");
        return;
    }
    
    fgetc(fpBooks); // skip the first \n character in the first of the file
    for(booksLength = 0; !feof(fpBooks); booksLength++)
    {
        fscanf(fpBooks, "%s", allBooks[booksLength].name);
        fscanf(fpBooks, "%ld", &(allBooks[booksLength].price));
    }
    fclose(fpBooks);
    for(bookmarksLength = 0; !feof(fpBookmarks); bookmarksLength++)
    {
        fscanf(fpBookmarks, "%s%s%ld%d%d%d%d%d", allBookmarks[bookmarksLength].name, allBookmarks[bookmarksLength].book.name, &(allBookmarks[bookmarksLength].book.price),
			&(allBookmarks[bookmarksLength].page), &(allBookmarks[bookmarksLength].lastMarkDate.weekday), &(allBookmarks[bookmarksLength].lastMarkDate.day),
				&(allBookmarks[bookmarksLength].lastMarkDate.month), &(allBookmarks[bookmarksLength].lastMarkDate.year)) ;
    }
    fclose(fpBookmarks);
    //until here reading data from file completed , now we am going to sort the array and write that in the food.txt file again

	maxLength = booksLength <= bookmarksLength ? booksLength : bookmarksLength;
    //sorting...
    for(i = 0;i < maxLength;i++)
    {
        for(j = i + 1;j < booksLength;j++)
        {
            if( i < booksLength && strcmp( strlwr(allBooks[j].name, _max_NameLength) , strlwr(allBooks[i].name, _max_NameLength) ) == -1 )
            {
            	// copies byval or byref !?
                Book tempBook = allBooks[j];
                allBooks[j] = allBooks[i];
                allBooks[i] = tempBook;
            }
            if( i < bookmarksLength && strcmp( strlwr(allBookmarks[j].book.name, _max_NameLength) , strlwr(allBookmarks[i].book.name, _max_NameLength) ) == -1 )
            {
            	// copies byval or byref !?
                Bookmark tempBook = allBookmarks[j];
                allBookmarks[j] = allBookmarks[i];
                allBookmarks[i] = tempBook;
            }
            
        }
    }

    //now we write new data from begging to the books.txt
    fpBooks = fopen(_filename_books, "w");
    fpBookmarks = fopen(_filename_bookmarks, "w");
    if(!fpBooks) // if cannot load the books file or it doesnt even exist!
    {
        showError("Program failed while updating the books file");
        return;
    }
    if(!fpBookmarks) // if cannot load the books file or it doesnt even exist!
    {
        showError("Program failed while updating the bookarks file");
        return;
    }
 
    system(CLEAR_SCREEN);
    printf("\n\n Row\t|\tName\t\t\t|\tPrice(Tomans)\n");
    insertSeperatorLine();
    for(i = 0; i < maxLength ; i++)
    {
    	if(i < booksLength)
        	fprintf(fpBooks, "\n%s\t%ld", allBooks[i].name, allBooks[i].price);
        if(i < bookmarksLength)
        	fprintf(fpBookmarks, "\n%s\t%s\t%ld\t%d\t%d\t%d\t%d\t%d",allBookmarks[i].name, allBookmarks[i].book.name, allBookmarks[i].book.price, allBookmarks[i].page, allBookmarks[i].lastMarkDate.weekday,
            	allBookmarks[i].lastMarkDate.day, allBookmarks[i].lastMarkDate.month, allBookmarks[i].lastMarkDate.year);
 //       printf( "%3d\t|%25s\t|\t%ld\n",i+1, allBooks[i].name, allBooks[i].price);
    }
    
    fclose(fpBooks);
    fclose(fpBookmarks);
    allBooks = NULL;
    allBookmarks = NULL; // freeing the pointer array
    printf("\n\n\tResult:\n\t\t# Successfully sorted and updated the menu #");
}

void bookmarkBook()
{
    Bookmark newMark;
    FILE *fpBooks,*fpBookmarks;
    int scanf_result = EOF;
    newMark.book.price = _value_Uninitialized;
    newMark.book.name[0] = NULL;

    printf("\n\t:: Bookmark Form ::\n");
    insertSeperatorLine();

    //food name input
    do //while the book name is not empty
    {
        printf("\n\t\tBook Name: ");
        scanf_result = scanf("%s",newMark.book.name);
    }while(scanf_result == EOF || newMark.book.name[0] == NULL);

    // start searching for book price

    fpBooks = fopen(_filename_books, "r");//open for reading data
    if( !fpBooks ) // if the couldint open normally
    {
        showError("Program failed while openning the book data file...Ordering failed...");
        return;
    }

    fgetc(fpBooks); // skip the first \n character in the first of the file
    while( !feof(fpBooks) )
    {
        char nextBookName[_max_NameLength] = { NULL };
        long int nextBookPrice = 0;
        fscanf(fpBooks, "%s", nextBookName);
        fscanf(fpBooks, "%ld", &nextBookPrice);
        if( compareStrings(newMark.book.name, nextBookName) == strings_equal )
        {
            newMark.book.price = nextBookPrice;
            break;
        }
    }
    fclose(fpBooks);
    if(newMark.book.price == _value_Uninitialized)
    {
        showError("No book found with this name...Please check the book name again...");
        return;
    }

    printf("\n\t\tPrice[T]: %ld\n",newMark.book.price);

    insertSeperatorLine();

    printf("\n\t:: Details Form ::\n");

    insertSeperatorLine();

    do //while the bookmarker name is not empty
    {
        printf("\n\t\tYour Name: ");
        scanf_result = scanf("%s",newMark.name);
    }while(scanf_result == EOF || newMark.name[0] == NULL);

    do //while the book page is not empty
    {
        printf("\n\t\tLast Page Read: ");
        scanf_result = scanf("%d",&newMark.page );
    }while(scanf_result == EOF || newMark.page < 0);

    do //while the book detail is not empty
    {
        printf("\n\t\tDate [day dd mm yyyy]: ");
        scanf_result = scanf("%d %d %d %d",&newMark.lastMarkDate.weekday, &newMark.lastMarkDate.day, &newMark.lastMarkDate.month, &newMark.lastMarkDate.year);
    } while(scanf_result == EOF);


    // now is time to save in the file!
    fpBookmarks = fopen(_filename_bookmarks, "a");//open for reading data
    if( !fpBookmarks ) // if the couldint open normally
    { 
        showError("Program failed while saving bookmark data in the file...Failed taking the Order...");
        return;
    }
    // save into file all the data program got from the user
    fprintf(fpBookmarks, "\n%s\t%s\t%ld\t%d\t%d\t%d\t%d\t%d",newMark.name, newMark.book.name, newMark.book.price, newMark.page, newMark.lastMarkDate.weekday,
            newMark.lastMarkDate.day, newMark.lastMarkDate.month, newMark.lastMarkDate.year);
    // display the succefful operation message
    printf("\n\tBookmarked in: \t\t\t%s, %d, %s, %d\n", DAY_NAMES[ newMark.lastMarkDate.weekday - 1], newMark.lastMarkDate.day, MONTH_NAMES[ newMark.lastMarkDate.month - 1], newMark.lastMarkDate.year);
	insertSeperatorLine();
	printf("\n\n    Result:\n\tOperation Successful!");
    fclose(fpBookmarks);

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
    char choice = NULL;
    printf("|? The Fuck ?|\n\n\n\tB <- Add Book\n\n\t S <- Sort Books\n\n\t  M <- Bookmark a Book\n\n\t   0 <- Close\n\n\t\t");
    while(choice != _SELECTING_CLOSE && choice != _SELECTING_ADD_BOOK && choice != _SELECTING_SORT_BOOKS && choice != _SELECTING_BOOKMARK)
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
    in[i] = NULL;
 }

 char compareStrings(char *s1, char *s2)
 {
    int i;
    char ltls1[_max_NameLength] = { NULL }, ltls2[_max_NameLength] = { NULL };
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


