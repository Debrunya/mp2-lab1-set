#include <gtest.h>

#define USE_GTESTS // ����������������, ����� ������������ ����� ���������� �����/������

#ifdef USE_GTESTS

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

#else

// ������������ ���������� �����/������

#include <iostream>
using namespace std;

#include "tset.h"
#include "tbitfield.h"

int main()
{
	setlocale(LC_ALL, "Russian");

	const int size = 10;
	
	TBitField testbit1(size), testbit2(size); // ������������ ���������� �������� ����
	cout << "������������ ���������� �������� ����" << endl;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 0) testbit1.SetBit(i);
	}
	cout << "�����, ��������� ����������(10 ���������, ������ ���� ��������): " << endl << testbit1 << endl << endl;

	cout << "���� ���� 10 ��������� (������ {0,1,1,0,1,0,1,...} ������������� � 1, 2, 4, 6,... ���� ��������)" << endl;  // ������ {0,1,1,0,1,0,1,...} ������������� � 1, 2, 4, 6,... ���� �������� 
	cin >> testbit2;
	cout << testbit2 << " <-- �����, ��������� �������������" << endl << endl << endl << endl << endl;

	TSet testset1(size), testset2(size); // ������������ ���������� ���������
	cout << "������������ ���������� ���������" << endl;
	for (int i = 0; i < size; i++)
	{
		if (i % 2 == 1) testset1.InsElem(i);
	}
	cout << "�����, ��������� ����������(10 ���������, �������� �������� ������������): " << endl << testset1 << endl << endl;

	cout << "���� ��������� 10 ��������� (������ {5,7,9,...} ������������� 5, 7, 9,... ��������)" << endl;  // ������ {5,7,9,...} ������������� 5, 7, 9,... ��������
	cin >> testset2;
	cout << testset2 << " <-- �����, ��������� �������������" << endl;

	return 0;
}
#endif