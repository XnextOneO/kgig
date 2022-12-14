// ChildView.cpp : реализация класса CChildView

#include "stdafx.h"
#include "Lab1.h"
#include "ChildView.h"
#include "LibGraph.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
}

CChildView::~CChildView()
{
}

BEGIN_MESSAGE_MAP(CChildView, CWnd)
	ON_WM_PAINT()
	ON_COMMAND(ID_TEST_MATRIXES, &CChildView::OnTestMatrixes)//запуск теста матриц при нажатии кнопки в меню
	ON_COMMAND(ID_TEST_FUNCTIONS, &CChildView::OnTestFunctions)//запуск теста функций при нажатии кнопки в меню
END_MESSAGE_MAP()

// обработчики сообщений CChildView

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS,
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW + 1), NULL);

	return TRUE;
}

void CChildView::OnPaint()
{
	CPaintDC dc(this); // контекст устройства для рисования

					   // TODO: Добавьте код обработки сообщений

					   // Не вызывайте CWnd::OnPaint() для сообщений рисования
}

void CChildView::OnTestMatrixes()
{
	RedrawWindow();
	CDC *dc = GetDC(); 

	CMatrix a(3, 3); 
	CMatrix b(3, 3);
	CMatrix v1(3);
	CMatrix v2(3);
	fillMatrix(a, 3);
	fillMatrix(b, -1);
	fillMatrix(v1, 3);
	fillMatrix(v2, 7);
	printMatrix(dc, 50, 50, L"МАТРИЦА A", a);
	printMatrix(dc, 250, 50, L"МАТРИЦА B", b);
	printMatrix(dc, 450, 50, L"ВЕКТОР V1", v1);
	printMatrix(dc, 650, 50, L"ВЕКТОР V2", v2);
	printMatrix(dc, 50, 400, L"A + B", a + b);
	printMatrix(dc, 250, 400, L"A * B", a * b);
	printMatrix(dc, 450, 400, L"A * V1", a * v1);
	printMatrix(dc, 650, 400, L"V1^T * V2", v1.transpose() * v2);
	printMatrix(dc, 850, 400, L"V1^T * A * V2", v1.transpose() * a * v2);
}

void CChildView::OnTestFunctions()
{
	RedrawWindow();
	CDC *dc = GetDC(); // контекст устройства для рисования

	CMatrix v1(3);//создание вектора
	CMatrix v2(3);
	CMatrix point(3);//создание
	fillMatrix(v1, 1);//начать создание вектора с 1
	fillMatrix(v2, 4);//начать создание ма
	fillMatrix(point, 1);
	printMatrix(
		dc, //контекст устройства рисования
		50,// точка начала рисунка по х
		50, // точка начала рисунка по у
		L"ВЕКТОР V1", //выводимая надпись
		v1);//вывод векоора
	printMatrix(dc, 250, 50, L"ВЕКТОР V2", v2);
	printMatrix(dc, 450, 50, L"ТОЧКА P", point);
	printMatrix(dc, 50, 400, L"V1 x V2", VectorMult(v1, v2));
	printNumber(dc, 250, 400, L"V1 * V2", ScalarMult(v1, v2));
	printNumber(dc, 450, 400, L"|V1|", module(v1));

	//printNumber(dc, 500, 400, L"|V2|", module(v2));

	printNumber(dc, 650, 400, L"cos(V1 /\\ V2)", cos(v1, v2));
	printMatrix(dc, 850, 400, L"ТОЧКА P (ПРЯМОУГОЛЬНАЯ СФЕРИЧЕСКИЕ В ДЕКАРТОВЫ)", sphericalToCartesian(point));
}