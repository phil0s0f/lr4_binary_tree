#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;
int* steck = new int[1];
int n = 0; // количество элементов в стеке
int j = 0; 

int N = 0; // количество элементов в очереди

struct queue
{
	int num;
	queue* next;
	queue* head;
	queue* tail;
} Q;
	
//добавление элемента в стек
void addSteck() // стек послед.
{
	int a;
	cout << "Введите новый элемент: ";
	cin >> a;

	for (int i = n; i > 0; i--)
	{
		int tmp = steck[i];
		steck[i] = steck[i - 1];
		steck[i - 1] = tmp;
	}
	steck[0] = a;  // добавляем в стек элемент
	j++;
	n = j;
}
//удаление верхнего элемента из стека
void deleteSteck()
{
	if (n == 0)
		cout << "Стек пуст" << endl;
	else
	{
		for (int i = 0; i < n; i++)
			steck[i] = steck[i + 1]; // сдвиг массива влево
		n--;
		j--;
	}
}
// вывод элементов стека на экран
void printSteck()
{
	if (n == 0)
		cout << "Стек пуст" << endl;
	else
	{
		cout << "Элементы стека: ";
		for (int i = 0; i < n; i++)
			cout << steck[i] << setw(2);
	}
}


//добавление в очередь
void addQueue(queue* Q) // очередь связ.
{
	int a;
	cout << "Введите новый элемент: ";
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
//вывод элементов очереди
void printQueue(queue* Q)
{

	queue* temp = Q->head;                       
	if (N==0) 				
			cout << "Очередь пуста!\n";		
	else
	{
		cout << "Очередь: ";
		while (temp != Q->tail->next) 
		{                 
			cout << temp->num << setw(2);
			temp = temp->next;                     
		}
	}
}
// удаление 1го элемента очереди
void delQueue(queue* Q)
{
	if (N == 0)
				
		cout << "Очередь пуста!\n";
	else
	{
		queue* temp = Q->head; 
		Q->head = Q->head->next; 
		//cout << "Удалённый элемент:  " << temp->num << "\n";    
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
            cout  << endl <<"1 - СТЕК" << endl
			<< "2 - ОЧЕРЕДЬ" << endl
			<< "0 - Выход" << endl << endl;
		cin >> x;
		switch (x)
		{
		case 1: 
		{
			do {
				cout << endl << endl << "1 - Добавить элемент в стек" << endl
					<< "2 - Удалить элемент из стека" << endl
					<< "3 - Вывод элементов стека" << endl
					<< "4 - Очистить экран" << endl
					<< "0 - Выход" << endl << endl;
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
				cout << endl << endl << "1 - Добавить элемент в очередь" << endl
					<< "2 - Удалить элемент из очереди" << endl
					<< "3 - Вывод элеметов очереди" << endl
					<< "4 - Очистить экран" << endl
					<< "0 - Выход" << endl << endl;
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