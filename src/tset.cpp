// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
using namespace std;

TSet::TSet(int mp) : MaxPower(mp), BitField(mp) {}

// конструктор копирования
TSet::TSet(const TSet &s) : MaxPower(s.MaxPower), BitField(s.BitField) {}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : MaxPower(bf.GetLength()), BitField(bf) {}

TSet::operator TBitField()
{
	TBitField bitfield(BitField);
	return bitfield;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
    return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
	return;
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
	return;
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	MaxPower = s.GetMaxPower();
	BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
    return (BitField == s.BitField);
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return (BitField != s.BitField);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet set(BitField | s.BitField);
	return set;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem > MaxPower)
  {
    TSet set(Elem);
    set.InsElem(Elem);
    TSet upd(BitField | set.BitField);
    return upd;
  }
  else
  {
    TSet set = *this;
    set.InsElem(Elem);
    return set;
  }
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
	{
		throw logic_error("Cant sub elem > maxpower");
	}
	else
	{
     TSet set = *this;
     set.DelElem(Elem);
     return set;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet set(BitField & s.BitField);
	return set;
}

TSet TSet::operator~(void) // дополнение
{
	TSet temp(~BitField);
	return temp;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int a;
	char string;
	
	do istr >> string; while (string != '{');

	do
	{
		istr >> a;
		s.InsElem(a);
		do istr >> string; while ((string != ',') && (string != '}'));
	}
	while (string != '}');
	
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	int len = s.GetMaxPower();
   int n = 0, k = 0, i = 0;

	ostr << "{";
	
	while ((n != 1) && (k < len))
	{
		if (s.IsMember(i) != 0)
		{
			ostr << i;
			n++;
		}
		i++;
		k++;
	}
	
	for (int i = k; i < len; i++)
	{
		if (s.IsMember(i)) ostr << "," << i;
	}
	
	ostr << "}";

	return ostr;
}
