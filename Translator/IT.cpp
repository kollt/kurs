#include "stdafx.h"
#include <string.h>
#include <iomanip>
#include "IT.h"
#include <sstream>

namespace IT
{

	Entry::Entry(char* id, int idxLT, char pref,IDDATATYPE datatype,IDTYPE idtype)
	{
		strncpy_s(this->id, ID_MAXSIZE, id, ID_MAXSIZE - 1);
		this->idxfirstLE = idxLT;
		this->iddatatype = datatype;
		this->idtype = idtype;
		this->value.vint = TI_INT_DEFAULT;
		this->value.vstr.len = NULL;
		this->value.vcr.len = NULL;
		this->pref = pref;
	}
	IdTable Create(int size)
	{
		IdTable idtable;
		idtable.table = new Entry[size];
		idtable.size = NULL;
		return idtable;
	}
	void Add(IdTable &idtable, Entry entry)
	{
		
		strncpy_s(idtable.table[idtable.size].id, entry.id,ID_MAXSIZE - 1);
		
		idtable.table[idtable.size].line = entry.line;
		idtable.table[idtable.size].idxfirstLE = entry.idxfirstLE;
		idtable.table[idtable.size].iddatatype = entry.iddatatype;
		idtable.table[idtable.size].idtype = entry.idtype;
		idtable.table[idtable.size].value.vint = TI_INT_DEFAULT;
		idtable.table[idtable.size].value.vstr.len = NULL;
		idtable.table[idtable.size].value.vstr.str[0] = TI_STR_DEFAULT;
		idtable.table[idtable.size].value.vstr.len = NULL;
		idtable.table[idtable.size].value.vstr.str[0] = TI_CR_DEFAULT;
		idtable.table[idtable.size].pref = entry.pref;
		idtable.size++;
	}
	Entry GetEntry(IdTable &idtable, int n)
	{
		return idtable.table[n];
	}
	int IsId(IdTable &idtable, char id[ID_MAXSIZE])
	{
		for (int i = 0; i < idtable.size; i++)
		{
			if (strcmp(idtable.table[i].id, id) == NULL)
				return i;
		}
		return -1;
	}
	int GetSize(IdTable &idtable)
	{
		return idtable.size;
	}
	void SetValue(IdTable &idtable, int indTI, char* token)
	{
		if (idtable.table[indTI].iddatatype == INT)
		{
			int tempInt = atoi(token);
			if (tempInt > INT_MAX)
				tempInt = INT_MAX;
			else if (tempInt < 0)
				tempInt = 0;
			idtable.table[indTI].value.vint = tempInt;
		 }
		else
		{
			idtable.table[indTI].value.vstr.len = strlen(token);
			strcpy_s(idtable.table[indTI].value.vstr.str, TI_STR_MAXSIZE, token);
		}
	}
}
