#include "iostream"
#include "string"
#include "time.h"
#include "../include/console.h"
#include "stdlib.h"
#include "fstream"

using namespace std;
string Address1 = "File1.txt",Address2 = "File2.txt" ;
char Menu();
int CountBooks();
int CreateId(int n, int *BookId);
void LoadBookId(int n, int *BookId);
void AddBooks(int NumberOfBooks, int Number);
int ChangeStatus(int n, int Id);
int DeleteBook(int n, int Id);
void Find();

/* 
	Dalile Load Kardan File dar har taabe mojazza:
	1. moshakhas nabodan tedad ketabhaaye mojod dar file
	2. taghyiire tedad ketabhaa heyne ejraye barname
	3. update shodane morattab va tatbigh baa taghyiraat
*/
int main()
{
	int NumberOfBooks = CountBooks(); //mohasebeye tedad ketabhaye mojood dar ketabkhene
	srand(time(0));
	char m = Menu();//Menu raa tashkil midahad va entekhaab kaarbar raa daryaft mikonad
	while (m != '5')
	{
		system(CLEAR_SCREEN);
		switch (m)
		{
		case '1':
		{
			int Number = 0;
			cout << endl << "How many books do you want to add? ";
			cin >> Number;
			AddBooks(NumberOfBooks, Number); 
			NumberOfBooks += Number;
		}break;

		case '2':
		{
			int Id = 0;
			cout << endl << "Book Id: ";
			cin >> Id;
			int t = ChangeStatus(NumberOfBooks, Id); /* in taabe Id vared shode raa search mikonad va vaziyat An raa taghyir midahad , dar sorati ke dar baz kardan file vorodi error pish Amad meghdaare -1
			 ,dar sorati ke Id peyda nashavad meghdaare 0 , va dar sorate peyda kardan meghdaare 1 raa barmigardaanad */
			if (t == -1)
				cout << endl << "File:Books.txt cannot be opened...Maybe the library is empty...";
			else if (t == 0)
				cout << endl << "There is no book matching the Id you entered...";

				
		}break;

		case '3':
		{
			int Id = 0;
			cout << "Book Id: ";
			cin >> Id;
			int t = DeleteBook(NumberOfBooks, Id); /* in taabe Id vared shode raa search mikonad va vaziyat An raa taghyir midahad , dar sorati ke dar baz kardan file vorodi error pish Amad meghdaare -1
													 ,dar sorati ke Id peyda nashavad meghdaare 0 , va dar sorate peyda kardan meghdaare 1 raa barmigardaanad */
			if (t == -1)
				cout << endl << "File:Books.txt cannot be opened...Maybe the library is empty...";
			else if (t == 0)
				cout << endl << "There is no book matching the Id you entered...";
		}break;

		case '4':
		{
			Find();
		}break;

		default:
			break;
		}
		getch();cin.get();
		system(CLEAR_SCREEN);
		m = Menu();
	}
}

char Menu()
{
	cout << "1-Add books" << endl;
	cout << "2-Borrow" << endl;
	cout << "3-Delete a book" << endl;
	cout << "4-Find" << endl;
	cout << "5-Quit ";
	char m = getch();
	return m;
}
int CountBooks()
{
	int r = 0;
	ifstream File1(Address1);
	if (File1)
	{
		while (!File1.eof())
		{
			int Temp1;
			string Temp2;
			File1 >> Temp1 >> Temp2 >> Temp2 >> Temp2>> Temp1;
			r++;
		}
		r--; // Halgheye akhari ke ejra mishavad ezaafist , ps tedaade daghighe ketabha r - 1 taast
	}
	File1.close();
	return r;
}

void LoadBookId(int n, int *BookId)
{
	ifstream File1(Address1);
	if (File1)
	{
		for (int a = 0; a < n; a++)
		{
			int Temp1;
			string Temp2;
			File1 >> BookId[a] >> Temp2 >> Temp2 >> Temp2 >> Temp1;
		}
	}
	File1.close();
}

int CreateId(int n , int *BookId)
{
	int Id = rand() % 90000 + 10000; //tolid adade tasaadofi beyne 10000 taa 99999
	for(int c = 0; c < n; c++)
	{
		if (Id == BookId[c]) // agar Id tekrari bashad :
		{
			Id = 0; // 0 bodane Id raa be ma'niye tekrari bodane meghdaare tasaadofi dar nazar migirim
			break;
		}
	}
	return Id;
}

void AddBooks(int NumberOfBooks , int Number)
{
	int *BookId = new int[NumberOfBooks + Number]; //id ketabha az roye file khaande mishavad va dar in Araye rikhte mishavad(baraye moghaayeseye Id haaye jadid baa ghadimiha
	LoadBookId(NumberOfBooks, BookId); //in taabe Araye BookId ra baa Id ketabhaa por mikonad
	fstream File1(Address1, ios::app);
	if (!File1) //agar meghdare FileBooks 0 shod , yani ehtemalan file vojod nadaarad
	{
		ofstream FileBooks("Books.txt");
	}
	for (int a = 0; a < Number; a++)
	{
		system(CLEAR_SCREEN);
		int Id = 0;
		while (Id == 0)
			Id = CreateId(NumberOfBooks + a, BookId); //in taabe id haaye jadid tolid mikonad , dar sorati ke id tasaadofiye jadid tekraari baashad meghdaare 0 raa bar migardaanad
		BookId[NumberOfBooks + a] = Id; // ezaafe kardan Id jadid be liste Id haa
		cout << endl << "Format: Name\tWriter\tPublisher" << endl << "\t" ;
		string Name, Writer, Publisher;
		cin >> Name >> Writer >> Publisher;
		File1 << Id << "\t" << Name << "\t" << Writer << "\t" << Publisher << "\t" << 1 << endl;
		cout << endl << a + 1 << " Book(s) Added...";
		getch();

	}
	cout << "Number of books: " << NumberOfBooks + Number; //tedade kolle ketabhaaye mojood dar ketaabkhaane ra cout mikonad
	File1.close();
}

int ChangeStatus(int n , int Id)
{
	ifstream File1(Address1);
	ifstream File2(Address2);
	int Flag = 0; // moshakhas mikonad Aya Id peyda shode yaa na... 0 bodane An be manaye peyda nashodane ketaab ast
	if (!File1) // agaar File1 NULL shavad , yani dar baaz kardane file moshkeli pish Amade , ke in yani ehtemaalan hanooz ketabi vaarede ketaabkhaane nashode va file "File1.txt" hanooz sakhte nashode
		return -1;
	if (!File1)// agaar File2 NULL shavad , yani dar baaz kardane file moshkeli pish Amade , ke in yani hanooz ketabi gharz daade nashode va file "File2.txt" hanooz sakhte nashode
	{
		ofstream FilePeople(Address2);//dar in sorate yek file be naame "File2.txt" misaazim ta dar An Benevisim
		FilePeople.close();
	}
	int *BookId = new int[n],*Status = new int[n];
	string *Name = new string[n], *Writer = new string[n], *Publisher = new string[n], *BFirstName = new string[n], *BLastName = new string[n] , *BDate = new string[n] ;
	/*Dar 2 khatte bala arayehaayi tarif shode ... etela'ate mojod dar file raa dar in Araye haa mirizim taa kaareman Asaan tar shavad*/

	int NumberOfAvailableBooks = 0; //Tedad ketabhaye dar dastras raa mishomarad
	for (int c = 0; c < n; c++)
	{
		File1 >> BookId[c] >> Name[c] >> Writer[c] >> Publisher[c] >> Status[c];
		if (Status[c] == 1)
		{
			if (Id == BookId[c])
			{
				cout << endl << "Book: " << Name[c] << "\t" << Writer[c] << "\t" << Publisher[c] << "\tis available...";
				cout << endl << "Enter borrower's details, Format: FirstName LastName Date:"<<endl<<"\t\t\t\t" ;
				cin >> BFirstName[c] >> BLastName[c] >> BDate[c];
				Status[c] = 0;
				Flag = 1; // 1 bodane flag be ma'naaye peyda shodane ketabe morede nazar ast
				cout << endl << "The book has been borrowed...";
			}
			else
			{
				NumberOfAvailableBooks++;
				BFirstName[c] = "";
				BLastName[c] = "";
				BDate[c] = "";
			}
		}
		else
		{
			int Temp1 = 0;
			File2 >>Temp1 >> BFirstName[c] >> BLastName[c] >> BDate[c];
			if (Id == BookId[c])
			{
				cout << endl << "Book: " << Name[c] << "\t" << Writer[c] << "\t" << Publisher[c] << "\thas been returned by " << BFirstName[c] << "\t" << BLastName[c];
				Status[c] = 1;
				NumberOfAvailableBooks++;
				BFirstName[c] = "";
				BLastName[c] = "";
				BDate[c] = "";
				Flag = 1;
				cout << endl << "The book has been returned to bookshelf...";
			}
		}
	}
	File1.close();
	File2.close();
	if (Flag == 0)
		return 0;
	cout << endl << "Number of books: " << n << ", Number of available books: " << NumberOfAvailableBooks << ", Number of Borrowed Books: " << n - NumberOfAvailableBooks << " "; //namayeshe Amaare ketabhaa
	ofstream OutFile1(Address1);
	ofstream OutFile2(Address2);
	for (int c = 0; c < n; c++)
	{
		OutFile1 << BookId[c] << "\t" << Name[c] << "\t" << Writer[c] << "\t" << Publisher[c] << "\t" << Status[c] << endl;
		if (Status[c] == 0)
		{
			OutFile2 << BookId[c] << "\t" << BFirstName[c] << "\t" << BLastName[c] << "\t" << BDate[c] << endl; // 3 Arayeye Akhar faghat baraaye ketaab haayi ke Status=1 ast por mikonim , baraaye baghiyeye ketaabhaa Anhaa raa khaali migozaarim
		}
	}
	OutFile1.close();
	OutFile2.close();
	return 1;
}

int DeleteBook(int n, int Id)
{
	int *BookId = new int[n], *Status = new int[n];
	string *Name = new string[n], *Writer = new string[n], *Publisher = new string[n], *BFirstName = new string[n], *BLastName = new string[n], *BDate = new string[n];
	/*Dar 2 khatte bala arayehaayi tarif shode ... ettela'ate mojod dar file raa dar in Araye haa mirizim taa kaareman Asaan tar shavad*/

	int NumberOfAvailableBooks = 0; //Tedad ketabhaye dar dastras raa mishomarad
	ifstream File1(Address1);
	ifstream File2(Address2);
	int Flag = 0,YesNo = -1; /* Flag moshakhas mikonad Aya Id peyda shode yaa na... 0 bodane An be manaye peyda nashodane ketaab ast
							 YesNo moshakhkhas mikonad kaarbar che tasmimi gerefte, 1 No   2 Yes     meghdaare -1 moshakhkhas mikonad ke kaarbar hanooz paasoz nadaadeh. */
	if (!File1) // agaar File1 NULL shavad , yani dar baaz kardane file moshkeli pish Amade , ke in yani ehtemaalan hanooz ketabi vaarede ketaabkhaane nashode va file "File1.txt" hanooz sakhte nashode
		return -1;
	if (!File2)// agaar File2 NULL shavad , yani dar baaz kardane file moshkeli pish Amade , ke in yani hanooz ketabi gharz daade nashode va file "File2.txt" hanooz sakhte nashode
	{
		ofstream FilePeople("People.txt");//dar in sorate yek file be naame "File2.txt" misaazim
		FilePeople.close();
	}

	for (int c = 0; c < n; c++)
	{
		File1 >> BookId[c] >> Name[c] >> Writer[c] >> Publisher[c] >> Status[c];

		if (Id == BookId[c])
		{
			cout << endl << "Book:\t" << Name[c] << "\t" << Writer[c] << "\t" << Publisher[c] << "\t" << Status[c] << endl;
			cout << "Borrower:  ";
			if (Status[c] == 1)
				cout << "No One" << endl;
			else
			{
				int Temp1 = 0;
				File2 >> Temp1 >> BFirstName[c] >> BLastName[c] >> BDate[c];
				cout << BFirstName[c] << "\t" << BLastName[c] << "\t" << BDate[c] << endl;
			}
			cout << endl << "Are you sure? 1-No  2-Yes ";
			char t = getch();
			YesNo = t - 48;
			Flag = 1;
			if (t == '2')
			{
				BookId[c] = -1;
				Name[c] = "";
				Writer[c] = "";
				Publisher[c] = "";
				Status[c] = -1;
				BFirstName[c] = "";
				BLastName[c] = "";
				BDate[c] = "";
				// In onsore Araye haa raa az mahdodeye maghaadire ghaabele ghaboole barname kharej mikonim
			}
		}
	}
	File1.close();
	File2.close();
	if (Flag == 0)
		return 0;
	if (YesNo == 2)
	{
		cout << endl << "Book Deleted...";
		ofstream OutFile1(Address1);
		ofstream OutFile2(Address2);
		for (int c = 0; c < n; c++)
		{
			if (BookId[c] != -1)
			{
				OutFile1 << BookId[c] << "\t" << Name[c] << "\t" << Writer[c] << "\t" << Publisher[c] << "\t" << Status[c] << endl;
				if (Status[c] == 0)
				{
					OutFile2 << BookId[c] << "\t" << BFirstName[c] << "\t" << BLastName[c] << "\t" << BDate[c] << endl; // 3 Arayeye Akhar faghat baraaye ketaab haayi ke Status=1 ast por mikonim , baraaye baghiyeye ketaabhaa Anhaa raa khaali migozaarim
				}
			}
		}
		n--;
		OutFile1.close();
		OutFile2.close();
	}
	cout << endl << "Number of books: " << n << " " ; //namayeshe tedad ketabhaaye baaghi
	return 1;
}

void Find()
{
	string Name, Writer, Publisher, BFirstName, BLastName, BDate;
	int BookId = 0, Status = 0;
	int Matched = 0;
	string Word;
	int Id;
	ifstream File1(Address1);
	ifstream File2(Address2);
	if (!File1)
	{
		cout << "File1.txt Cannot be opened...Probably you didnt add any books to the program...";
		getch();
		return;
	}
	cout << "Find By  1-Id  2-Name  3-Writer  4-Publisher ";
	char FindMode = getch();
	system(CLEAR_SCREEN);
	if (FindMode == '1')
	{
		cout << endl << "Book Id: ";
		cin >> Id;
	}
	else if (FindMode >= '2' && FindMode <= '4')
	{
		cout << endl << "Search phrase: ";
		cin >> Word;
	}
	else
		return;
	while (!File1.eof())
	{
		File1 >> BookId >> Name >> Writer >> Publisher >> Status;
		if ((FindMode == 1 && Id == BookId) || (FindMode == 2 && Name == Word) || (FindMode == 3 || Writer == Word) || (FindMode == 4 || Publisher == Word))
		{
			Matched = 1;
			cout << endl << "Book:\t" << Name << "\t" << Writer<< "\t" << Publisher << "\t" << Status << endl;
			cout << "Borrower:  ";
			if (Status == 1)
				cout << "No One" << endl;
			else
			{
				int Temp1 = 0;
				File2 >> Temp1 >> BFirstName >> BLastName >> BDate;
				cout << BFirstName << "\t" << BLastName << "\t" << BDate<< endl;
			}
		}
	}
	if (Matched == 0)
		cout << endl << "Nothing Found...";
	File1.close();
	File2.close();
	

}