//
// Created by Polina Yakimkina on 13.04.2022.
//

#include "db.h"

User	get_user(uint64_t id)
{
//	 const char[] connstr = (format("postgresql://%1%:%2%@%3%:%4%/%5%")
//			% DB_USER % DB_PASS % HOST % PORT % DB_NAME).str().c_str();

	User user = User();
	user.id = 0;
	const char connstr[] = "postgresql://postgres:123@localhost:5432/dbname=musdb";
	PGconn *conn = PQconnectdb(connstr);
                                                                                  
	if (PQstatus(conn) != CONNECTION_OK) {
		std::cout << "Connection to database failed: " << PQerrorMessage(conn)
				  << std::endl;
		PQfinish(conn);
		return user;
	} else {
		std::cout << "Connection to database succeed." << std::endl;
	}

	PGresult *res = NULL;


	char id_str[256];
	sprintf(id_str, "select * from public.users where id = %llu;", id);
	res = PQexec(conn,id_str);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Getting user failed: " << PQresultErrorMessage(res) << std::endl;
		PQclear(res);
		return user;
	}

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::cout << "Select failed: " << PQresultErrorMessage(res) << std::endl;
	} else {
		user.userName = PQgetvalue(res, 1, 0);
		user.firstName = PQgetvalue(res, 2, 0);
		user.secondName = PQgetvalue(res, 3, 0);
		user.email = PQgetvalue(res, 4, 0);
		user.phoneNumber = PQgetvalue(res, 5, 0);
	}
	PQclear(res);

	return user;
}

vector<Chat>	get_chat(uint64_t user_id)
{
	vector<Chat> chat;
	chat.push_back(Chat());
	chat[0].id = 0;
	const char connstr[] = "postgresql://postgres:123@localhost:5432/dbname=musdb";
	PGconn *conn = PQconnectdb(connstr);

	if (PQstatus(conn) != CONNECTION_OK) {
		std::cout << "Connection to database failed: " << PQerrorMessage(conn)
				  << std::endl;
		PQfinish(conn);
		return chat;
	} else {
		std::cout << "Connection to database succeed." << std::endl;
	}

	PGresult *res = NULL;


	char id_str[256];
	sprintf(id_str, "select * from public.chats where user_id = %llu;", user_id);
	res = PQexec(conn,id_str);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Getting user failed: " << PQresultErrorMessage(res) << std::endl;
		PQclear(res);
		return chat;
	}

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::cout << "Select failed: " << PQresultErrorMessage(res) << std::endl;
	} else {
		for (int i = 0; i < PQntuples(res); i++)
		{
			Chat tmp_chat = Chat();
			tmp_chat.id = atoi(PQgetvalue(res, i, 0));
//			tmp_chat.myMessages = PQgetvalue(res, i, 1);
//			tmp_chat.otherMessages = PQgetvalue(res, i, 2);
			chat.push_back(tmp_chat);
		}
	}
	PQclear(res);

	return chat;
}


vector<Message>	get_message(uint64_t user_id)
{
	vector<Message> mes;
	mes.push_back(Message());
	mes[0].id = 0;
	const char connstr[] = "postgresql://postgres:123@localhost:5432/dbname=musdb";
	PGconn *conn = PQconnectdb(connstr);

	if (PQstatus(conn) != CONNECTION_OK) {
		std::cout << "Connection to database failed: " << PQerrorMessage(conn)
				  << std::endl;
		PQfinish(conn);
		return mes;
	} else {
		std::cout << "Connection to database succeed." << std::endl;
	}

	PGresult *res = NULL;


	char id_str[256];
	sprintf(id_str, "select * from public.chats where user_id = %llu;", user_id);
	res = PQexec(conn,id_str);
	if (PQresultStatus(res) != PGRES_COMMAND_OK) {
		std::cout << "Getting user failed: " << PQresultErrorMessage(res) << std::endl;
		PQclear(res);
		return mes;
	}

	if (PQresultStatus(res) != PGRES_TUPLES_OK) {
		std::cout << "Select failed: " << PQresultErrorMessage(res) << std::endl;
	} else {
		for (int i = 0; i < PQntuples(res); i++)
		{
			Chat tmp_chat = Chat();
			tmp_chat.id = atoi(PQgetvalue(res, i, 0));
//			tmp_chat.myMessages = PQgetvalue(res, i, 1);
//			tmp_chat.otherMessages = PQgetvalue(res, i, 2);
			mes.push_back(tmp_chat);
		}
	}
	PQclear(res);

	return mes;
}


