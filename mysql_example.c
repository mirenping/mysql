#include<stdio.h>
#include<stdlib.h>
#include<mysql.h>

int main()
{
   //test file		
    int i,j=0;
    MYSQL_ROW row;
    //初始化mysql句柄
    MYSQL *mysql=mysql_init(NULL);
    //连接数据库
    mysql=mysql_real_connect(mysql,"192.168.19.155","root_mi","123","mi",3306,NULL,0);
    if(NULL==mysql)
    {
        perror("connect error\n");
        return -1;
    }
    //设置编码格式
    mysql_query(mysql,"set names utf8");
    //执行查询语句
    if(mysql_query(mysql,"select * from test"))
    {
        perror("query error");
        return -2;
    }
    //检索结果集
    MYSQL_RES *result=mysql_store_result(mysql);
    //获取结果集中的字段数
    unsigned int count=mysql_num_fields(result);
    //获得表头字段名
    for(i=0;i<count;++i)
    {
        MYSQL_FIELD *field=mysql_fetch_field(result);
        printf("%s\t",field->name);
    }
    printf("\n");
    //获取结果集中行的数据
    while(row=mysql_fetch_row(result))
    {
        for(j=0;j<count;++j)
        {
            printf("%s\t",row[j]);
        }
        printf("\n");
    }
    //释放结果集
    mysql_free_result(result);
    //关闭mysql连接
    mysql_close(mysql);
    return 0;

}
