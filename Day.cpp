
#include "qwq.h"

struct qwq {
    int year, month, day;
    qwq(){}
    qwq(int year, int month, int day):year(year), month(month),day(day) {}
};
inline bool operator < (const qwq& a, const qwq& b) {
    return a.year < b.year || a.month < b.month || a.day < b.day;
}
std::map<qwq, int> idOfDay;
struct CurrentDay {
    int year, month, day;
    CurrentDay() {
        time_t t = time(NULL);
        tm *tt = localtime(&t);
        year = tt->tm_year + 1900;
        month = tt->tm_mon + 1;
        day = tt->tm_mday;
    }
}Today;
struct Day {
    int year, month, day;
    int tot;
    int id;
    struct Task {
        std::string name;
        int type;
        int id;
        bool complete;
        Task():type(0), complete(0){
        }
        void printTask();
        void printTaskSave();
    };
    Day():tot(0){}
    std::vector<Task> list;
    void addTask();
    void listTask();
    void listSave();
    void listUndoneTask();
    void printDay();
};
inline bool cmpDay (const Day& a, const Day& b) {
    return a.year < b.year || (a.year == b.year && a.month < b.month) || (a.year == b.year && a.month
                                                                                              == b.month && a.day < b.day);
}

inline bool cmp(const Day::Task &a, const Day::Task &b) {
    return a.type < b.type || (a.type == b.type && a.id < b.id);
}

inline void printToday() {
    printf("Current time is %d %d %d\n", Today.year, Today.month, Today.day);
}

inline void Day::Task::printTask(){
    std::cout <<"id is "<< this->id << " name is " << this->name << " type is " << this->type << " complete is " << this->complete << '\n';
}

inline void Day::Task::printTaskSave(){
    std::cout <<this->id << " " << this->name << " " << this->type << " " << this->complete << '\n';
}

inline void Day::printDay() {
    printf("%d %d %d     id = %d\n", this->year, this->month, this->day, this->id);
}

inline void Day::listSave() {
    std::sort(this->list.begin(), this->list.end(), cmp);
    for(std::vector<Task>::iterator iter = this->list.begin(); iter != this->list.end(); ++iter) {
        (iter)->printTaskSave();
    }
}

inline void Day::listTask() {
    std::cout << this->list.size() << '\n';
    //   std::sort(this->list.begin(), this->list.end(), cmp);
    for(std::vector<Task>::iterator iter = this->list.begin(); iter != this->list.end(); ++iter) {
        (iter)->printTask();
    }
    std::string c;

    puts("input anything to continue;");
    std::cin >> c;
}
inline void Day::listUndoneTask() {
    std::sort(this->list.begin(), this->list.end(), cmp);
    for(std::vector<Task>::iterator iter = this->list.begin(); iter != this->list.end(); ++iter) {
        if(iter->complete == 0)
            (iter)->printTask();
    }
    std::string c;

    puts("input anything to continue;");
    std::cin >> c;

}

inline void Day::addTask() {
    Task x;
    x.id = ++(this->tot);
    std::cout << "please input the name of the task\n";
    std::cin >> x.name;
    std::cout << "pleast input the type of the task (0 means it is not necessary and 1 means it is necessary)\n";
    std::cin >> x.type;
    this->list.push_back(x);

    std::cout << "the task is added successfully\n";
    list.back().printTask();

}