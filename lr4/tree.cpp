#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <windows.h>

using namespace std;

struct btree
{
	int x;
	btree* left;
	btree* right;
	btree* previous  = NULL;
};
btree* root = NULL; //корень дерева

// добавление
btree* addTree(btree* root, int a, btree* ptr)
{
	if (root == NULL) //если дерева нет
	{
		root = new btree; // память
		root->x = a;
		root->left = NULL;
		root->right = NULL;
		root->previous = ptr;
	}
	else  if (a < root->x)
	{
		btree* ptr = root;
		root->left = addTree(root->left, a, ptr);	
	}
	else
	{
		btree* ptr = root;
		root->right = addTree(root->right, a, ptr);
	}
	return root;
}
btree* search(btree* root, int x)
{
	return root;
}

// удаление
btree* deleteTree(btree* root, int n)
{
	if (root == NULL)
		cout << "Пустое дерево";

	else if (root->x == n) // если нужный узел
	{
		if ((root->left == NULL) && (root->right == NULL) && (root->previous == NULL))
			root = NULL;
		// 0 потомков
		else if ((root->left == NULL) && (root->right == NULL))
		{
			root = root->previous;
			if (n > root->x)
				root->right = NULL;
			else
				root->left = NULL;
		}
		// 1 потомок
		else if ((root->left != NULL) && (root->right == NULL)) // если потомок слева
		{
			btree* ptr = root;
			if (root->previous == NULL) // если нет предка, т.е. это корень
			{
				root->left->previous = NULL;
				root = root->left;
			}
			else
			{
				root->left->previous = root->previous;
				if (root->previous->left == ptr)
					root->previous->left = root->left;
				else
					root->previous->right = root->left;
			}
		}
		else if ((root->left == NULL) && (root->right != NULL)) // если потомок справа
		{
			btree* ptr = root;
			if (root->previous == NULL) // если нет предка, т.е. это корень
			{
				root->right->previous = NULL;
				root = root->right;
			}
			else
			{
				root->right->previous = root->previous;
				if (root->previous->left == ptr)
					root->previous->left = root->right;
				else
					root->previous->right = root->right;
			}
		}
		// 2 потомка
		else
		{
			
			btree* ptrP = root->previous;
			btree* ptrR = root->right;
			btree* ptrL = root->left;
			
			do
			{
				if (root->right->right == NULL)
					break;
				else
					root->right = root->right->right;
			}
			while (root->right->right != NULL);
			
			root = root->right;

			root->previous = ptrP;
			if (n < root->previous->x)
				root->previous->left = root;
			else
				root->previous->right = root;
			root->right = ptrR;
			root->left = ptrL;
			root->right->previous = root;
			root->right->right = NULL; 
			/*
			btree* ptr = root;
			ptr = ptr->right;
			if (!ptr->left)
			{
				if (root->previous->x < n)
					root->previous->right = ptr;
				else 
					root->previous->left = ptr;
				ptr->left = root->left;
				//delete root;
			}
			else
			{
				btree* ptrP = NULL;
				while (ptr->left)
				{
					ptrP = ptr;
					ptr = ptr->left;
				}
				root->x = ptr->x;

				if (!ptr->right)
				{
					ptrP->left = NULL;
					delete ptr;
				}
				else
				{
					ptrP->left = ptr->right;
					delete ptr;
				}
			}*/
		}
	}
	else // ищем узел дальше
	{
		if (n < root->x)
			deleteTree(root->left, n);
		else
			deleteTree(root->right, n);
	}	
	return root;
}
// вывод
void printTree(btree* root, int n)
{
	if (root == NULL)
		return;                  
	else 
	{
		printTree(root->left, ++n);                   
		for (int i = 0; i < n; i++) 
			cout << "    ";
		cout << root->x << endl;
		n--;
	}
	printTree(root->right, ++n);
}

void main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	cout << "Количество чисел: ";
	int n, a; 
	cin >> n; 
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << endl << "Введите число: ";
		cin >> a;
		btree* ptr = NULL;
		cout << endl;
		if (i == 0)
		{
			root = addTree(root, a, ptr);
			printTree(root, 0);
		}
		else
		{
			addTree(root, a, ptr);
			printTree(root, 0);
		}
	}
	int x;
	for (;;)
	{
		cout << endl << "1 - Добавить элемент" << endl
			<< "2 - Удалить элемент" << endl
			<< "3 - Вывод дерева" << endl
			<< "0 - Выход" << endl << endl;
		cin >> x;

		switch (x)
		{
		case 1: // добавление числа
		{
			cout << endl << "Введите число, которое нужно добавить: ";
			int b;
			cin >> b;
			cout << endl;
			btree* ptr = NULL;
			addTree(root, b, ptr);
			printTree(root, 0);
			break;
		}
		case 2: // удаление числа
		{
			if (root == NULL)
				cout << "Пустое дерево";
			else
			{
				cout << endl << "Введите число, которое нужно удалить: ";
				int y;
				cin >> y;
				cout << endl;
				root = deleteTree(root, y);
				if (root == NULL)
					cout << "Пустое дерево";
				else
					printTree(root, 0);
			}
			break;
		}
		case 3: // вывод дерева
		{
			if (root == NULL)
				cout << "Пустое дерево";
			else
				printTree(root, 0);
			break;
		}
		case 0:
			exit(1);
			break;
		} 
	}
}