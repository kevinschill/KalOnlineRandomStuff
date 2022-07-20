#ifndef CDATABASE_H
#define CDATABASE_H
#pragma once

#include <windows.h> //!first include

#include <stdio.h>
#include <tchar.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

#include <sstream>

#include <map>

 class CDatabase
 {
	 public:
		 CDatabase::CDatabase(){}
		 CDatabase::~CDatabase()
		 {
			SQLFreeConnect(hdbc); 
			SQLFreeEnv(henv);
		 }
		RETCODE rc;        // ODBC return code 
		HENV henv;         // Environment 
		HDBC hdbc;         // Connection handle 
		HSTMT hstmt;       // Statement handle 
		SDWORD cbData;

		bool Connect();
		void Disconnect();
		std::map<int,int> getSkill(int PID);
		void ErrorMsg();
 };

#endif