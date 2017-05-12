#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_QUERY 512
#define HOSTNAME  "dursley.socs.uoguelph.ca"

#define USERNAME 
#define PASSWORD  
#define DATABASE  

void error(char *msg, MYSQL *mysql){
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(1);
}

/*
	clear the contents of an array of char's
*/
void clrstr(char *buf){
	buf[0] = '\0';
}

int main(int argc, char * argv[])
{
	char * temp = malloc(sizeof(char)*1024);
	MYSQL mysql;
	MYSQL_RES *res;
	MYSQL_ROW row;
	MYSQL_FIELD *field;
	int i;

	mysql_init(&mysql);
	mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
	if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,DATABASE, 0, NULL, 0)) 
	{
		free(temp);
        mysql_close(&mysql);
    	mysql_library_end();
	    error("Could not connect to host.",&mysql);
	}
	char query[MAX_QUERY];
	clrstr(query);

    if (strcmp(argv[1], "-clear") == 0)
    {
        strcpy(query, "DELETE FROM html");
        if (mysql_query(&mysql, query))
        {
        	free(temp);
    		mysql_close(&mysql);
    		mysql_library_end();
        	error("fail delete",&mysql);
        }
        clrstr(query);
    }
    else if (strcmp(argv[1], "-reset") == 0)
    {
    	strcpy(query, "drop table html");
    	if(mysql_query(&mysql,query))
    	{
    		free(temp);
    		mysql_close(&mysql);
    		mysql_library_end();
    		error("fail drop",&mysql);
    	}
    	clrstr(query);
    }
    else if (strcmp(argv[1], "-show") == 0)
    {
    	strcpy(query, "select name_txt, length_num, time_date from html");
		if(mysql_query(&mysql, query))
		{
			free(temp);
    		mysql_close(&mysql);
    		mysql_library_end();
			error("fail select",&mysql);
		}
		if (!(res = mysql_store_result(&mysql)))
		{
			free(temp);
    		mysql_close(&mysql);
    		mysql_library_end();
			error("fail store",&mysql);
		}
		while ((row = mysql_fetch_row(res))) 
		{
			for (i=0; i < mysql_num_fields(res); i++)
			{
				printf("%s ", row[i]);
			}
			printf("\n");
		}
		mysql_free_result(res);
    }
    else if (strcmp(argv[1], "-help") == 0)
    {
    	printf("-clear flag: the program removes all of the rows from the tables in the database.\n");
    	printf("-reset flag: the program deletes the tables from the database.\n");
    	printf("-show flag: the program prints out the name, length, and date for all files stored in the database.\n");
    	printf("-help flag: prints out a usage message\n");
    }
    else if (strcmp(argv[1], "-select") == 0)
    {
        strcpy(query, "select name_txt from html");
        if(mysql_query(&mysql, query))
        {
            free(temp);
            mysql_close(&mysql);
            mysql_library_end();
            error("fail select",&mysql);
        }
        if (!(res = mysql_store_result(&mysql)))
        {
            free(temp);
            mysql_close(&mysql);
            mysql_library_end();
            error("fail store",&mysql);
        }
        while ((row = mysql_fetch_row(res))) 
        {
            for (i=0; i < mysql_num_fields(res); i++)
            {
                printf("%s ", row[i]);
            }
            printf("\n");
        }
        mysql_free_result(res);
    }
    else if (strcmp(argv[1], "-data") == 0)
    {
        strcpy(query, "select html_txt from html where name_txt = '");
        strcat(query, argv[2]);
        strcat(query, "'");
        if(mysql_query(&mysql, query))
        {
            free(temp);
            mysql_close(&mysql);
            mysql_library_end();
            error("fail select",&mysql);
        }
        if (!(res = mysql_store_result(&mysql)))
        {
            free(temp);
            mysql_close(&mysql);
            mysql_library_end();
            error("fail store",&mysql);
        }
        while ((row = mysql_fetch_row(res))) 
        {
            for (i=0; i < mysql_num_fields(res); i++)
            {
                printf("%s ", row[i]);
            }
            printf("\n");
        }
        mysql_free_result(res);
    }
    free(temp);
    mysql_close(&mysql);
    mysql_library_end();
	return 0;
}
