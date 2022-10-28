#include <iostream>
#include <string>
#include <time.h>
#include <fstream>
#include <stdlib.h>
#include "../include/console.h"
#define max 100000


using namespace std;
void zakhiresazi(int tedad , int *id, string *ketab, string *nevisandeh, string *nasher, int *dastrasi, string *esm, string *famili, string *tarikh)
{
	ofstream fk("ketabha.txt");
	ofstream fa("ashkhas.txt");
	if (!fk || !fa)
		cout << "Zakhire sazi ba moshkel movajeh shod!\n\n";
	else
	{
		for (int i = 0; i < tedad; i++)
		{
			if (id[i] != 0)
			{
				fk << id[i] << "\t" << ketab[i] << "\t" << nevisandeh[i] << "\t" << nasher[i] << "\t" << dastrasi[i] << endl;
				if (dastrasi[i] == 0)
					fa << id[i] << "\t" << esm[i] << "\t" << famili[i] << "\t" << tarikh[i] << endl;
			}
		}
		cout << "Ba movafaghiyat zakhire shod.\n\n";
	}
	fk.close();
	fa.close();
}

int searchbaid(int tedad, int search, int *id)
{
	int natije = -1;
	for (int i = 0; i < tedad; i++)
	{
		if (id[i] == search && id[i] != 0)
		{
			natije = i;
			break;
		}
	}
	return natije;
}

int *searchbastring(int tedad, string search, string *dadeha)
{
	int natije[max] , jadid = 0;
	for (int i = 0; i < tedad; i++)
	{
		natije[i] = -1;
		if (dadeha[i] == search)
		{
			natije[jadid] = i;
			jadid++;
		}
	}
	return natije;
}
int main()
{
	srand(time(0));
	int *id = new int[max],*dastrasi = new int[max];
	string *ketab = new string[max], *nevisandeh = new string[max] , *nasher = new string[max], *esm = new string[max], *famili = new string[max], *tarikh = new string[max];
	int kononi = 0;

	ifstream testfk("ketabha.txt");
	ifstream testfa("ashkhas.txt");
	if (!testfa)
	{
		testfa.close();
		ofstream testfa2("ashkhas.txt");
		testfa2.close();
	}
	else
		testfa.close();
	if (!testfk)
	{
		testfk.close();
		ofstream testfk2("ketabha.txt");
		testfk2.close();
	}
	else
	{
		testfk.close();

		ifstream fk("ketabha.txt");
		ifstream fa("ashkhas.txt");
		if (!fk || !fa)
		{
			cout << "Bargozari ketabkhane ba moshkel robero shod!\n";
			pause;cin.get();// to prevent stream skipping 
			return 0;
		}

		while (fk >> id[kononi] >> ketab[kononi] >> nevisandeh[kononi] >> nasher[kononi] >> dastrasi[kononi])
		{
			if (dastrasi[kononi] == 0)
				fa >> id[kononi] >> esm[kononi] >> famili[kononi] >> tarikh[kononi];
			kononi++;
		}
		fk.close();
		fa.close();
	}
	while (1)
	{
		cout << "1.Ezafe kardan\n2.Gharz dadan ya pas gereftan\n3.Hazv\n4.Jostojo\n5.Khoroj\n";
		int n;
		cin >> n;
		system(CLEAR_SCREEN);
		if (n == 1)
		{
			int tedad;
			cout << "Chand ketab mikhahid ezafe konid? ";
			cin >> tedad;
			cout << "\n(Name ketab/Nevisandeh/Nasher)\n\n";
			for (int i = 0; i < tedad; i++)
			{
				cout << "Ketabe " << i + 1<<". ";
				cin >> ketab[kononi] >> nevisandeh[kononi] >> nasher[kononi];
				dastrasi[kononi] = 1;
				int testID,tekrari;
				do
				{
					tekrari = 0;
					testID = rand() % 90000;
					testID += 10000;
					for (int j = 0; j < kononi; j++)
					{
						if (testID == id[j])
						{
							tekrari = 1;
							break;
						}
					}
				} while (tekrari == 1);
				id[kononi] = testID;
				kononi++;
			}
			cout << "\n";
			zakhiresazi(kononi , id , ketab, nevisandeh, nasher, dastrasi, esm, famili, tarikh);
		}
		else if (n == 2)
		{
			int shenase;
			cout << "Lotfan id ketab ra vared namayid: ";
			cin >> shenase;
			int hadaf = searchbaid(kononi , shenase , id);
			system(CLEAR_SCREEN);
			if (hadaf != -1)
			{
				cout << "Ketabe " << ketab[hadaf] << " asare " << nevisandeh[hadaf] << " ( nasher: " << nasher[hadaf] << " ) ";
				if (dastrasi[hadaf] == 1)
				{
					cout << "be (Esm/Famili/Tarikhe gharz) :";
					cin >> esm[hadaf] >> famili[hadaf] >> tarikh[hadaf];
					dastrasi[hadaf] = 0;
					cout << "Gharz dadeh shod.\n\n";
				}
				else
				{
					cout << "az " << esm[hadaf] << " " << famili[hadaf] << " pas gerefte shod.\n\n";
					dastrasi[hadaf] = 1;
					esm[hadaf][0] = famili[hadaf][0] = tarikh[hadaf][0] = '\0';
				}
				zakhiresazi(kononi, id, ketab, nevisandeh, nasher, dastrasi, esm, famili, tarikh);
			}
			else
				cout << "Ketabe morede nazar yaft nashod!\n\n";

		}
		else if (n == 3)
		{
			int shenase;
			cout << "Lotfan id ketab ra vared namayid: ";
			cin >> shenase;
			int hadaf = searchbaid(kononi, shenase, id);
			system(CLEAR_SCREEN);
			if (hadaf != -1)
			{
				cout << "Ketab\\Nevisandeh\\Nasher\\Dastrasi\\Gharz girandeh\\Tarikh\n\n";
				cout << ketab[hadaf] << "\t" << nevisandeh[hadaf] << "\t" << nasher[hadaf] << "\t" << dastrasi[hadaf];
				if (dastrasi[hadaf] == 0)
				{
					cout << "\t" << esm[hadaf] << " " << famili[hadaf] << "\t" << tarikh[hadaf];
				}
				cout << "\n\nMotaenid ke mikhahid in ketab ra hazv konid?\ny. Yes\n";
				char t;
				cin >> t;
				system(CLEAR_SCREEN);
				if (t == 'y' || t == 'Y')
				{
					id[hadaf] = 0;
					dastrasi[hadaf] = -1;
					ketab[hadaf][0] = nevisandeh[hadaf][0] = nasher[hadaf][0] = esm[hadaf][0] = famili[hadaf][0] = tarikh[hadaf][0] = '\0';
					cout << "Hazv shod.\n\n";
					zakhiresazi(kononi, id, ketab, nevisandeh, nasher, dastrasi, esm, famili, tarikh);
				}
				else
					cout << "Amaliat laghv shod.\n\n";
			}
			else
				cout << "Ketabe morede nazar yaft nashod!\n\n";
		}
		else if (n == 4)
		{
			cout << "1. id\n2. Name Ketab\n3. Nevisandeh\n4. Nasher\n\n";
			cout << "Raveshe jostojo raa moshakhas nemayid: ";
			int r;
			cin >> r;
			system(CLEAR_SCREEN);
			if (r == 1)
			{
				int shenase;
				cout << "Lotfan id ketab ra vared namayid: ";
				cin >> shenase;
				int hadaf = searchbaid(kononi, shenase, id);
				system(CLEAR_SCREEN);
				cout << "Ketab\\Nevisandeh\\Nasher\\Dastrasi\\Gharz girandeh\\Tarikh\n\n";
				cout << ketab[hadaf] << "\t" << nevisandeh[hadaf] << "\t" << nasher[hadaf] << "\t" << dastrasi[hadaf];
				if (dastrasi[hadaf] == 0)
				{
					cout << "\t" << esm[hadaf] << " " << famili[hadaf] << "\t" << tarikh[hadaf];
				}
				cout << "\n\n";
			}
			else
			{
				string s;
				int *hadaf = nullptr;
				if (r == 2)
				{
					cout << "Lotfan name ketab ra vareh konid: ";
					cin >> s;
					hadaf = searchbastring(kononi, s, ketab);
				}
				else if (r == 3)
				{
					cout << "Lotfan name nevisandeh ra vareh konid: ";
					cin >> s;
					hadaf = searchbastring(kononi, s, nevisandeh);
				}
				else if (r == 4)
				{
					cout << "Lotfan name nasher ra vareh konid: ";
					cin >> s;
					hadaf = searchbastring(kononi, s, nasher);
				}
				else
					continue;
				system(CLEAR_SCREEN);
				if (hadaf != nullptr && hadaf[0] != -1)
				{
					cout << "Ketab\\Nevisandeh\\Nasher\\Dastrasi\\Gharz girandeh\\Tarikh\n\n";
					for (int i = 0; hadaf[i] != -1; i++)
					{
						cout << ketab[hadaf[i]] << "\t" << nevisandeh[hadaf[i]] << "\t" << nasher[hadaf[i]] << "\t" << dastrasi[hadaf[i]];
						if (dastrasi[hadaf[i]] == 0)
						{
							cout << "\t" << esm[hadaf[i]] << " " << famili[hadaf[i]] << "\t" << tarikh[hadaf[i]];
						}
						cout << "\n";
					}
					cout << "\n";
				}
				else
					cout << "Chizi peyda nashod!\n\n";
			}
		}
		else if (n == 5)
			return 0;
		pause;cin.get();// to prevent stream skipping 
		system(CLEAR_SCREEN);
	}
}