#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
int* steck = new int[1];
int n = 0; // ���������� ��������� � �����
int j = 0; 

int N = 0; // ���������� ��������� � �������

struct queue
{
	int num;
	queue* next;
	queue* head;
	queue* tail;
} Q;
	
//���������� �������� � ����
void addSteck() // ���� ������.
{
	int a;
	cout << "������� ����� �������: ";
	cin >> a;

	for (int i = n; i > 0; i--)
	{
		int tmp = steck[i];
		steck[i] = steck[i - 1];
		steck[i - 1] = tmp;
	}
	steck[0] = a;  // ��������� � ���� �������
	j++;
	n = j;
}
//�������� �������� �������� �� �����
void deleteSteck()
{
	if (n == 0)
		cout << "���� ����" << endl;
	else
	{
		for (int i = 0; i < n; i++)
			steck[i] = steck[i + 1]; // ����� ������� �����
		n--;
		j--;
	}
}
// ����� ��������� ����� �� �����
void printSteck()
{
	if (n == 0)
		cout << "���� ����" << endl;
	else
	{
		cout << "�������� �����: ";
		for (int i = 0; i < n; i++)
			cout << steck[i] << setw(2);
	}
}


//���������� � �������
void addQueue(queue* Q) // ������� ����.
{
	int a;
	cout << "������� ����� �������: ";
	cin >> a;

	queue* temp = new queue;         
	Q->next = NULL;                       
	temp->num = a;                      
	if (Q->head != NULL) 
	{
		Q->tail->next = temp;
		Q->tail = temp;
	}
	else 
		Q->head = Q->tail = temp;
	N++;
}
//����� ��������� �������
void printQueue(queue* Q)
{

	queue* temp = Q->head;                       
	if (N==0) 				
			cout << "������� �����!\n";		
	else
	{
		cout << "�������: ";
		while (temp != Q->tail->next) 
		{                 
			cout << temp->num << setw(2);
			temp = temp->next;                     
		}
	}
}
// �������� 1�� �������� �������
void delQueue(queue* Q)
{
	if (N == 0)
				
		cout << "������� �����!\n";
	else
	{
		queue* temp = Q->head; 
		Q->head = Q->head->next; 
		//cout << "�������� �������:  " << temp->num << "\n";    
		N--;
	}
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x, y;
	for (;;)
	{
            cout  << endl <<"1 - ����" << endl
			<< "2 - �������" << endl
			<< "0 - �����" << endl << endl;
		cin >> x;
		switch (x)
		{
		case 1: 
		{
			do {
				cout << endl << endl << "1 - �������� ������� � ����" << endl
					<< "2 - ������� ������� �� �����" << endl
					<< "3 - ����� ��������� �����" << endl
					<< "4 - �������� �����" << endl
					<< "0 - �����" << endl << endl;
				cin >> y;
				switch (y)
				{
					case 1:
						cout << endl;
						addSteck();
						printSteck();
						break;
					case 2:
						cout << endl;
						deleteSteck();
						printSteck();
						break;
					case 3:
						cout << endl;
						printSteck();
						break;
					case 4:
						system("cls");
						break;
				}
			} while (y != 0);
		}
			  break;
		case 2: 
		{
			do {
				cout << endl << endl << "1 - �������� ������� � �������" << endl
					<< "2 - ������� ������� �� �������" << endl
					<< "3 - ����� �������� �������" << endl
					<< "4 - �������� �����" << endl
					<< "0 - �����" << endl << endl;
				cin >> y;
				switch (y)
				{
				case 1:
					cout << endl;
					addQueue(&Q);
					printQueue(&Q);
					break;
				case 2:
					cout << endl;
					delQueue(&Q);
					printQueue(&Q);
					break;
				case 3:
					cout << endl;
					printQueue(&Q);
					break;
				case 4:
					system("cls");
					break;
				}
			} while (y != 0);
		}
			  break;
		case 0:
			exit(1);
			break;
		}
	}
	delete[] steck;
}