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

**DDL:数据定义语言。**

**查看表的语句**

```mysql
desc tb_name;
show tables;
show create table tb_name \G
```



## 4数据类型

**整型数据类型。**

**1,2,3,4,8字节信息。**

| **类型**        | **存储空间** |              **有符号范围** |    **无符号范围** |
| --------------- | -----------: | --------------------------: | ----------------: |
| **`TINYINT`**   |   **1 字节** |               **-128～127** |        **0～255** |
| **`SMALLINT`**  |   **2 字节** |           **-32768～32767** |      **0～65535** |
| **`MEDIUMINT`** |   **3 字节** |       **-8388608～8388607** |   **0～16777215** |
| **`INT`**       |   **4 字节** | **-2147483648～2147483647** | **0～4294967295** |
| **`BIGINT`**    |   **8 字节** |             **-2⁶³～2⁶³-1** |      **0～2⁶⁴-1** |

**默认是有符号的：有正有负的。**

**mysql中：不合法的数据会直接拦截我们，不让我们做对应的操作。反过来：插入进去的数据都是合法的。**

**mysql中：一般而言，数据类型也是一种约束。**

**mysql中：变量名称 ：类型。**



**bit类型**

**默认一个比特位。最大64个比特位。**

**使用几个比特位进行数据的表示。一般是不可见的。**

```mysql
select hex(num) from t3;
```



**小数类型**

**float[(m, d)] [unsigned] : M指定显示长度，d指定小数位数，占用空间4个字节**

**默认会四舍五入的。但是也不能够超过范围的。**



**精确小数**

**decimal**



| 对比项               | FLOAT            | DOUBLE           | DECIMAL                  |
| -------------------- | ---------------- | ---------------- | ------------------------ |
| **存储空间**         | **固定 4 字节**  | **固定 8 字节**  | **根据 M、D 变化**       |
| **数值类型**         | **近似值**       | **近似值**       | **精确值**               |
| **有效精度**         | **约 6～7 位**   | **约 15～16 位** | **最高由 M 决定**        |
| **数值范围**         | **很大**         | **非常大**       | **由 M、D 决定**         |
| **是否存在浮点误差** | **存在**         | **存在**         | **通常不存在**           |
| **金额**             | **不适合**       | **不适合**       | **适合**                 |
| **坐标**             | **精度可能不足** | **适合**         | **通常没必要**           |
| **测量数据**         | **适合**         | **高精度时适合** | **需要精确十进制时使用** |
| **空间成本**         | **较低**         | **较高**         | **与精度有关**           |

```
FLOAT：
4 字节，约 6～7 位有效数字。
适合普通传感器数据和允许误差的测量值。

DOUBLE：
8 字节，约 15～16 位有效数字。
适合坐标、科学计算、高精度测量值。

DECIMAL(M,D)：
精确十进制定点数。
M 是总位数，D 是小数位数，整数位数是 M-D。
适合价格、工资、余额、税率和财务数据。
```



**字符类型**

**char固定长度字符串**

**char(L): 固定长度字符串，L是可以存储的长度，单位为字符，最大长度值可以为255**

**char的单位是：字符。就是一个符号。**



**varchar变长字符串**

**字符最长是：65535个字符信息。 用多少，给多少。注意给定的上限。**

**字符的上限和编码有关系的。**



**日期类型**

**date：日期。年月日，需要自己手动插入**

**datetime：时间日期。  年月日+时分秒。需要自己手动插入**

**timestamp:时间戳。 每操作一次，表自己更更新一次。**



**枚举和集合类型**

**enum('选项1' , '选项2'， '选项3'  )  多选一。  约束只能选项中的一个。也可以插入数字代表选项。 注意从左往右是从一开始的。**

**set('选项1' , '选项2'， '选项3'  )  多选多。  选项的1---n的二进制约束。0-2^n-1, 范围。**



**一个函数的使用。枚举里面的使用方法。**

**查找的时候，可以根据数字=多少进行查找。这是严格匹配的。**



**find_in_set集合**

**只能是查找一个元素在集合里面的。**

```mysql
 select * from t10 where find_in_set('登山', hobby) and find_in_set('羽毛球', hobby);
```



## 5约束

**表的约束：表中一定要有各种约束。通过约束让我们未来插入数据表的数据是复合预期的。**

**约束的本质就是通过技术手段，倒逼程序员，插入正确的数据。mysql视角凡是插入进来的数据都是复合数据约束的。**

**保证数据的完整性和可约束性。**



**5.1非空约束**

**null   not null**

**null表示什么都没有的，null不参与计算的。注意null和空白字符的区别的。**

**null：可以什么都没有的。**

**not null不能是空的。**



**5.2默认值**

**default: 设置了，用户的数据存在了，就用用户的，不存在就用自己的。**

**default:不冲突的，互相补充的。**

**mysql默认是null的。这是mysql的优化的。**



**5.3 描述列。**

**相当于语言的注释。comment '注释的信息'。**

**列描述：comment，没有实际含义，专门用来描述字段，会根据表创建语句保存，用来给程序员或DBA 来进行了解。**





**5.4 zerofill**

**零填充约束。**

**显示方面的约束**

**`ZEROFILL` 是 MySQL 早期用于数字格式化显示的修饰符，它会根据显示宽度在数字左侧补零，并自动添加 `UNSIGNED` 属性。**

**它不会改变数据的实际存储值和存储空间，只影响查询显示效果。**

**从 MySQL 8.0.17 开始已被官方弃用，实际开发中通常使用 `LPAD()` 或由应用程序完成补零格式化。**

**hex()  转换成16进制的。**















