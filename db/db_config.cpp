#include "db_config.h"

namespace db {
   
   db_config::db_config(const std::string &&db_name, const db_config::vov &&uri_string) :
           client(uri(uri_string)) {
     database = client[db_name];
   }
}
