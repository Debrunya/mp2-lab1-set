// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <cmath>
#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw logic_error("Negative bit length");

	int size = (sizeof(TELEM) * 8);
	MemLen = (len + size - 1) / size;
	BitLen = len;
	pMem = new TELEM[MemLen];
	
	for (int k = 0; k < MemLen; k++)
	{
		pMem[k] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM[MemLen];
	
	for (int i = 0; i < MemLen; i++)
	{
		pMem[i] = bf.pMem[i];
	}
}

TBitField::~TBitField()
{
	delete pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	int size = sizeof(TELEM) * 8;
	int a = n / size;
	int b = n % size;
	
	if (a != 0) return b + 1;
	else return b;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) throw logic_error("Negative bit length");
	if (n >= BitLen) throw logic_error("Too large index");
	if (n % 1 != 0) throw logic_error("Lenght isnt integer");
	
	return pow(2, n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) throw logic_error("Negative bit length");
	if (n >= BitLen) throw logic_error("Too large index");

	int size = sizeof(TELEM) * 8;
	int i = n / size;
	int j = n % size;

	pMem[i] |= 1 << j;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw logic_error("Negative bit length");
	if (n >= BitLen) throw logic_error("Too large index");

	int size = sizeof(TELEM) * 8;
	int i = n / size;
	int j = n % size;

	pMem[i] &= ~(1 << j);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw logic_error("Negative bit length");
	if (n >= BitLen) throw logic_error("Too large index");
	
	int size = sizeof(TELEM) * 8;
	int i = n / size;
	int j = n % size;

	if ((pMem[i] & (1 << j)) == 0) return 0;
	else return 1;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++)
		{
			 if (pMem[i] != bf.pMem[i]) pMem[i] = bf.pMem[i];
		}
	}
	else
	{
		MemLen = bf.MemLen;
		BitLen = bf.BitLen;
		delete pMem;
		pMem = new TELEM[MemLen];

		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = bf.pMem[i];
		}
	}
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
 	if (BitLen != bf.BitLen) return 0;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) return 0;
		}
	}
   return 1;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (BitLen != bf.BitLen) return 1;
	else
	{
		for (int i = 0; i < MemLen; i++)
		{
			if (pMem[i] != bf.pMem[i]) return 1;
		}
	}
   return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	int k = BitLen;
	if (bf.BitLen > BitLen) k = bf.BitLen;
	TBitField temp(k);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] |= pMem[i];
    for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] |= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int k = BitLen;
	if (bf.BitLen > BitLen) k = bf.BitLen;
	TBitField temp(k);
	for (int i = 0; i < MemLen; i++) temp.pMem[i] = pMem[i];
	for (int i = 0; i < bf.MemLen; i++) temp.pMem[i] &= bf.pMem[i];
	return temp;
}

TBitField TBitField::operator~(void) // отрицание
{
  TBitField temp(BitLen);
  for (int k = 0; k < BitLen; k++)
	{
		int size = sizeof(TELEM) * 8;
		int i = k / size;
		int j = k % size;

		if ((pMem[i] & (1 << j)) == 0) temp.pMem[i] |= 1 << j;
		else temp.pMem[i] &= ~(1 << j);
	}
	return temp;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  int i = 0;
  char string;

  for (int a = 0; a < bf.GetLength(); a++)
  {
    istr >> string;
    if (string == '1') bf.SetBit(i);
    i++;
  };
	
  return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	
	for (int i = 0; i < len; i++)
	{
		if (bf.GetBit(i)) ostr << 1;
		else ostr << 0;
	}
	
	return ostr;
}


void TBitField::BFReadFile()
{
    ifstream fin("bfinput.txt");
    if (!fin.is_open())
    {
        cout << "File cant be opened!" << endl;
        return;
    }

    string line;
    getline(fin, line);
    int len = line.length();

    for (int i = 0; i < len; i++)
    {
        string temp = line;
        temp.erase(1, temp.length() - 1);
        
        int a = atoi(temp.c_str());
        if (a == 1) SetBit(i);
        line.erase(0, 1);
    }

    return;
}

void TBitField::BFWriteInFile()
{
    ofstream fout("bfoutput.txt");

    int len = BitLen;

    for (int i = 0; i < len; i++)
    {
        if (GetBit(i)) fout << 1;
        else fout << 0;
    }

    return;
}