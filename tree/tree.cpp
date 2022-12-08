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

// ����� ���. �������� � ������
// ��� �� ����� ����������, ���� �� �������� null
btree* minim(btree* root)
{
	if (root->left == NULL)
		return root;
	return minim(root->left);
}

// ��������
btree* deleteTree(btree* root, int n)
{
	if (root == NULL)
		cout << "������ ������";
	else
	{
		if (n < root->x) // ���� ���������� ��. � L ���������
			root->left = deleteTree(root->left, n);
		else if (n > root->x) // ���� � R 
			root->right = deleteTree(root->right, n);
		else if (root->left != NULL && root->right != NULL) // ���� ��� ������ � 2�� ���������
		{
			root->x = minim(root->right)->x; // �������� ���. ��������� �� R ���������
			root->right = deleteTree(root->right, root->x); // ������� ���� ������� �� R ���������
		}
		else // ���� 1 �������
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