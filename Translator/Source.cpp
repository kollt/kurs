#include "stdafx.h"
//#include "Header.h"
//#include <stack>
//#include <queue>
//
//using namespace std;
//int prior(char znak)
//{
//	switch (znak)
//	{
//	case '+':
//	case '-':
//		return 2;
//	case '*':
//	case '/':
//		return 3;
//	default:
//		return 0;
//	}
//}
////int searchExpression(int index, Lex::LEX *tables) //����� ���������
////{
////	for (int i = index; i < tables->Lextable.size; i++) //������� ������
////	{
////		if (tables->Lextable.table[i].lexema == '+' || tables->Lextable.table[i].lexema == '-'
////			|| tables->Lextable.table[i].lexema == '*' || tables->Lextable.table[i].lexema == '/') //������� ��������
////		{
////			for (; ; i--) //���������� ������� �������
////			{
////				if (tables->Lextable.table[i].lexema == '=')
////					return i + 1;
////			}
////		}
////	}
////	return -1; //���� �� ����� ���������� ����� 1
////}
//
//bool PolishNotation(int i, LeX::LEX& lex)
//{
//	/*int i = 0;
//	while (searchExpression(i, &lex) != -1)
//	{*/
//	stack<LT::Entry> stack;		// ���� ��� ��������
//	queue<LT::Entry> queue;		// ������� ��� ���������
//	LT::Entry temp;		temp.idxTI = -1;	temp.lexema = '#';	temp.sn = -1;	// ����������� �������, ��� ������ �������� ����� ���������� �� ���
//	LT::Entry func;		func.idxTI = -1;	func.lexema = '@';	func.sn = -1;	// ������� ��� ������ �������
//	int countLex = 0;			// ���������� ��������������� ������
//	int countParm = 0;			// ���������� ���������� �������
//	int posLex = i;				// ���������� ����� ������� ����� ���������������
//	bool findFunc = false;		// ���� ��� �������
//	bool findComma = false;		// ���� ��� ������� (���-�� ���������� +2 �����)
//	char* buf = new char[2];	// ����� ��� countParm � ��������� �������������
//	for (i; lex.Lextable.table[i].lexema != LEX_SEPARATOR; i++, countLex++)
//	{
//		switch (lex.Lextable.table[i].lexema)
//		{
//		case LEX_ID:	// ���� �������������
//		{
//			if (lex.IDtable.table[lex.Lextable.table[i].idxTI].idtype == IT::F)
//				findFunc = true;
//			queue.push(lex.Lextable.table[i]);
//			continue;
//		}
//		case LEX_LITERAL:		// ���� �������
//		{
//			queue.push(lex.Lextable.table[i]);	// �������� � �������
//			continue;
//		}
//		case LEX_LEFTHESIS:		// ���� (
//		{
//			stack.push(lex.Lextable.table[i]); // �������� �� � ����
//			continue;
//		}
//		case LEX_RIGHTTHESIS:	// ���� )
//		{
//			if (findFunc)		// ���� ��� ����� �������, �� ������� () ���������� �� @ � ���-�� ����������
//			{
//				if (findComma)
//				{
//					countParm++;
//				}
//				lex.Lextable.table[i] = func;
//				queue.push(lex.Lextable.table[i]);		// ��������� � ������� ������� ������ �������
//				_itoa_s(countParm, buf, 2, 10);			// �������������� ����� countParm � ������
//				stack.top().lexema = buf[0];
//				stack.top().idxTI = -1; stack.top().sn = -1;	// ��������� �������, ����������� ���������� ���������� �������
//				queue.push(stack.top());				// ��������� � ������� ��� �������
//				findFunc = false;
//			}
//			else {
//				while (stack.top().lexema != LEX_LEFTHESIS)	// ���� �� �������� (
//				{
//					queue.push(stack.top());	// ����������� �� ����� � �������
//					stack.pop();
//
//					if (stack.empty())
//						return false;
//				}
//			}
//			stack.pop();	// ���������� ( ��� �������, ����������� ���������� ���������� �������
//			continue;
//		}
//		case LEX_OPERATION:	// ���� ���� ���������
//		{
//			while (!stack.empty() && lex.Lextable.table[i].priority <= stack.top().priority)	// ���� ��������� �������� ��������� 
//																								//������ ��� ����� ���������� ��������� � ������� �����
//			{
//				queue.push(stack.top());	// ����������� �� ����� � �������� ������
//				stack.pop();
//			}
//			stack.push(lex.Lextable.table[i]);
//			continue;
//		}
//		case LEX_COMMA:	// ���� �������
//		{
//			findComma = true;
//			countParm++;
//			continue;
//		}
//		}
//	}
//	while (!stack.empty())	// ���� ���� �� ������
//	{
//		if (stack.top().lexema == LEX_LEFTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
//			return false;
//		queue.push(stack.top());	// ����������� ��� � �������
//		stack.pop();
//	}
//	while (countLex != 0)		// ������ �������� ��������� � ������� ������ �� ��������� � �����
//	{
//		if (!queue.empty()) {
//			lex.Lextable.table[posLex++] = queue.front();
//			queue.pop();
//		}
//		else
//		{
//			lex.Lextable.table[posLex++] = temp;
//		}
//		countLex--;
//	}
//
//	for (int i = 0; i < posLex; i++)		// �������������� �������� ������� ��������� � ������� ������ � ���������� �� ������� ���������������
//	{
//		if (lex.Lextable.table[i].lexema == LEX_OPERATION || lex.Lextable.table[i].lexema == LEX_LITERAL)
//			lex.IDtable.table[lex.Lextable.table[i].idxTI].idxfirstLE = i;
//	}
//	return true;
//}