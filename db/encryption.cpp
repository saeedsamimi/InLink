#include <openssl/sha.h>
#include "encryption.h"

string encryptUsingSHA256(const unsigned char *input,int length) {
  unsigned char hash[SHA256_DIGEST_LENGTH] = {0};
  SHA256(input, length, hash);
  string hashed;
  for (unsigned char h: hash) {
    char buf[3];
    std::sprintf(buf, "%02x", h);
    hashed += buf;
  }
  return hashed;
}

string encryptUsingSHA256(const string &input){
  auto uCharArr = reinterpret_cast<const unsigned char*>(input.c_str());
  return encryptUsingSHA256(uCharArr,(int)input.length());
}
