//#include "Source.cpp"
#include "stdafx.h"
#define EXP1 17

int _tmain(int argc, _TCHAR* argv[])
{
	
	setlocale(LC_ALL, "ru");
	Log::LOG log = Log::INITLOG;
	try
	{																	
		Parm::PARM parm = Parm::getparm(argc, argv);						
		log = Log::getlog(parm.log);// Создание log				
		Log::LOG out = Log::INITLOG;// Инициализация log файла	
		out = Log::getlog(parm.out);// Создание out файла		
		Log::writeLog(log);// Запись протокола			
		Log::writeParm(log, parm);// Запись параметров		
		In::IN in = In::getin(parm.in, parm.out);// Получение входящих параметров
		Log::writeIn(log, in);// Запись входящих параметров	
		LeX::LEX tables = LeX::INITLEX(in, log);// Получение таблицы лексем		
		Log::writeAllTokens(log, tables.IDtable ,tables.Lextable,in);// Запись 	
		/*bool rc = PolishNotation(EXP1, tables);
		if (rc)
		std::cout << "Польская запись построена" << std::endl;
		else
		std::cout << "Польская запись не построена" << std::endl;*/
		Log::writeLexicalTable(log, tables.Lextable,tables.IDtable);// Запись таблицы лекс.		

		Log::writeIDtable(log, tables.IDtable);// Запись таблицы индент.
		Log::writeLiterals(log, in);// Запись таблицы литералов
		Log::Close(log);														
		Log::Close(out);		
		MFST_TRACE_START
			MFST::Mfst Mfst(tables, GRB::getGreibach());
		    Mfst.start();
	}																	
	catch (Error::ERROR e)
	{
		Log::writeError(log, e);
	}
	return 0;
}

