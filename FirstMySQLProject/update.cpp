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
const string username = "user"; // 데이터베이스 사용자
const string password = "1234"; // 데이터베이스 접속 비밀번호

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

	con->setSchema("cpp_db");

	//update
	pstmt = con->prepareStatement("UPDATE inventory SET quantity = ? WHERE name = ?");
	pstmt->setInt(1, 200);
	pstmt->setString(2, "banana");
	pstmt->executeQuery();
	printf("Row updated\n");

	delete con;
	delete pstmt;
	system("pause");
	return 0;
}