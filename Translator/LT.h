#pragma once

#include"Error.h"
#include <string>

#define	LEXEMA_FIXSIZE	1			// Фиксированный размер таблицы лексем
#define	LT_MAXSIZE		65536		// Максимальный размер таблицы лексем
#define	LT_TI_NULLDX	0xffffffff	// Пустота в таблице лексем
#define	LEX_INT			't'			// Целый
#define	LEX_STRING	    't'			// Строка
#define LEX_OBJECT      't'			// Обьект						 типы   Беззнаковый целый ,Символьный    Целочисленные операции побитовые или, и, инверсия   Литералы целые восьмеричное | двоичное
#define LEX_CHAR        't'         // символ
#define	LEX_ID			'i'			// Индентификатор                строковые  произвольно Функции преобразование строки в число; произвольная   условный оператор
#define	LEX_LITERAL		'l'			// Литерал
#define	LEX_FUNCTION	'f'			// Функция
#define	LEX_DECL	    'd'			// Declare
#define LEX_STRLEN      'e'         // Пользовательский тип 1
#define LEX_SUBSTR      's'         // Пользовательский тип 2
#define	LEX_RETURN		'r'			// Rt
#define	LEX_PRINT		'p'			// Print
#define	LEX_GENL		'g'			// Genl
#define	LEX_SEPARATOR	';'			// ;
#define	LEX_COMMA		','			// ,
#define	LEX_LEFTBRACE	'{'			// {
#define	LEX_BRACELET	'}'			// }
#define	LEX_LEFTHESIS	'('			// (
#define	LEX_RIGHTTHESIS	')'			// )
#define	LEX_PLUS		'+'			// +
#define	LEX_MINUS		'-'			// -
#define	LEX_STAR		'*'			// *
#define	LEX_DIRSLASH	'/'			// /
#define	LEX_EQUAL		'='			// =
#define	LEX_OPERATION  	'v'			// v
#define LEX_RAITIF      '>'
#define LEX_LEFTIF      '<'
#define LEX_IIFF        'n'
#define LEX_EIIFF       'o'
#define LEX_SRAVN       '^'        //==
#define LEX_NOSRAVN     '@'
#define	LEX_TYPE_INT	    "int"	
#define LEX_TYPE_IF         "if"
#define LEX_TYP_ELSE        "else"
#define	LEX_TYPE_STRING	    "str"
#define LEX_TYPE_DECL       "decl"
#define LEX_TYPE_CHAR       "cr"
#define	LEX_TYPE_FUNCTION	"func"	
#define	LEX_TYPE_VARIABLE	"variable"	
#define LEX_TYPE_PARAMETR	"parametr"	
#define LEX_TYPE_LITERAL	"literal"
#define LEX_TYPE_STANDART	"standart"
#define LEX_TYPE_GENL       "genl"
namespace LT						
{
	struct Entry
	{
		char lexema;			// Лексема
		int sn;					// Номер строки в исходном тексте
		int idxTI;				// Индекс в таблице идентификаторов или LT_TI_NULLIDX
		int tokenId = 0;		
		char operation;			
		std::string value;		
		Entry() {};				
		Entry(char obl);
		Entry(char lexema, int snn, int idxti = LT_TI_NULLDX);		
		Entry(char lexema, int snn, char v, int idxti = LT_TI_NULLDX);
		int priority;
	};

	struct LexTable						// Экземпляр таблицы лексем
	{
		int maxsize;					// Ёмкость таблицы лексем
		int size;						// Текущий размер таблицы лексем
		Entry* table;					// Массив строк таблицы лексем
	};
	LexTable Create(int size);			// Ёмкость < LT_MAXSIZE
	void Add(LexTable &lextable, Entry entry);	// Экземпляр таблицы лексем, строка таблицы лексем
	Entry GetEntry(LexTable &lextable, int n);	// Экземпляр таблицы лексем, номер получаемой строки
	void Delete(LexTable &lextable);	// Удалить таблицу лексем (освободить память)

	struct LIT {
		std::string pref[65];
		std::string name[65];
        std::string literals[65];
	    std::string typel[65];
	};
}