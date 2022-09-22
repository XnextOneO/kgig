CMatrix CreateTranslate2D(double dx, double dy)
// ��������� ������� ��� �������������� ��������� ������� ��� ��� �������� 
// �� dx �� ��� X � �� dy �� ��� Y � ������������� ������� ���������
// --- ��� ---
// ��������� ������� ��� �������������� ��������� ������� ��� �������� ������
// ������� ��������� �� -dx ��� X � �� -dy �� ��� Y ��� ������������� ��������� �������
{
	CMatrix TS(3, 3);
	TS(0, 0) = 1; TS(0, 1) = 0; TS(0, 2) = dx;
	TS(1, 0) = 0; TS(1, 1) = 1; TS(1, 2) = dy;
	TS(2, 0) = 0; TS(2, 1) = 1; TS(2, 2) = 1;
	return TS;
}

CMatrix CreateRotate2D(double fi)
// ��������� ������� ��� �������������� ��������� ������� ��� ��� ��������
// �� ���� fi (��� fi>0 ������ ������� �������) � ������������� ������� ���������
// --- ��� ---
// ��������� ������� ��� �������������� ��������� ������� ��� �������� ������
// ������� ��������� �� ���� -fi ��� ������������� ��������� ������� 
// fi - ���� � ��������
{
	double ff = (fi * pi) / 180.0; // ������� � �������

	CMatrix RS(3, 3);
	RS(0, 0) = cos(ff); RS(0, 1) = -sin(ff); RS(0, 2) = 0;
	RS(1, 0) = sin(ff); RS(1, 1) = cos(ff);  RS(1, 2) = 0;
	RS(2, 0) = 0;       RS(2, 1) = 0;        RS(2, 2) = 1;
	return RS;
}