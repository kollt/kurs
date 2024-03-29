#pragma once
#define ID_MAXSIZE		8			//���� ����� �������� ��������������
#define TI_MAXSIZE		4096		//���� ����� ���������� ����� � ������� ���������������
#define TI_INT_DEFAULT	NULL		//�������� �� ��������� ��� int
#define TI_STR_DEFAULT	NULL		//�������� �� ��������� ��� sting
#define TI_CR_DEFAULT   NULL
#define TI_NULLIDX		0xffffffff	//��� �������� ������� ���������������
#define TI_STR_MAXSIZE	255

namespace IT
{
	enum IDDATATYPE { INT = 1, STR = 2, CR=3 ,BOOL=4 };			        //���� ������ ���������������
	enum IDTYPE { V = 1, F = 2, P = 3, L = 4, S = 5 };		//���� ���������������: ����������, �������, ��������, �������,��������.����.
	struct Entry
	{
		int			idxfirstLE;						//������ � ������� ������	
		int         line;                           //������ ������ � �������� ����
		char		id[ID_MAXSIZE];                 //�������������, ��������� ��������� �� ID_MAXSIZE
		char        pref ;                       //�������
		IDDATATYPE	iddatatype;						//��� ������
		IDTYPE		idtype;							//��� ��������������
	                                                                                                                                                                                                                                         	//string      obolv[ID_MAXSIZE];				// ������� ��������� 
		union
		{
			int	vint;								//�������� integer
			struct
			{
				int len;							//���������� �������� � string
				char str[TI_STR_MAXSIZE - 1];		//������� string
			}vstr;				                    //�������� string
			struct 
			{
				int len;
				char cr[2];
			}vcr;
		}value;										//�������� ��������������
		Entry()
		{
			this->value.vint = TI_INT_DEFAULT;
			this->value.vstr.len = NULL;
			this->value.vcr.len = NULL;
			this->pref = NULL;
		}
		Entry(char* id, int idxLT, char pref,IDDATATYPE datatype, IDTYPE idtype);
	};
	struct IdTable									//��������� ������� ���������������
	{
		int maxsize;								//������� ������� ��������������� < TI_MAXSIZE
		int size;									//������� ������ ������� ��������������� < maxsize
		Entry* table;								//������ ����� ������� ���������������
	};
	IdTable Create(int size = NULL);				//������� ������� ��������������� < TI_MAXSIZE
	void Add(										//�������� ������ � ������� ���������������
		IdTable &idtable,							//��������� ������� ���������������
		Entry entry);								//������ ������� ��������������� 
	Entry GetEntry(									//�������� ������ ������� ���������������
		IdTable &idtable,							//��������� ������� ���������������
		int n);										//����� ���������� ������
	int IsId(										//�������: ����� ������(���� ����), TI_NULLIDX(���� ����)
		IdTable &idtable,							//��������� ������� ���������������
		char id[ID_MAXSIZE]);						//�������������
	int GetSize(IdTable &idtable);					//�������� ������
	void SetValue(IdTable &idtable, int, char*);	//������ �������� ��������������

}