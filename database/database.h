#pragma once
#include <string>
#include <vector>
#include <sqlite3.h>
#include "../auth/auth.h"

struct User
{
    int user_id;
    std::string username;
    std::string password;
};
struct Train{
    int id_traint;
    int user_id;
    double weight;
    int reps;
    int max_weight;
    std::string date;
};

class Database {
private:
    sqlite3* db;
    std::string dbPath;
public:
    Database (std::string dbPath);
    ~Database();
    bool RegistUser (std::string username,std::string password);
    User SearchUser (std::string username);
    bool SaveTrain (
        int user_id, 
        double weight,
        int reps,
        int max_weight,
        std::string date);
    Train GetTrain (int user_id, int train_id) const;
    std::vector<Train> GetAllTrain(int user_id);
    bool CreateTables();
};