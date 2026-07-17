# MySQL 多表查询练习（优化版）

> 数据库：`company_join_practice`  
> 涉及表：`employees`、`departments`、`projects`、`employee_project`

---

## 一、多表查询书写规范

多表查询中尽量不要使用 `SELECT *`，而应明确写出所需字段：

```sql
SELECT
    e.employee_name,
    e.job,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id;
```

这样可以避免同名字段混淆，并减少无用数据返回。

建议统一使用表别名：

| 表 | 别名 |
|---|---|
| `employees` | `e` |
| `departments` | `d` |
| `projects` | `p` |
| `employee_project` | `ep` |

---

# 二、员工与部门：两表查询

## 1. 查询有部门的员工及其所属部门

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.job,
    e.salary,
    d.department_name,
    d.location
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY e.employee_id;
```

**结果说明：**

- `INNER JOIN` 只保留两张表中可以成功匹配的记录；
- 没有所属部门的员工不会显示；
- 结果按照员工编号升序排列。

---

## 2. 查询所有员工及其所属部门，包括没有部门的员工

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.job,
    e.salary,
    d.department_name,
    d.location
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY e.employee_id;
```

**结果说明：**

- `employees` 是左表，因此所有员工都会保留；
- 没有部门的员工，其部门字段显示为 `NULL`；
- 练习数据中的“林峰”也会显示。

---

## 3. 查询所有部门及其员工，包括没有员工的部门

```sql
SELECT
    d.department_id,
    d.department_name,
    d.location,
    e.employee_id,
    e.employee_name,
    e.job
FROM departments AS d
LEFT JOIN employees AS e
    ON d.department_id = e.department_id
ORDER BY d.department_id, e.employee_id;
```

**结果说明：**

- `departments` 是左表，所以所有部门都会显示；
- 没有员工的部门，其员工字段显示为 `NULL`；
- 练习数据中的“运维部”也会显示。

---

## 4. 查询所有员工的姓名、职位和部门名称

```sql
SELECT
    e.employee_name,
    e.job,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY d.department_id, e.employee_id;
```

---

## 5. 查询技术部的所有员工

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.job,
    e.salary,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.department_name = '技术部'
ORDER BY e.salary DESC;
```

---

## 6. 查询工资大于 12000 元员工的姓名、工资和部门

```sql
SELECT
    e.employee_name,
    e.salary,
    d.department_name
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
WHERE e.salary > 12000
ORDER BY e.salary DESC;
```

---

## 7. 查询部门位于北京的所有员工

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.job,
    e.salary,
    d.department_name,
    d.location
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
WHERE d.location = '北京'
ORDER BY e.salary DESC;
```

---

## 8. 查询员工姓名、部门名称和部门所在地

```sql
SELECT
    e.employee_name,
    d.department_name,
    d.location
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
ORDER BY d.department_id, e.employee_id;
```

---

# 三、员工表自连接

员工表中：

```text
manager_id → employee_id
```

因此可以让 `employees` 表自己连接自己：

```text
e：员工
m：直属领导
```

## 1. 查询每名员工及其直属领导

```sql
SELECT
    e.employee_id,
    e.employee_name AS employee_name,
    e.job AS employee_job,
    m.employee_name AS manager_name,
    m.job AS manager_job
FROM employees AS e
LEFT JOIN employees AS m
    ON e.manager_id = m.employee_id
ORDER BY e.employee_id;
```

**为什么使用 `LEFT JOIN`？**

最高级管理者的 `manager_id` 为 `NULL`。如果使用 `INNER JOIN`，这些没有直属领导的员工会被过滤掉。

---

## 2. 查询有直属领导的员工

```sql
SELECT
    e.employee_name AS employee_name,
    e.job AS employee_job,
    m.employee_name AS manager_name
FROM employees AS e
INNER JOIN employees AS m
    ON e.manager_id = m.employee_id
ORDER BY m.employee_id, e.employee_id;
```

---

## 3. 查询没有直属领导的员工

```sql
SELECT
    employee_id,
    employee_name,
    job,
    salary
FROM employees
WHERE manager_id IS NULL
ORDER BY employee_id;
```

---

# 四、项目与部门：两表查询

## 1. 查询所有有负责部门的项目

```sql
SELECT
    p.project_id,
    p.project_name,
    p.budget,
    p.project_status,
    d.department_name,
    d.location
FROM projects AS p
INNER JOIN departments AS d
    ON p.department_id = d.department_id
ORDER BY p.project_id;
```

原文件中连接条件写在了 `WHERE` 中。规范写法应当把表之间的关联条件写在 `ON` 后面：

```sql
INNER JOIN departments AS d
    ON p.department_id = d.department_id
```

其中：

- `ON`：描述表之间如何关联；
- `WHERE`：过滤连接后的记录。

---

## 2. 查询所有项目及其负责部门，包括没有负责部门的项目

```sql
SELECT
    p.project_id,
    p.project_name,
    p.budget,
    p.project_status,
    d.department_name,
    d.location
FROM projects AS p
LEFT JOIN departments AS d
    ON p.department_id = d.department_id
ORDER BY p.project_id;
```

---

## 3. 查询所有部门及其项目，包括没有项目的部门

```sql
SELECT
    d.department_id,
    d.department_name,
    p.project_id,
    p.project_name,
    p.budget,
    p.project_status
FROM departments AS d
LEFT JOIN projects AS p
    ON d.department_id = p.department_id
ORDER BY d.department_id, p.project_id;
```

---

# 五、三表查询：员工与项目

员工和项目是多对多关系，需要通过中间表连接：

```text
employees
    ↓ employee_id
employee_project
    ↓ project_id
projects
```

## 1. 查询员工参加的项目

```sql
SELECT
    e.employee_id,
    e.employee_name,
    p.project_id,
    p.project_name,
    ep.project_role,
    ep.join_date,
    ep.work_hours
FROM employees AS e
INNER JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
INNER JOIN projects AS p
    ON ep.project_id = p.project_id
ORDER BY e.employee_id, p.project_id;
```

**结果说明：**

一行表示“一名员工参加一个项目”。一名员工参加多个项目时，会出现多行，这是正常的多对多查询结果。

---

## 2. 查询参加“高并发HTTP服务器”项目的员工

```sql
SELECT
    e.employee_name,
    e.job,
    p.project_name,
    ep.project_role,
    ep.work_hours
FROM employees AS e
INNER JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
INNER JOIN projects AS p
    ON ep.project_id = p.project_id
WHERE p.project_name = '高并发HTTP服务器'
ORDER BY ep.work_hours DESC;
```

---

## 3. 查询每名员工参加项目的数量

```sql
SELECT
    e.employee_id,
    e.employee_name,
    COUNT(ep.project_id) AS project_count
FROM employees AS e
LEFT JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
GROUP BY
    e.employee_id,
    e.employee_name
ORDER BY project_count DESC, e.employee_id;
```

使用 `LEFT JOIN` 后，没有参加项目的员工也会显示，其项目数量为 0。

---

## 4. 查询参加两个及以上项目的员工

```sql
SELECT
    e.employee_id,
    e.employee_name,
    COUNT(ep.project_id) AS project_count
FROM employees AS e
INNER JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
GROUP BY
    e.employee_id,
    e.employee_name
HAVING COUNT(ep.project_id) >= 2
ORDER BY project_count DESC, e.employee_id;
```

---

## 5. 查询每名员工参加项目的总工时

```sql
SELECT
    e.employee_id,
    e.employee_name,
    COALESCE(SUM(ep.work_hours), 0) AS total_work_hours
FROM employees AS e
LEFT JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
GROUP BY
    e.employee_id,
    e.employee_name
ORDER BY total_work_hours DESC, e.employee_id;
```

---

## 6. 查询没有参加任何项目的员工

```sql
SELECT
    e.employee_id,
    e.employee_name,
    e.job
FROM employees AS e
LEFT JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
WHERE ep.project_id IS NULL
ORDER BY e.employee_id;
```

---

## 7. 查询每个项目的员工人数

```sql
SELECT
    p.project_id,
    p.project_name,
    COUNT(ep.employee_id) AS employee_count
FROM projects AS p
LEFT JOIN employee_project AS ep
    ON p.project_id = ep.project_id
GROUP BY
    p.project_id,
    p.project_name
ORDER BY employee_count DESC, p.project_id;
```

这里应使用：

```sql
COUNT(ep.employee_id)
```

不能随意使用 `COUNT(*)`。左连接没有匹配时仍会产生一行，`COUNT(*)` 可能把没有员工的项目统计为 1，而 `COUNT(ep.employee_id)` 会忽略 `NULL`，正确得到 0。

---

## 8. 查询没有员工参加的项目

```sql
SELECT
    p.project_id,
    p.project_name,
    p.project_status
FROM projects AS p
LEFT JOIN employee_project AS ep
    ON p.project_id = ep.project_id
WHERE ep.employee_id IS NULL
ORDER BY p.project_id;
```

---

# 六、四表综合查询

## 1. 查询员工、所属部门、项目及项目角色

```sql
SELECT
    e.employee_name,
    d.department_name,
    p.project_name,
    ep.project_role,
    ep.work_hours
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
INNER JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
INNER JOIN projects AS p
    ON ep.project_id = p.project_id
ORDER BY e.employee_id, p.project_id;
```

连接关系：

```text
employees
    ├── departments
    └── employee_project
            └── projects
```

---

## 2. 查询技术部员工参加的所有项目

```sql
SELECT
    e.employee_name,
    d.department_name,
    p.project_name,
    ep.project_role,
    ep.work_hours
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
INNER JOIN employee_project AS ep
    ON e.employee_id = ep.employee_id
INNER JOIN projects AS p
    ON ep.project_id = p.project_id
WHERE d.department_name = '技术部'
ORDER BY e.employee_id, p.project_id;
```

---

## 3. 查询项目所属部门与员工所属部门不同的记录

```sql
SELECT
    e.employee_name,
    ed.department_name AS employee_department,
    p.project_name,
    pd.department_name AS project_department,
    ep.project_role
FROM employee_project AS ep
INNER JOIN employees AS e
    ON ep.employee_id = e.employee_id
INNER JOIN projects AS p
    ON ep.project_id = p.project_id
LEFT JOIN departments AS ed
    ON e.department_id = ed.department_id
LEFT JOIN departments AS pd
    ON p.department_id = pd.department_id
WHERE e.department_id <> p.department_id
ORDER BY p.project_id, e.employee_id;
```

这里部门表连接了两次：

- `ed`：员工所属部门；
- `pd`：项目负责部门。

---

## 4. 查询所有部门及其项目数量

```sql
SELECT
    d.department_id,
    d.department_name,
    COUNT(p.project_id) AS project_count
FROM departments AS d
LEFT JOIN projects AS p
    ON d.department_id = p.department_id
GROUP BY
    d.department_id,
    d.department_name
ORDER BY project_count DESC, d.department_id;
```

---

## 5. 查询各部门负责项目的预算总额

```sql
SELECT
    d.department_id,
    d.department_name,
    COALESCE(SUM(p.budget), 0) AS total_budget
FROM departments AS d
LEFT JOIN projects AS p
    ON d.department_id = p.department_id
GROUP BY
    d.department_id,
    d.department_name
ORDER BY total_budget DESC, d.department_id;
```

---

# 七、多表查询完整结构

```sql
SELECT 字段列表
FROM 主表
JOIN 关联表1
    ON 连接条件
JOIN 关联表2
    ON 连接条件
WHERE 普通记录过滤条件
GROUP BY 分组字段
HAVING 分组过滤条件
ORDER BY 排序字段
LIMIT 查询数量;
```

逻辑执行顺序：

```text
FROM
→ JOIN / ON
→ WHERE
→ GROUP BY
→ HAVING
→ SELECT
→ ORDER BY
→ LIMIT
```

---

# 八、INNER JOIN 与 LEFT JOIN

## INNER JOIN

```sql
FROM employees AS e
INNER JOIN departments AS d
    ON e.department_id = d.department_id
```

只保留匹配成功的数据。

适合：

- 查询有部门的员工；
- 查询参加了项目的员工；
- 查询有直属领导的员工。

## LEFT JOIN

```sql
FROM employees AS e
LEFT JOIN departments AS d
    ON e.department_id = d.department_id
```

保留左表全部数据，右表匹配不到时显示 `NULL`。

适合：

- 查询所有员工，包括没有部门的员工；
- 查询所有部门，包括没有员工的部门；
- 查询所有项目，包括没有成员的项目；
- 查询每名员工，包括没有直属领导的员工。

---

# 九、多表查询常见错误

## 1. 直接使用 SELECT *

不推荐：

```sql
SELECT *
FROM employees AS e
JOIN departments AS d
    ON e.department_id = d.department_id;
```

推荐明确字段：

```sql
SELECT
    e.employee_name,
    e.job,
    d.department_name
FROM employees AS e
JOIN departments AS d
    ON e.department_id = d.department_id;
```

## 2. 忘记 ON 连接条件

不规范：

```sql
SELECT *
FROM projects AS p
INNER JOIN departments AS d
WHERE p.department_id = d.department_id;
```

规范：

```sql
SELECT
    p.project_name,
    d.department_name
FROM projects AS p
INNER JOIN departments AS d
    ON p.department_id = d.department_id;
```

## 3. 查询所有员工及领导时使用 INNER JOIN

`INNER JOIN` 会过滤掉没有领导的员工。应使用：

```sql
LEFT JOIN employees AS m
    ON e.manager_id = m.employee_id
```

## 4. 多表字段不加表别名

不够清晰：

```sql
WHERE salary > 12000;
```

推荐：

```sql
WHERE e.salary > 12000;
```

## 5. LEFT JOIN 后错误使用 COUNT(*)

统计右表匹配数量时，应使用：

```sql
COUNT(右表主键)
```

例如：

```sql
COUNT(ep.employee_id)
```

## 6. 误把多对多结果当作重复数据

一名员工参加多个项目时：

```text
员工A + 项目1
员工A + 项目2
员工A + 项目3
```

这是正常结果，不应盲目使用 `DISTINCT` 删除。

---

# 十、当前需要掌握的重点

1. 找出表之间的主键和外键关系；
2. 判断使用 `INNER JOIN` 还是 `LEFT JOIN`；
3. 把连接条件放在 `ON` 中；
4. 把普通筛选条件放在 `WHERE` 中；
5. 多对多关系必须经过中间表；
6. 自连接必须给同一张表设置不同别名；
7. 分组统计时注意 `COUNT(*)` 与 `COUNT(字段)`；
8. 使用 `LEFT JOIN ... IS NULL` 查询不存在的关联数据；
9. 多表查询中尽量避免 `SELECT *`；
10. 三表、四表查询只是继续增加 `JOIN`，核心仍然是表关系。

---

# 十一、继续练习

1. 查询每个部门工资最高的员工；
2. 查询工资高于所在部门平均工资的员工；
3. 查询每个项目中工资最高的员工；
4. 查询参加项目数量最多的员工；
5. 查询每个部门员工参加项目的总工时；
6. 查询没有员工的部门；
7. 查询没有负责项目的部门；
8. 查询跨部门参加项目的员工；
9. 查询每名员工参加项目的数量和总工时；
10. 查询人数不少于 3 人且总工时超过 800 小时的项目。
