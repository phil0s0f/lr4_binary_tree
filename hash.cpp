#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
using namespace std;

int hashSqr(int s) 
{
    int B = 100;
    int P;
    P = ((s*s) / B) % B;
    cout << s << " " << (s * s) << " " << P << endl;
    return P;
};

int hashMod(int s)
{
    int P = s % 50;
    cout << s << " " << P << endl;
    return P;
}

int hashFr(int s)
{
    int P = (s % 100) + (s / 100);
    cout << s << " " << P << endl;
    return P;
}

void main()
{
    int count = 0;
    int collisions = 0;
    int x;
    int array[50];

    FILE* file = fopen("C:\\Users\\user\\YandexDisk\\3 курс пи\\типы и структуры данных\\lr (1) (1)\\hash50.txt", "r");
    for (int i = 0; i < 50; i++)
    {
        fscanf(file, "%d", &x);
        array[count] = hashSqr(x);
        for (int i = 0; i < count; i++)
        {
            if (array[i] == array[count])
            {
                collisions++;
                break;
            }
        }
        count++;
    }
    fclose(file);

    cout << endl << "Total Input is " << count - 1 << endl;
    cout << "Collision # is " << collisions << endl << endl;

    count = 0;
    collisions = 0;
    int array1[50];

    file = fopen("C:\\Users\\user\\YandexDisk\\3 курс пи\\типы и структуры данных\\lr (1) (1)\\hash50.txt", "r");
    for (int i = 0; i < 50; i++)
    {
        fscanf(file, "%d", &x);
        array1[count] = hashMod(x);
        for (int i = 0; i < count; i++)
        {
            if (array1[i] == array1[count])
            {
                collisions++;
                break;
            }
        }
        count++;
    }
    fclose(file);

    cout << endl << "Total Input is " << count - 1 << endl;
    cout << "Collision # is " << collisions << endl << endl;

    count = 0;
    collisions = 0;
    int array2[50];

    file = fopen("C:\\Users\\user\\YandexDisk\\3 курс пи\\типы и структуры данных\\lr (1) (1)\\hash50.txt", "r");
    for (int i = 0; i < 50; i++)
    {
        fscanf(file, "%d", &x);
        array2[count] = hashFr(x);
        for (int i = 0; i < count; i++)
        {
            if (array2[i] == array2[count])
            {
                collisions++;
                break;
            }
        }
        count++;
    }
    fclose(file);

    cout << endl << "Total Input is " << count - 1 << endl;
    cout << "Collision # is " << collisions << endl << endl;
}