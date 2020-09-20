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
	if (len < 0) throw "Negative bit length";

	int size = (sizeof(int) * 8);
	MemLen = (len + size - 1) / size;
	BitLen = len;
	pMem = new TELEM(MemLen);
	
	for (int k = 0; k < MemLen; k++)
	{
		pMem[k] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	pMem = new TELEM(MemLen);
	
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
	int size = sizeof(int) * 8;
	int a = n / size;
	int b = n % size;
	
	if (a != 0) return b + 1;
	else return b;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0) throw "Negative bit index";
	if (n >= BitLen) throw "Too large index";
	if (n % 1 != 0) throw "Lenght isnt integer";
	
	return pow(2, n);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n < 0) throw "Negative bit index";
	if (n >= BitLen) throw "Too large index";

	int size = sizeof(int) * 8;
	int i = n / size;
	int j = n % size;

	pMem[i] |= 1 << j;
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n < 0) throw "Negative bit index";
	if (n >= BitLen) throw "Too large index";
	
	int size = sizeof(int) * 8;
	int i = n / size;
	int j = n % size;

	pMem[i] &= ~(1 << j);
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n < 0) throw "Negative bit index";
	if (n >= BitLen) throw "Too large index";
	
	int size = sizeof(int) * 8;
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
		pMem = new TELEM(MemLen);

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
	if (BitLen == bf.BitLen)
	{
		for (int k = 0; k < BitLen; k++)
		{
			int size = sizeof(int) * 8;
			int i = k / size;
			int j = k % size;

			if ((bf.pMem[i] & (1 << j)) != 0)
			{
				pMem[i] |= 1 << j;
			}
		}
		return *this;
	}
	else
	{
		if (BitLen > bf.BitLen)
		{
			for (int k = 0; k < bf.BitLen; k++)
			{
				int size = sizeof(int) * 8;
				int i = k / size;
				int j = k % size;

				if ((bf.pMem[i] & (1 << j)) != 0)
				{
					pMem[i] |= 1 << j;
				}
			}
			return *this;
		}
		else
		{
			for (int k = 0; k < BitLen; k++)
			{
				int size = sizeof(int) * 8;
				int i = k / size;
				int j = k % size;

				if ((pMem[i] & (1 << j)) != 0)
				{
					bf.pMem[i] |= 1 << j;
				}
			}
			return bf;
		}
	}
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	if (BitLen == bf.BitLen)
	{
		for (int k = 0; k < BitLen; k++)
		{
			int size = sizeof(int) * 8;
			int i = k / size;
			int j = k % size;

			if (((bf.pMem[i] & (1 << j)) != 0) && ((pMem[i] & (1 << j)) != 0))
			{
				pMem[i] |= 1 << j;
			}
		}
		return *this;
	}
	else
	{
		if (BitLen > bf.BitLen)
		{
			for (int k = 0; k < bf.BitLen; k++)
			{
				int size = sizeof(int) * 8;
				int i = k / size;
				int j = k % size;

				if (((bf.pMem[i] & (1 << j)) != 0) && ((pMem[i] & (1 << j)) != 0))
				{
					pMem[i] |= 1 << j;
				}
			}
			return *this;
		}
		else
		{
			for (int k = 0; k < BitLen; k++)
			{
				int size = sizeof(int) * 8;
				int i = k / size;
				int j = k % size;

				if (((bf.pMem[i] & (1 << j)) != 0) && ((pMem[i] & (1 << j)) != 0))
				{
					bf.pMem[i] |= 1 << j;
				}
			}
			return bf;
		}
	}
}

TBitField TBitField::operator~(void) // отрицание
{
	for (int k = 0; k < BitLen; k++)
	{
		int size = sizeof(int) * 8;
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
	for (int k = 0; k < bf.BitLen; k++)
	{
		int size = sizeof(int) * 8;
		int i = k / size;
		int j = k % size;

		int a;
		istr >> a;
		if (a == 0) bf.pMem[i] &= ~(1 << j);
		else bf.pMem[i] |= 1 << j;
	}
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int k = 0; k < bf.BitLen; k++)
	{
		int size = sizeof(int) * 8;
		int i = k / size;
		int j = k % size;
		
		ostr << (bf.pMem[i] & (1 << j));
	}
	ostr << endl;
	return ostr;
}
