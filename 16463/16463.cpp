#include <iostream>

using namespace std;

typedef struct _date {
    int day, month, year;

    bool isLeap() {
        if(year % 400 == 0) return true;
        if(year % 100 != 0 && year % 4 == 0) return true;
        return false;
    }
    
    bool operator<(const _date& a) {
        if(this->year < a.year) return true;
        else if(this->year == a.year && this->month < a.month) return true;
        else if(this->year == a.year && this->month == a.month && this->day < a.day) return true;

        return false;
    }

    void operator++() {
        //Feb
        if(day + 1 == 29 && month == 2 && !isLeap()) {
            *this = {1, month + 1, year};
        }
        else if(day + 1 == 30 && month == 2 && isLeap()) {
            *this = {1, month + 1, year};
        }

        //Jen, Mar, May, Jul, Aug, Oct
        else if(day + 1 == 32 && month != 12) {
            *this = {1, month + 1, year};
        }
        else if(day + 1 == 32 && month == 12) {
            *this = {1, 1, year + 1};
        } //Dec

        //Apr, Jun, Sep, Nov
        else if(day + 1 == 31 && (month == 4 || month == 6 || month == 9 || month == 11)) {
            *this = {1, month + 1, year};
        }
        else *this = {day + 1, month, year};
    }
} date;

int main() {
    int ret = 0;
    int idx = 0;
    bool day[] = {0, 0, 0, 1, 0, 0, 0};
    date s = {1, 1, 2019};

    int N; cin >> N;
    date e = {1, 1, N + 1};

    while(s < e) {
        if(day[idx] && s.day == 13) ret++;
        idx = (idx + 1) % 7;
        ++s;
    }
    
    cout << ret;
}