# sql笔记



## 2.库的操作

**2.1字符集和校验集**

**查看字符集：**

```mysql
show charset
```

**查看检验集:**

```mysql
show collation
```

**查看默认的字符集：**

```mysql
show  variables like 'character_set_database';
```

**查看默认的校验集:**

```mysql
show variables like 'collation_database';
```



**2.2创建和删除**

**创建数据库：**

```mysql
create database d1 character set utf8mb4 collate utf8mb4_general_ci;
```

**数据库最重要的就是字符集和校验集。**

**删除数据库：**

```mysql
drop database d1;
```



**2.3数据库的查看**

**查看数据库的个数：**

```mysql
show databases;
```

**查看如何创建数据库：**

```mysql
show create database d1;
```

**使用数据库：**

```mysql
use d1;
```



## 3.表的操作

**3.1创建表和删除表：**

**创建表：**

```mysql
create table users2 ( 
id int comment '序号', 
name varchar(20) comment '名称',  
passwd char(32)  comment '密码',  
birthday date comment '生日'  ) character set utf8mb4 collate utf8mb4_general_ci engine InnoDB;
```

**表的：字符集，校验集，存储引擎。**

**删除表：**

```mysql
drop table users2;
```



**3.2查看表：**

**表的逻辑结构：**

```mysql
desc users2;
```

**表的创建语句：**

```mysql
show create table users2 \G
```



**3.3表的性质修改：**

**修改表的名称：**

```mysql
alter table users2 rename to user
```

**增加一列属性：**

```mysql
alter table user add image_path varchar(30) comment '用户头像';
```

**删除一列属性：**

```mysql
alter table user drop id;
```

**修改属性：**

```mysql
alter table user modify name int;
```

```mysql
alter table user change name xingming varchar(30);
```

**总结：**

```mysql
alter table tb_name 
rename to  // 新名称
add        // 添加新的一行
drop       // 删除一行
modify     // 修改属性，表不变
change     // 修改名字和属性
```



































