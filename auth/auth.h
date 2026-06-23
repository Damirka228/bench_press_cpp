#pragma once
#include <string>
#include <openssl/sha.h>

class Auth {
public:
    std::string hashPassword (std::string password) const;
};