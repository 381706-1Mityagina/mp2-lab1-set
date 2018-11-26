// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
  if (mp >= 0)
  MaxPower = mp;
}
// ---------------------------------------------------------------------------
// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
  MaxPower = s.MaxPower;
  BitField = s.BitField;
}
// ---------------------------------------------------------------------------
// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
  MaxPower = bf.GetLength();
  BitField = bf;
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
  return MaxPower;
}
// ---------------------------------------------------------------------------
int TSet::IsMember(const int Elem) const // элемент множества?
{
  if (Elem < 0 || Elem >= MaxPower)
	throw "Smth's Wrong";
  return BitField.GetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::InsElem(const int Elem) // включение элемента множества
{
  if (Elem < 0 || Elem >= MaxPower)
	throw "Smth's Wrong";
  BitField.SetBit(Elem);
}
// ---------------------------------------------------------------------------
void TSet::DelElem(const int Elem) // исключение элемента множества
{
  if (Elem < 0 || Elem >= MaxPower)
	throw "Smth's Wrong";
  BitField.ClrBit(Elem);
}
// ---------------------------------------------------------------------------
// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
  BitField = s.BitField;
  MaxPower = s.GetMaxPower();
  return *this;
}
// ---------------------------------------------------------------------------
int TSet::operator==(const TSet &s) const // сравнение
{
  if (BitField == s.BitField)
	return 1;
}
// ---------------------------------------------------------------------------
int TSet::operator!=(const TSet &s) const // сравнение
{
  int inf = 0;
  if (MaxPower != s.MaxPower)
	 inf = 1;
  if (BitField != s.BitField)
	 inf = 1;
  return inf;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const TSet &s) // объединение
{
  int len = MaxPower;
  if (MaxPower < s.MaxPower)
  {
	len = s.MaxPower;
  }
  TSet temporary(len);
  temporary.BitField = BitField | s.BitField;
  return temporary;
}
// ---------------------------------------------------------------------------
TSet TSet::operator+(const int Elem) // объединение с элементом
{
  if (Elem < 0 || Elem >= MaxPower)
	throw "Smth's Wrong";
  BitField.SetBit(Elem);
  return *this;
}
// ---------------------------------------------------------------------------
TSet TSet::operator-(const int Elem) // разность с элементом
{
  if (Elem < 0 || Elem >= MaxPower)
	throw "Smth's Wrong";
  BitField.ClrBit(Elem);
  return *this;
}
// ---------------------------------------------------------------------------
TSet TSet::operator*(const TSet &s) // пересечение
{
  int len = MaxPower;
  if (s.MaxPower > MaxPower)
  {
	len = s.MaxPower;
  }
  TSet temporary(len);
  temporary.BitField = BitField & s.BitField;
  return temporary;
}
// ---------------------------------------------------------------------------
TSet TSet::operator~(void) // дополнение
{
  TSet temporary = *this;
  temporary.BitField = ~temporary.BitField;
  return temporary;
}
// ---------------------------------------------------------------------------
// перегрузка ввода/вывода

/*istream &operator>>(istream &istr, TSet &s) // ввод
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
}*/
istream &operator>>(istream &istr, TSet &s)
{
  int i;
  cin >> i;
  for (; ((i > -1) && (i < s.maxPower)); cin >> i)
    s.bitField.setBit(i);
  return istr;
}
// ---------------------------------------------------------------------------
ostream& operator<<(ostream &ostr, const TSet &s)
{
  ostr << s.bitField << ' ';
  return ostr;
}
// ---------------------------------------------------------------------------
