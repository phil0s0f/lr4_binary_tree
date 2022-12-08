#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

int N; // ���������� �������� � �������
int *mass;
bool flag = false;

void fileArray()
{
	mass = new int[100001];
	//FILE* file = fopen("C:\\Users\\user\\YandexDisk\\3 ���� ��\\���� � ��������� ������\\18,09 (1)\\array.txt", "r");
	//FILE* file = fopen("C:\\Users\\user\\YandexDisk\\3 ���� ��\\���� � ��������� ������\\18,09 (1)\\array1000.txt", "r");
	FILE* file = fopen("C:\\Users\\user\\YandexDisk\\3 ���� ��\\���� � ��������� ������\\lr\\100.txt", "r");
	for (int i = 0; i < 100000; i++)
	{
		fscanf(file, "%d", &mass[i]);
	}
	fclose(file);
	N = 100000;
}

void inputArray()
{
	cout << "������� ���������� ��������� �������: ";
	cin >> N;
	cout << "������� �������� �������: ";
	mass = new int[N+1];
	for (int i = 0; i < N; i++)
		cin >> mass[i]; 
}

void outputArray()
{
	for (int i = 0; i < N; i++)
		cout << mass[i] << " ";
	cout << endl;
}

void randArray()
{
	srand(time(NULL));
	cout << "������� ���������� ��������� �������: ";
	cin >> N;
	cout << "�������� �������: ";
	mass = new int[N];
	for (int i = 0; i < N; i++)
	{
		mass[i] = 1 + rand() % 100000000;
		cout << mass[i] << ' ';
	}
}

void sequentialSearch()
{
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	flag = false;
	cout << "������� ����: ";// (�� 1 �� "<< X <<") : ";
	int key;
	cin >> key;
	QueryPerformanceCounter(&start);
	for (int i = 0; i < N; i++)
	{
		if (mass[i] == key)
		{
			QueryPerformanceCounter(&finish);
			flag = true;
			cout << "�����. �������: " << i + 1;
			break;
		}
	}
	if (!flag)
	{
		QueryPerformanceCounter(&finish);
		cout << "�������.";
	}
	flag = false;
	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\n��������� %.10f �����������\n", time);
}

void fastSequentialSearch()
{
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	cout << "������� ����: ";// (�� 1 �� "<< X <<") : ";
	int key;
	cin >> key;
	mass[N+1] = key;

	QueryPerformanceCounter(&start);

	int i = 0;
	while (mass[i] != key)
			i++;
	if (i <= N)
	{
		QueryPerformanceCounter(&finish);
		cout << "�����. �������: " << i + 1;
	}
	else
	{
		QueryPerformanceCounter(&finish);
		cout << "�������.";
	}
	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\n��������� %.10f �����������\n", time);
}

void sort()
{
	int temp;
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
		{
			if (mass[i] > mass[j])
			{
				temp = mass[i];
				mass[i] = mass[j];
				mass[j] = temp;
			}
		}
	flag = true;
}

void binarySearch()
{
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);
	cout << "�������� ������ � ������� �����������: ";
	outputArray();
	cout << "������� ����: ";// (�� 1 �� "<< X <<") : ";
	int key;
	cin >> key;
	QueryPerformanceCounter(&start);
	int midd = 0, left = 0, right = N;
	while(left <= right)
	{
		midd = (left + right) / 2;

		if (key < mass[midd])       
			right = midd - 1;      
		else if (key > mass[midd])  
			left = midd + 1;    
		else                       
		{
			QueryPerformanceCounter(&finish);
			cout << "�����. �������: " << midd + 1;          
			break;
		}

		if (left > right)         
		{
			QueryPerformanceCounter(&finish);
			cout << "�������.";
			break;
		}
	}
	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\n��������� %.10f �����������\n", time);
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x;
	flag = false;
	for (;;)
	{
		cout << endl << "1 - ���� �������" << endl
			<< "2 - ��������� ������� " << endl
			<< "3 - ���������� ������� �� �����" << endl
			<< "4 - ���������������� ����� " << endl
			<< "5 - ������� ���������������� �����" << endl
			<< "6 - ��������  �����" << endl
			<< "7 - ����� �������" << endl
			<< "0 - �����" << endl << endl;
		cin >> x;

		switch (x)
		{
			case 1: inputArray();
				break;
			case 2: randArray();
				break;
			case 3: fileArray();
				break;
			case 4: sequentialSearch();
				break;
			case 5: fastSequentialSearch();
				break;
			case 6: 
				if (flag == false)
					sort();
				binarySearch();
				break;
			case 7: outputArray();
				break;
			case 0: delete[] mass;
				exit(1);            
				break;
		}
	}
}