#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>

using namespace std;

int N; // количество элеменов в массиве
int* A;
int* B;

void fileArray()
{
	cout << "Введите количество элементов массива в файле: ";
	cin >> N;
	A = new int[N];
	FILE* file = fopen("C:\\Users\\user\\YandexDisk\\3 курс пи\\типы и структуры данных\\lr (1)\\100.txt", "r");
	for (int i = 0; i < N; i++)
	{
		fscanf(file, "%d", &A[i]);
	}
	fclose(file);
}

void inputArray()
{
	cout << "Введите количество элементов массива: ";
	cin >> N;
	cout << "Введите элементы массива: ";
	A = new int[N];
	for (int i = 0; i < N; i++)
		cin >> A[i];
}

void outputArray()
{
	for (int i = 0; i < N; i++)
		cout << A[i] << " ";
	cout << endl;
}	  

void randArray()
{
	srand(time(NULL));
	cout << "Введите количество элементов массива: ";
	cin >> N;
	cout << "Элементы массива: ";
	A = new int[N];
	for (int i = 0; i < N; i++)
	{
		A[i] = 1 + rand() % 1000;
		cout << A[i] << ' ';
	}
}

// извлечение
void extracxtionSort() 
{
	inputArray();
	//fileArray();

	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	int min, temp;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < N; i++)
	{
		min = i;
		for (int j = i+1; j < N; j++)
			if (A[j] < A[min])
				min = j;
		temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
	QueryPerformanceCounter(&finish);

	outputArray();

	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\nЗатрачено %.10f миллисекунд\n", time);
	delete[] A;
}

// пузырёк
void bubbleSort() 
{
	inputArray();
	//fileArray();

	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	int temp;

	QueryPerformanceCounter(&start);
	for (int i = 0; i < N; i++)
		for (int j = i + 1; j < N; j++)
		{
			if (A[i] > A[j])
			{
				temp = A[i];
				A[i] = A[j];
				A[j] = temp;
			}
		}
	QueryPerformanceCounter(&finish);

	outputArray();

	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\nЗатрачено %.10f миллисекунд\n", time);
	delete[] A;
}

// подсчётом
void countingSort()
{
	inputArray();
	//fileArray();

	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	int k = 0;
	B = new int[N];
	QueryPerformanceCounter(&start);
	for (int i = 0; i < N; i++)
	{
		k = 0;
		for (int j = 0; j < N; j++)
		{
			if (A[i] > A[j])
				k++;
		}
		B[k] = A[i];
	}
	QueryPerformanceCounter(&finish);
	
	for (int i = 0; i < N; i++)
		cout << B[i] << " ";
	cout << endl;

	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\nЗатрачено %.10f миллисекунд\n", time);
	delete[] A; 
	delete[] B;
}

//включением
void insertSort()
{
	inputArray();
	//fileArray();
	
	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	int j = 0;
	B = new int[N]; // результирующий массив (B)

	QueryPerformanceCounter(&start);

	B[0] = A[0];
	for (int i = 1; i < N; ++i)
	{
		j = i - 1;
		while ((j >= 0) && (B[j] > A[i]))
		{
			B[j + 1] = B[j];
			B[j] = A[i];
			j--;
		}
		B[j + 1] = A[i];
	}

	QueryPerformanceCounter(&finish);

	for (int i = 0; i < N; i++)
		cout << B[i] << " ";
	cout << endl;

	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\nЗатрачено %.10f миллисекунд\n", time);
	delete[] A;
	delete[] B;
}

// сортировка включением через один массив
void insertSort2()
{
	//inputArray();
	fileArray();

	LARGE_INTEGER start, finish, freq;
	QueryPerformanceFrequency(&freq);

	int j = 0, key;
	QueryPerformanceCounter(&start);
	for (int i = 1; i < N; i++)
	{
		key = A[i];
		j = i - 1;
		while ((j >= 0) && (A[j] > key))
		{
			A[j + 1] = A[j];
			j--;
		}
		A[j + 1] = key;
	}
	QueryPerformanceCounter(&finish);
	outputArray();

	double time = (finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
	printf("\nЗатрачено %.10f миллисекунд\n", time);
	delete[] A;
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int x;
	for (;;)
	{
			cout << endl << "4 - Сортировка пузырьком " << endl
			<< "5 - Сортировка подсчётом" << endl
			<< "6 - Сортировка включением" << endl
			<< "7 - Сортировка извлечением" << endl
			<< "0 - Выход" << endl << endl;
		cin >> x;

		switch (x)
		{
		case 3: fileArray();
			break;
		case 4: bubbleSort();
			break;
		case 5: countingSort();
			break;
		case 6: insertSort();
			//insertSort2();
			break;
		case 7: extracxtionSort();
			break;
		case 0: delete[] A;
			exit(1);
			break;
		}
	}
}