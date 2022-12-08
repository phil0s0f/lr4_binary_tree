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
btree* root = NULL; //������ ������

// ����������
btree* addTree(btree* root, int a, btree* ptr)
{
	if (root == NULL) //���� ������ ���
	{
		root = new btree; // ������
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

// ��������
btree* deleteTree(btree* root, int n)
{
	if (root == NULL)
		cout << "������ ������";

	else if (root->x == n) // ���� ������ ����
	{
		if ((root->left == NULL) && (root->right == NULL) && (root->previous == NULL))
			root = NULL;
		// 0 ��������
		else if ((root->left == NULL) && (root->right == NULL))
		{
			root = root->previous;
			if (n > root->x)
				root->right = NULL;
			else
				root->left = NULL;
		}
		// 1 �������
		else if ((root->left != NULL) && (root->right == NULL)) // ���� ������� �����
		{
			btree* ptr = root;
			if (root->previous == NULL) // ���� ��� ������, �.�. ��� ������
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
		else if ((root->left == NULL) && (root->right != NULL)) // ���� ������� ������
		{
			btree* ptr = root;
			if (root->previous == NULL) // ���� ��� ������, �.�. ��� ������
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
		// 2 �������
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
	else // ���� ���� ������
	{
		if (n < root->x)
			deleteTree(root->left, n);
		else
			deleteTree(root->right, n);
	}	
	return root;
}
// �����
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
	cout << "���������� �����: ";
	int n, a; 
	cin >> n; 
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << endl << "������� �����: ";
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
		cout << endl << "1 - �������� �������" << endl
			<< "2 - ������� �������" << endl
			<< "3 - ����� ������" << endl
			<< "0 - �����" << endl << endl;
		cin >> x;

		switch (x)
		{
		case 1: // ���������� �����
		{
			cout << endl << "������� �����, ������� ����� ��������: ";
			int b;
			cin >> b;
			cout << endl;
			btree* ptr = NULL;
			addTree(root, b, ptr);
			printTree(root, 0);
			break;
		}
		case 2: // �������� �����
		{
			if (root == NULL)
				cout << "������ ������";
			else
			{
				cout << endl << "������� �����, ������� ����� �������: ";
				int y;
				cin >> y;
				cout << endl;
				root = deleteTree(root, y);
				if (root == NULL)
					cout << "������ ������";
				else
					printTree(root, 0);
			}
			break;
		}
		case 3: // ����� ������
		{
			if (root == NULL)
				cout << "������ ������";
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