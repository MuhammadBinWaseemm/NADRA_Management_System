#include<iostream>
#include<string>
#include<fstream>
#include<time.h>
#include<conio.h>
#include <locale>
#include <Windows.h>
#include<iomanip>
#include"Accounts.cpp"

using namespace std;
Account A;
int max_record = 3;
int tries = 0;
void login();

class Colors
{
	public:	
	    int color=10;
	    int color1;
	    void Design()
	    {
	    	HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,color1);
		    cout<<"  ";
	    	
		}
	    const void Default()
	    {
	    	HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,color);
		}
	    const void Black()
	    {
	    	HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,0);
		    cout<<"  ";
		}
		const void White()
		{
			HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,255);
		    cout<<"  ";
		}
	    const void DarkBlue()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		    SetConsoleTextAttribute(console_color,1);
		    color1=17;
		}
		const void DarkGreen()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,2);
			color1=34;
		}
		const void Red()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,4);
			color1=68;
		}
		const void DarkPurple()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,5);
			color1=85;
		}
		const void Gold()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,6);
			color1=102;
		}
		const void Blue()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,9);
			color1=153;
		}
		const void Green()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,10);
			color1=170;
		}
		const void Turquoise()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,11);
			color1=187;
		}
		const void Coral()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
		    SetConsoleTextAttribute(console_color,12);
		    color1=204;
		}
		const void Pink()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,13);
			color1=221;
		}
		const void White1()
		{
			HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,15);
			color1=255;
		}
};
class Theme
{
	public:
		int color1;
		int color2;
		const void Design()
		{
			HANDLE console_colorr; 
			SetConsoleTextAttribute(console_colorr,color1);
			cout<<" ";
			SetConsoleTextAttribute(console_colorr,color2);
			cout<<" ";
		}
		const void Default()
		{
			HANDLE console_colorr; 
            console_colorr = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_colorr, 15);
			color1=0;
			color2=255;
		}
		const void Zebra()
		{
		    HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console_color,240);
            color1=255;
            color2=0;
		}
		const void Aqua()
		{
		    HANDLE console_colorr; 
            console_colorr = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_colorr,177);
			color1=187;
			color2=17;
		}
		const void Buraikan()
		{
		    HANDLE console_colorr; 
            console_colorr = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console_colorr,96);
            color1=102;
            color2=0;
		}
		const void Blueberry()
		{
		      HANDLE console_colorr; 
            console_colorr = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console_colorr,180);
            color1=187;
            color2=68;
		}
		const void Jamun()
		{
		    HANDLE console_colorr; 
            console_colorr = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(console_colorr,219);
            color1=221;
            color2=187;
		}	
};
Colors C;
Theme T;
void menuStyle(bool isTitle, string menuNumber, string menuText)
{
	int minusLengthPress = 5;
	int minusLengthMenu = 25;

	if (isTitle)
	{
		minusLengthPress = 12;
		cout<< "\t\t|" << setw(minusLengthPress - menuNumber.length()) << menuNumber << setw(minusLengthPress - menuNumber.length() - 5) << "|";
		cout << "|" << setw(minusLengthMenu - menuNumber.length() + 7) << menuText << setw(minusLengthMenu - menuNumber.length() - 5) << "|";
		cout << endl << "\t\t";
	}
	else
	{
		cout << "|" << setw(minusLengthPress - menuNumber.length()) << menuNumber << setw(minusLengthPress - menuNumber.length()) << "|";
		cout << "|" << setw(minusLengthMenu - menuNumber.length() + 7) << menuText << setw(minusLengthMenu - menuNumber.length() - 12) << "|";
		cout << endl << "\t\t";
	}
	for (int i = 0; i < minusLengthMenu * 3 - (minusLengthMenu / 1.1); i++)
	{
		cout << "-";
	}
	cout << endl << "\t\t";
}
void delay(int *a) {
	for (int i = 0; i < 210000; i++) { for (int j = 1; j < 900; j++) { a++; } }
}
void logo() {
	
    	cout <<
		R"(
                       _   _     _     _____   ____      _    
                      | \ | |   / \   |  __ \ |  _ \    / \   
                      |  \| |  / _ \  | |  \ || |_) |  / _ \  
                      | |\  | / ___ \ | |/ ||  _ <  / ___ \ 
                      || \|//   \\|/ || \\//   \_\
        )" << endl;
    	
	}



struct node {
	int value;
	node* link;
};
struct Queue {
	node *front, *rear;
	int counter;
};
void enQueue(Queue *queue, int value) {
	node *temp = new node;
	temp->value = value;
	if (queue->front == NULL)
		queue->front = temp;
	else
		queue->rear->link = temp;
	queue->rear = temp;
	queue->rear->link = queue->front;
}
string checkCounter(string token) {
	int i = 0;
	string Return;
	while (1) {
		Return = token[i];
		i++;
		if (token[i] == '\0')
			break;
	}
	return Return;
}
int checkTokenNumber(string token) {
	int i = 0; int j = 0;
	char Return[20] = "";
	while (1) {
		i++;
		if (token[i] == '\0') {
			i--;
			break;
		}
	}
	for (j = 0; j < i; j++)
		Return[j] = token[j];
	Return[j] = '\0';
	int a;
	a = atoi(Return);
	return a;
}

class person {
public:
	string Fname, Lname, gender, address, ID;
	int D, M, Y, age, dose;
	person *left, *right;
	void getData() {
		system("cls");
		cout << "\n\t\t\t\t\tFirst-Name: ";
		cin >> Fname;
		cout << "\t\t\t\t\tLast-Name: ";
		cin >> Lname;
	loop:
		cout  << "\t\t\t\t\tDate of Birth:"  << " \n\t\t\t\t\t\tDay: " ;
		cin >> D;
		cout << "\t\t\t\t\t\tMonth: ";
		cin >> M;
		cout << "\t\t\t\t\t\tYear: ";
		cin >> Y;
		age = 2022 - Y;
		if (age < 0) {
			cout  << "\t\t\t\t\tOnly positives number allowed!!\n";
			goto loop;
		}
		if (age > 100) {
			cout  << "\t\t\t\t\tYou are DEAD BRO!!!!!!\n";
			goto loop;
		}
		char g;
	loop1:
		cout <<  "\t\t\t\t\tGender of " << Fname << " (M/F): ";
		cin >> g;
		if (g == 'm' || g == 'M')
			gender = "Male";
		else if (g == 'f' || g == 'F')
			gender = "Female";
		else {
			cout << "\n\t\t\t\t\tWrong Detail!!\n";
			goto loop1;
		}
	loop2:
		cout  << "\n\t\t\t\t\tVaccine Dose Taken: " ;
		cin >> dose;
		if (!(dose >= 0 && dose <= 2)) {
			cout << "\n\t\t\t\t\tWrong Detail!!\n";
			goto loop2;
		}
		cout << "\n\t\t\t\t\tAddress: ";
		getline(cin >> ws, address);
		int I[13] = { 6,1,1,0,1,1,5,2,2,1 };
		srand(time(0));
		for (int i = 9; i < 13; i++)
			I[i] = rand() % 9;
		for (int i = 0; i < 13; i++) {
			ID.push_back(I[i]+48);
			if (i == 4 || i == 11)
				ID.push_back('-');
		}
	}
};

class familyTree {
public:
	person *root;
	familyTree() {
		root = NULL;
	}

	person *search(person *temp, string per, string g) {
		if (temp == NULL || temp->Fname == per)
			return temp;
		if (temp->Fname != per && (g == "m" || g == "M" || g == "Male" || g == "male"))
			return search(temp->right, per, g);
		else
			return search(temp->left, per, g);
	}

	void addNewPerson() {
		auto temp = new person();
		temp->getData();
		string personChild, gen;
		if (root == NULL) {
			cout  << "\n\t\t\t\t\tFirst person added to the family!\n";
			root = temp;
		}
		else {
		again:
			cout  << "\t\t\t\t\tEnter Name of Person \"" << temp->Fname << "\" is related to: " ;
			cin >> personChild;
			cout << "\t\t\t\t\t"  << personChild << " is Male?(Y/N): " ;
			cin >> gen;
			if (search(root, personChild, (gen == "y" || gen == "Y" ? "M" : "F"))) {
				int opt;
				cout  << "\n\t\t\t\t\tWhat is the family relation?\n"
					<< "\t\t\t\t\t1: If "  << temp->Fname  << " is " << "Mother"  << " of "  << personChild
					 << "\n\t\t\t\t\t2: If "  << temp->Fname<< " is "  << "Father"  << " of "  << personChild
					 << "\n\t\t\t\t\tEnter: " ;
			loop1:
				cin >> opt;
	
				if (opt < 1 || opt > 2) {
					cout << "\n\t\t\t\t\tOnly a number of 1 or 2 is accepted!\n"
					 << "\t\t\t\t\tEnter: " ;
					goto loop1;
				}
				switch (opt) {
				case 1:
					addMother(search(root, personChild, gen), temp);
					cout << "\t\t\t\t\t"  << temp->Fname  << " is added as Mother!\n" ;
					break;
				case 2:
					addFather(search(root, personChild, gen), temp);
					cout << "\t\t\t\t\t"  << temp->Fname  << " is added as Father!\n" ;
					break;
				default:
					cout  << "\t\t\t\t\tError!!\n" ;
					system("pause");
				}
			}
			else {
				char ch;
				cout << "\n\t\t\t\t\tData Not Found!!"<<"\n\t\t\t\t\tDo you want to Try Again (Y/N): ";
				cin >> ch;
	
				if (ch == 'y' || ch == 'Y')
					goto again;
				else {}
			}
		}
	}
	void addMother(person *a, person *b) {
		if (a->left == NULL)
			a->left = b;
		else
			addMother(a->left, b);
	}
	void addFather(person *a, person *b) {
		if (a->right == NULL)
			a->right = b;
		else
			addFather(a->right, b);
	}

	void show(person *ptr) {
		cout << "\n\t\t\t\t\tName: "<< ptr->Fname + " " + ptr->Lname;
		cout << "\n\t\t\t\t\tAge: "  << ptr->age;
		cout  << "\n\t\t\t\t\tGender: " << ptr->gender;
		cout  << "\n\t\t\t\t\tCNIC: "  << ptr->ID;
		if (ptr->right == NULL) {
			cout  << "\n\n\t\t\t\t\tFather Data: N/A\n" ;
		}
		else {
			cout  << "\n\n\t\t\t\t\tFather Name: "  << ptr->right->Fname + " " + ptr->right->Lname;
			cout  << "\n\t\t\t\t\tFather Age: "  << ptr->right->age;
			cout  << "\n\t\t\t\t\tFather CNIC: "  << ptr->right->ID;
		}
		if (ptr->left == NULL) {
			cout  << "\n\n\t\t\t\t\tMother Data: N/A\n" ;
		}
		else {
			cout  << "\n\n\t\t\t\t\tMother Name: "  << ptr->left->Fname + " " + ptr->left->Lname;
			cout  << "\n\t\t\t\t\tMother age: "  << ptr->left->age;
			cout  << "\n\t\t\t\t\tMother CNIC: "  << ptr->left->ID;
		}
	}

	void card(person *ptr) {
		if (ptr->right == NULL) {
			cout  << "\n\t\t\t\t\tFather Data Not Found!!\n" ;
			system("pause");
			system("cls");
		}
		else {
			string country = "Pakistan";
			int idate = 1, imonth = 5, iyear = 2023;
			int a = 0;
			system("cls");
			delay(&a);			cout << "\t\t\t\t\t**" << endl;
			delay(&a);			cout << "\t\t\t\t\t*ISLAMIC REPUBLIC OF PAKISTAN*" << endl;
			delay(&a);			cout << "\t\t\t\t\t__" << endl;
			delay(&a);			cout << "\t\t\t\t\tName                                    " << endl;
			delay(&a);			cout << "\t\t\t\t\t    " << ptr->Fname << " " << ptr->Lname << endl;
			delay(&a);			cout << "\t\t\t\t\t__" << endl;
			delay(&a);			cout << "\t\t\t\t\tFather Name                             " << endl;
			delay(&a);			cout << "\t\t\t\t\t    " << ptr->right->Fname << " " << ptr->right->Lname << endl;
			delay(&a);			cout << "\t\t\t\t\t__" << endl;
			delay(&a);			cout << "\t\t\t\t\tGender       CNIC#            " << endl;
			delay(&a);			cout << "\t\t\t\t\t" << ptr->gender << "              \t|";
			delay(&a);			cout << ptr->ID << "               " << endl;
			delay(&a);			cout << "\t\t\t\t\t__" << endl;
			delay(&a);			cout << "\t\t\t\t\tIssue Date" << "    |" << "Expiry Date          " << endl;
			delay(&a);			cout << "\t\t\t\t\t    " << idate << "-" << imonth << "-" << iyear << "    \t|" << idate << "-" << imonth << "-" << iyear + 10 << endl;
			delay(&a);			cout << "\t\t\t\t\t__" << endl;
			delay(&a);			cout << "\t\t\t\t\tAddress\n\t";
			delay(&a);			cout << "\t\t\t\t\t" << ptr->address << endl;
			delay(&a);			cout << "\t\t\t\t\t**\n\n\n\n\n\n";
		}
	}

	void Ccertificate(person *p) {
		system("cls");
		cout << "\t\t\t\t\tMINISTRY OF NATIONAL HEALTH SERVICES REGULATIONS AND CORDINATION" << endl;
		cout << "\t\t\t\t\tIMMUNIZATION CERTIFICATE FOR COVID-19" << endl;
		cout << "\t\t\t\t\tName: " << p->Fname << " " << p->Lname << endl;
		cout << "\t\t\t\t\tDate of Birth: " << p->D << "-" << p->M << "-" << p->Y << endl;
		cout << "\t\t\t\t\tIdentity No: " << p->ID;
		cout << "\n\t\t\t\t\tHas been administrated COVID-19 following vaccination:" << endl;
		cout << "\t\t\t\t\tDoses:" << p->dose << endl;
		if (p->dose == 1)
			cout << "\t\t\t\t\tPartially_Vaccinated!\n";
		else if (p->dose == 2)
			cout << "\t\t\t\t\tFull_Vaccinated.\n" ;
		else
			cout << "\t\t\t\t\tNot_Vaccinated!!!\n" ;
	}

	void printInOrder(person *person, int space) {
		auto count = 7;
	
		space += count;
		if (person != NULL) {
			if (person->right != NULL)
				printInOrder(person->right, space);
			for (int i = count; i < space; i++)
				cout << " ";
			cout << person->Fname << "\n";
			if (person->left != NULL)
				printInOrder(person->left, space);
		}
		else
			cout  << "No tree exist!\n";
	}

	void saveData(person *person) {
		if (person != NULL) {
			addToFile(person);
			if (person->right != NULL)
				saveData(person->right);
			if (person->left != NULL)
				saveData(person->left);
		}
		else
			cout  << "No Data Exist!\n";
	}
	void addToFile(person *temp)
	{
		ofstream myFile;
		myFile.open("Record.txt", ios::app);

		myFile << "\t\t\tName: " << temp->Fname + " " + temp->Lname + "\n";
		myFile << "\t\t\tAge: " << to_string(temp->age) + "\n";
		myFile << "\t\t\tGender: " << temp->gender + "\n";
		myFile << "\t\t\tCNIC: " << temp->ID + "\n";
		myFile << "\t\t\tAddress: " << temp->address + "\n";
		myFile << "\t\t\tDOB: " << to_string(temp->D) + "-";
		myFile << to_string(temp->M) + "-";
		myFile << to_string(temp->Y) + "\n";
		myFile << "\t\t\tVaccine Dose: " << to_string(temp->dose) + "\n";
		if (temp->right == NULL) {
			myFile << "\n\n\t\t\tFather Data: N/A\n";
		}
		else {
			myFile << "\n\n\t\t\tFather Name: " << temp->right->Fname + " " + temp->right->Lname;
			myFile << "\n\t\t\tFather Age: " << temp->right->age;
			myFile << "\n\t\t\tFather CNIC: " << temp->right->ID << endl;
		}
		if (temp->left == NULL) {
			myFile << "\n\n\t\t\tMother Data: N/A\n";
		}
		else {
			myFile << "\n\n\t\t\tMother Name: " << temp->left->Fname + " " + temp->left->Lname;
			myFile << "\n\t\t\tMother age: " << temp->left->age;
			myFile << "\n\t\t\tMother CNIC: " << temp->left->ID << endl;
		}
		myFile << "-------------------------------------------------------------\n";

		myFile.close();
	}
	void readFromFile() {

		string myText;
		ifstream MyFile("Record.txt");

		while (getline(MyFile, myText))
		{
			cout << myText << "\n";
		}
		cout << endl;
		MyFile.close();
	}
};

void Menu() {
	menuStyle(true, "Press", "Main Menu");
	menuStyle(false, "1", "Add new person");
	menuStyle(false, "2", "Show information of a person.");
	menuStyle(false, "3", "Print complete family-tree.");
	menuStyle(false, "4", "Show Card View.");
	menuStyle(false, "5", "Show Corona Certificate.");
	menuStyle(false, "6", "Show All Data.");
	menuStyle(false, "7", "Theme");
	menuStyle(false, "8", "SignOut");
	cout << "\n\t\tYour choice: ";
}

int main() {
	familyTree fT;
	int a;
	string option;
	string str, g;
	int tokencounterA = 0;
	auto *queueA = new Queue; queueA->front = queueA->rear = NULL; queueA->counter = 1;
	LOGIN:;
	system("cls");
	HANDLE console_color; 
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color,10);
	login();
menu:
	tokencounterA++;
	system("cls");
	cout << "\n\t\t\t\t\t---------------------------------" << endl;
	cout << "\t\t\t\t\t\tToken Number : " << tokencounterA << "A " << endl;
	cout << "\t\t\t\t\t---------------------------------" << endl;
	enQueue(queueA, tokencounterA);
	cout << "\t\t\t\t\t      ---------------------" << endl;
	cout << "\t\t\t\t\t      | Counter Number : A |" << endl;
	cout << "\t\t\t\t\t      ---------------------\n\t\t\t\t\t";
	system("pause");
	system("cls");
	logo();
	string token;
countermenu:
	cout << "\t\t\t\tEnter Token Number: ";
	cin >> token;
	while (true) {
	main:
		system("cls"); 
		string counter = checkCounter(token);
		int tokenNumber = checkTokenNumber(token);
		if (counter == "A" || counter == "a")
		{
			system("cls");
			logo();
			cout << "\t\t\t**" << endl;
			cout << "\t\t\t|       Welcome To Counter A       |" << endl;
			cout << "\t\t\t**" << endl;
			cout << "\t\t\t\tCurrent Number is : " << queueA->counter << "A" << endl;
			cout << "\t\t ---------------------------------------------------" << endl;
			if (tokenNumber > queueA->counter)
			{
				cout << "\t\t\t\t\tPlease wait For your Turn." << endl;
				system("pause");
				system("cls");
				goto countermenu;

			}
			else if (tokenNumber < queueA->counter)
			{
				cout << "\t\t\t\t\tToken Already Used -- Please Get a New Token Number." << endl;
				system("pause");
				system("cls");
				goto menu;
			}
		}
		else {
			cout << "\t\t\t\t\tInvalid Token Number! Please Try Again." << endl;
			system("pause");
			system("cls");
			goto menu;
		}
		Menu();

		cin >> option;
		cin.ignore();
		switch (option[0])
		{
		case '1':
			fT.addNewPerson();
			cout << "\t\t\t\t\t";
			system("pause");
			break;
		case '2':
			system("cls");
			cout << "\t\t\t\t\tEnter name of person to show information: " ;
			cin >> str;
			cout << "\t\t\t\t\t" << str << " is Male?(Y/N): " ;
			cin >> g;

			if (fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F"))) {
				fT.show(fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F")));
				fT.addToFile(fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F")));
			}
			else
				cout  << "\n\t\t\t\t\tData Not Found!!\n" ;
			system("pause");
			break;
		case '3':
			system("cls"); 
			cout << "\n\n\n\n\n\t";
			fT.printInOrder(fT.root, 0);
			cout << "\n\n\n\n\n\n\n\n\n\n";
			system("pause");
			break;
		case '4':
			system("cls");
			cout << "\t\t\t\t\tEnter name of person to view card: ";
			cin >> str;
			cout << "\t\t\t\t\t" << str << " is Male?(Y/N): " ;
			cin >> g;

			if (fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F"))) {
				fT.card(fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F")));
			}
			else
				cout  << "\n\t\t\t\t\tData Not Found!!\n" ;
			system("pause");
			break;
		case '5':
			system("cls");
			cout << "\t\t\t\t\tEnter name of person to view Certificate: ";
			cin >> str;
			cout << "\t\t\t\t\t" << str << " is Male?(Y/N): " ;
			cin >> g;
	
			if (fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F"))) {
				fT.Ccertificate(fT.search(fT.root, str, (g == "y" || g == "Y" ? "M" : "F")));
			}
			else
				cout  << "\n\t\t\t\t\tData Not Found!!\n" ;
			system("pause");
			break;
		case '6':
			system("cls");
			fT.readFromFile();
			system("pause");
			break;
		case '7':
			{
				char ch;
	
    Themes:system("cls");
    cout<<"\n\t\tSet a Theme : ";
	cout<<"\n\n\t1.Default        ";
	T.Default();
	T.Design();
	C.Default();

	cout<<"\n\n\t2.Zebra          ";
	T.Zebra();
	T.Design();
	C.Default();

	cout<<"\n\n\t3.Aqua           ";
	T.Aqua();
	T.Design();
	C.Default();

	cout<<"\n\n\t4.Buraikan       ";
	T.Buraikan();
	T.Design();
	C.Default();

	cout<<"\n\n\t5.Blueberry      ";
	T.Blueberry();
	T.Design();
	C.Default();
	cout<<"\n\n\t6.Strawberry     ";
	T.Jamun();
	T.Design();
	C.Default();
	
	cout<<"\n\nConfirm(C)";

	cout<<"\n\n\tChoose from (1-6) : ";
	choice:;
	cin>>ch;
	cin.ignore();
	switch(ch)
	{
		case '1':
			T.Default();
			C.color=15;
			
			break;
		case '2':
			T.Zebra();
			C.color=240;
			
			break;
		case '3':
			T.Aqua();
			C.color=177;
			
			break;
		case '4':
			T.Buraikan();
			C.color=96;
			
			break;
		case '5':
			T.Blueberry();
			C.color=180;
			
			break;
		case '6':
			T.Jamun();
			C.color=219;
			
			break;
		case 'c':
		case 'C':
			goto settings;
			break;
		default:
			HANDLE console_color; 
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,4);
			cout<<"\n\t\tInvalid Choice";
	
            console_color = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(console_color,10);
			goto choice;
			break;
	}
	goto Themes;
	settings:system("cls");
			break;
		}
		case '8':
			fT.saveData(fT.root);
			goto LOGIN;
			break;
		default:
			cout  << "\n\t\t\t\t\tWrong Choice!!\n";
			system("pause");
			goto main;
		}
	}
}

void login() {
	int x;
	HANDLE console_color; 
    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console_color,10);
    int ch ;
    while(1)
    {
	    cout<<"\n\t\tNADRA Management System";                   //Account Management System
	    cout<<"\n\t\t1.SignUp";     
	    cout<<"\n\t\t2.SignIn";
	    cout<<"\n\t\t3.Exit";
	    cout<<"\n\t\tChoose from (1-3) : ";
	    cin>>ch;
	    cin.ignore();
	    switch(ch)
	    {
	    	case 1:
	    		A.SignUp();                          //Different Cases handled using switch
	    		system("cls");
	    		break;
	    	case 2:
	    		x=A.Signin();
	    		system("cls");
				if(x==1)
					return;
	    		break;
	    	case 3:
				exit(0);
	    	default:
	    		system("cls");
	    		HANDLE console_color; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,4);
	    		cout<<"\n\t\tInvalid Input"; 
			    console_color = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(console_color,15);
	    		break;
		}
	}
}