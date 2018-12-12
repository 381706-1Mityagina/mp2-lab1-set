// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : bitField(mp)
{
  if (mp >= 0)
  maxPower = mp;
}
// ---------------------------------------------------------------------------
// конструктор копирования
TSet::TSet(const TSet &s) : bitField(s.bitField)
{
  maxPower = s.maxPower;
  bitField = s.bitField;
}
// ---------------------------------------------------------------------------
// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : bitField(bf)
{
  maxPower = bf.GetLength();
  bitField = bf;
}
// ---------------------------------------------------------------------------
TSet::operator TBitField()
{
  TBitField temporary = (TBitField)*this;
  return temporary;
}
// ---------------------------------------------------------------------------
int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
  return maxPower;
}
// ---------------------------------------------------------------------------
int TSet::IsMember(const int Elem) const // элемент множества?
{
  if (Elem < 0 || Elem >= maxPower)
	throw "Smth's Wrong";
  return BitField.GetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::InsElem(const int Elem) // включение элемента множества
{
  if (Elem < 0 || Elem >= maxPower)
	throw "Smth's Wrong";
  BitField.SetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::DelElem(const int Elem) // исключение элемента множества
{
  if (Elem < 0 || Elem >= maxPower)
	throw "Smth's Wrong";
  BitField.ClrBit(Elem);
}
// ---------------------------------------------------------------------------
// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  bitField = s.bitField;
  maxPower = s.GetMaxPower();
  return *this;
}
// ---------------------------------------------------------------------------
int TSet::operator==(const TSet &s) const // сравнение
{
 	return (bitField == s.bitField);
}
// ---------------------------------------------------------------------------
int TSet::operator!=(const TSet &s) const // сравнение
{
  if (maxPower != s.maxPower) 
	  return 1;
	else
	if (bitField != s.bitField) return 1;
	return 0;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const TSet &s) // объединение
{
  int len = maxPower;
  if (maxPower < s.maxPower)
  {
	len = s.maxPower;
  }
  TSet temporary(len);
  temporary.bitField = bitField | s.bitField;
  return temporary;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem < 0 || Elem >= maxPower)
	throw "Smth's Wrong";
  BitField.SetBit(Elem);
  return *this;
}
// ---------------------------------------------------------------------------
TSet TSet::operator-(const int Elem) // разность с элементом
{
  if (Elem < 0 || Elem >= maxPower)
	throw "Smth's Wrong";
  BitField.ClrBit(Elem);
  return *this;
}
// ---------------------------------------------------------------------------
TSet TSet::operator*(const TSet &s) // пересечение
{
  int len = maxPower;
  if (s.maxPower > maxPower)
  {
	len = s.maxPower;
  }
  TSet temporary(len);
  temporary.bitField = bitField & s.bitField;
  return temporary;
}
// ---------------------------------------------------------------------------
TSet TSet::operator~(void) // дополнение
{
  TSet temporary = *this;
  temporary.bitField = ~temporary.bitField;
  return temporary;
}
// ---------------------------------------------------------------------------
// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
  char something;
  int insert;
  do
  {
	istr >> something;
  } while (something != '{');
  do
  {
	istr >> insert;
	s.InsElem(insert);
	istr >> something;
  } while (something != '}');
  return istr;
}
// ---------------------------------------------------------------------------
ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
  ostr << '{';
  for (int i = 0; i < s.GetMaxPower(); i++)
  {
	if (s.IsMember(i))
	  ostr << i;
	ostr << ',';
  }
  ostr << '}';
  return ostr;
}
// ---------------------------------------------------------------------------
