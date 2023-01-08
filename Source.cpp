/*
	Title			: Hotel Management System
	Language		: C++
	Author			: Victor Maravilla
	Date Created	: 10-22-2022
	Last Modified	: 01-08-2023
*/

#include<fstream>
#include<iostream>
#include<conio.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<process.h>
#include<dos.h>

using namespace std;


//Interface Functions
void intro() {
	cout << "\n\n C++ Project On Hotel Management System";
	cout << "\n\n\n\n";
}

void head() {
	system("cls");
	cout << "\t\t\t\t\t\t";
	cout << "*******HOTELS R US*******";
	cout << "\t\t\t\t\t\t\t\t";
}
void time() {
	int i = 0;
	long long j;
	cout << "	\nConnecting to Server\n\n";
}
//Hotel Class
class hotel {
private:
	int room_no;
	char name[30];
	char address[50];
	char phone[15];
	int days;
	float fare;
public:
	void main_menu();		//to display the main menu
	void add();				//to book a room
	void display(); 		//to display the customer record
	void rooms();			//to display allotted rooms
	void edit();			//to edit the customer record
	int check(int);	     	//to check room status
	void modify(int);		//to modify the record
	void delete_rec(int);   //to delete the record
};

// Main Menu
void hotel::main_menu() {
	int choice = 0;
	while (choice != 5) {
		system("cls");
		head();
		cout << "\n\t\t\t\t*************";
		cout << "\n\t\t\t\t* MAIN MENU *";
		cout << "\n\t\t\t\t*************";
		cout << "\n\n\n\t\t\t1.Book A Room";
		cout << "\n\t\t\t2.Customer Record";
		cout << "\n\t\t\t3.Rooms Allotted";
		cout << "\n\t\t\t4.Edit Record";
		cout << "\n\t\t\t5.Exit";
		cout << "\n\n\t\t\tEnter Your Choice: ";
		cin >> choice;
		switch (choice) {
		case 1:	add();
			break;
		case 2: display();
			break;
		case 3: rooms();
			break;
		case 4:	edit();
			break;
		case 5: break;
		default: {
			cout << "\n\n\t\t\tWrong choice.....!!!";
			cout << "\n\t\t\tPress any key to continue....!!";
			system("pause");
		}
		}
	}
}

//Adding new room
void hotel::add() {
	system("cls");
	head();
	int r, flag;
	ofstream fout("Record.dat", ios::app);
	cout << "\n Enter Customer Details";
	cout << "\n ----------------------";
	cout << "\n\n Room no: ";
	cin >> r;
	flag = check(r);
	if (flag)
		cout << "\n Sorry..!!!Room is already booked";
	else {
		
		cout << " Name: ";
		cin.ignore();
		cin.getline(name, sizeof name);
		cout << " Address: ";
		cin.getline(address, sizeof address);
		cout << " Phone No: ";
		cin.getline(phone, sizeof phone);
		cout << " No of Days to Checkout: ";
		cin >> days;
		room_no = r;
		fare = days * 900;	//900 is currently set as the
							//default price per day
		fout.write((char*)this, sizeof(hotel));
		cout << "\n Room is booked...!!!";
	}
	system("pause");
	fout.close();
}

//Display Room details
void hotel::display() {
	system("cls");
	head();
	ifstream fin("Record.dat", ios::in);
	int r, flag = 0;
	cout << "\n Enter room no: ";
	cin >> r;
	while (!fin.eof()) {
		fin.read((char*)this, sizeof(hotel));
		if (room_no == r) {
			system("cls");
			head();
			cout << "\n Customer Details";
			cout << "\n ----------------";
			cout << "\n\n Room no: " << room_no;
			cout << "\n Name: " << name;
			cout << "\n Address: " << address;
			cout << "\n Phone no: " << phone;
			cout << "\n Days: " << days;
			cout << "\n Total Fare: " << fare;
			flag = 1;
		}
	}
	if (flag == 0)
		cout << "\n Sorry Room no. not found or vacant....!!\n";
	system("pause");
	fin.close();
}

//List of rooms from file
void hotel::rooms() {
	system("cls");
	head();
	ifstream fin("Record.dat", ios::in);
	cout << "\n\t\t\t    List Of Rooms Allotted";
	cout << "\n\t\t\t    ----------------------";
	while (!fin.eof()) {
		fin.read((char*)this, sizeof(hotel));
		cout << "\n Room no: " << room_no << "\n Name: " << name;
		cout << "\n Address: " << address << "\n Phone: " << phone;
		cout << "\n Days: " << days << "\n Total: " << fare;
		cout << "\n**********************************";
	}
	system("pause");
	fin.close();
}

//Edit an exsisting room
void hotel::edit() {
	system("cls");
	head();
	int choice, r;
	cout << "\n EDIT MENU";
	cout << "\n ---------";
	cout << "\n\n 1.Modify Customer Record";
	cout << "\n 2.Delete Customer Record";
	cout << "\n Enter your choice: ";
	cin >> choice;
	system("cls");
	head();
	cout << "\n Enter room no: ";
	cin >> r;
	switch (choice) {
	case 1:	modify(r);
		break;
	case 2:	delete_rec(r);
		break;
	default: cout << "\n Wrong Choice.....!!\n";
	}
	system("pause");
}

int hotel::check(int r) {
	int flag = 0;
	ifstream fin("Record.dat", ios::in);
	while (!fin.eof()) {
		fin.read((char*)this, sizeof(hotel));
		if (room_no == r) {
			flag = 1;
			break;
		}
	}
	fin.close();
	return(flag);
}

void hotel::modify(int r) {
	system("cls");
	head();
	long pos, flag = 0;
	fstream file("Record.dat", ios::in | ios::out | ios::binary);
	while (!file.eof()) {
		pos = file.tellg();
		file.read((char*)this, sizeof(hotel));
		if (room_no == r) {
			cout << "\n Enter New Details";
			cout << "\n -----------------";
			cout << "\n Name: ";
			cin.ignore();
			cin.getline(name, sizeof name);
			cout << " Address: ";
			cin.getline(address, sizeof address);
			cout << " Phone no: ";
			cin.getline(phone, sizeof phone);
			cout << " Days: ";
			cin >> days;
			fare = days * 900;
			file.seekg(pos);
			file.write((char*)this, sizeof(hotel));
			cout << "\n Record is modified....!!\n";
			flag = 1;
			break;
		}
	}
	if (flag == 0)
		cout << "\n Sorry Room no. not found or vacant...!!\n";
	file.close();
}

void hotel::delete_rec(int r) {
	system("cls");
	head();
	int flag = 0;
	char ch;
	ifstream fin("Record.dat", ios::in);
	ofstream fout("temp.dat", ios::out);
	while (!fin.eof()) {
		fin.read((char*)this, sizeof(hotel));
		if (room_no == r) {
			cout << "\n Name: " << name;
			cout << "\n Address: " << address;
			cout << "\n Phone No: " << phone;
			cout << "\n Days: " << days;
			cout << "\n Total Fare: " << fare;
			cout << "\n\n Do you want to delete this record(y/n): ";
			cin >> ch;
			if (ch == 'n')
				fout.write((char*)this, sizeof(hotel));
			flag = 1;
			break;
		}
		else
			fout.write((char*)this, sizeof(hotel));
	}
	fin.close();
	fout.close();
	if (flag == 0)
		cout << "\n Sorry room no. not found or vacant...!!\n";
	else {
		remove("Record.dat");
		rename("temp.dat", "Record.dat");
	}
}


//Main() Function
int main() {
	system("color A1");
	hotel h;
	system("cls");
	cout << "\n\n\n";
	intro();
	time();
	system("pause");
	system("cls");
	head();
	char id[6], pass[7];
	cout << "\n\n\t\tPlease Log in to the system\n\n";
	cout << "\n\n\n\t\tusername:  ";
	cin >> id;
	cout << "\n\t\tpassword:  ";
	cin >> pass;
	cout << "\n\n\t";
	time();
	cout << "\t";
	// Username = admin
	// password = 1234
	if (strcmp(id, "admin") == 0 && strcmp(pass, "1234") == 0)
		cout << "\n\n\t\t\t  !!!Login Successfull!!!";
	else {
		cout << "\n\n\t!!!INVALID CREDENTIALS!!!\n";
		system("pause");
		exit(-1);
	}
	system("cls");
	h.main_menu();
	system("cls");

	return 0;
}
