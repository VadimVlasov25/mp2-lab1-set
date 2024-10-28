// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"
#include <algorithm>

// Конструктор TSet, инициализирует битовое поле и максимальную мощность
TSet::TSet(int mp) : BitField(mp), MaxPower(mp)
{

}

// Конструктор копирования, копирует битовое поле и максимальную мощность из другого множества
TSet::TSet(const TSet& s) : BitField(s.BitField), MaxPower(s.MaxPower)
{

}

// Конструктор преобразования типа из битового поля в множество
TSet::TSet(const TBitField& bf) : BitField(bf), MaxPower(bf.GetLength())
{
}

// Преобразование TSet в TBitField
TSet::operator TBitField()
{
	return BitField; // Возвращаем текущее битовое поле
}

// Получить максимальную мощность множества (максимальное количество элементов)
int TSet::GetMaxPower(void) const
{
	return MaxPower; // Возвращаем максимальную мощность
}

// Проверка, является ли элемент членом множества
int TSet::IsMember(const int Elem) const
{
	return BitField.GetBit(Elem); // Возвращаем 1, если элемент присутствует, иначе 0
}

// Включение элемента в множество
void TSet::InsElem(const int Elem)
{
	BitField.SetBit(Elem); // Устанавливаем бит для данного элемента
}

// Исключение элемента из множества
void TSet::DelElem(const int Elem)
{
	BitField.ClrBit(Elem); // Очищаем бит для данного элемента
}

// Теоретико-множественные операции

// Оператор присваивания
TSet& TSet::operator=(const TSet& s)
{
	MaxPower = s.MaxPower; // Копируем максимальную мощность
	BitField = s.BitField; // Копируем битовое поле
	return *this; // Возвращаем текущий объект
}

// Оператор сравнения (равенство)
int TSet::operator==(const TSet& s) const
{
	return ((MaxPower == s.MaxPower) & (BitField == s.BitField)); // Проверяем равенство мощностей и битовых полей
}

// Оператор сравнения (неравенство)
int TSet::operator!=(const TSet& s) const
{
	return ((MaxPower != s.MaxPower) | (BitField != s.BitField)); // Проверяем неравенство мощностей и битовых полей
}

// Оператор объединения двух множеств
TSet TSet::operator+(const TSet& s)
{
	TSet ABC(max(MaxPower, s.MaxPower)); // Создаем новое множество с максимальной мощностью
	ABC.BitField = BitField | s.BitField; // Объединяем битовые поля
	return ABC; // Возвращаем результат
}

// Оператор объединения с элементом
TSet TSet::operator+(const int Elem)
{
	TSet ABC(*this); // Копируем текущее множество
	ABC.BitField.SetBit(Elem); // Устанавливаем бит для нового элемента
	return ABC; // Возвращаем результат
}

// Оператор разности с элементом
TSet TSet::operator-(const int Elem)
{
	TSet ABC(*this); // Копируем текущее множество
	ABC.BitField.ClrBit(Elem); // Очищаем бит для элемента
	return ABC; // Возвращаем результат
}

// Оператор пересечения двух множеств
TSet TSet::operator*(const TSet& s)
{
	TSet ABC(max(MaxPower, s.MaxPower)); // Создаем новое множество с максимальной мощностью
	ABC.BitField = BitField & s.BitField; // Пересекаем битовые поля
	return ABC; // Возвращаем результат
}

// Оператор дополнения
TSet TSet::operator~(void)
{
	TSet ABC(*this); // Копируем текущее множество
	ABC.BitField = ~ABC.BitField; // Инвертируем биты
	return ABC; // Возвращаем результат
}

// Перегрузка оператора ввода
istream& operator>>(istream& istr, TSet& s)
{
	// Здесь можно добавить логику для ввода элементов множества
	return istr; // Возвращаем поток
}

// Перегрузка оператора вывода
ostream& operator<<(ostream& ostr, const TSet& s)
{
	// Здесь можно добавить логику для вывода элементов множества
	return ostr; // Возвращаем поток
}
