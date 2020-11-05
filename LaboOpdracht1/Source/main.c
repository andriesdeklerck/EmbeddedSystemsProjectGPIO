#include "PJ_RPI.h"
#include <stdio.h>
#include <mysql/mysql.h>

int main()
{
	MYSQL *conn;
	MYSQL_RES *res;
	MYSQL_ROW row;

	char *server = "andriesraspi";
	char *user = "root";
	char *password = "*****"; /* set me first */
	char *database = "Opdracht1GPIO";

	conn = mysql_init(NULL);

	/* Connect to database */
	if (!mysql_real_connect(conn, server,
							user, password, database, 0, NULL, 0))
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

	// Define gpio 17 as output
	INP_GPIO(17);
	OUT_GPIO(17);

	while (1)
	{
		// Toggle 17 (blink a led!)
		GPIO_SET = 1 << 17;
		sleep(1);

		GPIO_CLR = 1 << 17;
		sleep(1);
	}

	/* close connection */
	mysql_free_result(res);
	mysql_close(conn);
	if (map_peripheral(&gpio) == -1)
	{
		printf("Failed to map the physical GPIO registers into the virtual memory space.\n");
		return -1;
	}

	return 0;
}
