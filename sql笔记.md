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

**UTF-8 Multi-Byte 4-Byte General Case-Insensitive Collation**

**Unicode Transformation Format - 8-bit**



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

**查看链接数**

```mysql
show processlist;
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

**创建表的时候，信息是一行的，变量名，属性，约束等等。  也有可能约束在最后：例如复合主键的约束。**

**查询的时候：信息就是一列的。**

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
show create table users2 \G;  // 也可以看到自增主键的下一个值的
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
add        // 添加新的一行，这是创建
drop       // 删除一行
modify     // 修改属性，列名称不变
change     // 修改名字和属性
```

**查看表的操作**

```mysql
desc tb_name;
show create table tb_name \G
show tb_name;
```



## 4.数据类型

**4.1整型**

| **类型**        | **存储空间** |              **有符号范围** |    **无符号范围** |
| --------------- | -----------: | --------------------------: | ----------------: |
| **`TINYINT`**   |   **1 字节** |               **-128～127** |        **0～255** |
| **`SMALLINT`**  |   **2 字节** |           **-32768～32767** |      **0～65535** |
| **`MEDIUMINT`** |   **3 字节** |       **-8388608～8388607** |   **0～16777215** |
| **`INT`**       |   **4 字节** | **-2147483648～2147483647** | **0～4294967295** |
| **`BIGINT`**    |   **8 字节** |             **-2⁶³～2⁶³-1** |      **0～2⁶⁴-1** |

**默认是有符号的。 可以指定为无符号的。**

**mysql：中数据类型也是一种约束的。**

**mysql中： 变量名 ： 类型**

```mysql
create table t11(
    t1 tinyint,
    t2 tinyint unsigned);
```



**bit[(M)] : 位字段类型。M表示每个值的位数，范围从1到64。如果M被忽略，默认为1。**



**4.2浮点型**

| 类型               | 占用空间               | 数值性质   | 大约有效精度                         |
| ------------------ | ---------------------- | ---------- | ------------------------------------ |
| **`FLOAT`**        | **4 字节**             | **近似值** | **约 6～7 位十进制有效数字**         |
| **`DOUBLE`**       | **8 字节**             | **近似值** | **约 15～16 位十进制有效数字**       |
| **`DECIMAL(M,D)`** | **根据 `M`、`D` 决定** | **精确值** | **由 `M` 决定，最多保存 `M` 位数字** |

**注意:浮点型会四舍五入的。**

**四舍五入也不能超过范围的。**



**4.3字符型**

**char和varchar类型。**

| 对比项           | `CHAR(M)`                        | `VARCHAR(M)`                       |
| ---------------- | -------------------------------- | ---------------------------------- |
| **长度性质**     | **固定长度**                     | **可变长度**                       |
| **`M` 的含义**   | **最多存储 M 个字符**            | **最多存储 M 个字符**              |
| **长度范围**     | **0～255 个字符**                | **理论上 0～65535 个字符**         |
| **存储空间**     | **按声明长度处理，不足时补空格** | **按实际内容长度存储**             |
| **额外长度信息** | **通常不需要记录实际长度**       | **额外使用 1 或 2 字节记录长度**   |
| **尾部空格**     | **存储时补空格，查询时通常删除** | **不自动补空格，尾部空格通常保留** |
| **适合的数据**   | **长度基本固定**                 | **长度变化较大**                   |

**char存储的是字符：就是我们实际看到的字符样子。0-255之间的**

**varchar存储的底层是： 65535个字节，所以存储的字符个数还需要和编码信息统一，而且底层还有存储的容量计数的。**



**4.4日期类型**

| 类型            | 标准格式                  | 占用空间   | 主要范围                   | 常见用途                         |
| --------------- | ------------------------- | ---------- | -------------------------- | -------------------------------- |
| **`YEAR`**      | **`YYYY`**                | **1 字节** | **1901～2155，以及 0000**  | **出生年份、生产年份**           |
| **`DATE`**      | **`YYYY-MM-DD`**          | **3 字节** | **1000-01-01～9999-12-31** | **生日、入职日期、订单日期**     |
| **`TIME`**      | **`HH:MM:SS`**            | **3 字节** | **-838:59:59～838:59:59**  | **时刻、持续时间、时间间隔**     |
| **`DATETIME`**  | **`YYYY-MM-DD HH:MM:SS`** | **5 字节** | **1000-01-01～9999-12-31** | **业务日期时间、预约时间**       |
| **`TIMESTAMP`** | **`YYYY-MM-DD HH:MM:SS`** | **4 字节** | **1970-01-01～2038-01-19** | **创建时间、更新时间、日志时间** |

**date, datetime。需要程序员自己插入，插入需要安装字符串的格式进程插入的。**

**timestamp。时间戳，每一次操作数据库，会形成一个时间戳的。**



**4.5枚举和集合**

**enum('选项1','选项2','选项3',...);**

​	**insert的时候，可以直接插入1, 2，3 ....就是对应的选项了。枚举只能选择一个的。**

**set('选项值1','选项值2','选项值3', ...);**

​	**insert的时候，可以直接插入数字， 0-2^n-1次方的数字。  注意从左往右的数字。**

**mysql的字段进行比较的时候，都是严格的匹配的**

![image-20260706162053160](picture/image-20260706162053160.png)

**find_in_set函数的使用。**

![image-20260706162209154](picture/image-20260706162209154.png)



## 5约束

**5.1 非空约束**

**null表示什么都没有的，null不参与计算的。注意null和空白字符的区别的。**

**not null 非空的。**

**注意：数据库默认字段基本都是字段为空，但是实际开发时，尽可能保证字段不为空，因为数据为空没办 法参与运算。**



**5.2 默认值**

**default: 设置了，用户的数据存在了，就用用户的，不存在就用自己的。**

**default 和 not null不冲突的。 **

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



**5.5 主键约束**

**主键：primary key用来唯一的约束该字段里面的数据，不能重复，不能为空，一张表中最多只能有一个**

**主键；主键所在的列通常是整数类型。**

**主键约束默认就是 非空的**

```mysql
update t17 set name = '刘表' where id = 2;  //  主键存在方便更新。
alter table t17 drop primary key;           //  因为主键一张表一个，不要告诉我哪一个列的。
alter table t17 add primary key(id);         // 注意建表之前就使用 主键。
delete from t17 where name = '刘备';
```



**复合主键**

```mysql
mysql> create table t18(
    -> id int unsigned,
    -> coures char(10) comment '课程',
    -> score tinyint unsigned default 60 comment '成绩',
    -> primary key(id, coures)  // 复合主键，最后指定就行了。
    -> );
```

**复合主键的语法是：在最后面进行指示。约束的条件只需要有一个不一样就行了的。**



**5.6自增长**

**auto_increment：当对应的字段，不给值，会自动的被系统触发，系统会从当前字段中已经有的最大值 +1操作，得到一个新的不同的值。**

**通常和主键搭配使用，作为逻辑主键。**

**自增长的特点: 任何一个字段要做自增长，前提是本身是一个索引（key一栏有值）** 

**自增长字段必须是整数** 

**一张表最多只能有一个自增长**



**设定起始值的**

```mysql
create table t20( 
    id int primary key auto_increment, 
    name varchar(20) not null 
    )auto_increment = 55;
```



**5.7唯一键**

| 对比项                      | 主键约束 `PRIMARY KEY`           | 唯一键约束 `UNIQUE`                |
| --------------------------- | -------------------------------- | ---------------------------------- |
| **主要作用**                | **唯一标识表中的一条记录**       | **保证某列或某组列的数据不重复**   |
| **是否允许重复**            | **不允许**                       | **不允许**                         |
| **是否允许 `NULL`**         | **不允许**                       | **允许 `NULL`**                    |
| **一张表可以有几个**        | **只能有一个主键**               | **可以有多个唯一键**               |
| **是否自动具有 `NOT NULL`** | **是**                           | **否**                             |
| **常见用途**                | **用户编号、订单编号、商品编号** | **手机号、邮箱、身份证号、用户名** |
| **InnoDB 中的特殊作用**     | **默认作为聚簇索引**             | **一般作为唯一二级索引**           |



**5.8 外键**

**外键写自己，引用写父表；先建父表，再建子表；先删子表，再删父表。**

```mysql
mysql> desc class;
+-------+-------------+------+-----+---------+-------+
| Field | Type        | Null | Key | Default | Extra |
+-------+-------------+------+-----+---------+-------+
| id    | int(11)     | NO   | PRI | NULL    |       |
| name  | varchar(32) | NO   |     | NULL    |       |
+-------+-------------+------+-----+---------+-------+
2 rows in set (0.00 sec)

mysql> 
mysql> 
mysql> 
mysql> 
mysql> create table stu(
    -> id int unsigned primary key,
    -> name varchar(20) not null,
    -> telephone varchar(32) unique key,
    -> class_id int ,
    -> foreign key(class_id) references class(id)
    -> );
Query OK, 0 rows affected (0.02 sec)

mysql> 
```

```
FOREIGN KEY        外键
(class_id)         本表的字段
REFERENCES         引用
class(id)          class 表中的 id 字段
```

**约束总结：**

**1. null  not null**

**2. default**

**3. commet**

**4.zerofill**

**5. primary key**

**6. auto_increment**

**7. unique_key**

**8. foreign key     references   **

```
FOREIGN KEY        外键
(class_id)         本表的字段
REFERENCES         引用
class(id)          class 表中的 id 字段
```









## 6查询

**CURD**

**6.1 insert**

```mysql
insert into t22(id, sn, name, qq) values(2, 1, '张三', '2225'); // 全部指定列名
insert into t22 values(2, 1, '张三', '2225'); // 全部不指定列名，默认全插入
insert into t22(id, sn, name, qq) values(12, 126, '曹操', '25'),(14, 13, '孙权' ,'wee'); // 多行插入，注意括号

```

**查看自增约束的数字**

```mysql
show create tb_name \G
```

**自增约束可以不指定，会使用默认的下一个值。**



**更新**

 ```
 INSERT INTO 表名(字段1, 字段2, ...)
 VALUES(值1, 值2, ...)
 ON DUPLICATE KEY UPDATE
     字段1 = 新值,
     字段2 = 新值;
 ```

```
没有主键/唯一键冲突：直接 INSERT
发生主键/唯一键冲突：DELETE 旧记录，再 INSERT 新记录
```

```
UPDATE：修改原记录
ON DUPLICATE KEY UPDATE：插入失败则修改原记录
REPLACE：插入失败则删除原记录，再重新插入
```



**6.2 select**

**select**

```mysql
select * from exam_result;  // 取出整个表的结构
select name, chinese from exam_result;   // 取出指定列的数据
select name as 姓名, chinese as 语文, math as 数学,  english as 英语 from exam_result; // 取出指定列，然后指定别名  as可以省略的
select distinct math from exam_result;    // math 去重
select distinct math, name from exam_result;  // math + name 去重
select distinct math + 2, name from exam_result;   // 可以进行计算的取出的数据。
```

```mysql
SELECT * FROM tb_name;
1.先确定从哪张表读取数据；
2.再决定查询结果中显示哪些字段。
```



**where子句**

```mysql
语文成绩在 [80, 90] 分的同学及语文成绩
select * from employee where salary >= 10000 and salary <= 12000;
select * from employee where salary between 10000 and 12000;   // between and 是闭区间的
```

```mysql
数学成绩是 58 或者 59 或者 98 或者 99 分的同学及数学成绩
select * from employee where age=25 or age=43 or age=35 or age=36;
select * from employee where age in(25,43,35,36);             // in 可以进行列举的
```

```mysql
 姓孙的同学 及 孙某同学
select * from employee where name like '孙%';
select * from employee where name not like '孙%';
select * from employee where name like '孙_';
select * from employee where name not like '孙_'; // %任意字符 _任意一个字符 。 注意区别
```

```mysql
语文成绩好于英语成绩的同学
select name, chinese, english from exam_result where chinese > english;
```

```mysql
 总分在 200 分以下的同学
 select name, chinese+english+math 总分 from exam_result where chinese + math + english < 200;
```

```mysql
 select name, chinese+english+math 总分 from exam_result where chinese + math + english < 200;
 3                                      1                2
 1.先找到表
 2.筛选的条件
 3.展示
```

```
1. FROM：确定从哪张表中读取数据。
2. WHERE：根据条件对表中的行进行判断和筛选。
3. SELECT：选择需要展示的字段，形成最终查询结果。
```

**nulll的查询 is null, is not null**



**order by 排序**

```mysql
安装年龄排序
select * from employee order by age asc;
select * from employee order by age desc;
```

```mysql
// **前面的数据一样的话，才会按照后面的顺序进行排序。**
select * from employee order by status asc, salary asc;
```

```mysql
select name, chinese+math+english total from exam_result order by total desc;
```

**这里为什么能够使用别名呢？ 1.首先拿出 2.然后展示出来  3.然后按照顺序展示的。**

```
1. FROM exam_result
   找到数据表
2. WHERE name LIKE '孙%' OR name LIKE '曹%'
   筛选姓孙或姓曹的学生
3. SELECT name, math
   只展示姓名和数学成绩
4. ORDER BY math DESC
   按数学成绩从高到低排序
```



**limit  分页查询**

```mysql
// 第一到第五一个
select * from exam_result limit 5; // 表开始，连续读取五行

// 第二到后面五个
select * from exam_result limit 2, 5; // 从二开始，连续读取五行
// 注意开始位置，下标默认是从零开始的

select * from exam_result limit 3 offset 2; // offset表示起始位置，前面的就是步长
```



**update 更新**

```mysql
update employee set email='lichermionex@gmail.com' where  name='高峰';
update employee gender='女', age=46 where id = 14;
update employee set salary = salary + 300 order by salary limit  3; // 先筛选出来，然后在更新 注意执行的顺序
update employee set salary = salary * 2;  // 没有条件，就是整个表进行更新的。
```



**delete 删除**

```mysql
delete from employee where id = 1; // 删除只需要指定一行的一个信息就行了
delete from employee order by salary limit 1; // 先筛选出来，然后删除的

delete from stu; // 删除这个表，注意
```



**案例：删除表中的的重复复记录，重复的数据只能有一份**

```mysql
 create table no_duplicate_table like duplicate_table; // 创建一样的表
 insert into no_duplicate_table(id,name) select distinct * from duplicate_table; // 插入，全列插入可以省略的
 insert into no_duplicate_table select distinct * from duplicate_table;
 
 alter table duplicate_table rename to old_duplicate_table // 备份 
 alter table no_duplicate_table rename to duplicate_table // 修改
```

**创建一张格式类似的表，然后把旧表筛选的结果，插入到新表，然后改名的**



**聚合函数**

```mysql
select count(*) from employee;
select count(bonus) from employee;
select count(id) from employee;
select count(gender) from employee;
select count(distinct gender) from employee;
```

```mysql
select sum(salary) from employee;
select sum(salary)/count(*) from employee;
select count(salary) from employee where salary < 15000
```

```mysql
select count(salary) from employee where salary < 15000;
select avg(salary) from employee;
```

```mysql
select max(salary) from employee;
select min(salary) from employee;
```



**group by**

```mysql
select department_id, count(*) as 部门人数 from employee group by department_id;
3.展示分组，分组的统计	  				 1.先拿数据     2.分组了		
```

```mysql
select gender, count(gender) from employee group by gender;
3.展示分组			         1.拿数据       2.分组
```

```mysql
select department_id, avg(salary) from employee group by department_id;
3.展示分组，每一组的信息             1.拿数据      2.分组
```

```mysql
select department_id, max(salary), min(salary) from employee group by department_id;
1.按照部门分组，分成了对个表了
2.然后统计每张表的信息
3.展示
```

```mysql
select department_id, sum(salary) from employee group by deparetment_id;
```

**group by就是按照信息进行分组的。**



**1部门  2性别**

```mysql
select department_id, gender, count(*)  from employee group by department_id, gender;
3.展示。3.1部门一样 11 12 21 22           1.拿数据了             2.按照部门分组，然后就是性别了
```

**having子句进行判断的**

```mysql
select department_id, count(*) from employee group by department_id having count(*) > 2;
```

```mysql
select department_id, sum(salary) as sum_sal from employee group by department_id having sum(salary) > 25000;
select department_id, sum(salary) as sum_sal from employee group by department_id having sum_sal > 25000;
```

**1. insert   replace**

**2. select   where   having**

**3. is null, is not null**





## 7函数

**日期，时间，时间戳**

```mysql
select current_date();  // 日期
select current_time();  // 时间
select current_timestamp();  // 时间戳，但是显示的是上面的两个
```

**日期截取函数**

```mysql
select date('2000-2-10 1:1:1');
select date(now());

// 虽然都有可以插入，但是不合规的
select date(current_date());
select date(current_time());
select date(current_timestamp());
```

**日期加减**

```mysql
select date_add('2050-1-1', interval 10 day);
select date_add('2050-1-1', interval 50 day);
select date_add(now, interval 10 day);
select date_add(now(), interval 10 minute);
select date_add(now(), interval 10 second);
```

**判断日期的差距**

```mysql
select datediff(now(), '2000-2-10');
```



**7.2 字符串函数**

**charset：字符串函数**

```mysql
select charset('abc');
select charset(1233);
select charset(salary) from employee;
select charset(name) from employee;
```

**concat：拼接字符函数**

```mysql
select concat('a', 'c', 'fffffffffffffffffff') string;
select concat('a', 'c', 'fffffffffffffffffff', 123, 3.3123) string; // 数字也可以拼接的
```

**instr：子字符串函数的**

```mysql
select instr('aaaaaaaaaaabd', 'a');
select instr('aaaaaaaaaaabd', 'abd');
// 注意失败返回零的
```

**ucase, lcase：大小写转换**

```mysql
select ucase('lichermionex');
select lcase('SFDFFFCDFFASFSAFSDSCDFS3434545...;;;');
```

**left：右边字符串**

```mysql
select left('lichermione', 3);  // 返回的是字符串
select right('lichermionezzz', 3); // 
```

**length：字符串长度函数**

```mysql
select length('lichermionex');
```

**replace：查找替换函数**



**strcmp：字符串比较函数**



**substring：求子串**



**ltrim：前后空格字符串去处函数**



**获取表格某列的charset**

```mysql
select charset(id) from employee; // 里面填表的字段。 
select charset('abc'); // 查询数据就行了
// 1.使用的场景，乱码的时候查编码信息的。
```

**表格字符串的拼接**

```mysql
select concat(name,'的薪水:', salary) from employee;  // 表的字段信息和需要字符拼接
// 1.查询的信息不想用表格显示的时候，使用的
```

**字符串的字节长度**

```mysql
mysql> select length(mail) from employee;
select name, length(name) from employee;  // length 字节，字节数。 一个字符可能占多个字节
```

**字符串替换**

```mysql
select city, replace(city, '上海', 'shanghai'), from employee;  // 查询的信息进行替换，不会改变原来的信息的
```

**子字符串的截取**

```mysql
select substr(hire_date,1,4) from employee;  // 字符串是从1开始的。
select substr(hire_date,6) from employee;    // 省略就是到末尾的
```

**字符串前后的空格**

```mysql
select ltrim('        xxxxxxx                  ');
select rtrim('        xxxxxxx                  ');
select trim('         xxxxxxx                  ');
```

**7.3 数学函数**

```mysql
// 绝对值函数
select abs(-1110);
select abs(11110);

// 十进制转换二进制,16进制的
select bin(16); // 只能是整数的
select hex(16); //

// 任意进制的转换
select conv(10, 10 , 2);
select conv(10, 10 , 16);

// 取整函数
select ceiling(12.00000000000000001);
select floor(12.00000000000000001);
select ceiling(-12.00000000000000001);
select floor(-12.00000000000000001);
// 想象成数轴就行了的。  向上就是右边，向下就是左边的。

// 小数位数函数
select format(3.141567, 2);
select format(3.141567, 21);

// 模运算
select mod(10, 3);

 // 随机数
 select rand();
```

**7.4 其它函数**

```mysql
用户函数
select user();
摘要的
select md5('lichermionex');
当前数据
select database();
加密函数
select password('root');

select ifnull('aaa', 'bbbb');
select ifnull(null, 'bbbb');
```



## 8. 复合查询

**8.1 基本查询回顾**

**查询工资高于500或岗位为MANAGER的雇员，同时还要满足他们的姓名首字母为大写的J**

```mysql
select * from EMP where (sal > 500 or  job='MANAGER') and ename like 'J%';
// like用来模糊匹配的，通配匹配的
```

**按照部门号升序而雇员的工资降序排序**

```mysql
select deptno, sal from EMP order by deptno asc, sal desc;
// 排序，先一样的，然后在按照后面的进行排序的
```

**使用年薪进行降序排序**

```mysql
select ename, sal*12 + ifnull(comm, 0) as 年薪  from EMP  order by 年薪 desc;
// null不参与计算的。
```

**显示工资最高的员工的名字和工作岗位**

```mysql
// 子查询
select max(sal) from EMPl;
select ename, job , sal, sal from EMP where sal = (select max(sal) from EMP);
2.名字，工作岗位                              1.最高工资

select ename, job , sal from EMP order by sal desc limit 1;
// 先找到工资最高的员工
```

**显示工资高于平均工资的员工信息**

```mysql
// 子查询
select ename ,sal from EMP where sal > (select avg(sal) from EMP);
// 2.查查询                 	   2.子查询的信息
```

**显示每个部门的平均工资和最高工资**

```mysql
select deptno, avg(sal), max(sal) from EMP group by deptno;
// 2.每个部门， 部门的平均工资，最高工资       1.每个部门
```

**显示平均工资低于2200的部门号和它的平均工资**

```mysql
select deptno, avg(sal) from EMP group by deptno having avg(sal) < 2200;
2.每个组的平均工资                 1.分组           3.平均工资低于2200
```

**显示每种岗位的雇员总数，平均工资**

```mysql
select deptno, count(*), avg(sal) from EMP group by deptno;
```



**8.2 多表查询**

**显示雇员名、雇员工资以及所在部门的名字因为上面的数据来自EMP和DEPT表，因此要联合查询**

```
+-------+--------+-----------+------+------------+---------+---------+--------+
| empno | ename  | job       | mgr  | hiredate   | sal     | comm    | deptno |
+-------+--------+-----------+------+------------+---------+---------+--------+
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |
```

```
+--------+------------+----------+
| deptno | dname      | loc      |
+--------+------------+----------+
|     10 | ACCOUNTING | NEW YORK |
|     20 | RESEARCH   | DALLAS   |
|     30 | SALES      | CHICAGO  |
|     40 | OPERATIONS | BOSTON   |
+--------+------------+----------+
```

```
+-------+--------+-----------+------+------------+---------+---------+--------+--------+------------+----------+
| empno | ename  | job       | mgr  | hiredate   | sal     | comm    | deptno | deptno | dname      | loc      |
+-------+--------+-----------+------+------------+---------+---------+--------+--------+------------+----------+
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |     10 | ACCOUNTING | NEW YORK |
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |     20 | RESEARCH   | DALLAS   |
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |     30 | SALES      | CHICAGO  |
|  7369 | SMITH  | CLERK     | 7902 | 1980-12-17 |  800.00 |    NULL |     20 |     40 | OPERATIONS | BOSTON   |
```

```
select  * from EMP, DEPT; // 第一张表的每一个数据和第二张表的数据进行穷举的
select  * from EMP, DEPT where EMP.deptno= DEPT.deptno; // 筛选掉无意义的数据
select ename, sal, dname from EMP, DEPT where EMP.deptno= DEPT.deptno; // 完成任务的
显示雇员名、雇员工资以及所在部门的名字因为上面的数据来自EMP和DEPT表，因此要联合查询
```

**显示部门号为10的部门名，员工名和工资**

```mysql
select EMP.deptno, ename, sal, dname from EMP, DEPT where EMP.deptno= DEPT.deptno and EMP.deptno=10;
```

**显示各个员工的姓名，工资，及工资级别**

```mysql
select ename, sal, grade from EMP, SALGRADE where EMP.sal between losal and hisal;
```



**8.3 自连接**

```mysql
+-------+--------+-----------+------+------------+---------+---------+--------+
| empno | ename  | job       | mgr  | hiredate   | sal     | comm    | deptno |
+-------+--------+-----------+------+------------+---------+---------+--------+
         
```

```mysql
select * from SALGRADE as t1, SALGRADE as t2; // 注意需要重命名的
```

```mysql
显示员工FORD的上级领导的编号和姓名（mgr是员工领导的编号--empno）
select ename, empno from EMP  where empno=(select mgr from EMP where ename='FORD');

select e2.ename, e2.empno from EMP e1, EMP e2 where e1.ename='FORD' and e1.mgr = e2.empno;
```



**8.4 子查询**

**单行子查询**

**显示SMITH同一部门的员工**

```mysql
select * from EMP where deptno = (select deptno from EMP where ename='SMITH');
2.查询                            1.子查询，SMITH的部门所在
```

 **多行子查询**

**in关键字；查询和10号部门的工作岗位相同的雇员的名字，岗位，工资，部门号，但是不包含10自 己的**

```mysql
// 1.子查询多行
mysql> select distinct job from EMP where deptno=10;
+-----------+
| job       |
+-----------+
| MANAGER   |
| PRESIDENT |
| CLERK     |
+-----------+
// 2.查询
mysql> select ename, job, sal, deptno from EMP where job  in (select job from EMP where deptno=10);
+--------+-----------+---------+--------+
| ename  | job       | sal     | deptno |
+--------+-----------+---------+--------+
| SMITH  | CLERK     |  800.00 |     20 |
| JONES  | MANAGER   | 2975.00 |     20 |
| BLAKE  | MANAGER   | 2850.00 |     30 |
| CLARK  | MANAGER   | 2450.00 |     10 |
| KING   | PRESIDENT | 5000.00 |     10 |
| ADAMS  | CLERK     | 1100.00 |     20 |
| JAMES  | CLERK     |  950.00 |     30 |
| MILLER | CLERK     | 1300.00 |     10 |
+--------+-----------+---------+--------+
// 3去除部门号
mysql> select ename, job, sal, deptno from EMP where job  in (select job from EMP where deptno=10) and deptno != 10;
+-------+---------+---------+--------+
| ename | job     | sal     | deptno |
+-------+---------+---------+--------+
| SMITH | CLERK   |  800.00 |     20 |
| JONES | MANAGER | 2975.00 |     20 |
| BLAKE | MANAGER | 2850.00 |     30 |
| ADAMS | CLERK   | 1100.00 |     20 |
| JAMES | CLERK   |  950.00 |     30 |
+-------+---------+---------+--------+
```

```mysql
select ename, job, sal, deptno from EMP where job  in (select job from EMP where deptno=10) and deptno != 10;
select ename, job, sal, deptno from EMP where job  in (select job from EMP where deptno=10) and deptno <> 10;
```

**all关键字；显示工资比部门30的所有员工的工资高的员工的姓名、工资和部门号**

```mysql
mysql> select * from EMP where sal > (select max(sal) from EMP where deptno=30);
	   2.查询					      1.子查询				 
mysql> select * from EMP where sal > all(select sal from EMP where deptno=30);
       2.查询                         1.子查询
```

**any关键字；显示工资比部门30的任意员工的工资高的员工的姓名、工资和部门号（包含自己部门 的员工）**

```mysql
mysql> select * from EMP where sal > any(select distinct sal from EMP where deptno=30);
```

 **多列子查询**

**案例：查询和SMITH的部门和岗位完全相同的所有雇员，不含SMITH本人**

```mysql
select * from EMP  where (deptno, job) = (select deptno, job from EMP where ename='SMITH') and ename <> 'SMITH';
select * from EMP  where (deptno, job) in (select deptno, job from EMP where ename='SMITH') and ename <> 'SMITH';
```

**显示每个高于自己部门平均工资的员工的姓名、部门、工资、平均工资**

```mysql
select * from EMP, (select deptno, avg(sal) myavg from EMP group by deptno) tmp where EMP.deptno= tmp.deptno and sal > myavg;
```

**查找每个部门工资最高的人的姓名、工资、部门、最高工资**

```mysql
select * from EMP t1, ((select deptno, max(sal) mymax from EMP group by deptno) as t2) where t1.deptno=t2.deptno and t1.sal = t2.mymax;
```

**显示每个部门的信息（部门名，编号，地址）和人员数量**

```mysql
select DEPT.dname, DEPT.deptno, DEPT.loc,count(*) '部门人数' from EMP,
DEPT
where EMP.deptno=DEPT.deptno
group by DEPT.deptno,DEPT.dname,DEPT.loc
```

```mysql
-- 1. 对EMP表进行人员统计
select count(*), deptno from EMP group by deptno;
-- 2. 将上面的表看作临时表
select DEPT.deptno, dname, mycnt, loc from DEPT,
(select count(*) mycnt, deptno from EMP group by deptno) tmp
where DEPT.deptno=tmp.deptno
```

**案例：将工资大于2500或职位是MANAGER的人找出来**

```mysql
select * from EMP where sal > 2500 union select * from EMP where job='MANAGER';
```

**案例：将工资大于25000或职位是MANAGER的人找出来**

```mysql
select * from EMP where sal > 2500 union all select * from EMP where job='MANAGER';
```



## 9.表的内连和外连

**内连接**

**案例：显示SMITH的名字和部门名称**

```mysql
select * from DEPT, EMP where DEPT.deptno = EMP.deptno and ename='SMITH'; 
select ename, dname from EMP inner join DEPT on EMP.deptno=DEPT.deptno and ename='SMITH';
select ename, dname from EMP inner join DEPT on EMP.deptno=DEPT.deptno where ename='SMITH';
// 1.select * from tb1 inner join tb2 on ... where ...
//ON：写表与表之间的连接条件；WHERE：写对结果的筛选条件。
```

```mysql
select ename, dname                 -- 显示什么
from EMP                            -- 从哪张主表开始
inner join DEPT                     -- 连接哪张表
on EMP.deptno = DEPT.deptno         -- 两表根据什么匹配
where ename = 'SMITH';              -- 最后筛选谁
```

**左外连接**

**对stu表和exam表联合查询，把所有的成绩都显示出来，即使这个成绩没有学生与它对应，也要 显示出来**

```mysql
select * from stu right join exam on stu.id=exam.id;
```

**列出部门名称和这些部门的员工信息，同时列出没有员工的部门**

```mysql
方法一：
select d.dname, e.* from dept d left join emp e on d.deptno=e.deptno;
方法二：
select d.dname, e.* from emp e right join dept d on d.deptno=e.deptno;
```



## 10索引

**B+树的原理。**



## 11事务

**MySQL 的事务（Transaction），可以理解为：把多条 SQL 操作看成一个不可分割的整体：要么全部成功，要么全部失败。**

**1.事务的基本操作**

```mysql
start transaction;
commit;
rollback;
savepoint;
```

```mysql
start transaction;  begin; // 开启事务后，后续的增删改操作暂时不会被永久确认。
commit;                    // 当前事务中的所有修改都确认生效，并永久保存。
rollback;                  // 撤销当前事务中尚未提交的所有修改。
// 正确就提交，错误就回滚
```

**2. MySQL 默认自动提交**

**autocommit = 1**

```mysql
update EMP
set sal = 900
where empno = 7369;
```

相当于

```mysql
start transaction;
update EMP
set sal = 900
where empno = 7369;
commit;
```

**3. 显式开启事务后，自动提交暂时失效**

**4. 事务的四大特性：ACID**

**1. 原子性 Atomicity:  事务中的操作要么全部成功，要么全部失败。**

**2.一致性 Consistency：事务执行前后，数据库必须保持正确、合法的状态。**

**3. 隔离性 Isolation：多个事务同时执行时，彼此之间尽量互不干扰。**

**4.持久性 Durability：事务一旦提交，修改结果就应该被永久保存。**



**5. 事务的隔离级别**

```
READ UNCOMMITTED
READ COMMITTED
REPEATABLE READ
SERIALIZABLE
```

**1. READ UNCOMMITTED：读未提交, 一个事务可以读取另一个事务尚未提交的数据。**

​	**隔离级别最低，并发性能高，但安全性较差。**

**2. READ COMMITTED：读已提交, 只能读取其他事务已经提交的数据。**

​	**同一事务内两次读取结果不同。**

**3. REPEATABLE READ：可重复读, 同一个事务中，多次读取同一数据，结果通常保持一致。**

​	**保证当前事务中的读取视图相对稳定。**

**4.SERIALIZABLE：串行化 多个事务近似按照一个接一个的方式执行，可以避免更多并发问题，但并发性能最低，锁竞争也更明显。**



**MVCC 同一行数据在逻辑上可以存在多个历史版本，不同事务根据自己的可见性规则，读取适合自己的版本。**

```mysql
id = 1 name = 张三 balance = 1000
进程A
start transaction;
update account set balance = 500 where id = 1;

进程B
select balance from account where id = 1;
```

**1.事务B一直等到事务A完成任务。啰嗦。   影响并发性能**

**2.事务B直接读取事务A尚未提交的数据。  产生脏读**

**MVCC:  1.事务 A 修改新版本：500.  2. 事务 B 仍然读取旧版本：1000 **

**MVCC核心：数据版本链 + Read View 可见性判断**



**DB_TRX_ID：Database Transaction Identifier 记录最后一次修改这一行的事务 ID。**

**DB_ROLL_PTR**：**Database Rollback Pointer 回滚指针, 它指向这条记录的上一个历史版本。**

**DB_ROW_ID 如果表中没有合适的主键或唯一非空索引，InnoDB 可能生成隐藏的行 ID。**

**DB_TRX_ID：版本由哪个事务产生**
**DB_ROLL_PTR：上一个版本在哪里**



**Undo Log 和版本链**

**假设原始数据：1000   事务 101 修改为：800    事务 102 又修改为：500**

```
当前记录
balance = 500
trx_id = 102
      ↓
Undo Log
balance = 800
trx_id = 101
      ↓
Undo Log
balance = 1000
trx_id = 90
```

**当某个事务不能读取最新版本时，InnoDB 会沿着 `DB_ROLL_PTR` 向前查找，直到找到对该事务可见的版本。**

**Read View 是什么 当前事务应该看到哪个版本？**

**Read View 会记录当时哪些事务：**

```
已经提交
正在运行
还没有开始
```

**Read View 中可以重点理解以下信息：**

```
creator_trx_id：创建 Read View 的事务 ID
m_ids：创建时仍然活跃、未提交的事务 ID 集合
min_trx_id：活跃事务中的最小事务 ID
max_trx_id：下一个将要分配的事务 ID
```

**Read View 记录了当前有哪些事务还没有提交，用它判断某个数据版本是否可见。**

**MVCC 是 InnoDB 通过 Undo Log 保存数据历史版本，再利用 Read View 判断版本可见性，使普通读操作可以读取合适的数据版本，从而减少读写冲突、提高并发性能。**







































