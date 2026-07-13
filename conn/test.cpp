#include <iostream>
#include <unistd.h>
#include <string>
#include <mysql/mysql.h>
using namespace std;

const string host = "127.0.0.1";
const string user = "lic";
const string passwd = "123";
const string db = "conn";
const unsigned int port = 3306;

/*
 *g++ test.cpp  -L /lib64/mysql -l mysqlclient
 */

int main()
{
  /*
   *cout<< mysql_get_client_info() <<endl;  
   */

// 1.句柄
  MYSQL* my = mysql_init(nullptr);

  if(my ==  nullptr)
  {
    cerr<< "init failend" <<endl;
  }

  mysql_set_character_set(my, "utf8");
  
// 
  if(mysql_real_connect(my, host.c_str(), user.c_str(), passwd.c_str(), db.c_str(), port, nullptr, 0) == nullptr)
  {
    cerr<< "connect fail" <<endl;
  }

  cout<< "connect success" <<endl;

  string sql1 = "insert into user(name, age, tel) values('lic2', 342, '123d')";
	mysql_query(my, sql1.c_str());

  string sql2 = "insert into user(name, age, tel) values('lic3', 342, '123dt')";
  mysql_query(my, sql2.c_str());

  sql2 = "insert into user(name, age, tel) values('李海军22ddd', 342, '123dtdddab')";
  mysql_query(my, sql2.c_str());

  sql2 = "select * from user";
  mysql_query(my, sql2.c_str());
  
  MYSQL_RES * res = mysql_store_result(my);
  if(res == nullptr)
  {
    cout << "mysql_store_result failed" <<endl;
    return -1;
  }

// 1.mysql读取出来的就是当做字符串。
// 2.res指针数组。
// 3.MYSQL_RES char**数组
  /*
   * res---->data
   * */

  // 行数
  my_ulonglong rows = mysql_num_rows(res);
  // 列数
  unsigned int fileds = mysql_num_fields(res);
  cout<< "rows" << rows <<endl;
  cout<< "fileds" << fileds <<endl;
  cout<<endl;

  MYSQL_FIELD* fileds_array = mysql_fetch_fields(res);
  for(int i = 0; i < fileds; ++i)
  {
    cout<< fileds_array[i].name << "\t";
  }
  cout<<endl;
  cout<<endl;


  
  for(int i = 0; i < rows; ++i)
  {
    MYSQL_ROW row = mysql_fetch_row(res);
    for(int j = 0; j < fileds; ++j)
    {
      cout<< row[j] << " ";
    }
    cout<<endl;
  }

// 
/*
 *  string line;
 *  while(true)
 *  {
 *    cout<< "mysql>";
 *    getline(cin, line);
 *    mysql_query(my, line.c_str());
 *  }
 *
 */

  mysql_close(my);
  mysql_free_result(res);
  return 0;
}

