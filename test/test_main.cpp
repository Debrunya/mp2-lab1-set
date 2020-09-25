#include <gtest.h>

#define USE_GTESTS // Закомментировать, чтобы использовать тесты операторов ввода/вывода

#ifdef USE_GTESTS

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

// Тестирование операторов ввода/вывода

#include <iostream>
using namespace std;

#include "tset.h"
#include "tbitfield.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	const int size = 10;
	
	TBitField testbit1(size), testbit2(size); // тестирование операторов битового поля
	cout << "Тестирование операторов битового поля" << endl;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0) testbit1.SetBit(i);
	}
	cout << "Вывод, заданного программно(10 элементов, четные биты единички): " << endl << testbit1 << endl << endl;

	cout << "Ввод поля 10 элементов (формат {0,1,1,0,1,0,1,...} устанавливает в 1, 2, 4, 6,... биты единички)" << endl;  // формат {0,1,1,0,1,0,1,...} устанавливает в 1, 2, 4, 6,... биты единички 
	cin >> testbit2;
	cout << testbit2 << " <-- Вывод, заданного пользователем" << endl << endl << endl << endl << endl;

	TSet testset1(size), testset2(size); // тестирование операторов множества
	cout << "Тестирование операторов множества" << endl;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 1) testset1.InsElem(i);
	}
	cout << "Вывод, заданного программно(10 элементов, нечетные элементы присутствуют): " << endl << testset1 << endl << endl;

	cout << "Ввод множества 10 элементов (формат {5,7,9,...} устанавливает 5, 7, 9,... элементы)" << endl;  // формат {5,7,9,...} устанавливает 5, 7, 9,... элементы
	cin >> testset2;
	cout << testset2 << " <-- Вывод, заданного пользователем" << endl;

	return 0;
}
#endif