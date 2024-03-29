#include "stdafx.h"
#include "LexicalAnalysis.h"
#include "Graphs.h"
#include <sstream>
#include <string.h>
#include <iomanip>

#define LEX_IIFF 'n'

namespace LeX
{
	Graph graph[] =
	{
		{ LEX_INT, FST::FST(GRAPH_INT) },
		{ LEX_STRLEN, FST::FST(GRAPH_STRLEN) },
		{ LEX_CHAR, FST::FST(GRAPH_CHAR)},
		{ LEX_SUBSTR, FST::FST(GRAPH_SUBSTR) },
		{ LEX_STRING, FST::FST(GRAPH_STRING) },
		{ LEX_FUNCTION, FST::FST(GRAPH_FUNCTION) },
		{ LEX_DECL, FST::FST(GRAPH_DECLARE) },
		{ LEX_RETURN, FST::FST(GRAPH_RETURN) },
		{ LEX_PRINT, FST::FST(GRAPH_PRINT) },
		{ LEX_NOSRAVN, FST::FST(GRAPH_NOSRAVN)},
		{ LEX_SRAVN, FST::FST(GRAPH_SRAVN)},
		{ LEX_EIIFF,FST::FST(GRAPH_ELSE)},
		{ LEX_IIFF, FST::FST(GRAPH_IF) },
		{ LEX_GENL, FST::FST(GRAPH_GENL) },
		{ LEX_LITERAL, FST::FST(GRAPH_INT_LITERAL) },
		{ LEX_LITERAL, FST::FST(GRAPH_STRING_LITERAL) },
		{LEX_LITERAL,FST::FST(GRAPH_CHAR_LITERAL)},
		{ LEX_ID, FST::FST(GRAPH_ID) },
		{ LEX_SEPARATOR, FST::FST(GRAPH_SEPARATOR) },
		{ LEX_COMMA, FST::FST(GRAPH_COMMA) },
		{ LEX_LEFTBRACE, FST::FST(GRAPH_LEFT_CURLY_BRACE) },
		{ LEX_BRACELET, FST::FST(GRAPH_RIGHT_CURLY_BRACE) },
		{ LEX_LEFTHESIS, FST::FST(GRAPH_OPEN_PARENTHESIS) },
		{ LEX_RIGHTTHESIS, FST::FST(GRAPH_CLOSE_PARENTHESIS) },
		{ LEX_PLUS, FST::FST(GRAPH_PLUS) },
		{ LEX_MINUS, FST::FST(GRAPH_MINUS) },
		{ LEX_RAITIF, FST::FST(GRAPH_RAITIF)},
		{ LEX_LEFTIF, FST::FST(GRAPH_LEFTIF)},
		{ LEX_STAR, FST::FST(GRAPH_ASTERISK) },
		{ LEX_DIRSLASH, FST::FST(GRAPH_FORWARD_SLASH) },
		{ LEX_EQUAL, FST::FST(GRAPH_EQUALS) }
	};
	LEX INITLEX(In::IN InStruct, Log::LOG& log)
	{
		stack <char> obl;
		LEX Tables;
		char buf;
		Tables.Lextable = LT::Create(InStruct.TokenCount);
		Tables.IDtable = IT::Create(65536);
		bool isDeclare, isParam, isMainFunc, isExecuted, isLiteral;
		isDeclare = isParam = isMainFunc = isExecuted = isLiteral = false;
		IT::IDDATATYPE funcType = IT::INT;
		buf = 'g';
		obl.push(buf); 

		for (int i = 0; i < InStruct.TokenCount; i++)
		{
			for (int j = 0; j < LENGTH(graph); j++)
			{
				FST::FST fstex(InStruct.tokens[i].token, graph[j].graph);
				if (FST::execute(fstex))
				{
					isExecuted = true;
					switch (graph[j].Lexema)
					{
					case LEX_STRLEN:
					{
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_INT)
							{
								IT::Entry entryit(InStruct.tokens[i].token, i,obl.top(), funcType = IT::INT, IT::S);
								IT::Add(Tables.IDtable, entryit);
								
							}
						}
					}
					case LEX_SUBSTR:
					{
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION)
							{
								if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_STRING))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), funcType = IT::STR, IT::S);
									IT::Add(Tables.IDtable, entryit);
								}
								else if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_CHAR))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), funcType = IT::CR, IT::S);
									IT::Add(Tables.IDtable, entryit);
								}
								LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
								entrylt.tokenId = i;
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;
								break;
							}
						}
					}
					case LEX_ID:
					{
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i].token) == -1)
						{
							if (Tables.Lextable.table[i - 1].lexema == LEX_FUNCTION)
							{
							
								if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_INT))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i,obl.top(), funcType = IT::INT, IT::F);
									IT::Add(Tables.IDtable, entryit);
								}
								else if (!strcmp(InStruct.tokens[i - 2 ].token, LEX_TYPE_STRING))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(),funcType = IT::STR, IT::F);
									IT::Add(Tables.IDtable, entryit);
								}
								else if (!strcmp(InStruct.tokens[i - 2].token, LEX_TYPE_CHAR))
								{
									IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), funcType = IT::CR, IT::F);
									IT::Add(Tables.IDtable, entryit);
								}
								LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
								entrylt.tokenId = i;
								LT::Add(Tables.Lextable, entrylt);
								isParam = true;
								break;
							}
							else
								if (Tables.Lextable.table[i - 1].lexema == LEX_OBJECT)
								{
									if (isParam)
									{
										if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_INT))
										{
											char mas[1024] = {};
											strncat_s(mas, InStruct.tokens[i].token, 1024);
											IT::Entry entryit(mas, i, obl.top(), IT::INT, IT::P);
											IT::Add(Tables.IDtable, entryit);

										}
										else if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_STRING))
										{
											IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), IT::STR, IT::P);
											IT::Add(Tables.IDtable, entryit);
										}
										else if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_CHAR))
										{
											IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), IT::CR, IT::P);
											IT::Add(Tables.IDtable, entryit);
										}

										if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS)
											isParam = false;
									}
									else
										if (isDeclare)
										{
											if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_INT))
											{
												IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), IT::INT, IT::V);
												IT::Add(Tables.IDtable, entryit);
											}
											else if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_STRING))
											{
												IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), IT::STR, IT::V);
												IT::Add(Tables.IDtable, entryit);
											}
											else if (!strcmp(InStruct.tokens[i - 1].token, LEX_TYPE_CHAR))
											{
												IT::Entry entryit(InStruct.tokens[i].token, i, obl.top(), IT::CR, IT::V);
												IT::Add(Tables.IDtable, entryit);
											}

											if (InStruct.tokens[i + 1].token[0] == LEX_RIGHTTHESIS)
												isDeclare = false;
										}

									LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, Tables.IDtable.size - 1);
									entrylt.tokenId = i;
									LT::Add(Tables.Lextable, entrylt);
									break;
								}
							break;
						}
						else
						{
							LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, IT::IsId(Tables.IDtable, InStruct.tokens[i].token));
							entrylt.tokenId = i;
							LT::Add(Tables.Lextable, entrylt);
							break;
						}
					}
					case LEX_LITERAL:
					{
						isLiteral = true;
						break;
					}
					case LEX_PLUS:
					{
						LT::Entry entrylt(LEX_PLUS, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_MINUS:
					{
						LT::Entry entrylt(LEX_MINUS, NULL, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_STAR:
					{
						LT::Entry entrylt(LEX_STAR, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_LEFTIF:
					{
						LT::Entry entrylt(LEX_LEFTIF, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_RAITIF:
					{
						LT::Entry entrylt(LEX_RAITIF, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_NOSRAVN:
					{
						LT::Entry entrylt(LEX_NOSRAVN, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_SRAVN:
					{
						LT::Entry entrylt(LEX_SRAVN, InStruct.tokens[i].line);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_DIRSLASH:
					{
						LT::Entry entrylt(LEX_OPERATION, InStruct.tokens[i].line, InStruct.tokens[i].token[0]);
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_BRACELET: {
					obl.pop();
					break;
					}
					case LEX_LEFTBRACE: {
						std::cout << buf;
						obl.push(buf);
						break;
					}
					case LEX_SEPARATOR:
					{
						InStruct.tokens[i].isLiteral = false;
						LT::Entry entrylt(InStruct.tokens[i].token[0], InStruct.tokens[i].line, obl.top() );
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_GENL:
					{buf = 'm';
						if (isMainFunc)
							throw ERROR_THROW_IN(127, InStruct.tokens[i].line,NULL);
						isMainFunc = true;
						funcType = IT::INT;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, obl.top());
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_IIFF:
					{buf = 'i';
						funcType = IT::BOOL;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, obl.top());
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_EIIFF:
					{buf = 'n';
						funcType = IT::BOOL;
						LT::Entry entrylt(LEX_EIIFF, InStruct.tokens[i].line, obl.top());
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_DECL:
					{
						isDeclare = true;
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, obl.top());
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_PRINT:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, obl.top());
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					default:
					{
						LT::Entry entrylt(graph[j].Lexema, InStruct.tokens[i].line, obl.top());
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					}
					break;
				}
			}
			if (!isExecuted || isLiteral)
			{
				if (InStruct.tokens[i].isLiteral || isLiteral)
				{
					switch (Tables.Lextable.table[i - 1].lexema)
					{
					case LEX_EQUAL:
					{
						InStruct.tokens[i].isLiteral = true;
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line,  Tables.IDtable.size);
						LT::Add(Tables.Lextable, entrylt);
						if (IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token) != -1)
							if ((Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::V ||
								Tables.IDtable.table[IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token)].idtype == IT::P))
								if (Tables.Lextable.table[i - 4].lexema == LEX_DECL)
								{
									IT::SetValue(Tables.IDtable, IT::IsId(Tables.IDtable, InStruct.tokens[i - 2].token), InStruct.tokens[i].token);
								}
						break;
					}
					case LEX_PRINT:
					{
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line,  Tables.IDtable.size - 1);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					case LEX_RETURN:
					{
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size - 1);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
					default:
						LT::Entry entrylt(LEX_LITERAL, InStruct.tokens[i].line, Tables.IDtable.size);
						entrylt.tokenId = i;
						LT::Add(Tables.Lextable, entrylt);
						break;
					}
				}
				else
					throw ERROR_THROW_IN(124, Tables.Lextable.table[i - 2].sn, NULL);
			}
			isExecuted = false;
			isLiteral = false;
		}
		return Tables;
	}
}
