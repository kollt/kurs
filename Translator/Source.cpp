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
////int searchExpression(int index, Lex::LEX *tables) //поиск выражения
////{
////	for (int i = index; i < tables->Lextable.size; i++) //перебор лексем
////	{
////		if (tables->Lextable.table[i].lexema == '+' || tables->Lextable.table[i].lexema == '-'
////			|| tables->Lextable.table[i].lexema == '*' || tables->Lextable.table[i].lexema == '/') //находим операцию
////		{
////			for (; ; i--) //перебираем лексемы обратно
////			{
////				if (tables->Lextable.table[i].lexema == '=')
////					return i + 1;
////			}
////		}
////	}
////	return -1; //если не нашли возвращаем минус 1
////}
//
//bool PolishNotation(int i, LeX::LEX& lex)
//{
//	/*int i = 0;
//	while (searchExpression(i, &lex) != -1)
//	{*/
//	stack<LT::Entry> stack;		// стек для операций
//	queue<LT::Entry> queue;		// очередь для операндов
//	LT::Entry temp;		temp.idxTI = -1;	temp.lexema = '#';	temp.sn = -1;	// запрещенная лексема, все лишние элементы будут заменяться на нее
//	LT::Entry func;		func.idxTI = -1;	func.lexema = '@';	func.sn = -1;	// лексема для вызова функции
//	int countLex = 0;			// количество преобразованных лексем
//	int countParm = 0;			// количество параметров функции
//	int posLex = i;				// запоминаем номер лексемы перед преобразованием
//	bool findFunc = false;		// флаг для функции
//	bool findComma = false;		// флаг для запятой (кол-во параметров +2 сразу)
//	char* buf = new char[2];	// буфер для countParm в строковом представлении
//	for (i; lex.Lextable.table[i].lexema != LEX_SEPARATOR; i++, countLex++)
//	{
//		switch (lex.Lextable.table[i].lexema)
//		{
//		case LEX_ID:	// если идентификатор
//		{
//			if (lex.IDtable.table[lex.Lextable.table[i].idxTI].idtype == IT::F)
//				findFunc = true;
//			queue.push(lex.Lextable.table[i]);
//			continue;
//		}
//		case LEX_LITERAL:		// если литерал
//		{
//			queue.push(lex.Lextable.table[i]);	// помещаем в очередь
//			continue;
//		}
//		case LEX_LEFTHESIS:		// если (
//		{
//			stack.push(lex.Lextable.table[i]); // помещаем ее в стек
//			continue;
//		}
//		case LEX_RIGHTTHESIS:	// если )
//		{
//			if (findFunc)		// если это вызов функции, то лексемы () заменяются на @ и кол-во параметров
//			{
//				if (findComma)
//				{
//					countParm++;
//				}
//				lex.Lextable.table[i] = func;
//				queue.push(lex.Lextable.table[i]);		// добавляем в очередь лексему вызова функции
//				_itoa_s(countParm, buf, 2, 10);			// преобразование числа countParm в строку
//				stack.top().lexema = buf[0];
//				stack.top().idxTI = -1; stack.top().sn = -1;	// заполняем лексему, указывающую количество параметров функции
//				queue.push(stack.top());				// добавляем в очередь эту лексему
//				findFunc = false;
//			}
//			else {
//				while (stack.top().lexema != LEX_LEFTHESIS)	// пока не встретим (
//				{
//					queue.push(stack.top());	// выталкиваем со стека в очередь
//					stack.pop();
//
//					if (stack.empty())
//						return false;
//				}
//			}
//			stack.pop();	// уничтожаем ( или лексему, указывающую количество параметров функции
//			continue;
//		}
//		case LEX_OPERATION:	// если знак оператора
//		{
//			while (!stack.empty() && lex.Lextable.table[i].priority <= stack.top().priority)	// пока приоритет текущего оператора 
//																								//меньше или равен приоритету оператора в вершине стека
//			{
//				queue.push(stack.top());	// выталкиваем со стека в выходную строку
//				stack.pop();
//			}
//			stack.push(lex.Lextable.table[i]);
//			continue;
//		}
//		case LEX_COMMA:	// если запятая
//		{
//			findComma = true;
//			countParm++;
//			continue;
//		}
//		}
//	}
//	while (!stack.empty())	// если стек не пустой
//	{
//		if (stack.top().lexema == LEX_LEFTHESIS || stack.top().lexema == LEX_RIGHTTHESIS)
//			return false;
//		queue.push(stack.top());	// выталкиваем все в очередь
//		stack.pop();
//	}
//	while (countLex != 0)		// замена текущего выражения в таблице лексем на выражение в ПОЛИЗ
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
//	for (int i = 0; i < posLex; i++)		// восстановление индексов первого вхождения в таблицу лексем у операторов из таблицы идентификаторов
//	{
//		if (lex.Lextable.table[i].lexema == LEX_OPERATION || lex.Lextable.table[i].lexema == LEX_LITERAL)
//			lex.IDtable.table[lex.Lextable.table[i].idxTI].idxfirstLE = i;
//	}
//	return true;
//}