#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
using namespace std;

//for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306"; // �����ͺ��̽� �ּ�
const string username = "user2"; // �����ͺ��̽� �����
const string password = "10130424"; // �����ͺ��̽� ���� ��й�ȣ

int main()
{
	sql::Driver* driver;
	sql::Connection* con;
	sql::PreparedStatement* pstmt;
	sql::ResultSet* result;

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

	//select  
	pstmt = con->prepareStatement("SELECT * FROM characters;");
	result = pstmt->executeQuery();

	while (result->next())
		printf("Reading from table=(%d, %s, %d, %d, %d, %d, %d, %d)\n",
			result->getInt(1), result->getString(2).c_str(), result->getInt(3),
			result->getInt(4), result->getInt(5), result->getInt(6),
			result->getInt(7), result->getInt(8));

	delete result;
	delete pstmt;
	delete con;
	system("pause");
	return 0;
}