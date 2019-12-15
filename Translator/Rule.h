#pragma once
#include "stdafx.h"
#define GRB_ERROR_SERIES 605
#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(
		NS('S'), // ��������� ������
		TS('$'), //��� �����      
		8,									  // ���������� ������
		Rule(
			NS('S'),
			GRB_ERROR_SERIES + 0,    // �������� ��������� ���������
			4,                                // 
			Rule::Chain(13, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(8, TS('g'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';')),
			Rule::Chain(9, TS('g'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S')),
			Rule::Chain(14, TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'), NS('N'), TS('r'), NS('E'), TS(';'), TS('}'), TS(';'), NS('S'))
		),
		Rule(
			NS('N'),
			GRB_ERROR_SERIES + 1,    // ����������� � ��������
			16,                               // 
			Rule::Chain(5, TS('d'), TS('t'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(7, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(6, TS('d'), TS('t'), TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(5, TS('i'), TS('='), NS('E'), TS(';'), NS('N')),
			Rule::Chain(9, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('i'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), TS('l'), TS(';'), NS('N')),
			Rule::Chain(4, TS('p'), NS('E'), TS(';'), NS('N')),
			Rule::Chain(3, TS('p'), NS('E'), TS(';')),
			Rule::Chain(4, TS('d'), TS('t'), TS('i'), TS(';')),
			Rule::Chain(8, TS('d'), TS('t'), TS('f'), TS('i'), TS('('), NS('F'), TS(')'), TS(';')),
			Rule::Chain(3, TS('p'), TS('i'), TS(';')),
			Rule::Chain(3, TS('p'), TS('l'), TS(';')),
			Rule::Chain(3, TS('n'), NS('I'), NS('N')),
			Rule::Chain(2, TS('n'), NS('I'))

		),
		Rule(
			NS('E'),
			GRB_ERROR_SERIES + 2,    // ������ � ���������
			9,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(1, TS('F')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('F'),
			GRB_ERROR_SERIES + 3,    // ������ � ���������� �������
			2,                                // 
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('W'),
			GRB_ERROR_SERIES + 4,    // ������ � ���������� ���������� ������� 
			4,                                // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'), TS(','), NS('W')),
			Rule::Chain(3, TS('l'), TS(','), NS('W'))
		),
		Rule(
			NS('M'),
			GRB_ERROR_SERIES + 5,    // ��������
			4,								  //
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E'))
		),
		Rule(
			NS('I'),
			GRB_ERROR_SERIES + 6,
			8,
			Rule::Chain(9,  TS('('), TS('i'), NS('O'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(9,  TS('('), TS('l'), NS('O'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N') ),
			Rule::Chain(9,  TS('('), TS('i'), NS('O'), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(9,  TS('('), TS('l'), NS('O'), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(13, TS('('), TS('i'), NS('O'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), TS('o'),TS('{'),NS('N'),TS('}'),NS('N')),
			Rule::Chain(13, TS('('), TS('l'), NS('O'), TS('i'), TS(')'), TS('{'), NS('N'), TS('}'), TS('o'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(13, TS('('), TS('i'), NS('O'), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), TS('o'), TS('{'), NS('N'), TS('}'), NS('N')),
			Rule::Chain(13, TS('('), TS('l'), NS('O'), TS('l'), TS(')'), TS('{'), NS('N'), TS('}'), TS('o'), TS('{'), NS('N'), TS('}'), NS('N'))
		),
		Rule(
			NS('O'),
			GRB_ERROR_SERIES + 7,
			4,								  //
			Rule::Chain(1, TS('>')),
			Rule::Chain(1, TS('<')),
			Rule::Chain(1, TS('^')),
			Rule::Chain(1, TS('@'))
		)
	);
}