#include <stdlib.h>
#include <iostream>

#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
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
	sql::Statement* stmt;
	sql::PreparedStatement* pstmt;

	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
		
	}
	catch (sql::SQLException e)
	{
		cout << "Could not connect to server. Error message: " << e.what() << endl;
		system("pause");
		exit(1);
	}

	//please create database "quickstartdb" ahead of time
	con->setSchema("cpp_db_practice");

	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS characters");
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE characters (id serial PRIMARY KEY, name VARCHAR(50), LEVEL INTEGER, HP INTEGER, MP INTEGER, STR INTEGER, DEX INTEGER, _INT INTEGER, LUK INTEGER);");	//���̺� ��Ģ
	cout << "Finished creating table" << endl;
	delete stmt;

	pstmt = con->prepareStatement("INSERT INTO characters(name, LEVEL, HP, MP, STR, DEX, _INT, LUK) VALUES(? ,? ,? ,? ,? ,? ,? ,? )");

	pstmt->setString(1, "Warrior");
	pstmt->setInt(2, 10);
	pstmt->setInt(3, 200);
	pstmt->setInt(4, 50);
	pstmt->setInt(5, 10);
	pstmt->setInt(6, 8);
	pstmt->setInt(7, 4);
	pstmt->setInt(8, 4);
	pstmt->execute();
	cout << "���� ����" << endl;

	pstmt->setString(1, "Archer");
	pstmt->setInt(2, 12);
	pstmt->setInt(3, 150);
	pstmt->setInt(4, 100);
	pstmt->setInt(5, 8);
	pstmt->setInt(6, 10);
	pstmt->setInt(7, 4);
	pstmt->setInt(8, 4);
	pstmt->execute();
	cout << "�ü� ����" << endl;

	pstmt->setString(1, "Mage");
	pstmt->setInt(2, 8);
	pstmt->setInt(3, 50);
	pstmt->setInt(4, 250);
	pstmt->setInt(5, 4);
	pstmt->setInt(6, 4);
	pstmt->setInt(7, 10);
	pstmt->setInt(8, 8);
	pstmt->execute();
	cout << "������ ����" << endl;

	pstmt->setString(1, "Thief");
	pstmt->setInt(2, 11);
	pstmt->setInt(3, 100);
	pstmt->setInt(4, 150);
	pstmt->setInt(5, 4);
	pstmt->setInt(6, 8);
	pstmt->setInt(7, 4);
	pstmt->setInt(8, 10);
	pstmt->execute();
	cout << "���� ����" << endl;

	delete pstmt;
	delete con;
	system("pause");
	return 0;
}