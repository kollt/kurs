#pragma once
#include "stdafx.h"
#include "Parm.h"
#include <fstream>
#include "In.h"
#include "Error.h"
#include "IT.h"
#include "LT.h"
using namespace std;

namespace Log 
{
	struct LOG 
	{
		wchar_t logfile[PARM_MAX_SIZE];
		std::ofstream *stream;
	};

	static const LOG INITLOG = { L"", NULL };
	LOG getlog(wchar_t logfile[]);
	void writeLine(const LOG &log, char *c, ...);
	void writeLine(const LOG &log, wchar_t *c, ...);
	void writeLog(const LOG &log);
	void writeParm(const LOG &log, const Parm::PARM &parm);
	void writeIn(const LOG &log, const In::IN &in);
	void writeError(const LOG &log, const Error::ERROR &error);
	void writeLexicalTable(const LOG &log, LT::LexTable &lextable, IT::IdTable &IDtable);
	void writeIDtable(const LOG &log, IT::IdTable &IDtable);
	void writeAllTokens(const LOG &log, IT::IdTable& IDtable, LT::LexTable& lextable,In::IN &In );
	//void writeIntermediateCode(LOG &log, LT::LexTable &lextable);
	void Close(const LOG &log);
	void writeLiterals(const LOG& log, In::IN& In);
}
