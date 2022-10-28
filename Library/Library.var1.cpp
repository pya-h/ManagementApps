#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#define LOAD_SUCCESSFULL 1
#define LIB_LOAD_FAILED 0
#define BORROWERS_LOAD_FAILED -1
using namespace std;
struct Borrower
{
	string firstName, lastName, date;
};
struct Book
{
	int id;
	string name , writer, publisher;
	bool isAvailable = true, isDeleted = false;;
	Borrower borrower;
	Book *nextBook = nullptr;
} *firstBook,*lastBook; 
int generateId();
short int load();
bool save();
void showRecord(Book *);
Book *search(short int);

int main()
{
	firstBook = lastBook = new Book;
	short int loadResult = load();
	if (loadResult == BORROWERS_LOAD_FAILED)
	{
		fstream newfile("borrowers.txt", ios::out);
		if (!newfile)
		{
			cout << "An Error Occured While Creating The File: borrowers.txt!" << endl;
			system("pause");
			return 0;
		}
		newfile.close();
	}
	else if (loadResult == LIB_LOAD_FAILED)
	{
		fstream newfile("lib.txt", ios::out);
		fstream newfile2("borrowers.txt", ios::out);
		if (!newfile)
		{
			cout << "An Error Occured While Creating The File: lib.txt!" << endl;
			system("pause");
			return 0;
		}
		else if (!newfile2)
		{
			cout << "An Error Occured While Creating The File: borrowers.txt!" << endl;
			system("pause");
			return 0;
		}
		newfile.close();
		newfile2.close();
	}
	while (1)
	{
		cout << "1) Add Records" << endl;
		cout << "2) Borrow/Return" << endl;
		cout << "3) Delete a Record" << endl;
		cout << "4) Search" << endl;
		cout << "5) Exit " << endl;
		char x;
		cin >> x;
		system("cls");
		switch (x)
		{
		case '1':
		{
			int numberOfRecords;
			cout << "Enter The Number Of Records You Want To Add: ";
			cin >> numberOfRecords;
			Book *newBook = lastBook;
			for (int i = 1; i <= numberOfRecords; i++)
			{
				cout << "Generating a Random ID...";
				newBook->id = generateId();
				system("cls");
				cout << "Record #" << i << ": ";
				cin >> newBook->name >> newBook->writer >> newBook->publisher;
				newBook = newBook->nextBook = new Book;
			}
			lastBook = newBook;
			cout << "Done!"<<endl;
			if (save())
				cout << "Successfully Saved!"<<endl;
			else
				cout << "An Error Occured While Saving!"<<endl;
		}
		break;

		case '2':
		{
			Book *book = search(1);
			if (book == nullptr)
				cout << "There Is No Book With This ID!"<<endl;
			else
			{
				if (book->isAvailable)
				{
					cout << "Borrow:\n";
					cout << "First Name\tLast Name\tDate" << endl;
					cin >> book->borrower.firstName >> book->borrower.lastName >> book->borrower.date;
					book->isAvailable = false;
				}
				else
				{
					book->isAvailable = true;
					cout << "The Book Returned.\n";
				}

			}
			if (save())
				cout << "Successfully Saved!"<<endl;
			else
				cout << "An Error Occured While Saving!"<<endl;
			
		}
		break;

		case '3':
		{
			Book *book = search(1);
			if (book == nullptr)
				cout << "There Is No Book With This ID!"<<endl;
			else
			{
				cout << "Are You Sure?" << endl;
				cout << "1) Yes" << endl;
				cout << "2) No" << endl;
				char answer;
				do
				{
					cin >> answer;
				} while (answer !='1' && answer != '2');
				if (answer == '1')
				{
					book->isDeleted = true;
					cout << "Done!" << endl;
					if (save())
						cout << "Successfully Saved!" << endl;
					else
						cout << "An Error Occured While Saving!" << endl;
				}

			}
		}
		break;

		case '4':
		{
			cout << "Search By:" << endl;
			cout << "1) ID" << endl;
			cout << "2) Name" << endl;
			cout << "3) Writer" << endl;
			cout << "4) Publisher" << endl;
			char mode;
			do
			{
				cin >> mode;
			} while (mode < '1' && mode > '4');
			system("cls");
			if (search(mode - '0') == nullptr)
				cout << "No Records Found!" << endl;
		}
		break;

		case '5':
			return 0;

		}
		system("pause");
		system("cls");
	}
}

int generateId()
{
	srand((time(NULL)));
	int newId = (rand() % 90000) + 10000;
	Book *next = firstBook;
	while (!next)
	{
		if (next->id == newId)
			return generateId();
	}
	return newId;
}

short int load()
{
	fstream input("lib.txt",ios::in);
	fstream borrowers("borrowers.txt", ios::in);
	if (!input)
		return LIB_LOAD_FAILED;
	if (!borrowers)
		return BORROWERS_LOAD_FAILED;
	Book *book = firstBook;
	while (input >> book->id >> book->name >> book->writer >> book->publisher >> book->isAvailable)
	{
		if (!book->isAvailable)
		{
			borrowers >> book->id >> book->borrower.firstName >> book->borrower.lastName >> book->borrower.date;
		}
		book->nextBook = new Book;
		book = book->nextBook;
	}
	lastBook = book;
	input.close();
	borrowers.close();
	return LOAD_SUCCESSFULL;
}

bool save()
{
	fstream out("lib.txt", ios::out);
	fstream borrowers("borrowers.txt", ios::out);
	if (!out || !borrowers)
		return false;
	Book *book = firstBook;
	while (book != lastBook)
	{
		if (!book->isDeleted)
		{
			out << book->id << "\t" << book->name << "\t" << book->writer << "\t" << book->publisher << "\t" << (short int)book->isAvailable << endl;
			if (!book->isAvailable)
			{
				borrowers << book->id << "\t" << book->borrower.firstName << "\t" << book->borrower.lastName << "\t" << book->borrower.date << endl;
			}
		}
		book = book->nextBook;
	}
	out.close();
	borrowers.close();
	return true;
}

void showRecord(Book *book)
{
	if (!book->isDeleted)
	{
		cout << endl << book->id << "\t" << book->name << "\t" << book->writer << "\t" << book->publisher << "\t";
		if (book->isAvailable)
			cout << "Available\n";
		else
		{
			cout << "Borrowed\n";
			cout << "\tBorrowed By: " << book->borrower.firstName << "\t" << book->borrower.lastName << "\t" << book->borrower.date << endl;
		}
	}
}

Book *search(short int mode)
{
	Book *book = firstBook,*lastFound = nullptr;
	bool found;
	switch (mode)
	{
	case 1:
	{
		int id;
		cout << "Enter The Book ID: ";
		cin >> id;
		while (book != lastBook)
		{
			if (book->id == id)
			{
				showRecord(book);
				return book;
			}
			book = book->nextBook;
		}
	}
	break;

	case 2:
	{
		string name;
		cout << "Enter The Book Name: ";
		cin >> name;
		while (book != lastBook)
		{
			if (book->name == name)
				showRecord(book);
			lastFound = book;
			book = book->nextBook;
		}
	}
	break;

	case 3:
	{
		string writer;
		cout << "Enter The Writer's Name: ";
		cin >> writer;
		while (book != lastBook)
		{
			if (book->writer == writer)
				showRecord(book);
			lastFound = book;
			book = book->nextBook;
		}
	}
	break;
		
	case 4:
	{
		string publisher;
		cout << "Enter The Publisher's Name: ";
		cin >> publisher;
		while (book != lastBook)
		{
			if (book->publisher == publisher)
				showRecord(book);
			lastFound = book;
			book = book->nextBook;
		}
	}
	break;
	}
	return lastFound;
}