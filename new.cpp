// ConsoleApplication2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"


#include <iostream>
#include <fstream>


using namespace std;

int timeToMinutes(const char* time) {
    int hh, mm;
    sscanf_s(time, "%d:%d", &hh, &mm);
    return hh * 60 + mm;
}

void minutesToTime(int minutes, char* buffer) {
    int hh = minutes / 60;
    int mm = minutes % 60;
    sprintf_s(buffer, 6, "%02d:%02d", hh, mm);
}

int main() {

    ifstream inputFile("test.txt");
    int count_vis;
    inputFile >> count_vis;

    const int hourInDay = 1440;

    int mass[hourInDay] ={0};

    for (int i = 0; i < count_vis; ++i) {
        char arrival[6], left_buf[6];
        inputFile >> arrival >> left_buf;
        int arrive = timeToMinutes(arrival);
        int left = timeToMinutes(left_buf);
        for(int j = 0; j < hourInDay; j++) {
            if (j >= arrive && left <= j) {
                mass[j]++;
            }
        }
    }

    int max_vis = 0;
    for (int i = 0; i < hourInDay; i++) {
        if (mass[i] >= max_vis) {max_vis = mass[i];}
    }

    int maxStartTime = 0;
    int maxEndTime = 0;
    bool flag = false;

    for (int i = 0; i < hourInDay; i++) {
        if ((mass[i] == max_vis) && !flag){maxStartTime = i; flag = true;}
        else if((mass[i] != max_vis) && flag){maxEndTime = i; break;}

    }

  /*  int max_vis = 0;
    int cur_vis = 0;
    int maxStartTime = 0;
    int maxEndTime = 0;

    int i = 0, j = 0;

    while (i < count_vis && j < count_vis) {
        if (arrive[i] <= left[j]) {
            cur_vis++;
            if (cur_vis > max_vis) {
                max_vis = cur_vis;
                maxStartTime = arrive[i];
                maxEndTime = left[j];
            }
            i++;
        }
        else {
            cur_vis--;
            j++;
        }
    }*/

    char startTime[6], endTime[6];
    minutesToTime(maxStartTime, startTime);
    minutesToTime(maxEndTime, endTime);

    cout << max_vis << " " << startTime << " " << endTime;

    return 0;
}
