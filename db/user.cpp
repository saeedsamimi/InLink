#include "user.h"
#include "encryption.h"

#include <mongocxx/exception/bulk_write_exception.hpp>
#include <bsoncxx/json.hpp>
#include <sstream>

namespace db {
   std::string userCollectionName = "users";
   
   user::user(const stdstr &&usr_name, const stdstr &&pass)
           : username(usr_name), password(pass) {}
   
   user::insert_result user::addToDB(const db_config &db) {
     try {
       auto res = db.database[userCollectionName].insert_one(toEncryptedDoc());
     } catch (mongocxx::bulk_write_exception &e) {
       switch (e.code().value()) {
         case 11000:
           return {false, "The username exists!"};
         default:
           std::stringstream msg_error;
           msg_error << "an unexpected error occurred with status of: " << e.code().value();
           return {false, msg_error.str()};
       }
     }
     return {true, "Succeed"};
   }
   
   bool user::validateInDB(const db_config &db) {
     streamDoc findDoc;
     findDoc << "username" << username;
     auto findResult = db.database[userCollectionName].find_one(findDoc.view());
     return findResult &&
            encryptUsingSHA256(password) == findResult->operator[]("password").get_string().value;
   }
   
   bsoncxx::document::value user::toEncryptedDoc() {
     return bsoncxx::builder::basic::make_document(
             kvp("username", username),
             kvp("password", encryptUsingSHA256(password))
     );
   }
  
} // db