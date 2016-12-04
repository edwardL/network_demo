#ifndef MYSQL_CONNECTION_H
#define MYSQL_CONNECTION_H
#include "../../mysqlconnector/v32/include/mysql.h"
#include "mysql/mysqlconnection.h"
#include "mysql/mysqlconnfactory.h"
#include "connpool.h"
#include<iostream>
using namespace std;
#include <string.h>

#pragma comment(lib,"libmysql.lib")

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>

#define STRING_LEN 20
char username	[STRING_LEN] = "edward2";
char userpass	[STRING_LEN] = "askjsadkjas";


class MySQL_Connection
{
public:
	MySQL_Connection()
	{
		printf("mysql client version : %d\n",mysql_get_client_version());
		MYSQL *conn_ptr;
		MYSQL_RES *res;

		char* host = "192.168.7.98";
		//char* host = "192.168.4.189";
		char* user = "root";
		char* passwd = "121212";
		char* db = "g2_98_0_game";
		//char* db = "testdbname";
		unsigned short port = 4580;
		char* unix_socket = NULL;
		char* charset = "utf8";

		MysqlConnection conn(host,user,passwd,db,port,charset);

		conn.Connect();
		if(conn.IsActive())
		{
			printf("mysql connection is active\n");
		}else{
		}

		// test mysqlconnfactory
		MysqlConnFactory connFactory(host,user,passwd,db,port,charset);
		IConnection* iconnection = connFactory.CreateConn();
		delete iconnection;
		// test  connpool
		ConnPool::Instance()->Init(&connFactory);
		IConnection* a = ConnPool::Instance()->GetConn();
		IConnection* b = ConnPool::Instance()->GetConn();

		// test mysql statement
		if (strcmp(host,"192.168.4.189") == 0)
		{
	//		Mysql_Statement((MYSQL*)a->GetConn());
			Mysql_Statement((MYSQL*)a->GetConn());
		}
/*
		MYSQL* tmp = 0;
		conn_ptr = mysql_init(0);
		unsigned long client_flag = 0;
		client_flag |= CLIENT_FOUND_ROWS;
		tmp = mysql_real_connect(conn_ptr, host,user,passwd,db, port, 0, client_flag);
		if (0 == tmp)
		{
			printf("%s\n",mysql_error(conn_ptr));
			printf("failed\n");
			return;
		}
		*/
	}

	void Mysql_Statement2(MYSQL* mysql)
	{
		MYSQL_STMT* stmt = mysql_stmt_init(mysql);
		char * query = "insert into userinfo(username,userpass) values(?,?);";
	}

	void Mysql_Statement(MYSQL * mysql)
	{
		/// ≤‚ ‘ ß∞‹
		int ret = 0;
		char errMsg[200] = {0};

		const char* statement = "insert into table_name(age) values(?);";
		MYSQL_STMT *stmt = mysql_stmt_init(mysql);
		if(!stmt)
		{
			fprintf(stderr,"mysql_stmt_init,2 failed\n");
			fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
			exit(0);
		}
		if(mysql_stmt_prepare(stmt,statement,strlen(statement)))
		{
			fprintf(stderr,"mysql_stmt_prepare,2 failed\n");
			fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
			exit(0);
		}
		int i = 0;
		int max_num = 3;
		const int FIELD_NUM = 1;
		while(i < max_num)
		{
			MYSQL_BIND bind[FIELD_NUM];
			memset(bind,0,FIELD_NUM * sizeof(MYSQL_BIND));
			
			int age = 111;

			bind[0].buffer_type = MYSQL_TYPE_LONG;
			bind[0].buffer = &age;




			if(mysql_stmt_bind_param(stmt,bind))
			{
				fprintf(stderr,"mysql_stmt_bind_param failed\n");
				fprintf(stderr,"%s\n",mysql_stmt_error(stmt));
				exit(0);
			}
			cout << "before execute\n";
			if(mysql_stmt_execute(stmt))
			{
				fprintf(stderr,"mysql stmt execute failed\n");
				fprintf(stderr,mysql_stmt_error(stmt));
				exit(0);
			}
			cout << "after execute\n";

			i++;
		}
		mysql_commit(mysql);
	//	mysql_stmt_send_long_data(stmt);
		mysql_stmt_close(stmt);
	}
};



#endif