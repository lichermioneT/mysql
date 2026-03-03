# MySql

## 1. 数据库基础

###  1.1服务器，数据库，表关系

![image-20260303154932924](picture/image-20260303154932924.png)



### 1.2MySQL架构

![image-20260303155124928](picture/image-20260303155124928.png)



### 1.3SQL语句分类

**DDL【data definition language】 数据定义语言，用来维护存储数据的结构**

​	**代表指令: create, drop, alter**

**DML【data manipulation language】 数据操纵语言，用来对数据进行操作**

​	**代表指令： insert，delete，update**

​	**DML中又单独分了一个DQL，数据查询语言，代表指令： select**

**DCL【Data Control Language】 数据控制语言，主要负责权限管理和事务**

​	**代表指令： grant，revoke，commit**



### 1.4存储引擎

**SQL的存储引擎**

**这是MySQL的一个核心特性——**插件式存储引擎架构（Pluggable Storage Engine Architecture）**。**

![image-20260303160356806](picture/image-20260303160356806.png)



Client
   ↓
SQL 接口
   ↓
解析器 (Parser)
   ↓
优化器 (Optimizer)
   ↓
执行器 (Executor)
   ↓
存储引擎 (Storage Engine)   ← 你问的核心
   ↓
磁盘文件



| 能力         | 是否由存储引擎决定 |
| ------------ | ------------------ |
| 数据如何存储 | ✅                  |
| 是否支持事务 | ✅                  |
| 是否支持行锁 | ✅                  |
| 索引实现方式 | ✅                  |
| 崩溃恢复机制 | ✅                  |
| 外键支持     | ✅                  |



 ## 2.库的操作

### 2.1创建库和基本操作

**创建数据库：指定编码集和校验集合**

```sql
create database if not exists review character set utf8mb4 collate utf8mb4_general_ci;
```

**查看数据库的编码集**

```sql
show variables like 'character_set_database';
```

**查看数据库的校验集**

```sql
show variables like 'collation_database';
```

**查看系统的字符集**

```sql
show charset;
```

**查看系统的校验集**

```sql
show collation;
```

**列出数据库**

```sql
show databases;
```

**列出数据库的表**

```sql
show tables;
```

**显示如何创建的数据库**

​	**SQL语句一般会被优化的**

```sql
show create database database_name
```



### 2.2数据库的修改

```sql
ALTER DATABASE 数据库名
CHARACTER SET = 字符集
COLLATE = 排序规则;
```

**`CHARACTER SET` 和 `CHARSET` 完全等价。**



## 3.表的操作

**创建的表会继承，数据库的字符集和校验集。**

```sql
CREATE TABLE IF NOT EXISTS users (
    id INT,
    name CHAR(32) COMMENT '用户名',
    password CHAR(32) COMMENT '密码是32位的md5值',
    birthday DATE COMMENT '用户的生日'
);
```



**数据库本质就是linux下面的一个文件夹**

**表本质就是文件夹下面的文件**

![image-20260303211038312](picture/image-20260303211038312.png)



```sql
desc users
```

![image-20260303211203204](picture/image-20260303211203204.png)





















