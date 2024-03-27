#ifndef DATABASE_ENCRYPTION_H
#define DATABASE_ENCRYPTION_H

#include <string>

using std::string;

string encryptUsingSHA256(const unsigned char *input, int length);

string encryptUsingSHA256(const string &input);

#endif //DATABASE_ENCRYPTION_H
