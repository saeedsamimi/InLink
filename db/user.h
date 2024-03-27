#ifndef DATABASE_DB_USER_H
#define DATABASE_DB_USER_H

#include <string>
#include "db_config.h"
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/builder/stream/document.hpp>

using bsoncxx::builder::basic::make_document;
using bsoncxx::builder::basic::kvp;

namespace db {
   class user;
} // db

class db::user {
  using stdstr = std::string;
  using insert_result = std::pair<bool, std::string>;
  using streamDoc = bsoncxx::builder::stream::document;
public:
  user() = default;
  user(const stdstr &&, const stdstr &&);
  
  insert_result addToDB(const db_config &);
  
  bool validateInDB(const db_config &);
private:
  stdstr username;
  stdstr password;
  
  bsoncxx::document::value toEncryptedDoc();
};

#endif //DATABASE_DB_USER_H
