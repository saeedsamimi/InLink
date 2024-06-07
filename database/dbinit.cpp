#include "dbinit.h"

void initDB() {
  // create connection and try to connect
  QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
  db.setHostName("localhost");
  db.setPort(8080);
  db.setUserName("postgres");
  db.setPassword("12345678");
  db.setDatabaseName("InLink");
  if (!db.open())
    throw db.lastError();
  qDebug() << "cenncted to database successfully!";
}
