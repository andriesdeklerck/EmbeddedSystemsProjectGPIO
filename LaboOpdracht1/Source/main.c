#include "PJ_RPI.h"
#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
//#include <string.h>

//#define GPIO_READ(g) *(gpio.addr + 13) &= (1 << (g))

int main()
{
	if (map_peripheral(&gpio) == -1)
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "localhost";
	char *user = "pi";
	char *password = "RaspiAndries"; /* set me first */
	char *database = "Opdracht1GPIO";

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	/* send SQL query */
	if (mysql_query(conn, "show tables"))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}

	res = mysql_use_result(conn);

	/* output table name */
	printf("MySQL Tables in mysql database:\n");
	while ((row = mysql_fetch_row(res)) != NULL)
		printf("%s \n", row[0]);

	//Define gpio 15 as output
	INP_GPIO(3);

	while (1)
	{
		printf("%d\n",GPIO_READ(3));
		if (GPIO_READ(3))
		{
			printf("on");
			if (mysql_query(conn, ("INSERT INTO TabelOpdracht1 (Level, Pin) VALUES ('1', '15')")))
			{
				fprintf(stderr, "%s\n", mysql_error(conn));
			}
		}
		else
		{
			printf("off");
			if (mysql_query(conn, ("INSERT INTO TabelOpdracht1 (Level, Pin) VALUES ('0', '15')")))
			{
				fprintf(stderr, "%s\n", mysql_error(conn));
			}
		}

		sleep(10);
	}

	/* close connection */
	//mysql_free_result(res);
	mysql_close(conn);
	if (map_peripheral(&gpio) == -1)
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

	return 0;
}
