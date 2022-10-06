#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <stdlib.h>

int main(void) {
	MYSQL* conn;
	MYSQL_RES* resultado;
	MYSQL_ROW row;
	
	int err;
	
	conn = mysql_init(NULL);
	
	if (conn == NULL)
	{
		printf("Error al crear la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	conn = mysql_real_connect(conn, "localhost", "root", "mysql", NULL, 0, NULL, 0);
	
	if (conn == NULL)
	{
		printf("Error al inicializar la conexión: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	/* Asumimos la base de datos ya está creada */
	/* mysql> source bd.sql */
	
	err = mysql_query(conn, "select jugador.nombre from (jugador, partida) where jugador.edad < 18 and partida.ganador = jugador.id");
	
	if (err != 0)
	{
		printf("Error al ejecutar la consulta: %u %s\n", mysql_errno(conn), mysql_error(conn));
		exit(1);
	}
	
	resultado = mysql_store_result(conn);
	row = mysql_fetch_row(resultado);
	
	if (row == NULL)
	{
		printf("No se han obtenido resultados en la consulta");
	} else
	{
		int i = 0;
		while (row != NULL)
		{
			printf("Ganador menor de edad %d: %s", i, row[0]);
			
			i++;
			row = mysql_fetch_row(resultado);
		}
	}
	
	mysql_close(conn);
	
	return 0;
}

