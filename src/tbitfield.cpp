// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
  if (len <= 0)
	throw "Smth's Wrong"; 
	bitLen = len;
	memLen = (bitLen / (sizeof(TELEM) * 8)) + 1;
	pMem = new TELEM[memLen];
	//if (pMem != 0)
	  for (int i = 0; i < memLen; i++)
		pMem[i] = 0;
}
// ---------------------------------------------------------------------------
TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
  memLen = bf.memLen;
  bitLen = bf.bitLen;
  pMem = new TELEM[memLen];
	for (int i = 0; i < memLen; i++)
	{
	  pMem[i] = bf.pMem[i];
	}
}
// ---------------------------------------------------------------------------
TBitField::~TBitField()
{
  delete[]pMem;
  pMem = NULL;
}
// ---------------------------------------------------------------------------
int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
  if ((n < 0) || (n >= bitLen))
	throw "Smth's Wrong";
  return (n / (sizeof(TELEM) * 8));
}
// ---------------------------------------------------------------------------
TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
  if ((n < 0) || (n >= bitLen))
	throw "Smth's Wrong";
  return (1 << ((n - 1) % (8 * sizeof(TELEM))));
}
// ---------------------------------------------------------------------------
// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return bitLen;
}
// ---------------------------------------------------------------------------
void TBitField::SetBit(const int n) // установить бит
{
  if ((n < 0) || (n >= bitLen))
	throw "Smth's Wrong";
  int i = GetMemIndex(n);
  pMem[i] = pMem[i] | GetMemMask(n);
}
// ---------------------------------------------------------------------------
void TBitField::ClrBit(const int n) // очистить бит
{
  if ((n < 0) || (n >= bitLen))
	throw "Smth's Wrong";
  {
	int i = GetMemIndex(n);
	pMem[i] = pMem[i] & ~GetMemMask(n);
  }
}
// ---------------------------------------------------------------------------
int TBitField::GetBit(const int n) const // получить значение бита
{
  if ((n < 0) || (n >= bitLen))
	throw "Smth's Wrong";
  {
	int i = GetMemIndex(n);
	return (pMem[i] & GetMemMask(n));
  }
}
// ---------------------------------------------------------------------------
// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
  if (this != &bf)
  {
	delete[]pMem;
	bitLen = bf.bitLen;
	memLen = bf.memLen;
	pMem = new TELEM[memLen];
	for (int i = 0; i < memLen; i++)
	  pMem[i] = bf.pMem[i];
  }
  return *this;
}
// ---------------------------------------------------------------------------
int TBitField::operator==(const TBitField &bf) const // сравнение
{
  int r = 1;
  if (bitLen != bf.bitLen)
	r = 0;
  else
	for (int i = 0; i < memLen; i++)
	  if (pMem[i] != bf.pMem[i])
	  {
		r= 0;
		break;
	  }
  return r;
}
// ---------------------------------------------------------------------------
int TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if (bitLen != bf.bitLen)
	return 1;
  else
	for (int i = 0; i < memLen; i++)
	  if (pMem[i] != bf.pMem[i])
	  {
		return 1;
		break;
	  }
	return 0;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
  int len = bitLen;
  if (bf.bitLen > len)
  {
	len = bf.bitLen;
  }
	TBitField temporary(len);
	for (int i = 0; i < memLen; i++)
	  temporary.pMem[i] = pMem[i];
	for (int i = 0; i < bf.memLen; i++)
	  temporary.pMem[i] |= bf.pMem[i];
  return temporary;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
  int len = bitLen;
  if (bitLen < bf.bitLen)
  {
	len = bf.bitLen;
  }
  TBitField temporary(len);
  for (int i = 0; i < memLen; i++)
	temporary.pMem[i] = pMem[i];
  for (int i = 0; i < bf.memLen; i++)
	temporary.pMem[i] &= bf.pMem[i];
  return temporary;
}
// ---------------------------------------------------------------------------
TBitField TBitField::operator~(void) // отрицание
{
  TBitField temporary = *this;
  for (int i = 0; i < temporary.bitLen; i++)
  {
	if (temporary.GetBit(i))
	  temporary.ClrBit(i);
	else
	  temporary.SetBit(i);
  }
  return temporary;
}
// ---------------------------------------------------------------------------

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
  char vvod;
  int i = 0;
  istr >> vvod;
  while ((vvod == '1') || (vvod == '0'))
  {
	switch (vvod)
	{
	case '1': bf.SetBit(i);
	  break;
	case '0': bf.ClrBit(i);
	  break;
	default:
	{
	  cout << "Wrong";
	}
	break;
	}
  }
  return istr;
}
// ---------------------------------------------------------------------------
ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
  for (int i = 0; i < bf.bitLen; i++)
	ostr << bf.GetBit(i);
  return ostr;
}
// ---------------------------------------------------------------------------
