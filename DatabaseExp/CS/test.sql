SELECT NAME FROM sys.Databases;
SELECT NAME FROM sys.Tables;

--建表
CREATE TABLE Course (cno CHAR(4), cname Varchar(40), cpno CHAR(4), ccredit SMALLINT);
CREATE TABLE Student ( sno CHAR(9), sname Varchar(20), ssex CHAR(2), sage SMALLINT, sdept Varchar(50));
CREATE TABLE SC (sno CHAR(9), cno CHAR(4), grade SMALLINT);
CREATE TABLE Teacher (tno CHAR(5), tname Varchar(10), tsex CHAR(2), tdep Varchar(50));

--建表加入基本约束
CREATE TABLE Student 
(
    sno CHAR(9) PRIMARY KEY,
    sname VARCHAR(20) NOT NULL,
    ssex CHAR(2),
    sage SMALLINT,
    dept VARCHAR(50) 
)
CREATE TABLE course
(
    cno CHAR(4) PRIMARY KEY,
    cname VARCHAR(50) UNIQUE,
    cpno CHAR(4),
    ccredit SMALLINT
)
CREATE TABLE sc
(
    sno CHAR(9),
    cno CHAR(4),
    grade SMALLINT,
    PRIMARY KEY(sno, cno)
)

--外码约束
CREATE TABLE sc
(
    sno CHAR(9),
    cno CHAR(4),
    grade SMALLINT,
    PRIMARY KEY (sno, cno),
    FOREIGN KEY (sno) REFERENCES student(sno),
    FOREIGN KEY (cno) REFERENCES course(cno)
)

--检查是否满足布尔表达式
CREATE TABLE Student
(
    sno char(9) PRIMARY KEY,
    sname VARCHAR(20) not NULL UNIQUE,
    ssex CHAR(2) CHECK (ssex in ('男', '女')),
    sage SMALLINT,
    sdept VARCHAR(50)
)

create table sc
(  
    sno  char(9),
    cno   char(4),
    grade  smallint 
    check ((grade>=0) and (grade<=100)),
    primary key(sno,cno) ,
    foreign key(sno) references  student(sno),
    foreign key(cno) references  course(cno)
)

CREATE TABLE course
(
    cno CHAR(4),
    cname VARCHAR(30) UNIQUE,
    ctype CHAR(6) CHECK (ctype in ('a', 'b', 'c')),
    ccredit SMALLINT CHECK ((ccredit > 0) AND (ccredit <= 8)),
    cdep VARCHAR(50)
)

--疑问Constraint  checktype 和 check 有啥区别，有啥用
--constraint用来把约束条件起个名字，方便之后的修改删除什么的，比如checktype\checkcredit什么的
create  table  course
( 
    cno  char(4)  primary key,
    cname varchar(30) unique,
    ctype  char(6) Constraint  checktype check (ctype in ('必修','限选','任选')),     
    ccredit smallint Constraint  checkcredit check((ccredit>0) and (ccredit<=8)) ,
    cdep  varchar(50)    
)

--删除基本表
DROP TABLE table-name RESTRICT | CASCADE

--修改基本表
ALTER TABLE course drop checktype;
ALTER TABLE course drop checkcredit;
ALTER TABLE course drop COLUMN cdep;
ALTER TABLE course ADD cdept CHAR(4);
ALTER TABLE course ALTER COLUMN cdept VARCHAR(20);

--建立索引
CREATE UNIQUE INDEX Stusno ON Student(sno)
CREATE UNIQUE INDEX Coucno ON Course(cno)
CREATE UNIQUE INDEX SCno ON SC(sno ASC, cno DESC)

--分组查询
--查询每个学生成绩大于等于90分且数目大于等于3的课程数量
select sno, count(*) from sc where score >=90 group by sno having count(*) >= 3;

--查询每一门课的先修课的先修课
SELECT first.cno, second.cpreno from Course first, Course second where first.cpreno = second.cno

--左外连接
SELECT * FROM (Student LEFT OUTER Join SC on Student.sno = SC.sno)
--右外连接
SELECT * FROM (Student RIGHT OUTER Join SC on Student.sno = SC.sno)

--带有in谓词的嵌套查询
SELECT sno, sname, sdept from Student where sdept IN (select sdept from Student WHERE sname = '刘晨')
--使用自身连接完成同样的操作
SELECT S1.sno, S1.sname, S1.sdept FROM Student S1, Student S2 WHERE S1.sdept = S2.sdept AND S2.sname = '刘晨'
--同样可以用=代替in
SELECT sno, sname, sdept from Student where sdept = (SELECT sdept from student WHERE sname = '刘晨')

SELECT sno, cno FROM SC x WHERE grade >= (SELECT AVG(grade) FROM SC y WHERE y.sno = x.sno)

--查询选修了所有课程的学生姓名
--等价于 没有一门课程没有选
SELECT sname FROM Student WHERE NOT EXISTS (SELECT * FROM Course WHERE NOT EXISTS (SELECT * FROM SC WHERE SC.sno = Student.sno AND SC.cno = Course.cno))
--查询至少选修了学生学号为95002选修的全部课程的学生号码
--蕴含式转换为 不存在这样的课程y，学生95002选修了y，而学生x没有选y
SELECT DISTINCT sno FROM SC x WHERE NOT EXISTS (SELECT * FROM SC y WHERE y.sno = '95002' AND NOT EXISTS (SELECT * FROM SC z WHERE z.sno = x.sno AND z.cno = y.cno))

--插入数据
INSERT INTO Student VALUES(123, 'wangwang', 'CS')
INSERT INTO Student(sno, sname) VALUES(123, 'wangwang')

--对每一个系，求学生的平均年龄，并把结果存入数据库。
--第一步建表
CREATE TABLE Deptage (Sdept CHAR(15), Avgage SMALLINT)
--第二步插入数据
INSERT INTO Deptage(Sdept, Avgage) SELECT Sdept, AVG(sage) FROM Student GROUP BY Sdept

--修改数据
UPDATE Student SET sage=22 WHERE sno='95002'
UPDATE Student SET sage=sage+1
UPDATE SC SET score=0 WHERE 'CS' = (SELECT sdept FROM Student WHERE Student.sno = SC.sno)

--删除数据
DELETE from Student where sno = '95002'

--行列子集视图
CREATE VIEW IS_Student
AS
    SELECT sno, sname, sage from Student WHERE sdept='IS'
    WITH CHECK OPTION; --加入限制，只涉及IS学生
-- 修改操作：DBMS自动加上Sdept= ‘IS’的条件
-- 删除操作：DBMS自动加上Sdept= ‘IS’的条件
-- 插入操作：DBMS自动检查Sdept属性值是否为'IS' 
-- 如果不是，则拒绝该插入操作 
-- 如果没有提供Sdept属性值，则自动定义Sdept为'IS'

--带表达式的视图
CREATE VIEW BT_S(sno, sname, sbirth)
AS
    SELECT sno, sname, 2019-sgae FROM Student
--sbirth为派生属性列，虚拟列

--分组视图
CREATE VIEW Student_AVG_Grade(sno, Gavg)
AS
    SELECT sno, AVG(grade) FROM SC GROUP BY sno

--删除视图
--DROP VIEW <视图名>[CASCADE]； 
--不使用CASCADE关键字，由该视图导出的其他视图定义仍在数据字典中，但已不能使用，必须显式删除
--如果使用CASCADE,则把该视图和由它导出的所有视图一起删除
--删除基表时，由该基表导出的所有视图定义都必须显式删除
DROP VIEW IS_S1;
--执行该语句时，由于IS_S1视图还导出了IS_S2视图，所以该语句拒绝执行。如果要确实删除，则使用级联删除语句
DROP VIEW IS_S1 CASCADE;

-- [例3]在S_G视图中查询平均成绩在90分以上的学生学号和平均成绩 
	SELECT * 
	FROM   S_G
	WHERE  Gavg>=90； 
-- S_G视图定义：        
CREATE VIEW S_G(Sno, Gavg)          
AS  
    SELECT  Sno，AVG(Grade) 
	FROM  SC 
	GROUP BY Sno；
--查询转换
-- 错误： 
SELECT Sno，AVG(Grade) 
FROM     SC 
WHERE  AVG(Grade)>=90/* Where子句只能对基表筛选*/
GROUP BY Sno；
 
-- 正确：
SELECT  Sno，AVG(Grade) 
FROM  SC 
GROUP BY Sno 
HAVING AVG(Grade)>=90；/* 对组进行筛选 */

/*
若视图由多个表导出，则不允许更新。如P120例3在插入数据时会异常。
视图字段来自表达式或常数，不允许更新。
视图字段来自集函数则不允许更新。
分组视图不允许更新，P121，例6。
视图中含DISTINCT短语，不允许更新。
视图定义中含嵌套查询则不允许更新。
不允许更新的视图上定义的视图不允许更新。
*/
