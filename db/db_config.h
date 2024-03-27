#ifndef DATABASE_DB_CONFIG_H
#define DATABASE_DB_CONFIG_H

#include <string>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

namespace db {
   class db_config;
}

class db::db_config {
  using vov = bsoncxx::string::view_or_value;
  using uri = mongocxx::uri;
public:
  explicit db_config(const std::string &&db_name,
                     const vov &&uri_string = uri::k_default_uri);
private:
  mongocxx::instance instance{};
  mongocxx::client client;
  mongocxx::database database;
  friend class user;
};

#endif //DATABASE_DB_CONFIG_H
