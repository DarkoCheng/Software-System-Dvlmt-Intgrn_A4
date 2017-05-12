/*

*/
#include "listio.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <mysql/mysql.h>
#include <sys/stat.h>

struct returnStruct *buildHeader()
{
	struct returnStruct * temp;
	temp = malloc(sizeof(struct returnStruct));
	if (temp == NULL)
	{
		temp->value = FAILURE;
		temp->header = NULL;
        return temp;
	}
	else
	{
		memset(temp, 0, sizeof(struct returnStruct));
		temp->header = malloc(sizeof(struct dataHeader));
		if (temp->header == NULL)
		{
            temp->value = FAILURE;
		    temp->header = NULL;
            return temp;
		}
		memset(temp->header, 0, sizeof(struct dataHeader));
        temp->value = SUCCESS;
	    return temp;
	}
}

int setName(struct dataHeader *header, char *name)
{
	if (name == NULL)
	{
        return FAILURE;
	}
	header->name = malloc(strlen(name)+1);
	if (header->name == NULL)
	{
        return FAILURE;
	}
	memset(header->name, 0, strlen(name)+1);
    strcpy(header->name, name);

    return SUCCESS;
}

char * getName(struct dataHeader *header)
{
    char * temp;
    if (header->name == NULL)
    {
        return NULL;
    }
    temp = header->name;

    return temp;

}

int getLength(struct dataHeader *header)
{
	int a;
	if (header->length == 0)
	{
        return FAILURE;
	}
	a = header->length;

	return a;
}

int addString(struct dataHeader *header, char *str)
{
	if (str == NULL)
	{
         return FAILURE;
	}
	struct dataString * newString, *temp;
	newString = malloc(sizeof(struct dataString));
	if (newString == NULL)
	{
        return FAILURE;
	}
	newString->string = malloc((strlen(str)+1));
	if (newString->string == NULL)
	{
        return FAILURE;
	}
	memset(newString->string, 0, strlen(str)+1);
	newString->next = NULL;
    strcpy(newString->string, str);
	if (header->next == NULL)
	{
        header->next = newString;
        header->length = header->length + strlen(str);
	}
	else
	{
		temp = header->next;
		while(temp->next != NULL)
		{
            temp = temp->next;
		}
		temp->next = newString;
		header->length = header->length + strlen(str);
	}

	return SUCCESS;
}

int printString(struct dataHeader *header)
{
	struct dataString * temp;
	if (header == NULL)
	{
        return FAILURE;
	}
	temp = header->next;
	while(temp != NULL)
	{
        //printf("%s\n", temp->string);
        temp = temp->next; 
	}

	return SUCCESS;
}

void deslP(struct dataHeader * header)
{
    struct dataString * temp;
    temp = header->next;
    char * stringTemp;
    char * stringTemp1;
    stringTemp1 = malloc(sizeof(char)*10240000);
    stringTemp =  malloc(sizeof(char)*10240000);
    memset(stringTemp, 0, sizeof(char)*10240000);
    //int i = 0;
    int a = 0;
    int b = 0;
    while (temp != NULL)
    {
    	strcpy(stringTemp, temp->string);
    	b = strlen(stringTemp)-1;

    	while (1)
    	{
    		if (b < 0)
    		{
    			b = 3;
    			break;
    		}
	    	if (memcmp(stringTemp+b, "\t", 1) == 0)
	    	{
	            b = b - 1;
	    	}
	    	else if (memcmp(stringTemp+b, " ", 1) == 0)
	    	{
	            b = b - 1;
	    	}
	    	else if (memcmp(stringTemp+b-3, "<BR>", 4) == 0)
	    	{
	            b = b - 4;
	    	}
	    	else
	    	{
	    		break;
	    	}
	    }
	   // printf("b: %d\n", b);
	    if (memcmp(stringTemp+b-2, "<P>", 3) == 0)
	    {
	    	if (temp->next == NULL)
	    	{
	    	    free(stringTemp);
    			free(stringTemp1);
	    		return;
	    	}
            strcpy(stringTemp1, temp->next->string);
            while(1)
            {
            	if (memcmp(stringTemp1+a, "\t", 1) == 0)
		    	{
		            a = a + 1;
		    	}
		    	else if (memcmp(stringTemp1+a, " ", 1) == 0)
		    	{
		            a = a + 1;
		    	}
		    	else if (memcmp(stringTemp1+a, "<BR>", 4) == 0)
		    	{
		            a = a + 4;
		    	}
		    	else
		    	{
		    		break;
		    	}
            }
            if (memcmp(stringTemp1+a, "<P>", 3) == 0)
            {
                memset(temp->string, 0, strlen(temp->string)+1);
                memcpy(temp->string, stringTemp, b-2);
                memset(temp->next->string, 0, strlen(temp->next->string)+1);
                memcpy(temp->next->string, stringTemp1+a, strlen(stringTemp1)-a+1);
            }
	    }
	    a = 0;
	    b = 0;
    	temp = temp->next;
    	memset(stringTemp, 0 , sizeof(char)*10240000);
    	memset(stringTemp1, 0,  sizeof(char)*10240000);
    }
    free(stringTemp);
    free(stringTemp1);
    return;
}

void error(char *msg, MYSQL *mysql)
{
	printf("%s\n%s\n",msg,mysql_error(mysql));
	exit(1);
}

void clrstr(char *buf)
{
	buf[0] = '\0';
}

int processStrings(struct dataHeader *header, int d)
{
	header->length = 0;
	FILE *fp;
	struct dataString * tempList, * tempList2;
	if (header == NULL || header->next == NULL)
	{
        return FAILURE;
	}
	tempList = header->next;
	tempList2 = header->next;
	char * buffer;
    char* outSpace = malloc(sizeof(char)*10240000);
    if (outSpace == NULL)
    {
        return FAILURE;
    }
    char * outTab = malloc(sizeof(char)*10240000);
    if (outTab == NULL)
    {
        return FAILURE;
    }
    char * outP = malloc(sizeof(char)*10240000);
    if (outP == NULL)
    {
        return FAILURE;
    }
    char * outR = malloc(sizeof(char)*10240000);
    if (outR == NULL)
    {
        return FAILURE;
    }    
    char * outNewLine = malloc(sizeof(char)*10240000);
    if (outNewLine == NULL)
    {
        return FAILURE;
    }   
    memset(outR, 0, 10240000);
    memset(outP, 0, 10240000);
    memset(outNewLine, 0, 10240000);
    memset(outTab, 0, 10240000);
    memset(outSpace, 0, 10240000);
    int a = 0;
    int b = 0;
    int c = 0;

    
    while (tempList != NULL)
    {
    	buffer = tempList->string;
	    while (1)  // deal mutil spaces.
	    {
	    	if (buffer[a] == '\0')
	    	{
	    		outSpace[c] = '\0';
	    		break;
	    	}
	        else if (buffer[a] == ' ')
	        {
	        	/*
    				check if there are mutil spaces/
    				Same in rest of loops.
	        	*/
	            if (buffer[a+1] == ' ') 
	            {
	            	b = a+1;
	            	while (1)
	            	{
	            		if (buffer[b] != ' ')
	            		{
	            			a = b;
	            			outSpace[c] = ' ';
	            			c++;
	            			break;
	            		}
	            		b++;
	            	}
	            }
	            else
	            {
	            	outSpace[c] = buffer[a];
	            	a++;
	            	c++;
	            }
	        }
	        else
	        {
	        	outSpace[c] = buffer[a];
	        	c++;
	        	a++;
	        }
	    }
	    /*
        Everytime finish a loop need to reset the a,b,c var in order to do the next loop.
        Same in rest of loops.
         */
	    a = 0;
	    b = 0;
	    c = 0;
	    while(1)  // deal mutil <tab>
	    {
	    	if (outSpace[a] == '\0')
	    	{
	    		outTab[c] = '\0';
	    		break;
	    	}
	    	else if (outSpace[a] == '\t')
	    	{
	    		if (outSpace[a+1] == '\t')
	    		{
	    			b = a + 1;
	    			while (1)
	    			{
	    				if (outSpace[b] != '\t')
	    				{
    						a = b;
    						outTab[c] = '\t';
    						c++;
    						break; 
	    				}
	    				b++;
	    			}
	    		}
	    		else
	    		{
	    			outTab[c] = outSpace[a];
	    			c++;
	    			a++;
	    		}
	    	}
	    	else
	    	{
	    		outTab[c] = outSpace[a];
	        	c++;
	        	a++;
	    	}
	    }
	    a = 0;
	    b = 0;
	    c = 0;
	    while (1)   // deal mutil \n
	    {
	    	if (outTab[a] == '\0')
	    	{
	    		outP[c] = '\0';
	    		break;
	    	}
	    	else if (outTab[a] == '\n' || outTab[a] == '\r')
	    	{
	    		if (outTab[a+1] == '\n' || outTab[a+1] == '\r')
	    		{
	    			b = a + 1;
	    			while (1)
	    			{
	    				if (outTab[b] != '\n' && outTab[b] != '\r')
	    				{
	    					a = b;
	    					outP[c] = '<';
	    					outP[c+1] = 'P';
	    					outP[c+2] = '>';
	    					c = c + 3;
	    					break;
	    				}
	    				b++;
	    			}
	    		}
	    		else
	    		{
	    			outP[c] = outTab[a];
	    			c++;
	    			a++;
	    		}
	    	}
	    	else
	    	{
	    		outP[c] = outTab[a];
	    		a++;
	    		c++;
	    	}
	    }
	    a = 0;
	    b = 0;
	    c = 0;
	    while (1)  // deal mutil \r
	    {
	    	if (outP[a] == '\0')
	    	{
	    		outP[c] = '\0';
	    		break;
	    	}
	    	else if (outP[a] == '\r')
	    	{
	    		if (outP[a+1] == '\r')
	    		{
	    			b = a + 1;
	    			while (1)
	    			{
	    				if (outP[b] != '\r')
	    				{
	    					a = b;
	    					outR[c] = '<';
	    					outR[c+1] = 'P';
	    					outR[c+2] = '>';
	    					c = c + 3;
	    					break;
	    				}
	    				b++;
	    			}
	    		}
	    		else
	    		{
	    			outR[c] = outP[a];
	    			c++;
	    			a++;
	    		}
	    	}
	    	else
	    	{
	    		outR[c] = outP[a];
	    		a++;
	    		c++;
	    	}
	    }
	    a = 0;
	    b = 0;
	    c = 0;
	    while(1)   // deal single \r ot \n
	    {
	    	if (outR[a] == '\0')
	    	{
	    		outR[c] = '\0';
	    		break;
	    	}
	    	else if (outR[a] == '\n' || outR[a] == '\r')
	    	{
                outNewLine[c] = '<';
                outNewLine[c+1] = 'B';
                outNewLine[c+2] = 'R';
                outNewLine[c+3] = '>';
                c = c + 4;
                a++;
	    	}
	    	else
	    	{
	    		outNewLine[c] = outR[a];
	    		c++;
	    		a++;
	    	}
	    }
	    a = 0;
	    b = 0;
	    c = 0;
	    free(tempList->string);
	    tempList->string = malloc(sizeof(char)*10240000);
        if (tempList->string == NULL)
        {
            return FAILURE;
        } 
	    memset(tempList->string, 0, sizeof(char)*10240000);
	    strcpy(tempList->string, outNewLine);
	    header->length = header->length + strlen(outNewLine);
	    // below is to reset all strings.
	    memset(outNewLine, 0, sizeof(char)*10240000);
	    memset(outR, 0, sizeof(char)*10240000);
	    memset(outSpace, 0, sizeof(char)*10240000);
	    memset(outTab, 0, sizeof(char)*10240000);
	    memset(outP, 0, sizeof(char)*10240000);
	    tempList = tempList->next;
	}
	//deslP(header);
	free(outNewLine);
	free(outR);
	free(outSpace);
	free(outTab);
	free(outP);

	// python part
	fp = fopen("q1", "w");
	fprintf(fp, header->name);
	fprintf(fp, "\n");
    while (tempList2 != NULL)
    {
        fprintf(fp, tempList2->string);
        tempList2 = tempList2->next;    
    }
    fclose(fp);
    system("chmod a+rx a4.py");
    system("./a4.py");
    
    if (d == 0)
    {
	    FILE * op;
	    FILE * final;
	    char * name;
	    name = malloc(sizeof(char)*10240);
	    strcpy(name, header->name);
	    strcat(name, ".html");
	    final = fopen(name, "w+");
	    op = fopen("q2", "r");
	    char * str = malloc(sizeof(char)*10240000);
	    while(fgets(str, 99999, op) != NULL)
	    {
	    	fputs(str, final);
	    }
	    fclose(op);
	    remove("q2");
	    fclose(final);
	    free(name);
	    free(str);
	}
	else
	{
		FILE * op;
		op = fopen("q2", "r");
		MYSQL mysql;
		MYSQL_RES *res;
		//MYSQL_ROW row;
		//MYSQL_FIELD *field;
		char query[MAX_QUERY];
		//int x;
		//int i = 0;
		mysql_init(&mysql);
        mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "db");
        if (!mysql_real_connect(&mysql, HOSTNAME, USERNAME, PASSWORD,DATABASE, 0, NULL, 0)) 
        {
	   		error("Could not connect to host.",&mysql);
		}

		clrstr(query);
		strcat(query, "create table html (");
		strcat(query, "html_txt  varchar(2147483647),");
		strcat(query, "length_num int,");
		strcat(query, "name_txt varchar(255),");
		strcat(query, "time_date DATETIME)");
		mysql_query(&mysql,"select * from html");
		if (!(res = mysql_store_result(&mysql)))
		{
			
			if(mysql_query(&mysql, query))
			{
				printf("query: %s\n", query);
	  			error("Could not create table!",&mysql);
			}
	    }
	    mysql_free_result(res);
	    clrstr(query);
		char * temp1 = malloc(sizeof(char)*102400);
		char * temp8 = malloc(sizeof(char)*102400);
		fgets(temp1, 99999, op);
		strcpy(temp8, temp1);
		memset(temp1, 0, sizeof(char)*102400);
		while(fgets(temp1, 99999, op)!=NULL)
		{
            strcat(temp8, temp1);
            memset(temp1, 0, sizeof(char)*102400);
		}
		char * temp2 = malloc(sizeof(char)*1024);
		strcpy(temp2, header->name);
		char * temp3; // start after files/
		temp3 = strstr(temp2, "/");
		char * temp4;  // the start postion of .
		temp4 = strstr(temp2, ".");
		char * temp5; // html name into databse
		temp5 = malloc(sizeof(char)*10240);
		memset(temp5, 0, sizeof(char)*10240);
		memcpy(temp5, temp2+6, temp4-temp3-1);
		char * temp6 = malloc(sizeof(char)*10240);
		strcpy(temp6, "insert into html values ('");
    	strcat(temp6, temp8);
    	strcat(temp6, "',");
    	int e = strlen(temp8);
    	char * temp7 = malloc(sizeof(char)*1024);
    	sprintf(temp7,"%d", e);
    	strcat(temp6, temp7);
    	strcat(temp6, ",'");
    	strcat(temp6, temp5);
    	strcat(temp6, "',");
    	strcat(temp6, "now())");
    	if(mysql_query(&mysql, temp6))
    	{
			printf("Failure to insert: %s\n",temp6);
			error("Could not insert record",&mysql);
		}
		free(temp6);
		free(temp2);
		free(temp8);
		free(temp7);
		free(temp5);

	    /*if(mysql_query(&mysql,"drop table html"))
	    {
	    	error("fail drop 1",&mysql);
	    }*/
    	mysql_close(&mysql);
    	mysql_library_end();
		fclose(op);
        remove("q2");
        free(temp1);
/*
        FILE * op1;
	    FILE * final1;
	    char * name;
	    name = malloc(sizeof(char)*10240);
	    strcpy(name, header->name);
	    strcat(name, ".html");
	    final1 = fopen(name, "w+");
	    op1 = fopen("q2", "r");
	    char * str = malloc(sizeof(char)*10240000);
	    while(fgets(str, 99999, op1) != NULL)
	    {
	    	fputs(str, final1);
	    }
	    fclose(op1);
	    fclose(final1);
	    remove("q2");
	    free(name);
	    free(str);*/
    }
    return SUCCESS;
}

int freeStructure(struct dataHeader *header)
{
	struct dataString * temp, * tempFree;
	if (header == NULL || header->next == NULL)
	{
		return FAILURE;
	}
	temp = header->next;
	while (temp != NULL)
	{
        tempFree = temp;
		temp = temp -> next;
		free(tempFree->string);
		free(tempFree);
    }
    free(header->name);
    free(header);
    return SUCCESS;
}

int writeStrings(char *filename, struct dataHeader * header)
{
	FILE * fp;
	if (filename == NULL)
	{
        return FAILURE;
	}
	fp = fopen(filename, "wb");
	if (fp == NULL)
	{
        return FAILURE;
	}
    struct dataString * temp;
    if (header == NULL || header->next == NULL)
    {
    	return FAILURE;
    }
    temp = header->next;
    int nameLength = strlen(header->name);
    int stringLength;
    int headerLength;
    char * name;
    name = getName(header);
    headerLength = getLength(header);
    fwrite(&nameLength, sizeof(int), 1, fp);
    fwrite(name, sizeof(char), strlen(name)+1, fp);
    if (name == NULL)
    {
    	return FAILURE;
    }
    fwrite(&headerLength, sizeof(int), 1, fp);
    while(temp != NULL)
    {
    	stringLength = strlen(temp->string)+1;
    	fwrite(&stringLength, sizeof(int), 1, fp);
    	fwrite(temp->string, sizeof(char),  strlen(temp->string)+1,fp);
    	if (temp->string == NULL)
    	{
    		return FAILURE;
    	}
        temp = temp->next;
    }
    
    fclose(fp);
    return SUCCESS;
}

struct returnStruct *readStrings(char *filename)
{
	struct returnStruct * rempReturn;
    rempReturn = buildHeader();
    if (rempReturn->value == FAILURE)
    {
        rempReturn->value = FAILURE;
    	rempReturn->header = NULL;
    	return rempReturn;  
    }
    FILE * fp;
    if (filename == NULL)
    {
        rempReturn->value = FAILURE;
    	rempReturn->header = NULL;
    	return rempReturn;  
    }
    fp = fopen(filename, "rb");
    if (fp == NULL)
    {
        rempReturn->value = FAILURE;
    	rempReturn->header = NULL;
    	fclose(fp);
    	return rempReturn;  
    }
    int a;
    char * buffer;
    buffer = malloc(sizeof(char)*10240);
    if (buffer == NULL)
    {
        rempReturn->value = FAILURE;
    	rempReturn->header = NULL;
    	free(buffer);
    	fclose(fp);
    	return rempReturn;   
    }
    fread(&a, 1, 4, fp);
    fread(buffer, sizeof(char), a+1, fp);
    setName(rempReturn->header, buffer);
    fread(&a, 1, 4, fp);
    if (a == 0)
    {
        rempReturn->value = FAILURE;
    	rempReturn->header = NULL;
    	free(buffer);
    	fclose(fp);
    	return rempReturn;     
    }
    memset(buffer, 0, sizeof(char)*10240);
    int c;
    while(!feof(fp))
    {
        c = fread(&a, 1, 4, fp); 
        if (c != 4)
        {
        	break;
        }
        fread(buffer, sizeof(char), a, fp);
        if (buffer == NULL)
        {
        	rempReturn->value = FAILURE;
    		rempReturn->header = NULL;
    		free(buffer);
    		fclose(fp);
    		return rempReturn; 
        }
        addString(rempReturn->header, buffer);
        memset(buffer, 0, sizeof(char)*10240); 
    }
    free(buffer);
    fclose(fp);
    rempReturn->value = SUCCESS;
    return rempReturn;
}
