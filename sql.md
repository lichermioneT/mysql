# sql

## 1.单表查询

1. 查询所有员工信息

```
select * from employee;
```

2. 只查询姓名、部门和工资

```
select name, department, salary from employee;
```

3. 给查询结果设置别名

```
select name as 姓名, department as 部门, salary as 工资 from employee;
select name  姓名, department  部门, salary 工资 from employee;
```

4. 查询公司有哪些部门，要求去重

```mysql
select distinct  department from employee;
```

查询工资大于 10000 元的员工。

```
select * from employee where salary > 10000;
```

查询工资在 8000～15000 元之间的员工。

```
select * from employee where salary >= 8000 and salary <= 15000;
```

查询年龄小于 30 岁的员工。

```
select * from employee where age < 30;
```

查询技术部的所有员工。

```
select * from employee where department='技术部';
```

查询技术部并且工资大于 10000 元的员工。

```
select * from employee where department='技术部' and salary > 10000;
```

查询技术部或者测试部的员工。

```
select * from employee where department='技术部' or department='测试部';
```

查询不属于技术部的员工。

```
select * from employee where not department='技术部';
```

查询年龄为 25、28、30 岁的员工。

```
select * from employee where age in(25,28,30);
```

查询奖金为空的员工。

```
select * from employee where bonus is null;
```

查询奖金不为空的员工。

```
select * from employee where bonus is not null;
```

查询已经离职的员工。

```
select * from employee where status=0;
```

查询当前在职的员工。

```
select * from employee where status=1;
```

查询在北京工作并且工资大于 8000 元的员工。

```
 select * from employee where city='北京' and salary > 8000;
```

查询工资小于 8000 元或者大于 18000 元的员工。

```
select * from employee where city='北京' and (salary > 8000 or salary < 18000);
```

查询 2022 年以后入职的员工。

```
select * from employee where hire_date >= '2022-01-01';
```

1. 查询姓“张”的员工

```
select * from employee where name like '张%';
```

查询名字以“乔”结尾的员工。

```
 select * from employee where name like '%乔';
```

查询姓名中包含“尚”的员工。

```
select * from employee where name like '%尚%';
```

查询名字恰好为两个汉字的员工。

```
select * from employee where name like '__';
```

查询职位中包含“工程师”的员工。

```
select * from employee where job like '%工程师%';
```

查询职位以“经理”结尾的员工。

```
select * from employee where job like '%经理';
```

查询姓名以“孙”开头的员工。

```
select * from employee where name like '孙%';
```

查询城市名称中包含“京”的员工。

```
 select * from employee where city like '%京%';
```



按工资从高到低排列。

```
select * from employee order by salary desc;
```

按工资从低到高排列。

```
select * from employee order by salary asc;
```

按年龄从小到大排列。

```
select * from employee order by age asc;
```

先按部门升序，再按工资降序排列。

```
select * from employee order by department asc, salary desc;
```

按入职日期从早到晚排列。

```
select * from employee order by hire_date asc;
```

查询技术部员工，并按工资降序排列。

```
select * from employee where department='技术部' order by salary desc;
```

查询工资最高的 5 名员工。

```
select * from employee order by salary desc limit 5;
```

查询工资排名第 6～10 名的员工。

```
select * from employee order by salary desc limit 5, 5;
```



查询每位员工的总收入。

```
select salary + ifnull(bonus, 0) as 年薪  from employee;
```

查询总收入大于 15000 元的员工。

```
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee
WHERE salary + IFNULL(bonus, 0) > 15000;
```



按总收入从高到低排序。

```
select salary*12 + ifnull(bonus, 0) as 年薪  from employee order by 年薪;
修改
SELECT
    name,
    salary,
    bonus,
    salary + IFNULL(bonus, 0) AS total_income
FROM employee
ORDER BY total_income DESC;
```

查询总收入最高的 3 名员工。

```
select name, salary*12 + ifnull(bonus, 0) as 年薪  from employee order by 年薪 desc limit 3;
```

假设每位员工工资上涨 10%，显示上涨后的工资，但不要真正修改数据

```
SELECT name,salary, salary * 1.1 AS new_salary FROM employee;
```



统计员工总人数。

```
select count(*) from employee;
```

统计在职员工人数。

```
select count(*) from employee where status=1;
```

统计离职员工人数。

```
 select count(*) from employee where status=0;
```

统计有奖金的员工人数。

```
select count(bonus) from employee;
```

统计没有奖金的员工人数。

```
select count(*) from employee where bonus is null;
```

查询最高工资。

```
select max(salary) from employee;
```

查询最低工资。

```
select min(salary) from employee;
```

查询平均工资。

```
select avg(salary) from employee;
```

查询公司每月需要支付的工资总额。

```
select avg(salary)*count(*) from employee;
SELECT SUM(salary) AS monthly_salary_total FROM employee;
```

查询技术部的平均工资。

```
select avg(salary) from employee where department='技术部';
```

查询女性员工的平均工资。

```
select avg(salary) from employee where gender='女';
```

查询 30 岁以下员工的最高工资

```
select max(salary) from employee where age<30;
```



统计每个部门的人数。

```
select department, count(*) from employee group by department;
```

统计每个部门的平均工资。

```
select department, count(*), avg(salary) from employee group by department;
```

查询每个部门的最高工资。

```
 select department, count(*), max(salary) from employee group by department;
```

查询每个部门的最低工资。

```
 select department, count(*), min(salary) from employee group by department;

```

查询每个部门的工资总额。

```
select department, count(*), sum(salary) from employee group by department;
```

按性别统计员工人数。

```
select gender, count(*) from employee group by gender ;
```

按城市统计员工人数。

```
select city, count(*) from employee group by city ;
```

按员工状态统计人数。

```
select status, count(*) from employee group by status;
```

统计每个部门在职员工的人数。

```
select department ,count(*) from employee where status=1 group by department;
```

查询每个部门的平均年龄。

```
select department, avg(age) from employee  group by department;
```

查询每个部门的平均奖金。

```
select department, avg(ifnull(bonus, 0)) from employee  group by department;
```

查询每个城市的最高工资。

```
select city, max(salary) from employee  group by city;
```





查询员工人数不少于 3 人的部门。

```
select department, count(*) as sum from employee  group by department having sum >=3;
```

查询平均工资超过 10000 元的部门。

```
select department, avg(salary) as avg_sal from employee  group by department having avg_sal > 10000;
```

查询最高工资超过 15000 元的部门。

```
select department, max(salary) as max_sal from employee  group by department having max_sal > 15000;
```

查询工资总额超过 30000 元的部门。

```
select department, sum(salary) as sum_sal from employee  group by department having sum_sal > 30000;
```

查询平均年龄小于 30 岁的部门。

```
select department, avg(age) as avg_age from employee  group by department having avg_age < 30;
```

查询在职员工不少于 2 人的部门。

```
select department from employee where status = 1 group by department having count(*) >= 2;
```

查询有奖金员工数量不少于 2 人的部门。

```
select department from employee where bonus is not null group by department having count(*) >= 2;
```



查询在职员工中，工资最高的 5 名员工，显示姓名、部门、职位和工资。

```
select name, department, job, salary from employee order by salary desc limit 5;
```

查询技术部中工资高于技术部平均工资的员工。

```
select * from employee where salary > (select avg(salary) from employee where department = '技术部') and department = '技术部';
```

查询总收入最高的 5 名员工。

```
select salary*12 + ifnull(bonus, 0) as sal from employee order by sal limit 5;
```

查询每个部门平均工资，并按平均工资从高到低排序。

```
select department, avg(salary) as avg_sal from employee group by department order by avg_sal desc;;
```

查询员工人数不少于 2 人的部门，并按人数降序排列。

```
select department, count(*) as conn from employee group by department having conn >=2 order by conn desc;
```

查询 2020 年至 2023 年入职的在职员工，并按入职日期升序排列。

```
select * from employee where hire_date >= '2020-1-1' and hire_date <= '2023-12-31' order by hire_date asc;
```

查询每个部门工资最高的员工工资。

```
select department, max(salary) as max_sal from employee group by department;
```

查询工资高于公司平均工资的员工。

```
select * from employee where salary >(select avg(salary) from employee);
```

查询奖金高于所有员工平均奖金的员工。

```
select * from employee where bonus >(select avg(salary) from employee);
```

查询每个城市的员工数量，只显示员工数不少于 2 人的城市。

```
select city, count(*) as conn from employee group by city;
```



## 2.多表查询

**先验证内连接**

```
select * from employees, departments where employees.department_id = departments.department_id;
```

```
select * from employees inner join departments on employees.department_id = departments.department_id;
```

**注意：没有部门的林峰不会出现在结果中，因为内连接只保留能够匹配的数据。**

**验证左连接**

```
select * from employees as e left join departments as d on e.department_id=d.department_id;
```

**查询所有部门及其员工**

```
select * from departments  as d left join employees as e on d.department_id=e.department_id;
```

**自连接查询领导**

```my]
select * from employees as e1 left join employees as e2 on e1.manager_id=e2.employee_id;
```



















