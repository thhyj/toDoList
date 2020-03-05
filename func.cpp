#include "qwq.h"
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