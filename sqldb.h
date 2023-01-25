#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <bits/stdc++.h>

#include <sqlite3.h>


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    int i;
    for(i=0; i<argc; i++)   {
        printf("%s = %s\n", azColName[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

class SQLiteDB{
private:
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char *sql;
    int iterNum = 0;

    int dbInit();
public:
    int success = dbInit();
    int insert(std::string);
};

int SQLiteDB::dbInit(){
    rc = sqlite3_open("test.db", &db);

    if(rc)  {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 0;
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    // Create SQL statement
    sql = "CREATE TABLE SINGLEDECKS(" \
        "ID INT PRIMARY KEY     NOT NULL,"  \
        "DECK           TEXT    NOT NULL);";

    
    // Execute SQL statement
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Table created successfully\n");
    }
    sqlite3_close(db);
    return 0;
}

int SQLiteDB::insert(std::string sIn){
    rc = sqlite3_open("test.db", &db);
    
    // SQL open error check
    if( rc ) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return(0);
    } 

    std::string dbInput = "INSERT INTO SINGLEDECKS (ID,DECK) VALUES (" + std::to_string(iterNum);
    dbInput += ", '" + sIn + "');";
    iterNum++;
    rc = sqlite3_exec(db, dbInput.c_str(), callback, 0, &zErrMsg);
    // SQL execute error check
    if (rc != SQLITE_OK){
        fprintf(stderr,"SQL error %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);
    return 0;
}