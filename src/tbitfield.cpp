// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"
#include <cstring>
#include <algorithm>
#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8) // Количество бит в одном элементе

// Конструктор класса TBitField
TBitField::TBitField(int len) : BitLen(len) {
    if (len <= 0) throw "Invalid length"; // Проверка на корректность длины
    // Вычисление количества элементов памяти, необходимых для хранения битов
    MemLen = (len + BITS_IN_ONE_MEM - 1) / BITS_IN_ONE_MEM; // Округление вверх
    pMem = new TELEM[MemLen]; // Выделение памяти для битового поля
    memset(pMem, 0, sizeof(TELEM) * MemLen); // Инициализация нулями
}

// Конструктор копирования
TBitField::TBitField(const TBitField& bf) {
    BitLen = bf.BitLen; // Копируем длину битового поля
    MemLen = bf.MemLen; // Копируем количество элементов памяти
    pMem = new TELEM[MemLen]; // Выделяем память для нового битового поля
    for (TELEM i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i]; // Копируем данные из другого битового поля
    }
}

// Деструктор
TBitField::~TBitField() {
    delete[] pMem; // Освобождаем выделенную память
}

// Получение индекса элемента памяти для бита n
int TBitField::GetMemIndex(const int n) const {
    return n / BITS_IN_ONE_MEM; // Индекс элемента, в котором хранится бит n
}

// Получение битовой маски для бита n
TELEM TBitField::GetMemMask(const int n) const {
    if (n < 0 || n >= BitLen) throw "Wrong bit for get_mask"; // Проверка на корректность индекса
    return ((TELEM)1 << (n % BITS_IN_ONE_MEM)); // Возвращаем маску для бита n
}

// Доступ к битам битового поля

// Получить длину (количество битов)
int TBitField::GetLength(void) const {
    return BitLen; // Возвращаем длину битового поля
}

// Установить бит
void TBitField::SetBit(const int n) {
    if ((n < 0) || (n >= BitLen)) // Проверка на корректность индекса
        throw "Out of range diapason";
    TELEM i = GetMemIndex(n); // Получаем индекс элемента памяти
    TELEM j = GetMemMask(n); // Получаем маску для бита
    pMem[i] = (pMem[i] | j); // Устанавливаем бит
}

// Очистить бит
void TBitField::ClrBit(const int n) {
    TELEM i = GetMemIndex(n); // Получаем индекс элемента памяти
    TELEM j = ~GetMemMask(n); // Получаем маску для очистки бита
    pMem[i] = (pMem[i] & j); // Очищаем бит
}

// Получить значение бита
int TBitField::GetBit(const int n) const {
    TELEM i = GetMemIndex(n); // Получаем индекс элемента памяти
    TELEM j = GetMemMask(n); // Получаем маску для бита
    return int((pMem[i] & j) != 0); // Возвращаем значение бита (0 или 1)
}

// Битовые операции

// Оператор присваивания
TBitField& TBitField::operator=(const TBitField& bf) {
    if (this == &bf) return *this; // Проверка самоприсваивания
    BitLen = bf.BitLen; // Копируем длину
    MemLen = bf.MemLen; // Копируем количество элементов памяти
    delete[] pMem; // Освобождаем старую память
    pMem = new TELEM[MemLen]; // Выделяем новую память
    for (TELEM i = 0; i < MemLen; i++) {
        pMem[i] = bf.pMem[i]; // Копируем данные из другого битового поля
    }
    return *this; // Возвращаем ссылку на текущий объект
}

// Оператор сравнения (равенство)
int TBitField::operator==(const TBitField& bf) const {
    if (MemLen != bf.MemLen) return 0; // Сравниваем размеры
    for (TELEM i = 0; i < MemLen; i++) {
        if (pMem[i] != bf.pMem[i]) return 0; // Сравниваем содержимое
    }
    return 1; // Поля равны
}

// Оператор сравнения (неравенство)
int TBitField::operator!=(const TBitField& bf) const {
    return !(*this == bf); // Используем оператор равенства
}

// Оператор "или"
TBitField TBitField::operator|(const TBitField& bf) {
    TELEM size = std::max(BitLen, bf.BitLen); // Вычисляем максимальный размер
    TBitField out(size); // Создаем новое битовое поле

    for (TELEM i = 0; i < out.MemLen; i++) {
        if (i < MemLen && i < bf.MemLen)
            out.pMem[i] = pMem[i] | bf.pMem[i]; // Операция "или" для общих элементов
        else {
            if (i < MemLen) out.pMem[i] = pMem[i]; // Если только в текущем
            else if (i < bf.MemLen) out.pMem[i] = bf.pMem[i]; // Если только в bf
        }
    }
    return out; // Возвращаем результат
}

// Оператор "и"
TBitField TBitField::operator&(const TBitField& bf) {
    TELEM size = std::max(BitLen, bf.BitLen); // Вычисляем максимальный размер
    TBitField out(size); // Создаем новое битовое поле

    for (TELEM i = 0; i < out.MemLen; i++) {
        if (i < MemLen && i < bf.MemLen)
            out.pMem[i] = pMem[i] & bf.pMem[i]; // Операция "и" для общих элементов
    }
    return out; // Возвращаем результат
}

// Оператор отрицания
TBitField TBitField::operator~(void) {
    TBitField out(BitLen); // Создаем новое битовое поле
    for (TELEM i = 0; i < BitLen; i++) {
        if (this->GetBit(i)) out.ClrBit(i); // Если бит установлен, очищаем его
        else out.SetBit(i); // Иначе устанавливаем
    }
    return out; // Возвращаем результат
}

// Ввод/вывод

// Оператор ввода
istream& operator>>(istream& istr, TBitField& bf) {
    TELEM g = 3; // Переменная для ввода
    cout << "Input -1 for end input" << endl; // Подсказка для пользователя
    cin >> g; // Считываем элемент
    while (g != -1) { // Пока не введен -1
        if (g >= 0 && g < bf.GetLength()) { // Проверка на допустимость
            bf.SetBit(g); // Устанавливаем бит
        }
        else {
            cout << "Element " << g << " is out of range." << endl; // Сообщаем об ошибке
        }
        cin >> g; // Считываем следующий элемент
    }

    return istr; // Возвращаем поток
}

// Оператор вывода
ostream& operator<<(ostream& ostr, const TBitField& bf) {
    for (TELEM i = 0; i < bf.BitLen; i++) { // Проходим по всем битам
        if (bf.GetBit(i)) cout << i << ", "; // Если бит установлен, выводим его
    }
    return ostr; // Возвращаем поток
}
