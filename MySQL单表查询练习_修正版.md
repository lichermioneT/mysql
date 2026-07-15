# MySQL 单表查询练习（修正版）

> 练习表：`employee`

---

## 一、基础查询

### 1. 查询所有员工信息

```sql
SELECT *
FROM employee;
```

### 2. 只查询姓名、部门和工资

```sql
SELECT name, department, salary
FROM employee;
```

### 3. 给查询结果设置别名

使用 `AS`：

```sql
SELECT
    name AS 姓名,
    department AS 部门,
    salary AS 工资
FROM employee;
```

省略 `AS`：

```sql
SELECT
    name 姓名,
    department 部门,
    salary 工资
FROM employee;
```

### 4. 查询公司有哪些部门，要求去重

```sql
SELECT DISTINCT department
FROM employee;
```

**基本查询：想要那一列select就行。**

---

## 二、WHERE 条件查询

### 1. 查询工资大于 10000 元的员工

```sql
SELECT *
FROM employee
WHERE salary > 10000;
```

### 2. 查询工资在 8000～15000 元之间的员工

```sql
SELECT *
FROM employee
WHERE salary BETWEEN 8000 AND 15000;
```

等价写法：

```sql
SELECT *
FROM employee
WHERE salary >= 8000
  AND salary <= 15000;
```

### 3. 查询年龄小于 30 岁的员工

```sql
SELECT *
FROM employee
WHERE age < 30;
```

### 4. 查询技术部的所有员工

```sql
SELECT *
FROM employee
WHERE department = '技术部';
```

### 5. 查询技术部并且工资大于 10000 元的员工

```sql
SELECT *
FROM employee
WHERE department = '技术部'
  AND salary > 10000;
```

### 6. 查询技术部或者测试部的员工

```sql
SELECT *
FROM employee
WHERE department IN ('技术部', '测试部');
```

等价写法：

```sql
SELECT *
FROM employee
WHERE department = '技术部'
   OR department = '测试部';
```

### 7. 查询不属于技术部的员工

```sql
SELECT *
FROM employee
WHERE department <> '技术部';
```

也可以写成：

```sql
SELECT *
FROM employee
WHERE department != '技术部';
```

**<> != 等价**

### 8. 查询年龄为 25、28、30 岁的员工

```sql
SELECT *
FROM employee
WHERE age IN (25, 28, 30);
```

### 9. 查询奖金为空的员工

```sql
SELECT *
FROM employee
WHERE bonus IS NULL;
```

### 10. 查询奖金不为空的员工

```sql
SELECT *
FROM employee
WHERE bonus IS NOT NULL;
```

### 11. 查询已经离职的员工

```sql
SELECT *
FROM employee
WHERE status = 0;
```

### 12. 查询当前在职的员工

```sql
SELECT *
FROM employee
WHERE status = 1;
```

### 13. 查询在北京工作并且工资大于 8000 元的员工

```sql
SELECT *
FROM employee
WHERE city = '北京' AND salary > 8000;
```

### 14. 查询工资小于 8000 元或者大于 18000 元的员工

```sql
SELECT *
FROM employee
WHERE salary < 8000
   OR salary > 18000;
```

### 15. 查询 2022 年及以后入职的员工

```sql
SELECT *
FROM employee
WHERE hire_date >= '2022-01-01';
```

**where:条件筛选。**

---

## 三、LIKE 模糊查询

### 1. 查询姓“张”的员工

```sql
SELECT *
FROM employee
WHERE name LIKE '张%';
```

### 2. 查询名字以“乔”结尾的员工

```sql
SELECT *
FROM employee
WHERE name LIKE '%乔';
```

### 3. 查询姓名中包含“尚”的员工

```sql
SELECT *
FROM employee
WHERE name LIKE '%尚%';
```

### 4. 查询名字恰好为两个汉字的员工

```sql
SELECT *
FROM employee
WHERE name LIKE '__';
```

### 5. 查询职位中包含“工程师”的员工

```sql
SELECT *
FROM employee
WHERE job LIKE '%工程师%';
```

### 6. 查询职位以“经理”结尾的员工

```sql
SELECT *
FROM employee
WHERE job LIKE '%经理';
```

### 7. 查询姓名以“孙”开头的员工

```sql
SELECT *
FROM employee
WHERE name LIKE '孙%';
```

### 8. 查询城市名称中包含“京”的员工

```sql
SELECT *
FROM employee
WHERE city LIKE '%京%';
```

---

## 四、ORDER BY 与 LIMIT

### 1. 按工资从高到低排列

```sql
SELECT *
FROM employee
ORDER BY salary DESC;
```

### 2. 按工资从低到高排列

```sql
SELECT *
FROM employee
ORDER BY salary ASC;
```

### 3. 按年龄从小到大排列

```sql
SELECT *
FROM employee
ORDER BY age ASC;
```

### 4. 先按部门升序，再按工资降序排列

```sql
SELECT *
FROM employee
ORDER BY department ASC, salary DESC;
```

### 5. 按入职日期从早到晚排列

```sql
SELECT *
FROM employee
ORDER BY hire_date ASC;
```

### 6. 查询技术部员工，并按工资降序排列

```sql
SELECT *
FROM employee
WHERE department = '技术部'
ORDER BY salary DESC;
```

### 7. 查询工资最高的 5 名员工

```sql
SELECT *
FROM employee
ORDER BY salary DESC
LIMIT 5;
```

### 8. 查询工资排名第 6～10 名的员工

```sql
SELECT *
FROM employee
ORDER BY salary DESC
LIMIT 5, 5;
```

---

## 五、计算字段

### 1. 查询每位员工的总收入

这里将总收入定义为：

```text
总收入 = 基本工资 + 奖金
```

```sql
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee;
```

### 2. 查询总收入大于 15000 元的员工

```sql
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee
WHERE salary + IFNULL(bonus, 0) > 15000;
```

### 3. 按总收入从高到低排序

```sql
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee
ORDER BY total_income DESC;
```

### 4. 查询总收入最高的 3 名员工

```sql
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee
ORDER BY total_income DESC
LIMIT 3;
```

### 5. 假设每位员工工资上涨 10%，显示上涨后的工资，但不修改原数据

```sql
SELECT
    name,
    salary,
    salary * 1.10 AS new_salary
FROM employee;
```

---

## 六、聚合函数

### 1. 统计员工总人数

```sql
SELECT COUNT(*) AS employee_count
FROM employee;
```

### 2. 统计在职员工人数

```sql
SELECT COUNT(*) AS active_employee_count
FROM employee
WHERE status = 1;
```

### 3. 统计离职员工人数

```sql
SELECT COUNT(*) AS inactive_employee_count
FROM employee
WHERE status = 0;
```

### 4. 统计有奖金的员工人数

```sql
SELECT COUNT(bonus) AS employee_with_bonus
FROM employee;
```

也可以写成：

```sql
SELECT COUNT(*) AS employee_with_bonus
FROM employee
WHERE bonus IS NOT NULL;
```

### 5. 统计没有奖金的员工人数

```sql
SELECT COUNT(*) AS employee_without_bonus
FROM employee
WHERE bonus IS NULL;
```

### 6. 查询最高工资

```sql
SELECT MAX(salary) AS max_salary
FROM employee;
```

### 7. 查询最低工资

```sql
SELECT MIN(salary) AS min_salary
FROM employee;
```

### 8. 查询平均工资

```sql
SELECT AVG(salary) AS avg_salary
FROM employee;
```

### 9. 查询公司每月需要支付的基本工资总额

```sql
SELECT SUM(salary) AS monthly_salary_total
FROM employee;
```

如果需要统计“基本工资加奖金”：

```sql
SELECT SUM(salary + IFNULL(bonus, 0)) AS monthly_income_total
FROM employee;
```

### 10. 查询技术部的平均工资

```sql
SELECT AVG(salary) AS avg_salary
FROM employee
WHERE department = '技术部';
```

### 11. 查询女性员工的平均工资

```sql
SELECT AVG(salary) AS avg_salary
FROM employee
WHERE gender = '女';
```

### 12. 查询 30 岁以下员工的最高工资

```sql
SELECT MAX(salary) AS max_salary
FROM employee
WHERE age < 30;
```

---

## 七、GROUP BY 分组查询

### 1. 统计每个部门的人数

```sql
SELECT
    department,
    COUNT(*) AS employee_count
FROM employee
GROUP BY department;
```

### 2. 统计每个部门的平均工资

```sql
SELECT
    department,
    AVG(salary) AS avg_salary
FROM employee
GROUP BY department;
```

### 3. 查询每个部门的最高工资

```sql
SELECT
    department,
    MAX(salary) AS max_salary
FROM employee
GROUP BY department;
```

### 4. 查询每个部门的最低工资

```sql
SELECT
    department,
    MIN(salary) AS min_salary
FROM employee
GROUP BY department;
```

### 5. 查询每个部门的工资总额

```sql
SELECT
    department,
    SUM(salary) AS salary_total
FROM employee
GROUP BY department;
```

### 6. 按性别统计员工人数

```sql
SELECT
    gender,
    COUNT(*) AS employee_count
FROM employee
GROUP BY gender;
```

### 7. 按城市统计员工人数

```sql
SELECT
    city,
    COUNT(*) AS employee_count
FROM employee
GROUP BY city;
```

### 8. 按员工状态统计人数

```sql
SELECT
    status,
    COUNT(*) AS employee_count
FROM employee
GROUP BY status;
```

### 9. 统计每个部门在职员工的人数

```sql
SELECT
    department,
    COUNT(*) AS active_employee_count
FROM employee
WHERE status = 1
GROUP BY department;
```

### 10. 查询每个部门的平均年龄

```sql
SELECT
    department,
    AVG(age) AS avg_age
FROM employee
GROUP BY department;
```

### 11. 查询每个部门的平均奖金

如果没有奖金的员工按 0 元计算：

```sql
SELECT
    department,
    AVG(IFNULL(bonus, 0)) AS avg_bonus
FROM employee
GROUP BY department;
```

如果只计算有奖金员工的平均奖金：

```sql
SELECT
    department,
    AVG(bonus) AS avg_bonus
FROM employee
GROUP BY department;
```

### 12. 查询每个城市的最高工资

```sql
SELECT
    city,
    MAX(salary) AS max_salary
FROM employee
GROUP BY city;
```

---

## 八、HAVING 分组过滤

### 1. 查询员工人数不少于 3 人的部门

```sql
SELECT
    department,
    COUNT(*) AS employee_count
FROM employee
GROUP BY department
HAVING employee_count >= 3;
```

### 2. 查询平均工资超过 10000 元的部门

```sql
SELECT
    department,
    AVG(salary) AS avg_salary
FROM employee
GROUP BY department
HAVING avg_salary > 10000;
```

### 3. 查询最高工资超过 15000 元的部门

```sql
SELECT
    department,
    MAX(salary) AS max_salary
FROM employee
GROUP BY department
HAVING max_salary > 15000;
```

### 4. 查询工资总额超过 30000 元的部门

```sql
SELECT
    department,
    SUM(salary) AS salary_total
FROM employee
GROUP BY department
HAVING salary_total > 30000;
```

### 5. 查询平均年龄小于 30 岁的部门

```sql
SELECT
    department,
    AVG(age) AS avg_age
FROM employee
GROUP BY department
HAVING avg_age < 30;
```

### 6. 查询在职员工不少于 2 人的部门

```sql
SELECT
    department,
    COUNT(*) AS active_employee_count
FROM employee
WHERE status = 1
GROUP BY department
HAVING active_employee_count >= 2;
```

### 7. 查询有奖金员工数量不少于 2 人的部门

```sql
SELECT
    department,
    COUNT(*) AS employee_with_bonus
FROM employee
WHERE bonus IS NOT NULL
GROUP BY department
HAVING employee_with_bonus >= 2;
```

---

## 九、综合查询

### 1. 查询在职员工中工资最高的 5 名员工

显示姓名、部门、职位和工资：

```sql
SELECT
    name,
    department,
    job,
    salary
FROM employee
WHERE status = 1
ORDER BY salary DESC
LIMIT 5;
```

### 2. 查询技术部中工资高于技术部平均工资的员工

```sql
SELECT *
FROM employee
WHERE department = '技术部'
  AND salary > (
      SELECT AVG(salary)
      FROM employee
      WHERE department = '技术部'
  );
```

### 3. 查询总收入最高的 5 名员工

```sql
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee
ORDER BY total_income DESC
LIMIT 5;
```

### 4. 查询每个部门的平均工资，并按平均工资从高到低排序

```sql
SELECT
    department,
    AVG(salary) AS avg_salary
FROM employee
GROUP BY department
ORDER BY avg_salary DESC;
```

### 5. 查询员工人数不少于 2 人的部门，并按人数降序排列

```sql
SELECT
    department,
    COUNT(*) AS employee_count
FROM employee
GROUP BY department
HAVING employee_count >= 2
ORDER BY employee_count DESC;
```

### 6. 查询 2020～2023 年入职的在职员工，并按入职日期升序排列

```sql
SELECT *
FROM employee
WHERE status = 1
  AND hire_date BETWEEN '2020-01-01' AND '2023-12-31'
ORDER BY hire_date ASC;
```

### 7. 查询每个部门的最高工资

```sql
SELECT
    department,
    MAX(salary) AS max_salary
FROM employee
GROUP BY department;
```

### 8. 查询工资高于公司平均工资的员工

```sql
SELECT *
FROM employee
WHERE salary > (
    SELECT AVG(salary)
    FROM employee
);
```

### 9. 查询奖金高于所有员工平均奖金的员工

只统计有奖金员工的平均奖金：

```sql
SELECT *
FROM employee
WHERE bonus > (
    SELECT AVG(bonus)
    FROM employee
);
```

如果没有奖金的员工按 0 元参与平均值计算：

```sql
SELECT *
FROM employee
WHERE IFNULL(bonus, 0) > (
    SELECT AVG(IFNULL(bonus, 0))
    FROM employee
);
```

### 10. 查询每个城市的员工数量，只显示员工数不少于 2 人的城市

```sql
SELECT
    city,
    COUNT(*) AS employee_count
FROM employee
GROUP BY city
HAVING employee_count >= 2;
```

---

# 十、单表查询总结

## 1. 单表查询完整语法

```sql
SELECT [DISTINCT] 字段列表
FROM 表名
WHERE 行过滤条件
GROUP BY 分组字段
HAVING 分组过滤条件
ORDER BY 排序字段 ASC | DESC
LIMIT 起始位置, 查询数量;
```

各子句的作用：

| 子句 | 作用 |
|---|---|
| **`SELECT`** | **决定最终显示哪些字段** |
| **`DISTINCT`** | **对查询结果去重** |
| **`FROM`** | **指定数据来自哪张表** |
| **`WHERE`** | **对原始记录进行过滤** |
| **`GROUP BY`** | **将记录按照指定字段分组** |
| **`HAVING`** | **对分组后的结果进行过滤** |
| **`ORDER BY`** | **对最终结果排序** |
| **`LIMIT`** | **限制返回记录的数量** |

---

## 2. SQL 的逻辑执行顺序

SQL 的书写顺序：

```text
SELECT
FROM
WHERE
GROUP BY
HAVING
ORDER BY
LIMIT
```

SQL 的逻辑执行顺序：

```text
FROM
WHERE
GROUP BY
HAVING
SELECT
ORDER BY
LIMIT
```

因此：

- `WHERE` 中通常不能直接使用 `SELECT` 定义的别名；
- `ORDER BY` 和 MySQL 的 `HAVING` 中通常可以使用查询别名。

---

## 3. WHERE 常用条件

### 比较运算符

```sql
=
<>
!=
>
<
>=
<=
```

### 逻辑运算符

```sql
AND
OR
NOT
```

优先级通常为：

```text
NOT > AND > OR
```

条件较复杂时，应主动使用括号，避免歧义。

### 范围查询

```sql
WHERE salary BETWEEN 8000 AND 15000;
```

`BETWEEN` 包含左右边界。

### 集合查询

```sql
WHERE department IN ('技术部', '测试部');
```

### 空值判断

```sql
WHERE bonus IS NULL;
WHERE bonus IS NOT NULL;
```

不能写成：

```sql
WHERE bonus = NULL;
```

因为 `NULL` 表示未知值，不能使用普通等号判断。

---

## 4. LIKE 模糊匹配

```text
%：匹配任意数量的字符
_：匹配任意一个字符
```

常见形式：

```sql
WHERE name LIKE '张%';    -- 以张开头
WHERE name LIKE '%乔';    -- 以乔结尾
WHERE name LIKE '%尚%';   -- 包含尚
WHERE name LIKE '__';     -- 恰好两个字符
```

---

## 5. 排序与分页

### 排序

```sql
ORDER BY salary ASC;   -- 升序
ORDER BY salary DESC;  -- 降序
```

`ASC` 是默认值，可以省略。

多字段排序：

```sql
ORDER BY department ASC, salary DESC;
```

含义是：

1. 先按部门升序；
2. 部门相同时，再按工资降序。

### 分页

```sql
LIMIT 起始下标, 查询数量;
```

例如：

```sql
LIMIT 0, 5;  -- 第 1～5 条
LIMIT 5, 5;  -- 第 6～10 条
```

页码分页公式：

```text
起始下标 = (页码 - 1) × 每页记录数
```

---

## 6. 聚合函数

| 函数 | 作用 |
|---|---|
| `COUNT()` | 统计数量 |
| `SUM()` | 求和 |
| `AVG()` | 求平均值 |
| `MAX()` | 求最大值 |
| `MIN()` | 求最小值 |

注意：

```sql
COUNT(*)
```

统计所有记录。

```sql
COUNT(bonus)
```

只统计 `bonus` 不为 `NULL` 的记录。

除 `COUNT(*)` 外，大多数聚合函数都会忽略 `NULL`。

---

## 7. GROUP BY 与 HAVING

### GROUP BY

```sql
SELECT department, COUNT(*)
FROM employee
GROUP BY department;
```

表示按照部门分组，每个部门产生一条统计结果。

### WHERE 与 HAVING 的区别

`WHERE`：

- 分组之前执行；
- 过滤原始记录；
- 通常不能直接使用聚合函数。

`HAVING`：

- 分组之后执行；
- 过滤分组结果；
- 可以使用聚合函数或聚合结果别名。

示例：

```sql
SELECT
    department,
    AVG(salary) AS avg_salary
FROM employee
WHERE status = 1
GROUP BY department
HAVING avg_salary > 10000;
```

执行过程：

1. 从 `employee` 读取数据；
2. 使用 `WHERE` 保留在职员工；
3. 按部门分组；
4. 计算每个部门平均工资；
5. 使用 `HAVING` 保留平均工资超过 10000 元的部门。

---

## 8. NULL 与 IFNULL

任何值与 `NULL` 进行普通算术运算，结果通常仍然是 `NULL`：

```sql
salary + bonus
```

当 `bonus` 为 `NULL` 时，结果也为 `NULL`。

可以使用：

```sql
IFNULL(bonus, 0)
```

将空值临时替换为 0：

```sql
salary + IFNULL(bonus, 0)
```

---

## 9. 子查询

子查询是嵌套在另一条 SQL 中的查询。

例如，查询工资高于公司平均工资的员工：

```sql
SELECT *
FROM employee
WHERE salary > (
    SELECT AVG(salary)
    FROM employee
);
```

执行过程：

1. 子查询先计算公司平均工资；
2. 外层查询再筛选工资高于该平均值的员工。

---

## 10. 单表查询容易出现的错误

### 错误一：漏掉题目条件

题目要求“在职员工”，必须写：

```sql
WHERE status = 1
```

### 错误二：把升序写成降序，或忘记写 DESC

```sql
ORDER BY total_income DESC;
```

### 错误三：混淆工资、奖金、月收入和年收入

```text
基本工资：salary
奖金：bonus
总收入：salary + IFNULL(bonus, 0)
年基本工资：salary * 12
年收入：salary * 12 + IFNULL(bonus, 0)
```

具体公式应根据题目对奖金周期的定义确定。

### 错误四：分组后忘记使用 HAVING

```sql
GROUP BY city
HAVING COUNT(*) >= 2;
```

### 错误五：聚合字段写错

查询平均奖金：

```sql
AVG(bonus)
```

不能误写成：

```sql
AVG(salary)
```

### 错误六：NULL 使用等号判断

错误：

```sql
bonus = NULL
```

正确：

```sql
bonus IS NULL
```

---

## 十一、当前掌握情况

目前已经基本掌握：

- 基础字段查询和别名；
- `DISTINCT` 去重；
- `WHERE` 条件过滤；
- `AND、OR、IN、BETWEEN`；
- `IS NULL` 与 `IS NOT NULL`；
- `LIKE` 模糊匹配；
- `ORDER BY` 排序；
- `LIMIT` 分页；
- 聚合函数；
- `GROUP BY` 分组；
- `HAVING` 分组过滤；
- 简单子查询。

接下来应重点强化：

1. 读题时完整提取所有限制条件；
2. 区分 `WHERE` 与 `HAVING`；
3. 熟练计算字段和 `NULL` 处理；
4. 熟练“分组、聚合、过滤、排序”的组合查询；
5. 开始学习多表连接查询。



