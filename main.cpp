#include <bits/stdc++.h>

int totDay;
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
std::vector<Day> allDay;
void createNewDay();
void printToday();
void getIdOfDay();
void Save();
void Load();
void Menu();
void listAllTask();
void listAllUndoneTask();
void listTodayTask();
void addTodayTask();
void addTomorrowTask();
void addTaskOfCertainDay();
void addTask();
void listSave();
void listTask();
void finishTask();


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

inline int getIdofDay(int year, int month, int day) {
    return idOfDay[qwq(year, month, day)];
}

inline void listAllTask() {
    for(std::vector<Day>::iterator iter = (++allDay.begin()); iter != allDay.end(); ++iter) {
        iter->printDay();
        iter->listTask();
    }
}


inline void listAllUndoneTask() {
    for(std::vector<Day>::iterator iter = (++allDay.begin()); iter != allDay.end(); ++iter) {
        iter->printDay();
        iter->listUndoneTask();
    }
}

inline void listTodayTask() {
    int id = getIdofDay(Today.year, Today.month, Today.day);
    if(!id) {
        puts("There is no task");
        goto end;
    }
    printf("allDay.size() = %d\n", allDay.size());
    allDay[id].listTask();
    end:puts("---------------------------------------------") ;
    return;
}

inline void createNewDay(int year, int month, int day) {
    Day x;
    x.id = ++totDay;
    x.year = year;
    x.month = month;
    x.day = day;
    idOfDay[qwq(year, month, day)] = x.id;
    allDay.push_back(x);
}

inline void addTaskOfCertainDay(int year, int month, int day) {
    int id = getIdofDay(year, month, day);
    if(!id) {
        createNewDay(year, month, day);
    }
    Day *now = &allDay.back();
    printf("the day you are adding task is ");
    now->printDay();
    char x;
    while(true) {
        now->addTask();
        puts("continue ? (Y/N)");
        do {
            std::cin>>x;
            if(x == 'Y' || x == 'y') {
                break;

            } else {
                if(x == 'N' || x == 'n') {
                    goto end;
                } else {
                    puts("please input Y/y/N/n");
                }
            }
        } while(true);
    }
    end: return;
}

inline void addTask() {
    puts("please input year month day");
    int year, month, day;
    std::cin>>year>>month>>day;
    addTaskOfCertainDay(year, month, day);
    end:puts("---------------------------------------------") ;

}

inline void addTodayTask() {
    addTaskOfCertainDay(Today.year, Today.month, Today.day);
    end:puts("---------------------------------------------") ;

}

inline void listTask() {
    puts("which day's task? (input year, month, day)");
    int year, month, day;
    std::cin>>year >> month >> day;
    int id = getIdofDay(year, month, day);
    if(!id) {
        puts("There is no task");
        goto end;
    }
    allDay[id].listTask();
    end:puts("---------------------------------------------") ;
    return;
}

inline void finishTask() {
    listTodayTask();
    Day *now = &allDay[getIdofDay(Today.year, Today.month, Today.day)];
    while(true){
        puts("input which task have you finished? (input its id)");
        int id;
        std::cin >> id;
        id-=1;
        now->list[id].complete = 1;
        puts("modify successful");
        now->list[id].printTask();
        puts("continue ? (Y/N)");
        char x;
        do {
            std::cin>>x;
            if(x == 'Y' || x == 'y') {
                break;

            } else {
                if(x == 'N' || x == 'n') {
                    goto end;
                } else {
                    puts("please input Y/y/N/n");
                }
            }
        } while(true);
    }
    end:return;
}

inline void Menu() {
    while(1) {
        printToday();
        puts("r.finishTask");
        puts("1.list today task");
        puts("2.add today task");
        puts("3.add tomorrow task (uncompleted)");
        puts("4.add task");
        puts("5.list task");
        puts("6.list all task");
        puts("7.list all undone task");
        puts("8.exit");
        char k;
        std::cin >>k;
        switch (k) {
            case 'r':finishTask();break;
            case '1':listTodayTask(); break;
            case '2':addTodayTask();break;
           // case 3:addTomorrowTask();break;
            case '4':addTask(); break;
            case '5':listTask();break;
            case '6':listAllTask(); break;
            case '8':goto end; break;
            default: puts("在做了 在做了");break;
        }
    }
    end: return;
}

inline void Save() {
    std::cerr<<"Saving Data\n";
    freopen("data", "w", stdout);
    std:: cout << totDay<<'\n';
    sort((++allDay.begin()), allDay.end(), cmpDay);
    int tot = 0;
    for(auto iter = (++allDay.begin()); iter != allDay.end(); ++iter) {
        iter->id = ++tot;
        printf("%d %d %d %d %d\n", iter->year, iter->month, iter->day, iter -> id, iter->list.size());
        iter->listSave();
    }
    std::cerr<<"Saving Completed";
}

inline void Load() {
    puts("Loading Data");
    Day empty;
    allDay.push_back(empty);
    std::ifstream infile("data");
    if(! infile.is_open()){
        puts("data is empty");
        goto end;
    }
    infile>>totDay;
    for(int i = 1; i <= totDay; ++i) {
        Day x;
        int n;
        infile>>x.year >> x.month >> x.day >> x.id >> x.tot;

        idOfDay[qwq(x.year, x.month, x.day)] = x.id;
        for(int j = 1; j <= x.tot; ++j) {
            Day::Task y;
            infile>>y.id>>y.name>>y.type>>y.complete;
            x.list.push_back(y);
        }
        allDay.push_back(x);
    }
    end:puts("Loading Completed");
}

inline void run() {
    Load();
    Menu();
    Save();
}
int main() {
    run();
    return 0;
}