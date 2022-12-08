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
	//btree* previous = NULL;
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
	//  root->previous = ptr;
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

// поиск мин. элемента в дереве
// идём по левым указателям, пока не встретим null
btree* minim(btree* root)
{
	if (root->left == NULL)
		return root;
	return minim(root->left);
}

// удаление
btree* deleteTree(btree* root, int n)
{
	if (root == NULL)
		cout << "Пустое дерево";
	else
	{
		if (n < root->x) // если удаляемыек эл. в L поддереве
			root->left = deleteTree(root->left, n);
		else if (n > root->x) // если в R 
			root->right = deleteTree(root->right, n);
		else if (root->left != NULL && root->right != NULL) // если это корень с 2мя потомками
		{
			root->x = minim(root->right)->x; // заменяем мин. элементом из R поддерева
			root->right = deleteTree(root->right, root->x); // удаляем этот элемент из R поддерева
		}
		else // если 1 потомок
		{
			if (root->left != NULL)
				root = root->left;
			else if (root->right != NULL)
				root = root->right;
			else
				root = NULL;
		}
	}
	return root;
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