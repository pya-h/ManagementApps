

#include "iostream"
#include "fstream"
#include "string"
#include "stdlib.h"

using namespace std;

int jadval()
{
	cout << "1) Ezaafe Kardan"<<endl;
	cout << "2) Hazf Kardan"<<endl;
	cout << "3) Peyda Kardan"<<endl;
	cout << "4) Namaayesh Daadan"<<endl;
	cout << "5) Khoroj";
	int n;
	cin >> n;
	return n;
}

void zakhire(string naam[], string faamily[], long int telephone[], long int mobile[], string goroh[], int tedaad)
{
	ofstream pf2("daftar.txt");
	for (int i = 0; i < tedaad; i++)
	{
		if (goroh[i] != "hazfi") //Aanhaayi ke gharaar bod hazf beshan , goroheshaan raa be "hazfi" taghyir daadim.pas nabaayad dar file neveshte shavand. ( moraaje'e shavad be else if(n == 2) )
			pf2 << naam[i] << " " << faamily[i] << "  " << telephone[i] << " " << mobile[i] << " " << goroh[i] << endl;
	}
	pf2.close();

}

int main()
{
	
	//vaared kardane file be haafezeye barnaame :
	string naam[500], faamily[500], goroh[500];
	long int telephone[500], mobile[500];
	int i = 0;
	int tedaade_azaa = 0;
	ifstream pf1("daftar.txt");
	if (!pf1)//darsorati ke file az avval mojof nabaashad barnaame be moshkel mokhorad.
		ofstream pf1("daftar.txt");
	else
	{
		while (!pf1.eof())
		{
			pf1 >> naam[i];
			pf1 >> faamily[i];
			pf1 >> telephone[i];
			pf1 >> mobile[i];
			pf1 >> goroh[i];
			i++;
			
		}
		tedaade_azaa = i - 1;
	}
	pf1.close();
	

	//tashkile jadval:
	int n = jadval();

	while ( n != 5 )
	{
		if (n == 1)
		{
			cout << "Chand nafar mikhaahid ezaafe konid?";
			int tedaad;
			cin >> tedaad;
			for (int i = tedaade_azaa; i < tedaad + tedaade_azaa; i++)
			{
				cout << "moshakhasaate nafare "<<i+1<<" raa vaared konid"<<endl;
				cout << "naam : ";
				cin >> naam[i];
				cout << "faamily :";
				cin >> faamily[i];
				cout << "telephone :";
				cin >> telephone[i];
				cout << "mobile :";
				cin >> mobile[i];
				cout << "goroh :";
				cin >> goroh[i];
				//barrasie errorhaa :
				if (telephone[i] == 0 && mobile[i] == 0)
				{
						cout << "error...hadde aghal yek shomaare baayad vaared shavad...dobaare vaared konid." << endl;
						i--;
				}
				else if (naam[i][0] == '\0' )
				{
					cout << "error...naam vaared nashode...dobaare vaared konid." << endl;
					i--;
				}
				else if (faamily[i][0] == '\0')
				{
					cout << "error...faamily vaared nashode...dobaare vaared konid." << endl;
					i--;
				}
				else if (goroh[i][0] == '\0')
				{
					cout << "error...goroh vaared nashode...dobaare vaared konid." << endl;
					i--;
				}

			}
			tedaade_azaa += tedaad;
			zakhire(naam, faamily, telephone, mobile, goroh, tedaade_azaa);
			cout << "baa movafaghiat zakhire shod.";
		}
		else if (n == 2)
		{
			cout << "shomaareye telephone yaa mobile shakhs raa vaared konid."<<endl;
			long int s;
			cin >> s;
			for (int i = 0; i < tedaade_azaa; i++)
			{
				if (s == telephone[i] || s == mobile[i])
				{
					cout << naam[i] << " " << faamily[i] << " " << telephone[i] << " " << mobile[i] << " " << goroh[i] <<endl;
					cout << "Aayaa az hazfe in shakhs motma'enid? ( tayid ba yes ) ";
					string t;
					cin >> t;
					if (t == "yes")
						goroh[i] = "hazfi";
					break;

				}
			}
			zakhire(naam, faamily, telephone, mobile, goroh, tedaade_azaa);
			cout << "baa movafaghiat hazf shod.";
		}
		else if (n == 3)
		{
			cout << "joste jo baa kodaam? ( naam yaa faamily )";
			string s1;
			cin >> s1;
			if (s1 == "naam")
				cout << "naam raa vaared konid." << endl;
			else if (s1 == "faamily")
				cout << "faamily raa vaared konid." << endl;
			string s2;
			cin >> s2;
			for (int i = 0; i < tedaade_azaa; i++)
			{
				if (s1 == "naam" && s2 == naam[i])
				{
					cout << naam[i] << " " << faamily[i] << " " << telephone[i] << " " << mobile[i] << " " << goroh[i] << endl;
				}
				else if (s1 == "faamily" && s2 == faamily[i])
				{
					cout << naam[i] << " " << faamily[i] << " " << telephone[i] << " " << mobile[i] << " " << goroh[i] << endl;
				}
			}
			system("pause");
		}
		else if (n == 4)
		{
			cout << "a'zaaye kodaam goroh raa mikhaahid bebinid?";
			string s;
			cin >> s;
			for (int i = 0; i < tedaade_azaa; i++)
			{
				if (s == goroh[i])
					cout << naam[i] << " " << faamily[i] << " " << telephone[i] << " " << mobile[i] << " " << goroh[i] << endl;
			}
			system("pause");
		}
		system("cls");
		n = jadval();
	}
}