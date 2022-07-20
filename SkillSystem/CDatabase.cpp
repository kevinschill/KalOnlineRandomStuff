#include "CDatabase.h"

std::map<int,int> CDatabase::getSkill(int PID)
 {
	std::map<int,int> retMap;
	SQLAllocHandle(SQL_HANDLE_STMT, hdbc, &hstmt);
	std::stringstream s;
	s << "SELECT * FROM [kal_db].[dbo].[Skill] WHERE PID=" << PID;
	if(SQL_SUCCESS!=SQLExecDirectA(hstmt, (SQLCHAR*)s.str().c_str(), SQL_NTS))
	{
		printf("fail\n");
		std::map<int,int> ret;
		ret[0] = 0;
		return ret;
    }
	else
	{
		int Skill = 0;
		int Level = 0;
        while(SQLFetch(hstmt)==SQL_SUCCESS)
		{
			SQLGetData(hstmt, 2, SQL_C_TINYINT, &Skill, 0, NULL);
            SQLGetData(hstmt, 3, SQL_C_TINYINT, &Level, 0, NULL);
			retMap[Skill] = Level;
        }
		return retMap;
	}    
 }
void CDatabase::ErrorMsg()
{
 /* Buffer für die ODBC-Fehlernachricht */
 unsigned char * ErrorBuffer= new unsigned char [SQL_MAX_MESSAGE_LENGTH];

 SQLErrorA(henv,                 // Environment Handle
    hdbc,                   // Connection Handle
    hstmt,                  // Statement Handle
    NULL,                   // SQLSTATE (= ODBC ErrorCode)
    NULL,                   // Native Error Code (Data Source spez.)
    ErrorBuffer,            // Adresse eines Strings für den Fehlertext
    SQL_MAX_MESSAGE_LENGTH, // max. Länge des Strings von vorigem Parameter
    NULL);                  // Reserve für Fehlertextrückgabe

 printf("Error: %s\n",ErrorBuffer);
}
 bool CDatabase::Connect()
 {
	char db[] = "kal_db";
    SQLAllocEnv(&henv);
	SQLSetEnvAttr(henv, SQL_ATTR_ODBC_VERSION,(SQLPOINTER) SQL_OV_ODBC3, SQL_IS_UINTEGER);
	SQLAllocHandle(SQL_HANDLE_DBC, henv, &hdbc);
    SQLAllocConnect(henv, &hdbc); 
    rc = SQLConnectA(hdbc, (unsigned char*)db, SQL_NTS, 0, 0, 0, 0);
	if ((rc != SQL_SUCCESS) && (rc != SQL_SUCCESS_WITH_INFO)) 
    { 
		printf("failxx\n");
		ErrorMsg();
        SQLFreeConnect(hdbc); 
        SQLFreeEnv(henv); 
        return false; 
    }
	else
		return true;
 }
 void CDatabase::Disconnect()
 {
	 SQLFreeConnect(this->hdbc); 
     SQLFreeEnv(this->henv);
 }