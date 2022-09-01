CREATE TABLE admintable ( adid nchar ( 5 ) PRIMARY KEY NOT NULL, adpass nchar ( 20 ) NOT NULL );
INSERT INTO admintable ( adid, adpass )
VALUES
	( '00001', '12345678' ),
	( '00002', '12345678' );
CREATE TABLE studentpasstable ( stid char ( 6 ) PRIMARY KEY NOT NULL, spass nchar ( 20 ) NOT NULL );
INSERT INTO studentpasstable ( stid, spass )
VALUES
	( '000001', '12345678' ),
	( '000102', '000000' ),
	( '000011', '99999' );
CREATE TABLE stutable (
	stid char ( 6 ) PRIMARY KEY NOT NULL,
	sname char ( 5 ) NOT NULL,
	ssex nchar ( 1 ),
	sage tinyint,
	splace nchar ( 50 ),
	smajor nchar ( 50 ) 
);
INSERT INTO stutable ( stid, sname, ssex, sage, splace, smajor )
VALUES
	( '000001', '张三', '男', '20', '四川省成都市郫都区', '计算机与软件工程学院计算机科学与技术2班' ),
	( '000102', '李四', '男', '19', '上海市浦东新区', '管理学院会计学2班' ),
	( '000011', '李娜', '女', '20', '北京市朝阳区', '理学院信息与计算科学1班' );
CREATE TABLE gradetable (
	stid nchar ( 6 ) NOT NULL,
	grademath numeric ( 4, 1 ) NOT NULL,
	gradeen numeric ( 4, 1 ) NOT NULL,
	gradec numeric ( 4, 1 ) 
);
INSERT INTO gradetable ( stid, grademath, gradeen, gradec )
VALUES
	( '000001', '84', '86', '72' ),
	( '000011', '15', '45', '100' ),
	( '000102', '30.5', '74', '99' )