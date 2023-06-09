#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
using namespace std;
// for demonstration only. never save your password in the code!
const string server = "tcp://127.0.0.1:3306"; // 데이터베이스 주소
											  // tcp 방식을 이용해서 127.0.0.1(자기자신) 컴퓨터에 3306번(mysql 기본 포트) 으로 접속하라
const string username = "user"; // 데이터베이스 사용자
const string password = "1234"; // 데이터베이스 접속 비밀번호

int main()
{
	// MySQL Connector/C++ 초기화
	sql::Driver* driver; // 추후 해제하지 않아도 Connector/C++가 자동으로 해제해 줌
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
	// please create database "cpp_db" ahead of time
	con->setSchema("cpp_db");
	// 데이터베이스 쿼리 실행
	stmt = con->createStatement();
	stmt->execute("DROP TABLE IF EXISTS inventory");
	cout << "Finished dropping table (if existed)" << endl;
	stmt->execute("CREATE TABLE inventory (id serial PRIMARY KEY, name VARCHAR(50), quantity INTEGER);");
	cout << "Finished creating table" << endl;
	delete stmt;

	pstmt = con->prepareStatement("INSERT INTO inventory(name, quantity) VALUES(?,?)");
	pstmt->setString(1, "banana");
	pstmt->setInt(2, 150);
	pstmt->execute();
	cout << "One row inserted." << endl;
	pstmt->setString(1, "orange");
	pstmt->setInt(2, 154);
	pstmt->execute();
	cout << "One row inserted." << endl;
	pstmt->setString(1, "apple");
	pstmt->setInt(2, 100);
	pstmt->execute();
	cout << "One row inserted." << endl;

	pstmt->setString(1, "human");
	pstmt->setInt(2, 970);	//  자료형 호출(몇번째 항목인지? , 속성값?)
	pstmt->execute();
	cout << "One row inserted. 사람도 음식임." << endl;
	
	// MySQL Connector/C++ 정리
	delete pstmt;
	delete con;
	system("pause");
	return 0;
}