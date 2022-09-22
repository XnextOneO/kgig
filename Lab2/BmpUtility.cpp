#include "stdafx.h"
#include "BmpUtility.h"

HBITMAP LoadBmp(CString fileName)
{
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL,
		fileName,
		IMAGE_BITMAP, 0, 0, //SIZE
		LR_LOADFROMFILE | LR_CREATEDIBSECTION);
	return hBmp;
}

void ShowBmp(HWND hWindow, HBITMAP hBmp, int x, int y)
{
	BITMAP bmp; //тут будет храниться файл в виде битов
	GetObject(hBmp,
		sizeof(BITMAP),
		(LPSTR)&bmp); 

	HDC dcDisplay = GetDC(hWindow);
	HDC dcMemory = CreateCompatibleDC(dcDisplay);//создает  контекст памяти совместимый с контекстом отображения

	HBITMAP oldBmp = (HBITMAP)SelectObject(dcMemory, hBmp);  // Выбираем изображение bitmap в контекст памяти

	BitBlt(//рисуем изображение
		dcDisplay, x, y, 
		bmp.bmWidth, bmp.bmHeight, 
		dcMemory,
		0, 0, 
		SRCCOPY); 

	SelectObject(dcMemory, oldBmp);    // Восстанавливаем контекст памяти

	ReleaseDC(hWindow, dcDisplay); //освобождаем управление окном
	DeleteDC(dcMemory);// удаляем контекст памяти
}

void SaveBmp(HWND hWindow, RECT& area, CString fileName)
{
	HDC dcDisplay = GetDC(hWindow);
	HDC dcMemory = CreateCompatibleDC(dcDisplay);//создает контекст памяти совместимый с контекстом отображения

	HBITMAP hBmp = CreateCompatibleBitmap(dcDisplay, //создание точечного рисунка
		abs(area.right - area.left),
		abs(area.bottom - area.top));
	HBITMAP hOldBmp = (HBITMAP)SelectObject(dcMemory, hBmp); // Выбираем изображение bitmap в контекст памяти
	BitBlt(//рисуем изображение
		dcMemory, 0, 0, 
		abs(area.right - area.left), abs(area.bottom - area.top), 
		dcDisplay,
		area.left, area.top, 
		SRCCOPY);


	hBmp = (HBITMAP)SelectObject(dcMemory, hOldBmp);// Восстанавливаем контекст памяти

	BITMAP bmp;
	BITMAPINFOHEADER bmpInfoHeader;//передаст структуру с инфой о изображении
	BITMAPFILEHEADER bmpFileHeader; //сюда запишем сам файл
	int colorDepth = 32; //глубина цвета

	GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp);// получаем объект

	bmpInfoHeader.biSize = sizeof(BITMAPINFOHEADER);//колличество байт необходимое структуре
	bmpInfoHeader.biWidth = bmp.bmWidth;
	bmpInfoHeader.biHeight = bmp.bmHeight;
	bmpInfoHeader.biPlanes = 1;
	bmpInfoHeader.biBitCount = colorDepth; 
	bmpInfoHeader.biCompression = BI_RGB; 
	bmpInfoHeader.biSizeImage = 0; 
	bmpInfoHeader.biXPelsPerMeter = 0; 
	bmpInfoHeader.biYPelsPerMeter = 0;
	bmpInfoHeader.biClrUsed = 0; 
	bmpInfoHeader.biClrImportant = 0; 

	DWORD dwBitSize = ((bmp.bmWidth * colorDepth + 31) / 32) *
		4 * bmp.bmHeight; //битовый размер
		DWORD dwDibSize = sizeof(BITMAPFILEHEADER) +
		sizeof(BITMAPINFOHEADER) +
		dwBitSize;

	bmpFileHeader.bfType = ('M' << 8) | 'B'; //тип файла
	bmpFileHeader.bfSize = dwDibSize; //размер в байтах файла растрового изображения.
	bmpFileHeader.bfReserved1 = 0; //Зарезервированный
	bmpFileHeader.bfReserved2 = 0;
	bmpFileHeader.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
		(DWORD)sizeof(BITMAPINFOHEADER); //Смещение в байтах от начала структуры к битам битовой карты.

	HANDLE hDib = GlobalAlloc(//выделяет глобальный блок памяти
		GHND, 
		dwBitSize + sizeof(BITMAPINFOHEADER));
	LPBITMAPINFOHEADER lpBmpInfoHeader = (LPBITMAPINFOHEADER)GlobalLock(hDib); 
	*lpBmpInfoHeader = bmpInfoHeader;

	GetDIBits(//извлекает биты заданного совместимого точечного рисунка и копирует их в буфер как DIB
		dcMemory,
		hBmp,  
		0, 
		(UINT)bmp.bmHeight,  
		(LPSTR)lpBmpInfoHeader + sizeof(BITMAPINFOHEADER), 
		(BITMAPINFO*)lpBmpInfoHeader, 
		DIB_RGB_COLORS);

	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, 0, NULL,
		CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL |
		FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		MessageBox(NULL, L"Не удалось создать файл", L"Ошибка", MB_ICONSTOP);
		return;
	}

	DWORD dwWritten;

	WriteFile(hFile, 
		(LPSTR)&bmpFileHeader, 
		sizeof(BITMAPFILEHEADER),
		&dwWritten, 
		NULL);
	WriteFile(hFile, (LPSTR)lpBmpInfoHeader, dwDibSize,
		&dwWritten, NULL);

	GlobalUnlock(hDib);//Далее освобождение памяти
	GlobalFree(hDib);
	CloseHandle(hFile);

	ReleaseDC(hWindow, dcDisplay);
	DeleteDC(dcMemory);

	if (dwWritten == 0)
	{
		MessageBox(NULL, L"Не удалось записать файл", L"Ошибка", MB_ICONSTOP);
		return;
	}
}

//Заголовок из структуры BITMAPFILEHEADER и блока BITMAPINFO.Последний содержит :
//Информационные поля.
//Битовые маски для извлечения значений цветовых каналов(опциональные).
//Таблица цветов(опциональная).
//Цветовой профиль(опциональный).
//Пиксельные данные.