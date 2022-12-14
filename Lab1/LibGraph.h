#pragma once

#include "CMatrix.h"

void fillMatrix(CMatrix&, double);								//вывод матрицы с начальным значением 

void printMatrix(CDC*, int, int, CString, CMatrix&);			//вывод матриц

void printNumber(CDC*, int, int, CString, double);				//вывод значения

double cos(CMatrix&, CMatrix&);									//подсчет косинуса угла между двумя векторами

CMatrix VectorMult(CMatrix&, CMatrix&);							//вектораное произведение векторов

double ScalarMult(CMatrix&, CMatrix&);							// скалярное произведение

double module(CMatrix&);										//модуль\длинна вектора

CMatrix sphericalToCartesian(CMatrix&);							// перевод из сферических координат в декартовые