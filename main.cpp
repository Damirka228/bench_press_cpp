#include <iostream>
#include "diagram/diagram.h"
#include "ctime"
#include <vector>
#include "calculator/calculator.h"
#include "database/database.h"
#include "auth/auth.h"
using namespace std;

string getDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    string year = to_string(1900 + ltm->tm_year);
    string month = (ltm->tm_mon + 1 < 10 ? "0" : "") + to_string(1 + ltm->tm_mon);
    string day = (ltm->tm_mday < 10 ? "0" : "") + to_string(ltm->tm_mday);
    return year + "-" + month + "-" + day;
}

void printLogo() {
    cout << " ___                                     ___" << endl;
    cout << "|   |                                   |   |" << endl;
    cout << "|   |=====[=== BENCH PRESS MAX ===]=====|   |" << endl;
    cout << "|___|                                   |___|" << endl;
    cout << "" << endl;
}

void showMenu() {
    cout << "Калькулятор мужчинского жима лежа!" << endl;
    printLogo();
    cout << "1. Регистрация" << endl;
    cout << "2. Вход" << endl;
    cout << "3. Выход" << endl;
    cout << "4. Калькулятор жима (без авторизации)" << endl;
    cout << "================================" << endl;
}

Results SaveCalc() {
    double weight; int reps;
    cout << "Введите вес штанги: "; cin >> weight;
    cout << "Введите количество повторений: "; cin >> reps;
    cout << "================================" << endl;
    Calculator c;
    Results res = c.calculate(weight,reps);
    cout << "Формула Эпли: " << res.epley << endl;
    cout << "Формула Бжицки: " << res.brzycki << endl;
    cout << "Формула Лэндера: " << res.lander << endl;
    cout << "Формула Ломбарди: " << res.lombardi << endl;
    cout << "Формула Мэйхью: " << res.mayhew << endl;
    cout << "Формула О'Коннор: " << res.oconner << endl;
    cout << "Формула Ватана: " << res.watan << endl;
    cout << "================================" << endl;
    cout << "Ваш разовый МАКСИМУМ: " << res.average << endl;
    cout << "================================" << endl;
    res.weight = weight; res.reps = reps;
    return res;
}

void SoloCalc() {
    double weight; int reps;
    cout << "Введите вес штанги: ";
    cin >> weight;
    cout << "Введите количество повторений: ";
    cin >> reps;
    cout << "================================" << endl;
    Calculator c;
    Results res = c.calculate(weight,reps);
    cout << "Формула Эпли: " << res.epley << endl;
    cout << "Формула Бжицки: " << res.brzycki << endl;
    cout << "Формула Лэндера: " << res.lander << endl;
    cout << "Формула Ломбарди: " << res.lombardi << endl;
    cout << "Формула Мэйхью: " << res.mayhew << endl;
    cout << "Формула О'Коннор: " << res.oconner << endl;
    cout << "Формула Ватана: " << res.watan << endl;
    cout << "================================" << endl;
    cout << "Ваш разовый МАКСИМУМ: " << res.average << endl;
    cout << "================================" << endl;
}

void userMenu (User u, Database& db) {
    while (true)
    {
    Diagram d;
    int choose, n, reps;
    double weight;
    string date = getDate();
    cout << "1. Калькулятор + сохранение тренировки" << endl;
    cout << "2. История тренировок + диаграмма прогресса" << endl;
    cout << "3. Выйти из аккаунта" << endl;
    cout << "Выберите действие(1-3): "; cin >> choose;
    switch (choose)
    {
    case 1:
        {Results res = SaveCalc();
        cout << "Сохранить результат?(1-да, 2-нет): "; cin >> n;
        if (n == 1) {
            db.SaveTrain(u.user_id, res.weight, res.reps, res.average, date);
        } }
    break;
    case 2:{
        cout << "Сохраненные тренировки: " << endl;
        vector<Train> allTrains = db.GetAllTrain(u.user_id);
        int cnt = 1;
        for (Train t : allTrains){
            cout << "================================" << endl;
            cout << "Тренировка #" << cnt << endl;
            cout << "Дата: " << t.date << endl;
            cout << "Вес: " << t.weight << " кг" << endl;
            cout << "Повторения: " << t.reps << endl;
            cout << "Максимум: " << t.max_weight << " кг" << endl;
            cnt ++;
        }
    cout << "================================" << endl;
    cout << "Диаграмма прогресса по всем тренировкам: "<< endl;
    d.ShowDiagram(allTrains);
    }
    break;
    case 3: return;
    default:
        break;
    }
    }
    
    
}

int main(){
    User u;
    Auth auth;
    Database db("bench.db");
    db.CreateTables();
    
    while (true) {
        showMenu();
        int choose, reps;
        double weight;
        string username, password; 
        cout << "Выберите действие(1-4): ";
        cin >> choose;
        switch(choose){
            case 1: 
            cout << "Регистрация!" << endl; 
            cout << "Введите логин: " ; cin >> username; 
            cout << "Введите пароль: "; cin >> password;
            password = auth.hashPassword(password);
            u = db.SearchUser(username);
            if (u.user_id == 0) {
                db.RegistUser(username,password); 
                cout << "Регистрация прошла успешно!" << endl;
            } else {
                cout << "Пользователь существует! Войдите в аккаунт" << endl;
            }
            break;
            case 2: 
            cout << "Вход в аккаунт!" << endl; 
            cout << "Введите логин: " ; cin >> username; 
            cout << "Введите пароль: "; cin >> password;  
            password = auth.hashPassword(password);
            u = db.SearchUser(username);   
            if (u.user_id == 0) {
                cout << "Вас нет в базе! Пройдите регестрацию" << endl;
            } else if (u.password != password || u.username != username)
            {
                cout << "Неверный логин или пароль!" << endl;
            } else { cout << "Успешный вход!" << endl; userMenu(u, db);}

            break;
            case 3: cout << "До свиданий! Новых рекородов, меньше травм!" << endl; return 0;
            case 4: SoloCalc(); break;
            default: cout << "Неккореткное значение" << endl; break;
        }
    }
    
    return 0;
}