/*The first version of the code used a **rows instead of a single pointer.
 * I wanted to try out if it was possible, even though uglier, to make 
 * it work this way. It worked and now I understand a little bit more about 
 * pointers.
 * */
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>


struct Address {
	int id;
	int set;
	char *name;
	char *email;
};

struct Database {
	int max_rows;
	int max_data;
	struct Address *rows;
};

struct Connection { // contain everything in a single struct
	FILE *file; // it is a pointer because fread and fwrite store their values in a pointer
	struct Database *db;
};

void Database_close(struct Connection *conn);
struct Connection *Database_open(const char *filename,char mode);
void Database_load(struct Connection *conn);


void die(const char *message, struct Connection *conn) // be sure that the message won't be touched
{
	if(errno) { // number that previous error returned
		perror(message); // print description for the error
	} else {
		printf("ERROR: %s\n", message);
	}
	
	Database_close(conn);

	exit(1);
}

void Address_print(struct Address *addr)
{
	printf("%d %s %s\n", addr->id, addr->name, addr->email);
}

struct Connection *Database_open(const char *filename,char mode)
{
	struct Connection *conn = malloc(sizeof(struct Connection));
	if(!conn) die("Memory error", conn); // if conn different from NULL. !NULL == true, !NOTNULL == false
	
	conn->db = malloc(sizeof(struct Database));
	if(!conn->db) die("Memory error. (Database allocation)", conn);

	if(mode == 'c') {
		conn->file = fopen(filename,"w");
	} else {
		conn->file = fopen(filename, "r+");
		
		if(conn->file) {
			Database_load(conn);
		}
	} 
	
	if(!conn->file) die("Failed to open the file", conn);
	
	return conn;
}


void Database_load(struct Connection *conn)
{
	rewind(conn->file);

	int rc = fread(&conn->db->max_rows, sizeof(conn->db->max_rows),1,conn->file);
	if(rc != 1) die("Failed to load database. (max_rows error)", conn);

	rc = fread(&conn->db->max_data, sizeof(conn->db->max_data),1,conn->file);
	if(rc != 1) die("Failed to load database. (max_data error)", conn);

	conn->db->rows = malloc(sizeof(struct Address)*conn->db->max_rows);
	if(!conn->db->rows) die("Memory error. (Rows allocation)", conn);

	for(int i=0;i<conn->db->max_rows;i++){

		struct Address* row = &conn->db->rows[i];

		row->name = malloc(conn->db->max_data);
		row->email = malloc(conn->db->max_data);

		assert(row->name && row->email);

		if (!(row->name && row->email))
                        die("Database load : Failed to Allocate Address strings", conn);


		rc = fread(&row->id, sizeof(row->id),1,conn->file);
		if(rc != 1) die("Failed to load database. (id error)", conn);
		
		rc = fread(&row->set, sizeof(row->set),1,conn->file);
		if(rc != 1) die("Failed to load database. (set error)", conn);

		rc = fread(row->name, conn->db->max_data,1,conn->file);
		if(rc != 1) die("Failed to load database. (name error)", conn);

		rc = fread(row->email, conn->db->max_data,1,conn->file);
		if(rc != 1) die("Failed to load database. (email error)", conn);
	}

}


void Database_close(struct Connection *conn)
{
	if(conn) {
		for(int i=0;i<conn->db->max_rows;i++){
			struct Address* row = &conn->db->rows[i];
			free(row->name);
			free(row->email);
		}

		if(conn->file) fclose(conn->file);

		if(conn->db->rows) free(conn->db->rows);
		if(conn->db) free(conn->db);
		free(conn);
	}
}

void Database_write(struct Connection *conn)
{
	rewind(conn->file);
	
	int rc = fwrite(&conn->db->max_rows, sizeof(conn->db->max_rows), 1, conn->file);
	if(rc != 1) die("Failed to write database. (Struct error)", conn);

	rc = fwrite(&conn->db->max_data, sizeof(conn->db->max_data), 1, conn->file);
	if(rc != 1) die("Failed to write database. (Data error)", conn);
	
	for(int i=0;i<conn->db->max_rows;i++){
		struct Address* row = &conn->db->rows[i];

		rc = fwrite(&row->id, sizeof(row->id),1,conn->file);
		if(rc != 1) die("Failed to write database. (id error)", conn);
		
		rc = fwrite(&row->set, sizeof(row->set),1,conn->file);
		if(rc != 1) die("Failed to write database. (set error)", conn);

		rc = fwrite(row->name, conn->db->max_data,1,conn->file);
		if(rc != 1) die("Failed to write database. (name error)", conn);

		rc = fwrite(row->email, conn->db->max_data,1,conn->file);
		if(rc != 1) die("Failed to write database. (email error)", conn);
	}

	rc = fflush(conn->file);
	if(rc == -1) die("Cannot flush database.", conn);
}

void Database_create(struct Connection *conn, int n_rows, int n_data)
{
	conn->db->max_rows = n_rows;
	conn->db->max_data = n_data;
	
	int init = 0;

	conn->db->rows = malloc(sizeof(struct Address)*conn->db->max_rows);
	if(!conn->db->rows) die("Memory error. (Rows allocation)", conn);

	for(int i=0;i<conn->db->max_rows;i++){

		struct Address *row = &conn->db->rows[i];

		row->id = init;
		row->set = 0;

		row->name = malloc(conn->db->max_data);
		row->email = malloc(conn->db->max_data);

		assert(row->name && row->email);

		if (!(row->name && row->email))
                        die("Database load : Failed to Allocate Address strings", conn);


	}

}

void Database_set (struct Connection *conn, int id, const char *name, const char *email)
{
	struct Address *addr = &conn->db->rows[id];
	if(addr->set) die("Already set, delete it first.", conn);
	
	addr->id = id;
	addr->set = 1;

	char *res = strncpy(addr->name,name,conn->db->max_data);
	addr->name[conn->db->max_data - 1] = '\0';
	if(!res) die("Name copy failed", conn);
	
	res = strncpy(addr->email, email, conn->db->max_data);
	addr->email[conn->db->max_data - 1] = '\0';
	if(!res) die("Email copy failed", conn);
}

void Database_get(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];
	
	if(addr->set) {
		Address_print(addr);
	} else {
		die("ID is not set", conn);
	}
}

void Database_delete(struct Connection *conn, int id)
{
	struct Address *addr = &conn->db->rows[id];	

	addr->id = id;
	addr->set = 0;
}

void Database_list(struct Connection *conn)
{
	int i = 0;
	struct Database *db = conn->db;
	
	for(i=0; i < db->max_rows; i++){
		struct Address *cur = &db->rows[i];
		
		if(cur->set) {
			Address_print(cur);
		}
	}
}

void Database_size(struct Connection *conn, int max_rows, int max_data)
{
	conn->db->max_rows = max_rows;
	
	if(!conn->db->max_rows) die ("max_rows isn't set.", conn);
	
	conn->db->max_data = max_data;
	
	if(!conn->db->max_data) die ("max_data isn't set.", conn);
}

int main(int argc, char *argv[])
{
	if(argc < 3) printf("ERROR: %s\n", "USAGE: ex17 <dbfile> <action> [action params]");
	
	char *filename = argv[1];
	char action = argv[2][0];
	struct Connection *conn = Database_open(filename, action);
	int id = 0;
	
	if(argc > 3) id = atoi(argv[3]);
	//if(id >= conn->db->max_rows  && conn->db->max_rows != 0) die("There's not that many records", conn);
	
	switch(action) {
		case 'c':
			Database_create(conn, 100, 255);
			Database_write(conn);
			break;
		case 'g':
			if(argc != 4) die("Need id to get", conn);
			
			Database_get(conn, id);
			break;
		case 's':
			if(argc != 6) die("Need id, name, email to set", conn);
			
			Database_set(conn, id, argv[4], argv[5]);
			Database_write(conn);
			break;
		case 'd':
			if(argc != 4) die("Need id to delete", conn);
			
			Database_delete(conn, id);
			Database_write(conn);
			break;
		case 'l':
			Database_list(conn);
			break;
		case 'z':
			Database_size(conn, atoi(argv[3]), atoi(argv[4]));
			Database_write(conn);
			break;
		default:
			die("Invalid action, only: c=create, g=get, s=set, d=del, l=list", conn);
	}
	
	Database_close(conn);
	
	return 0;
}

