// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include <cmath>
#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0) throw std::logic_error("Negative bit length");

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
	if (n < 0) throw std::logic_error("Negative bit length");
	if (n >= BitLen) throw std::logic_error("Too large index");
	if (n % 1 != 0) throw std::logic_error("Lenght isnt integer");
	
	return pow(2, n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) throw std::logic_error("Negative bit length");
	if (n >= BitLen) throw std::logic_error("Too large index");

	int size = sizeof(TELEM) * 8;
	int i = n / size;
	int j = n % size;

	pMem[i] |= 1 << j;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw std::logic_error("Negative bit length");
	if (n >= BitLen) throw std::logic_error("Too large index");

	int size = sizeof(TELEM) * 8;
	int i = n / size;
	int j = n % size;

	pMem[i] &= ~(1 << j);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw std::logic_error("Negative bit length");
	if (n >= BitLen) throw std::logic_error("Too large index");
	
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
			pMem[i] = bf.pMem[i];
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
		return 1;
	}
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
		return 0;
	}
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++) bf.pMem[i] |= pMem[i];
		return bf;
	}
	else
	{
		for (int i = 0; i < bf.MemLen; i++) pMem[i] |= bf.pMem[i];
		return *this;
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen < bf.BitLen)
	{
		for (int i = 0; i < MemLen; i++) bf.pMem[i] &= pMem[i];
		return bf;
	}
	else
	{
		for (int i = 0; i < bf.MemLen; i++) pMem[i] &= bf.pMem[i];
		return *this;
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int k = 0; k < BitLen; k++)
	{
		int size = sizeof(TELEM) * 8;
		int i = k / size;
		int j = k % size;

		if ((pMem[i] & (1 << j)) == 0) pMem[i] |= 1 << j;
		else pMem[i] &= ~(1 << j);
	}
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int a, i = 0;
	char string;

	do istr >> string; while (string != '{');

	do
	{
		istr >> a;
		if (a == 1) bf.SetBit(i);
		i++;
		do istr >> string; while ((string != ',') && (string != '}'));
	}
	while (string != '}');

	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	int len = bf.GetLength();
	
	ostr << "{";
	int temp = bf.GetBit(0);
	ostr << temp;
	
	for (int i = 1; i < len; i++)
	{
		if (bf.GetBit(i)) ostr << "," << 1;
		else ostr << "," << 0;
	}

   ostr << "}";
	
	return ostr;
}
