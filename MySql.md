# MySql

## 1. 数据库基础

**07 数据库基础**

1. **mysql它是数据库服务的客户端**
2. **mysqld它是数据库服务的服务端。**
3. **mysq本质：基于C(mysql) S(mysqld)模式的一种网络服务**

**mysql是一套给我们提供 数据存取的网络程序。**

**数据库一般指的是：在磁盘或者内存中存储的 特定组织数据。-----  将来在磁盘上存储的一套数据库方案。**

**数据库服务---mysqld。**



**一般的文件确实提供了文件的存储能力，但是文件并没有提供非常好的数据管理能力(站在用户角度)。 c/c++文件太麻烦了。基本读写，内容没有提供。**

**数据本质：对数据内容  存储的一套解决方案。 你给我字段或者要求，我直接给你结果就行的。**

**数据库总结：：：存储解决方案的。**



**mysql    ----        mysqld ---------------  磁盘。**

**数据库的水平是衡量一个程序员水平的重要指标。**



**08 见见mysql**

**mysql的配置文件：/etc/my.cnf。 里面就有mysql的数据存放的位置。**

**1.建立数据库本质，linux下的一个目录。**

**2.数据库建表本质：linux下创建一个文件即可。**

**3.数据库本质 其实也是文件，只不过这些文件并不由程序员直接操作，而是由数据库服务帮我们操作。**

**上面的操作是mysqld帮我们做的。 SQL语句帮我们做。**



**09 主流数据库**

**mysql: 百万级千万级的并发没有压力的。mysql的生态特别好的。**

**mysql: 关系型数据库。**



**10  服务器，数据库，表**

###  1.1服务器，数据库，表关系

![image-20260303154932924](picture/image-20260303154932924.png)

**mysql客户端， mysqld服务端   数据库。**

**数据库服务器：mysqld. 数据库管理系统程序。**



**11 mysql架构**

**逻辑结构：程序员眼中的数据库长什么样**。

**物理结构：数据最终在磁盘上到底怎么存。**



### 1.2MySQL架构

**mysqld: 网络结构。**

![image-20260303155124928](picture/image-20260303155124928.png)

```
             Client
                │
        ┌───────▼────────┐
        │ Connector连接器 │
        └───────┬────────┘
                │
        ┌───────▼────────┐
        │   SQL Interface │
        └───────┬────────┘
                │
        ┌───────▼────────┐
        │ Parser解析器    │
        └───────┬────────┘
                │
        ┌───────▼────────┐
        │ Optimizer优化器 │
        └───────┬────────┘
                │
        ┌───────▼────────┐
        │ Executor执行器 │
        └───────┬────────┘
                │
 ┌──────────────▼──────────────┐
 │      Storage Engine         │
 │ InnoDB MyISAM Memory ...    │
 └──────────────┬──────────────┘
                │
             Disk
```

**1.客户端 2.链接器  3.SQL交互界面 4.解析器 5. 优化器 6.执行器  7.存储引擎  8.disk 。**



**12SQL语句的分类**

### 1.3SQL语句分类

**DDL【data definition language】 数据定义语言，用来维护存储数据的结构**

​	**代表指令: create, drop, alter**

**DML【data manipulation language】 数据操纵语言，用来对数据进行操作**

​	**代表指令： insert，delete，update**

​	**DML中又单独分了一个DQL，数据查询语言，代表指令： select**

**DCL【Data Control Language】 数据控制语言，主要负责权限管理和事务**

​	**代表指令： grant，revoke，commit**

**1.创建表。 2.操作表的内容。 3.权限和事务的控制。**



**13存储引擎**

### 1.4存储引擎

**SQL的存储引擎**

**这是MySQL的一个核心特性——**插件式存储引擎架构（Pluggable Storage Engine Architecture）**。**

**99% 的业务场景使用的都是 InnoDB。**

**InnoDB = Innovative Database Engine**

**show engines**

![image-20260303160356806](picture/image-20260303160356806.png)

![image-20260623220158893](picture/image-20260623220158893.png)

**Client**
   **↓**
**SQL 接口**
   **↓**
**解析器 (Parser)**
   **↓**
**优化器 (Optimizer)**
   **↓**
**执行器 (Executor)**
   **↓**
**存储引擎 (Storage Engine)   ← 你问的核心**
   **↓**
**磁盘文件**



**14 mysql预备：注意下面是数据库的操作。**

 ## 2.库的操作



**15创建数据库**

### 2.1创建库和基本操作

```sql
create database db_name;  // 本质就是 /var/lib/mysql下的一个目录
drop   database db_name;  // 删除这个目录

create database if not exists db_name;  // 本质就是 /var/lib/mysql下的一个目录
drop   database if exists db_name;  // 删除这个目录
```

**数据库的编码集合校验集**

```
字符集：字符怎么存，怎么还原的
排序规则：字符怎么比
```

```mysql
show charset;   // 查看全部的字符集
show collation; // 查看全部的校验集
```

```mysql
show variables like 'character_set_database'; // 当前默认数据库使用的字符集。
show variables like 'collation_database';    // 当前默认数据库使用的排序规则，也就是校验规则。
```

**推荐的字符集和校验集**

```mysql
CHARACTER SET utf8mb4
COLLATE utf8mb4_0900_ai_ci;
```



**创建数据库**

```mysql
create database d1
create database d2 charset=utf8;
create database d3 character set utf8;
create database d4 character set utf8 collate uft8_general_ci;
```

**18**

```mysql
CREATE DATABASE database_name
CHARACTER SET utf8mb4
COLLATE utf8mb4_general_ci;  // 创建数据库
```

**19**

```mysql
drop database  db_name // 删除数据库
use db_name
select database();  //
show databases(); // 
alter database d3 character set gbk  collate gbk_chinese_ci;
show create database d3;
```

**20**

**数据库备份**



## mysql库操作总结

```mysql
show databases; // 查看数据库
create database if not exists d1 character set utf8 collate utf8_general_ci; // 创建数据库
show create database d1; // 查看创建爱数据库的指令
use d1; // 使用数据库
alter database d1 character set gbk collate gbk_chinese_ci; // 修改数据库
select database(); // 查看当前使用的数据
drop databse d1;
```

```mysql
mysqldump -u root -p d1 > d1.sql
mysql -u root -p d1 < d1.sql
```



## 3.表的操作

**创建表**

**数据库本质就是linux下面的一个文件夹**

**表本质就是文件夹下面的文件**

```mysql
create table users2
( id int, comment '序号'
name varchar(20) comment '名称', 
passwd char(32)  comment '密码', 
birthday date comment '生日' 
)character set utf8 collate utf8_general_ci engine InnoDB;
```

```mysql
show tables;
```

![image-20260303211038312](picture/image-20260303211038312.png)

**查看表**

```mysql
show tables;
```

```sql
desc users
```

![image-20260303211203204](picture/image-20260303211203204.png)

```mysql
show create table users \G;
```

**表的修改**

```mysql
alter table users2 rename to user; // 表名的修改
```

```mysql
alter table user add image_path varchar(128) comment '用户头像路径' after birthday; // 新增一列
```

```mysql
alter table user modify name varchar(60); // 修改属性
```

```mysql
alter table user drop passwd;
```

```mysql
alter table users change name xingming varchar(20);
```



**表的删除**

```mysql
drop table tb_name
```















