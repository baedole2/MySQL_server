#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
const string username = "user2"; // 데이터베이스 사용자
const string password = "10130424"; // 데이터베이스 접속 비밀번호

int main()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;

	try
	{
		driver = get_driver_instance();
		//for demonstration only. never save password in the code!
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	con->setSchema("cpp_db_practice");

	//update
	pstmt = con->prepareStatement("UPDATE characters SET _INT = ? WHERE name = ?");
	pstmt->setInt(1, 300);
	pstmt->setString(2, "Mage");
	pstmt->executeQuery();
	printf("Row updated\nMage's INT : 10 -> 300 !!\n");

	delete con;
	delete pstmt;
	system("pause");
	return 0;
}