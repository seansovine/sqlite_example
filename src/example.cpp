// An example program for using SQLite with C++
// Modified from original version here:
//   https://gist.github.com/enile8/2424514

#include <sqlite3.h>

#include <iostream>
#include <string>
#include <vector>

int resultRowCallback( void *NotUsed, int argc, char **argv, char **azColName ) {
  int i;
  for ( i = 0; i < argc; i++ ) {
    std::cout << azColName[ i ] << " = " << ( argv[ i ] ? argv[ i ] : "NULL" ) << "\n";
  }
  std::cout << "\n";

  return 0;
}

int main() {
  sqlite3 *db;
  int lastReturnCode;
  lastReturnCode = sqlite3_open( "books.db", &db );

  // Check for error in opening database.
  if ( lastReturnCode ) {
    std::cout << "Can't open database: " << sqlite3_errmsg( db ) << "\n";
  } else {
    std::cout << "Open database successfully\n\n";
  }

  // clang-format off
  std::vector< std::string > queries = {
      "create table myTable (Title varchar(256), Author varchar(30), Date smallint, Publisher varchar(30))",
      "insert into myTable (Title, Author, Date, Publisher) values ('War and Peace', 'Leo Tolstoy', 1869, 'Penguin')",
	  "insert into myTable (Title, Author, Date, Publisher) values ('Dune', 'Frank Herbert', 1965, 'Penguin Classics')",
      "select * from myTable",
	  "delete from myTable",
	  "drop table myTable"
	};
  // clang-format on

  // Execute SQL statements.
  for ( int i = 0; i < queries.size(); i++ ) {
    const auto &query = queries[ i ];
    char *zErrMsg = nullptr;
    lastReturnCode = sqlite3_exec( db, query.c_str(), resultRowCallback, 0, &zErrMsg );

    // Check for query error and get message if present.
    if ( lastReturnCode != SQLITE_OK ) {
      std::cout << "Error in query #" << i << ".\n";
      std::cout << "  " << query.c_str() << "\n.";
      std::cout << "SQL error: " << sqlite3_errmsg( db ) << "\n";
      sqlite3_free( zErrMsg );
      break;
    }
  }

  sqlite3_close( db );
  return 0;
}
