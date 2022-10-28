
/*      masire file : pusheye barname          */
/*      name file : pb.txt                     */

#include "iostream"
#include "fstream"
#include "../include/console.h"
#include "string"
#include "stdlib.h"

#define max 1000
using namespace std;

int main()
{
	char choice = 0;
	while (choice != '5')
	{
		cout << "1) Add Records\n";
		cout << "2) Delete a Record\n";
		cout << "3) Find Records\n";
		cout << "4) Show Records by Group Type\n";
		cout << "5) Exit";

		choice = getch();
		system(CLEAR_SCREEN);
		if (choice == '1')
		{
			fstream fp("pb.txt", ios::app);
			if (!fp)
				ofstream fp("pb.txt");
			cout << "How many records do you want to add ?";
			int n;
			cin >> n;
			string firstname, lastname, telnumber, phonenumber, group;
			for (int i = 0; i < n; i++)
			{
				cout << "Enter the next record informations. ( firstname lastname telnumber phonenumber group )\n";
				cin >> firstname >> lastname >> telnumber >> phonenumber >> group;
				if (telnumber[0] == '-' && phonenumber[0] == '-')
					cout << "This record is not allowed to be saved since at least one number must be provided.\n\n";
				else if (firstname[0] == '-' || lastname[0] == '-' || group[0] == '-')
					cout << "This record is not allowed to be saved since at least one of the essential inputs is missing.\n\n";
				else
				{
					fp << firstname << "\t" << lastname << "\t";
					if (telnumber[0] == '-')
						fp << '\0' << "\t";
					else
						fp << telnumber << "\t";
					if (phonenumber[0] == '-')
						fp << '\0' << "\t";
					else
						fp << phonenumber << "\t";
					fp << group <<endl;
				}
			}
			fp.close();
			pause;cin.get();
		}
		else
		{
			string load[max][5];
			int end = 0;
			ifstream fp2("pb.txt"); 
			while (!fp2.eof())
			{
				for (int i = 0; i < 5; i++)
					fp2 >> load[end][i];
				end++;
			}

			fp2.close();
			if (choice == '2')
			{
				cout << "Enter the record's tel or phone number : \n";
				string target;
				cin >> target;
				for (int i = 0; i < end; i++)
				{
					if (target == load[i][2] || target == load[i][3])
					{
						cout << endl<<load[i][0] << "\t" << load[i][1] << "\t" << load[i][2] << "\t" << load[i][3] << "\t" << load[i][4];
						cout << "\nAre you sure about deleting this record ? 0) No\t1) Yes ";
						char ch = getch();
						if (ch == '1')
							load[i][0][0] = '\0';

					}
				}
				ofstream fp3("pb.txt");
				for (int i = 0; i < end; i++)
					if (load[i][0][0] != '\0')
						fp3 << load[i][0] << "\t" << load[i][1] << "\t" << load[i][2] << "\t" << load[i][3] << "\t" << load[i][4] << endl;
				fp3.close();
				cout << endl;
				pause;cin.get();
			}
			else if (choice == '3')
			{
				cout << "Find by : 0) firstname 1) lastname ";
				char ch = getch();
				string target;
				cout << "\nEnter the name : ";
				cin >> target;
				for (int i = 0; i < end; i++)
					if (target == load[i][ch - 48])
						cout << endl << load[i][0] << "\t" << load[i][1] << "\t" << load[i][2] << "\t" << load[i][3] << "\t" << load[i][4];
				cout << endl;
				pause;cin.get();
			}
			else if (choice == '4')
			{
				cout << "Which group do you want to be shown ?";
				string target;
				cin >> target;
				for (int i = 0; i < end; i++)
				{
					if (target == load[i][4])
						cout << load[i][0] << "\t" << load[i][1] << "\t" << load[i][2] << "\t" << load[i][3] << "\t" << load[i][4] << endl;
				}
				pause;cin.get();
			}
		}
		system(CLEAR_SCREEN);
	}
}