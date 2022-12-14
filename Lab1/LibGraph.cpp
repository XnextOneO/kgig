#include "stdafx.h"
#include "LibGraph.h"
#include "CMatrix.h"

#define SPACING 50 //расстояние между элементами матриц
#define PI 3.14159

void fillMatrix(CMatrix& matrix, double begin)//стартовое значение в матрице
{
	for (int i = 0; i < matrix.countRows(); i++)
	{
		for (int j = 0; j < matrix.countCols(); j++, begin++)
		{
			matrix(i, j) = begin;
		}
	}
}

void printMatrix(CDC* dc, int x, int y, CString caption, CMatrix& matrix)//вывод матриц
{
	CString str = L"";//переменная для элементов
	//dc - ссылка на контекст
	dc->TextOut(x, y, caption);//выводит заголовок пример "Матрица V1"
	y += SPACING;//создаем расстояние между текстом и саомой матрицей
	for (int i = 0; i < matrix.countRows(); i++)
	{
		for (int j = 0; j < matrix.countCols(); j++)
		{
			str.Format(L"%.2lf", matrix(i, j));// преобразуем каждый элемени в число с двумя знаками после
			dc->TextOut(x + j * SPACING, y + i * SPACING, str);//вывод элемента с учетом отступов
		}
	}
}

void printNumber(CDC* dc, int x, int y, CString caption, double number)// вывод значения
{
	CString str = L"";
	dc->TextOut(x, y, caption);//вывод заголовка
	str.Format(L"%.2lf", number);// преобразуем в число с двумя знаками после
	dc->TextOut(x, y + SPACING, str); // вывод значения
}

double cos(CMatrix& left, CMatrix& right) // косинус угла между двумя векторами
{
	if (left.countCols() > 1 || right.countCols() > 1)//проверка наналичие строк и столбцов
	{
		CString error = L"double cos(CMatrix&, CMatrix&): объект не является вектором";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	if (left.countRows() != right.countRows())// проверка на отсутствие квадратной матрицы
	{
		CString error = L"double cos(CMatrix&, CMatrix&): несоответствие размерностей";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	return ScalarMult(left, right) / (module(left) * module(right));//вывод значения
}

CMatrix VectorMult(// векторное произведение
	CMatrix& left, //первый вектор
	CMatrix& right) //второй вектор
{
	if (left.countCols() > 1 || right.countCols() > 1)// проверка на наличие столбцов и строк в векторе
	{
		CString error = L"CMatrix VectorMult(CMatrix&, CMatrix&): объект не является вектором";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	if (left.countRows() != 3 || right.countRows() != 3)// проверка на то, являются ли векторы векторами, т.е. на наличие столбца на 3 элемента
	{
		CString error = L"CMatrix VectorMult(CMatrix&, CMatrix&): операция определена только для трехмерных векторов";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	CMatrix result(3);
	result(0) = left(1) * right(2) - left(2) * right(1);
	result(1) = left(2) * right(0) - left(0) * right(2);
	result(2) = left(0) * right(1) - left(1) * right(0);
	return result;
}

double ScalarMult(CMatrix& left, CMatrix& right)// скалярное произведение
{
	if (left.countCols() > 1 || right.countCols() > 1)
	{
		CString error = L"double ScalarMult(CMatrix&, CMatrix&): объект не является вектором";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	if (left.countRows() != right.countRows())
	{
		CString error = L"double ScalarMult(CMatrix&, CMatrix&): несоответствие размерностей";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	double result = 0;
	for (int i = 0; i < left.countRows(); i++)
	{
		result += left(i) * right(i);
	}
	return result;
}

double module(CMatrix& vector)// модуль\длина
{
	if (vector.countCols() > 1)
	{
		CString error = L"double module(CMatrix&): объект не является вектором";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	double sum = 0;
	for (int i = 0; i < vector.countRows(); i++)
	{
		sum += vector(i) * vector(i);
	}
	return sqrt(sum); //возвращаем корень
}

CMatrix sphericalToCartesian(CMatrix& point)// преобразование из сферических в декартовы координаты
{
	if (point.countCols() > 1)
	{
		CString error = L"CMatrix sphericalToCartesian(CMatrix&): объект не является вектором";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	if (point.countRows() != 3)
	{
		CString error = L"CMatrix sphericalToCartesian(CMatrix&): операция определена только для трехмерных векторов";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	double r = point(0),//радиус
		theta = point(1), // азимут, от оси Х
		phi = point(2); // угл, от оси Z
	if (r < 0 || phi < 0 || phi > PI)
	{
		CString error = L"CMatrix sphericalToCartesian(CMatrix&): недопустимые аргументы";
		MessageBox(NULL, error, L"Ошибка", MB_ICONSTOP);
		exit(1);
	}
	CMatrix result(3);
	result(0) = r * sin(phi) * cos(theta);
	result(1) = r * sin(phi) * sin(theta);
	result(2) = r * cos(phi);
	return result;
}