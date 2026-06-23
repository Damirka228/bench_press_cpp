#include "database.h"
#include "../auth/auth.h"

Database::Database(std::string dbPath){
    this->dbPath = dbPath;
    sqlite3_open(dbPath.c_str(), &db);
};
Database::~Database(){
    sqlite3_close(db);
};
bool Database::CreateTables(){
    const char* sqlMain = "CREATE TABLE IF NOT EXISTS users (id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT)";
    sqlite3_exec(db, sqlMain, 0, 0, 0);
    const char* sqlTrain = "CREATE TABLE IF NOT EXISTS trains (id INTEGER PRIMARY KEY AUTOINCREMENT, user_id INTEGER, weight REAL, reps INTEGER, max_weight INTEGER, date TEXT)";
    sqlite3_exec(db, sqlTrain, 0, 0, 0);
    return true;
};
bool Database::RegistUser(std::string username, std::string password){
    Auth auth;
    std::string sqlConvert = "INSERT INTO users (username, password) VALUES ('" + username + "', '" + password + "')";
    const char* sqlAddUser = sqlConvert.c_str();
    sqlite3_exec(db, sqlAddUser, 0, 0, 0);
    return true;
};
User Database::SearchUser(std::string username) {
    std::string sqlConvert = "SELECT * FROM users WHERE username = '"+username+"'";
    const char* sqslSearchUser = sqlConvert.c_str();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqslSearchUser, -1, &stmt, 0);
    User user;
    user.user_id = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW){
        user.user_id = sqlite3_column_int(stmt, 0);     
        user.username = (char*)sqlite3_column_text(stmt, 1);
        user.password = (char*)sqlite3_column_text(stmt, 2); 
    };
    sqlite3_finalize(stmt);
    return user;
};
bool Database::SaveTrain (
    int user_id, 
    double weight,
    int reps,
    int max_weight,
    std::string date) {
        std::string sqlConv = "INSERT INTO trains (user_id, weight, reps, max_weight, date) VALUES ('" + std::to_string(user_id) + "', '" + std::to_string(weight) + "', '" + std::to_string(reps) + "', '" + std::to_string(max_weight) + "', '" + date + "')";
        const char* sqlSaveTrain = sqlConv.c_str();
        sqlite3_exec(db, sqlSaveTrain, 0, 0, 0);
        return true;
    };
std::vector<Train> Database::GetAllTrain (int user_id) {
    std::vector<Train> trains;
    std::string sqlConvert = "SELECT * FROM trains WHERE user_id = '"+std::to_string(user_id)+"'";
    const char* sqslSearchUser = sqlConvert.c_str(); 
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqslSearchUser, -1, &stmt, 0);
    while (sqlite3_step(stmt) == SQLITE_ROW){
        Train train; 
        train.id_traint = sqlite3_column_int(stmt, 0); 
        train.user_id = sqlite3_column_int(stmt, 1);   
        train.weight = sqlite3_column_double(stmt,2);
        train.reps = sqlite3_column_int(stmt, 3);  
        train.max_weight = sqlite3_column_int(stmt, 4);
        train.date = (char*)sqlite3_column_text(stmt, 5);
        trains.push_back(train);
    }  
    sqlite3_finalize(stmt);
    return trains;
};
Train Database::GetTrain(int user_id, int train_id) const {
    std::string sqlConvert = "SELECT * FROM trains WHERE user_id = '"+std::to_string(user_id)+"' AND id = '"+std::to_string(train_id)+"'";
    const char* sqslSearchTrain = sqlConvert.c_str();
    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, sqslSearchTrain, -1, &stmt, 0);
    Train train;
    if (sqlite3_step(stmt) == SQLITE_ROW){
        train.id_traint = sqlite3_column_int(stmt, 0);     
        train.user_id = sqlite3_column_int(stmt, 1); 
        train.weight = sqlite3_column_double(stmt, 2); 
        train.reps = sqlite3_column_int(stmt, 3); 
        train.max_weight = sqlite3_column_int(stmt, 4); 
        train.date = (char*)sqlite3_column_text(stmt,5);
    };
    sqlite3_finalize(stmt);
    return train;
};