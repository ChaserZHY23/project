# 基于 C++ 的博客系统

1. 简单的Web服务器设计能力
2. C/C++ 操作 MySQL 数据库
3. 数据库设计
4. Restful 风格 API
5. json 和 jsoncpp 的使用
6. 强化 HTTP 协议的理解
7. cpp-httplib 的使用和原理
8. 正则表达式
9. Postman 工具的使用
10. boost 的使用
11. 前端页面的开发方法和技巧(免费模板 + bootstrap + Vue.js)

## 整体架构

**博客服务器**

1. 对博客的增删改查管理能力

2. 对标签的增删查改能力

**博客客户端**

1. 博客标题列表页面
2. 博客内容展示页面
3. 博客管理页面
4. 博客内容编辑页面

**关于数据存储和交互**

1. 服务器存储 markdown 格式的数据
2. 前端通过 editor.md 这个工具将markdown的文档内容提交给服务器, 或者解析服务器返回的 markdown 作为前端页面内容. 

## 数据库设计

### 创建数据库

```sql
create database if not exists blog_system;
use blog_system;
```

### 创建博客表

```sql
drop table if exists `blog_table`
create table `blog_table`(blog_id int not null primary key auto_increment,
                          title varchar(50), 
                          content text, 
                          tag_id int, 
                          create_time varchar(50))
```

### 创建标签表

```sql
drop table if exists `tag_table`
create table `tag_table`(tag_id int not null primary key auto_increment,
						 tag_name varchar(50))
```

### 使用 MySQL C API 操作数据库

#### 插入数据库

```c++

#include <cstdio>
#include <cstdlib>
#include <mysql/mysql.h>

int main() {
  MYSQL* connect_fd = mysql_init(NULL);
  if (mysql_real_connect(connect_fd, "127.0.0.1", "root", "",
											  "blog_system", 3306, NULL, 0) == NULL) {
    printf("连接失败! %s\n", mysql_error(connect_fd));
    return 1;
  }
  // 3. 设置编码格式
  mysql_set_character_set(connect_fd, "utf8");
  // 4. 拼装 SQL 语句
	char sql[1024 * 4] = {0};
  char title[] = "立一个 flag";
  char content[] = "我要拿 30w 年薪";
  int tag_id = 2;
  char datetime[] = "2019/05/14 12:00";
	sprintf(sql, "insert into blog_table values(null, '%s', '%s', %d, '%s')",
      title, content, tag_id, datetime);
  // 5. 执行 SQL 语句
  int ret = mysql_query(connect_fd, sql);
  if (ret < 0) {
    printf("执行 sql 失败! %s\n", mysql_error(connect_fd));
    return 1;
  }
  // 6. 关闭句柄
  mysql_close(connect_fd);
  printf("执行成功!\n");
  return 0;
}
```

#### 查找数据库

mysql_select.cc

```c++
#include <cstdio>
#include <cstdlib>
#include <mysql/mysql.h>

int main() {
  MYSQL* connect_fd = mysql_init(NULL);
  if (mysql_real_connect(connect_fd, "127.0.0.1", "root", "",
											  "blog_system", 3306, NULL, 0) == NULL) {
    printf("连接失败! %s\n", mysql_error(connect_fd));
    return 1;
  }
  mysql_set_character_set(connect_fd, "utf8");
	char sql[1024 * 4] = {0};
	sprintf(sql, "select * from blog_table")
  int ret = mysql_query(connect_fd, sql);
  if (ret < 0) {
    printf("执行 sql 失败! %s\n", mysql_error(connect_fd));
    return 1;
  }
  MYSQL_RES* result = mysql_store_result(connect_fd);
  if (result == NULL) {
    printf("获取结果失败! %s\n", mysql_error(connect_fd));
    return 1;
  }
  int rows = mysql_num_rows(result);
  int fields = mysql_num_fields(result);
  printf("rows: %d, fields: %d\n", rows, fields);
  for (int i = 0; i < rows; ++i) {
    MYSQL_ROW row = mysql_fetch_row(result);
    for (int j = 0; j < fields; ++j) {
      printf("%s\t", row[j]);
    }
    printf("\n");
  }
  mysql_free_result(result);
  mysql_close(connect_fd);
  printf("执行成功!\n");
  return 0;
}
```

## 服务器 API 设计

### 博客管理 API 设计

#### 新增博客

```json
请求:
POST /blog
{
    "title": "我的第一篇博客",
    "content": "博客的 markdown 格式内容",
    "tag_id": 1,
    "create_time": "2019/05/14 12:00",
}

响应:
HTTP/1.1 200 OK
{
	"ok": true,
}
```

#### 获取所有博客标题

```json
请求(使用 tag_id 参数筛选指定标签下的博客):
GET /blog?tag_id=1

响应: 
HTTP/1.1 200 OK
[
	{
		"blog_id": 1,
        "blog_url": "/blog/1",
		"title": "我的第一篇博客",
        "tag_id": 1,
        "create_time": "2019/05/14 12:00"
	},
	{
		"blog_id": 2,
        "blog_url": "/blog/2",
		"title": "C 语言的类型",
        "tag_id": 1,
        "create_time": "2019/05/14 12:00"
	}
]
```

#### 删除博客

```json
请求:
DELETE /blog/:blog_id

响应:
HTTP/1.1 200 OK
{
	"ok": true,
}
```

#### 修改博客

```json
请求:
PUT /blog/:blog_id
{
    "title": "我的第一篇博客",
    "content": "博客的 markdown 格式内容",
    "tag_id": 1
}

响应:
HTTP/1.1 200 OK
{
	"ok": true,
}
```
#### 获取博客详细内容

```json
请求:
GET /blog/:blog_id

响应:
HTTP/1.1 200 OK
{
	"blog_id": 1,
	"title": "我的第一篇博客",
	"content": "博客的 markdown 格式内容",
    "tag_id": 1
}
```

### 标签管理 API 设计

#### 新增标签

```json
请求:
POST /tag
{
	"tag_name": "C 语言",
}

响应:
HTTP/1.1 200 OK
{
	"ok": true,
}
```

#### 删除标签

```json
请求:
DELETE /tag/:tag_id

响应:
HTTP/1.1 200 OK
{
	"ok": true,
}
```

#### 获取所有标签

```json
请求:
GET /tag

响应:
HTTP/1.1 200 OK
[
    {
        "tag_id": 1,
        "tag_name": "C语言"
    },
    {
        "tag_id": 2,
        "tag_name": "数据结构"
    }
]
```

## 客户端设计

### 博客标题列表页面

显示一共有哪些博客

### 博客内容展示页面

点击某个博客标题, 进入内容页, 显示博客内容

### 博客管理页面

对博客进行增删

### 博客内容编辑页面

编辑修改博客内容

## 服务器端实现

### 数据库操作整体结构

db.hpp

```c++
namespace blog_system {

static MYSQL* MySQLInit() {
  MYSQL* connect_fd = mysql_init(NULL);
  if (mysql_real_connect(connect_fd, "127.0.0.1", "root", "",
											  "blog_system", 3306, NULL, 0) == NULL) {
    printf("连接失败! %s\n", mysql_error(connect_fd));
    return NULL;
  }
  mysql_set_character_set(connect_fd, "utf8");
  return connect_fd;
}

static void MySQLRelease(MYSQL* mysql) {
  mysql_close(mysql);
}

class BlogTable {
public:
  BlogTable(MYSQL* mysql) : mysql_(mysql) {  }

  bool Insert(const Json::Value& blog) {
    
  }

  bool SelectAll(Json::Value* blogs, const std::string& tag_id = "") {
    
  }

  bool SelectOne(int32_t blog_id, Json::Value* blog) {
    
  }

  bool Update(const Json::Value& blog) {
    
  }

  bool Delete(int blog_id) {
   
  }
private:
  MYSQL* mysql_;
};

class TagTable {
public:
  TagTable(MYSQL* mysql) : mysql_(mysql) {  }

  bool SelectAll(Json::Value* tags) {
   
  }

  bool Insert(const Json::Value& tag) {

  }

  bool Delete(int tag_id) {

  }
private:
  MYSQL* mysql_;
};
} 
```

#### 使用 Json 作为参数

json 出自 JavaScript, 是一种非常方便的键值对数据组织格式, 目前被业界广泛使用. 

C++ 中可以使用 jsoncpp 这个库来解析和构造 json 数据

```
yum install jsoncpp-devel
```

#### 实现插入博客

```c++
  bool Insert(const Json::Value& blog) {
    const std::string& content = blog["content"].asString();
    std::unique_ptr<char> content_escape(new char[content.size() * 2 + 1]);
    mysql_real_escape_string(mysql_, content_escape.get(), content.c_str(), content.size());
    std::unique_ptr<char> sql(new char[content.size() * 2 + 4096]);
    sprintf(sql.get(), "insert into blog_table values(null, '%s', '%s', %d,'%s')",
        blog["title"].asCString(), content_escape.get(),
        blog["tag_id"].asInt(), blog["create_time"].asCString());
    int ret = mysql_query(mysql_, sql.get());
    if (ret != 0) {
      printf("执行 sql 失败! sql=%s, %s\n", sql.get(), mysql_error(mysql_));
      return false;
    }
    return true;
  }
```

#### 实现查询所有博客

```c++
  bool SelectAll(Json::Value* blogs, const std::string& tag_id = "") {
    char sql[1024 * 4] = {0};
    if (tag_id.empty()) {
      sprintf(sql, "select blog_id, title, tag_id, create_time from blog_table");
    } else {
      sprintf(sql, "select blog_id, title, tag_id, create_time\
          from blog_table where tag_id = '%s'", tag_id.c_str());
    }
    int ret = mysql_query(mysql_, sql);
    if (ret != 0) {
      printf("执行 sql 失败! %s\n", mysql_error(mysql_));
      return false;
    }
    MYSQL_RES* result = mysql_store_result(mysql_);
    if (result == NULL) {
      printf("获取结果失败! %s\n", mysql_error(mysql_));
      return false;
    }
    int rows = mysql_num_rows(result);
    for (int i = 0; i < rows; ++i) {
      MYSQL_ROW row = mysql_fetch_row(result);
      Json::Value blog;
      blog["blog_id"] = atoi(row[0]);
      blog["title"] = row[1];
      blog["tag_id"] = atoi(row[2]);
      blog["create_time"] = row[3];
      // 遍历结果依次加入到 dishes 中
      blogs->append(blog);
    }
    return true;
  }
```

#### 实现查询单个博客

```c++
  bool SelectOne(int32_t blog_id, Json::Value* blog) {
    char sql[1024 * 4] = {0};
    sprintf(sql, "select * from blog_table where blog_id = %d", blog_id);
    int ret = mysql_query(mysql_, sql);
    if (ret != 0) {
      printf("执行 sql 失败! %s\n", mysql_error(mysql_));
      return false;
    }
    MYSQL_RES* result = mysql_store_result(mysql_);
    if (result == NULL) {
      printf("获取结果失败! %s\n", mysql_error(mysql_));
      return false;
    }
    int rows = mysql_num_rows(result);
    if (rows != 1) {
      printf("查找结果不为 1 条. rows = %d!\n", rows);
      return false;
    }
    MYSQL_ROW row = mysql_fetch_row(result);
    (*blog)["blog_id"] = atoi(row[0]);
    (*blog)["title"] = row[1];
    (*blog)["content"] = row[2];
    (*blog)["tag_id"] = atoi(row[3]);
    (*blog)["create_time"] = row[4];
    return true;
  }
```

#### 实现更新博客

```c++
  bool Update(const Json::Value& blog) {
    const std::string& content = blog["content"].asString();
    std::unique_ptr<char> content_escape(new char[content.size() * 2 + 1]);
    mysql_real_escape_string(mysql_, content_escape.get(), content.c_str(), content.size());
    std::unique_ptr<char> sql(new char[content.size() * 2 + 4096]);
    sprintf(sql.get(), "update blog_table SET title='%s', content='%s',\
        tag_id=%d where blog_id=%d",
        blog["title"].asCString(),
        content_escape.get(),
        blog["tag_id"].asInt(),
        blog["blog_id"].asInt());

    
    int ret = mysql_query(mysql_, sql.get());
    if (ret != 0) {
      printf("执行 sql 失败! sql=%s, %s\n", sql.get(), mysql_error(mysql_));
      return false;
    }
    return true;
  }
```

#### 实现删除博客

```c++
  bool Delete(int blog_id) {
    char sql[1024 * 4] = {0};
    sprintf(sql, "delete from blog_table where blog_id=%d", blog_id);
    int ret = mysql_query(mysql_, sql);
    if (ret != 0) {
      printf("执行 sql 失败! sql=%s, %s\n", sql, mysql_error(mysql_));
      return false;
    }
    return true;
  }
```

#### 实现新增标签

```c++
  bool Insert(const Json::Value& tag) {
    char sql[1024 * 4] = {0};
    sprintf(sql, "insert into tag_table values(null, '%s')",
        tag["tag_name"].asCString());
    int ret = mysql_query(mysql_, sql);
    if (ret != 0) {
      printf("执行 sql 失败! sql=%s, %s\n", sql, mysql_error(mysql_));
      return false;
    }
    return true;
  }
```

#### 实现删除标签

```c++
  bool Delete(int tag_id) {
    char sql[1024 * 4] = {0};
    sprintf(sql, "delete from tag_table where tag_id = %d", tag_id);
    int ret = mysql_query(mysql_, sql);
    if (ret != 0) {
      printf("执行 sql 失败! sql=%s, %s\n", sql, mysql_error(mysql_));
      return false;
    }
    return true;
  }
```

#### 实现查看所有标签

```c++
  bool SelectAll(Json::Value* tags) {
    char sql[1024 * 4] = {0};
    sprintf(sql, "select * from tag_table");
    int ret = mysql_query(mysql_, sql);
    if (ret != 0) {
      printf("执行 sql 失败! %s\n", mysql_error(mysql_));
      return false;
    }
    MYSQL_RES* result = mysql_store_result(mysql_);
    if (result == NULL) {
      printf("获取结果失败! %s\n", mysql_error(mysql_));
      return false;
    }
    int rows = mysql_num_rows(result);
    for (int i = 0; i < rows; ++i) {
      MYSQL_ROW row = mysql_fetch_row(result);
      Json::Value tag;
      tag["tag_id"] = atoi(row[0]);  
      tag["tag_name"] = row[1];
      tags->append(tag);
    }
    return true;
  }
```

### 测试数据库操作



db_test.cc

```c++
void TestBlogTable() {
  bool ret = false;
  // 更友好的格式化显示 Json
  Json::StyledWriter writer;
  MYSQL* mysql = MySQLInit();

  Json::Value blog;
  blog["title"] = "初识 C 语言";
  std::string content;
  FileUtil::ReadFile("./test_data/1.md", &content);
  blog["content"] = content;
  blog["tag_id"] = 1;
  blog["create_time"] = "2019/05/14 12:00";

  std::cout << "==============测试插入=====================" << std::endl;
  BlogTable blog_table(mysql);
  ret = blog_table.Insert(blog);
  std::cout << "Insert: " << ret << std::endl;

  std::cout << "==============测试查找=====================" << std::endl;
  Json::Value blogs;
  ret = blog_table.SelectAll(&blogs);
  std::cout << "SelectAll: " << ret << std::endl
            << writer.write(blogs) << std::endl;

  std::cout << "==============测试更新=====================" << std::endl;
  blog["blog_id"] = 1;
  blog["title"] = "测试更新博客";
  blog["content"] = content;
  blog["tag_id"] = 2;
  blog["create_time"] = "2019/05/20 12:00";
  Json::Value blog_out;
  ret = blog_table.Update(blog);
  std::cout << "Update: " << ret << std::endl;
  ret = blog_table.SelectOne(1, &blog_out);
  std::cout << "SelectOne: " << ret << std::endl
            << writer.write(blog_out) << std::endl;

  std::cout << "==============测试删除=====================" << std::endl;
  int blog_id = 6;
  ret = blog_table.Delete(blog_id);
  std::cout << "Delete: " << ret << std::endl;

  MySQLRelease(mysql);
}

void TestTagTable() {
  bool ret = false;
  Json::StyledWriter writer;
  MYSQL* mysql = MySQLInit();
  TagTable tag_table(mysql);

  std::cout << "==============测试插入=====================" << std::endl;
  Json::Value tag;
  tag["tag_name"] = "Java";
  ret = tag_table.Insert(tag);
  std::cout << "Insert: " << ret << std::endl;

  std::cout << "==============测试查看=====================" << std::endl;
  Json::Value tags;
  ret = tag_table.SelectAll(&tags);
  std::cout << "SelectAll: " << ret << std::endl
            << writer.write(tags) << std::endl;

  std::cout << "==============测试删除状态=====================" << std::endl;
  ret = tag_table.Delete(5);
  std::cout << "ChangeState ret:" << ret << std::endl;

  MySQLRelease(mysql);
}

int main() {
  // TestBlogTable();
  TestTagTable();
  return 0;
}
```

### 实现服务器接口

#### 使用 httplib 搭建服务器框架

使用 cpp-httplib 实现一个 hello world

```c++
#include "httplib.h"

int main() {
  using namespace httplib;
  Server server;
  server.Get("/", [](const Request& req, Response& resp) {
    (void)req;
    resp.set_content("<html>hello</html>", "text/html");
  });  
  server.set_base_dir("./wwwroot");
  server.listen("0.0.0.0", 9092);
  return 0;
}
```

编译选项

```
g++ main.cc -lpthread -std=c++11
```

#### 搭建服务器整体框架

blog_server.cc

```c++
MYSQL* mysql = NULL;

int main() {
  using namespace httplib; 
  using namespace blog_system;
  Server server;
  
  // 1. 数据库客户端初始化和释放
  mysql = MySQLInit();
  signal(SIGINT, [](int) { MySQLRelease(mysql); exit(0);});
  BlogTable blog_table(mysql);
  TagTable tag_table(mysql);

  server.Post("/blog", [&blog_table](const Request& req, Response& resp) {
    
  });
  server.Get("/blog", [&blog_table](const Request& req, Response& resp) {
   
  });

  server.Get(R"(/blog/(\d+))", [&blog_table](const Request& req, Response& resp) {
    
  });
  server.Delete(R"(/blog/(\d+))", [&blog_table](const Request& req, Response& resp) {
   
  });

  server.Put(R"(/blog/(\d+))", [&blog_table](const Request& req, Response& resp) {
    
  });

  server.Post("/tag", [&tag_table](const Request& req, Response& resp) {
    
  });


  server.Delete(R"(/tag/(\d+))", [&tag_table](const Request& req, Response& resp) {
    
  });


  server.Get("/tag", [&tag_table](const Request& req, Response& resp) {
    
  });


  server.set_base_dir("./wwwroot");

  server.listen("0.0.0.0", 9093);
  return 0;
}
```

#### 实现新增博客

```c++
  server.Post("/blog", [&blog_table](const Request& req, Response& resp) {
    LOG(INFO) << "新增博客: " << req.body << std::endl;
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value req_json;
    Json::Value resp_json;
    bool ret = reader.parse(req.body, req_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "parse Request failed!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    if (req_json["title"].empty() || req_json["content"].empty()
        || req_json["tag_id"].empty() || req_json["create_time"].empty()) {
      resp_json["ok"] = false;
      resp_json["reason"] = "Request fields error!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    ret = blog_table.Insert(req_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "Insert failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp_json["ok"] = true;
    resp.set_content(writer.write(resp_json), "application/json");
    return;
  });
```

#### 实现查看所有博客

```c++

  server.Get("/blog", [&blog_table](const Request& req, Response& resp) {
    LOG(INFO) << "查看所有博客" << std::endl;
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value resp_json;
    const std::string& tag_id = req.get_param_value("tag_id");
    Json::Value blogs;
    bool ret = blog_table.SelectAll(&blogs, tag_id);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "SelectAll failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp.set_content(writer.write(blogs), "application/json");
    return;
  });
```

#### 实现查看指定博客内容

```c++

  server.Get(R"(/blog/(\d+))", [&blog_table](const Request& req, Response& resp) {
    Json::Value resp_json;
    Json::FastWriter writer;
    int blog_id = std::stoi(req.matches[1]);
    LOG(INFO) << "查看指定博客: " << blog_id << std::endl;
    bool ret = blog_table.SelectOne(blog_id, &resp_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "SelectOne failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp_json["ok"] = true;
    resp.set_content(writer.write(resp_json), "application/json");
    return;
  });
```

#### 实现删除博客

```c++
 
  server.Delete(R"(/blog/(\d+))", [&blog_table](const Request& req, Response& resp) {
    Json::Value resp_json;
    Json::FastWriter writer;
    int blog_id = std::stoi(req.matches[1]);
    LOG(INFO) << "删除指定博客: " << blog_id << std::endl;
    bool ret = blog_table.Delete(blog_id);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "Delete failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp_json["ok"] = true;
    resp.set_content(writer.write(resp_json), "application/json");
    return;
  });
```

#### 实现修改博客

```c++

  server.Put(R"(/blog/(\d+))", [&blog_table](const Request& req, Response& resp) {
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value req_json;
    Json::Value resp_json;
    int blog_id = std::stoi(req.matches[1]);
    LOG(INFO) << "修改博客 " << blog_id << "|" << req.body << std::endl;
    bool ret = reader.parse(req.body, req_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "parse Request failed!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    req_json["blog_id"] = blog_id;
    if (req_json["title"].empty() || req_json["content"].empty()
        || req_json["tag_id"].empty()) {
      resp_json["ok"] = false;
      resp_json["reason"] = "Request has no name or price!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    ret = blog_table.Update(req_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "Update failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp_json["ok"] = true;
    resp.set_content(writer.write(resp_json), "application/json");
    return;
  });
```

#### 实现新增标签

```c++

  server.Post("/tag", [&tag_table](const Request& req, Response& resp) {
    LOG(INFO) << "新增订单: " << req.body << std::endl;
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value req_json;
    Json::Value resp_json;
    bool ret = reader.parse(req.body, req_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "parse Request failed!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    if (req_json["tag_name"].empty()) {
      resp_json["ok"] = false;
      resp_json["reason"] = "Request has no table_id or time or dish_ids!\n";
      resp.status = 400;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    ret = tag_table.Insert(req_json);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "TagTable Insert failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp_json["ok"] = true;
    resp.set_content(writer.write(resp_json), "application/json");
  });
```

#### 实现删除标签

```c++

  server.Delete(R"(/tag/(\d+))", [&tag_table](const Request& req, Response& resp) {
    Json::Value resp_json;
    Json::FastWriter writer;
    int tag_id = std::stoi(req.matches[1]);
    LOG(INFO) << "删除指定标签: " << tag_id << std::endl;
    bool ret = tag_table.Delete(tag_id);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "TagTable Insert failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp_json["ok"] = true;
    resp.set_content(writer.write(resp_json), "application/json");
    return;
  });
```

#### 实现获取所有标签

```c++

  server.Get("/tag", [&tag_table](const Request& req, Response& resp) {
    (void) req;
    LOG(INFO) << "查看所有订单" << std::endl;
    Json::Reader reader;
    Json::FastWriter writer;
    Json::Value resp_json;
    Json::Value tags;
    bool ret = tag_table.SelectAll(&tags);
    if (!ret) {
      resp_json["ok"] = false;
      resp_json["reason"] = "SelectAll failed!\n";
      resp.status = 500;
      resp.set_content(writer.write(resp_json), "application/json");
      return;
    }
    resp.set_content(writer.write(tags), "application/json");
    return;
  });
```

### 使用 Postman 测试接口

使用 Postman 构造请求测试即可. 

## 客户端实现

### 实现博客标题列表页面

#### 使用免费模板

使用 amaze ui 提供的免费模板

http://tpl.amazeui.org/

#### 基于免费模板进行修改

复制 lw-index.html 为 index.html, 并进行修改. 

#### 使用 Vue.js 

网页中需要动态交互的部分, 使用 JS 来实现. 但是原生的基于 Dom API 的交互方式比较麻烦, 因此 Vue.js 提供了更简单更方便的做法. 

Vue.js 官网: <https://cn.vuejs.org/v2/guide/>

参考官网引入 CDN, 并复制官方的 hello world 代码

在 data 中新增一个属性 author, 并在页面合适的位置绑定

```js
data: {
   author: '',
}
```

 

#### 构造 blogs 和 tags 数据并绑定到页面

数据参考 API 接口返回的数据格式

```javascript
    data: {
        author: '',
        blogs: [
            {
                "blog_id": 1,
                "title": "我的第一篇博客",
                "tag_id": 1,
                "create_time": "2019/05/14 12:00"
            },
            {
                "blog_id": 2,
                "title": "C 语言的类型",
                "tag_id": 1,
                "create_time": "2019/05/14 12:00"
            }
        ],
        tags: [
            {
                "tag_id": 1,
                "tag_name": "C语言"
            },
            {
                "tag_id": 2,
                "tag_name": "数据结构"
            }
        ]
    },
```

在页面合适的位置绑定数据. 

```html
<article class="am-g blog-entry-article" v-for="blog in blogs">
    <div class="am-u-lg-6 am-u-md-12 am-u-sm-12 blog-entry-text">
        <span><a href="" class="blog-color">{{blog.tag_id}} &nbsp;</a></span>
        <span> @汤老湿 &nbsp;</span>
        <span>{{blog.create_time}}</span>
        <!-- 注意, 此时 get_blog 函数还没实现呢!!! -->
        <h1><a v-on:click="get_blog(blog.blog_id)">{{blog.title}}</a></h1>
        <p>我是摘要信息</p>
        <p><a href="" class="blog-continue">continue reading</a></p>
    </div>
</article>
```

此时刷新网页, 应该就能看到和构造数据匹配的界面了. 

#### 实现展示标签名字

当前展示的只是标签 id, 需要根据 id 转为 标签名. 

在 methods 中添加一个方法

```javascript
    methods: {
        tag_id2name(tag_id) {
            // 注意, 要访问 tags 和 blogs 需要带 this
            for(var index in this.tags) {
                if (this.tags[index].tag_id == tag_id) {
                    return this.tags[index].tag_name;
                }
            }
            return null;
        },
    },
```

然后在需要用到标签 id 的位置调用函数获取标签名

```html
<span><a href="" class="blog-color">{{tag_id2name(blog.tag_id)}} &nbsp;</a></span>
```

#### 通过网络获取服务器上的 blogs 和 tags 数据

使用 JQuery 的 ajax 方法, 文档参见 <http://www.w3school.com.cn/jquery/ajax_ajax.asp>

**实现获取博客列表**

```javascript
get_blogs(tag_id) {
    var url = "blog";
    if (tag_id != null) {
        url = "/blog?tag_id=" + tag_id;
    }
    $.ajax({
        url: url,
        type: "get",
        context: this,
        success: function(data, status) {
            this.blogs = data
        }
    }) 
},
```

**实现获取标签列表**

要保证先获取到 tag 列表, 再获取博客列表. 思考一下为什么?

```javascript
init() {
    $.ajax({
        url: "/tag",
        type: "get",
        context: this,
        success: function(data, status) {
            this.tags = data;
            // 在获取到 tags 之后再获取 blogs, 防止时序上出现问题
            this.get_blogs();
        }
    });
},
```

在合适的位置调用 初始化 函数

```js
app.init()
```

#### 部署到服务器上进行测试

在 服务器 目录下创建 wwwroot 目录, 将客户端代码拷贝进去. 并且在服务器中 `set_base_dir` 来指定 http 服务器的根目录. 

之后通过浏览器访问, 如果页面显示不正确, 通过 chrome 控制台查看错误信息. 

#### 使用 cloak 优化显示

此时在网速较慢的情况下, 能够看到渲染前的插值表达式. 为了解决这个问题, 可以使用 Vue.js 提供的 cloak 功能

cloak 原意为 "披风" 能够把丑陋的插值表达式给遮盖住. 

```html
<style>
    [v-cloak] {
    	display: none;
    }
</style>
```

然后在需要用到差值表达式的标签上加上 v-cloak 属性即可

```html
<div class="am-u-md-8 am-u-sm-12" v-cloak>
```

### 实现博客内容展示页面

#### 新增 blog 对象

在 data 中新增一个 blog 对象

```javascript
blog: {
    title: "",
    content: "",
    blog_id: null,
    tag_id: null,           
},
```

并且将之前的博客列表使用 v-show 控制起来. 如果 blog_id 为 null, 则显示博客列表. 如果 blog_id 为非 null, 则显示 博客内容. 

#### 创建博客显示容器

```html
    <div class="am-u-md-8 am-u-sm-12" v-show="blog.blog_id != null">
        <article id="test-editormd-view">

        </article>
    </div
```

#### 介绍 Editor.md 的用法(参考附录)

#### 使用 Editor.md 将 markdown 转为 html

这个代码复制自 `editormd\examples\html-preview-markdown-to-html.html` 并稍加修改. 

先引入 Editor.md. 照着官方示例复制粘贴即可. 

```html
<!-- 引入 Editor.md 完成 markdown 的操作, 注意路径-->
<script src="/editor.md/lib/marked.min.js"></script>
<script src="/editor.md/lib/prettify.min.js"></script>
<script src="/editor.md/lib/raphael.min.js"></script>
<script src="/editor.md/lib/underscore.min.js"></script>
<script src="/editor.md/lib/sequence-diagram.min.js"></script>
<script src="/editor.md/lib/flowchart.min.js"></script>
<script src="/editor.md/lib/jquery.flowchart.min.js"></script>
<script src="/editor.md/editormd.js"></script>
```

编写点击博客标题的响应函数.

```js
get_blog(blog_id) {
    $.ajax({
        url: "/blog/" + blog_id,
        type: "get",
        context: this,
        async: false,
        success: function(data, status) {
            this.blog = data;
            // [注意!] 需要先清理上次的结果, 再填充新结果
            $('#test-editormd-view').empty();
            testEditormdView = editormd.markdownToHTML("test-editormd-view", {
                markdown        : this.blog.content ,//+ "\r\n" + $("#append-test").text(),
                //htmlDecode      : true,       // 开启 HTML 标签解析，为了安全性，默认不开启
                htmlDecode      : "style,script,iframe",  // you can filter tags decode
                //toc             : false,
                tocm            : true,    // Using [TOCM]
                //tocContainer    : "#custom-toc-container", // 自定义 ToC 容器层
                //gfm             : false,
                //tocDropdown     : true,
                // markdownSourceCode : true, // 是否保留 Markdown 源码，即是否删除保存源码的 Textarea 标签
                emoji           : true,
                taskList        : true,
                tex             : true,  // 默认不解析
                flowChart       : true,  // 默认不解析
                sequenceDiagram : true,  // 默认不解析
            });
        }
    });
}
```

此时就可以验证看博客内容是否展示正确了. 注意观察控制台中的错误日志. 

#### 制作一个返回列表的按钮

```html
    <div class="am-u-sm-2">
        <button type="button" class="am-btn am-btn-default am-round" v-on:click="main_page()">主页</button>
    </div>
```

实现响应函数

```js
main_page() {
    this.blog.blog_id = null
    this.blog.tag_id = null
    this.blog.title = ""
    this.blog.content = ""
}
```

### 实现博客管理页面

复制 index.html 为 admin.html, 并修改标题. 

**注意!!!** 博客的管理页面和之前的展示页面不再共用同一份页面了. 

#### 引入 status 状态

为了更好的管理页面状态变换, 引入一个 status 变量, 取值为

```
blog_list: 表示展示博客列表状态
blog_edit: 表示编辑博客状态
```

初始化设定为 `blog_list` 状态

此时需要调整 `main_page` 函数

```js
main_page() {
    this.status = 'blog_list';
},
```

#### 实现删除博客功能

每个博客标题下方新增删除按钮

```html
<button type="button" class="am-btn am-btn-danger am-round" v-on:click="delete_blog(blog.blog_id)">删除</button>
```

新增删除方法

```js
delete_blog(blog_id) {
    $.ajax({
        url: "/blog/" + blog_id,
        type: "delete",
        context: this,
        success: function(data, status) {
            this.status = 'blog_list';
            this.get_blogs(); // 重新从服务器获取数据
            alert("删除成功!");
        }
    });
}
```

#### 实现编辑博客功能1

修改 博客标题 点击事件的响应

```html
<h1><a v-on:click="edit_blog(blog)">{{blog.title}}</a></h1>
```

新增 edit_blog 方法

```js
edit_blog(blog_id) {
    this.blog = {}
    $.ajax({
        url: "/blog/" + blog_id,
        type: "get",
        context: this,
        success: function(data, status) {
            this.blog = data;
            editor = editormd("test-editor", {
                width  : "100%",
                height : "740px",
                path: "editor.md/lib/"
            });
            this.status = 'blog_edit'
        }
    });
},
```

新增一个编辑区(替换掉原有的展示博客内容区域)

```html
<div class="am-u-md-12 am-u-sm-12" v-show="status == 'blog_edit'" v-cloak>
    <div id="test-editor">
        <textarea>{{blog.content}}</textarea>
    </div>
</div>
```

设定侧边栏也能自动隐藏

```html
<div class="am-u-md-4 am-u-sm-12 blog-sidebar" v-show="status == 'blog_list'">
```

**注意!!!!! **, 此时页面中需要引入 Editor.md 的对应的 CSS, 否则编辑框显示不正确. 

```html
<link rel="stylesheet" href="editor.md/css/editormd.min.css" />
```

此时就可以验证博客是否能进行编辑了

#### 实现编辑博客功能2

再新增一个提交按钮

```html
<button type="button" class="am-btn am-btn-default am-round" v-show="status == 'blog_edit'" v-on:click="update_blog()" v-cloak>提交</button>
```

实现 `update_blog` 函数

```js
update_blog() {
    var content = editor.getMarkdown()
    var body = {
        title: this.blog.title,
        content: content,
        tag_id: this.blog.tag_id,
    }
    $.ajax({
        url: "/blog/" + this.blog.blog_id,
        type: "put",
        contentType: "application/json;charset=utf-8",
        data: JSON.stringify(body),
        context: this,
        success: function(data, status) {
            this.get_blogs()
            alert("提交成功!");
            this.status = 'blog_list'
        }
    });
}
```

验证能否正确修改博客. 





