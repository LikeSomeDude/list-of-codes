#include <iostream>
#include <fstream>
#include <algorithm>

// Преобразуем время в минуты
int timeToMinutes(const char* time) {
    int hh, mm;
    sscanf(time, "%d:%d", &hh, &mm);
    return hh * 60 + mm;
}

// Преобразуем минуты обратно в время
void minutesToTime(int minutes, char* buffer) {
    int hh = minutes / 60;
    int mm = minutes % 60;
    sprintf(buffer, "%02d:%02d", hh, mm);
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <input_file>" << std::endl;
        return 1;
    }

    std::ifstream inputFile(argv[1]);
    if (!inputFile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    int N;
    inputFile >> N;

    // Создаем массивы для времени прихода и ухода
    int arrivals[N];
    int departures[N];

    for (int i = 0; i < N; ++i) {
        char arrival[6], departure[6];
        inputFile >> arrival >> departure;
        arrivals[i] = timeToMinutes(arrival);
        departures[i] = timeToMinutes(departure);
    }

    // Сортируем оба массива
    std::sort(arrivals, arrivals + N);
    std::sort(departures, departures + N);

    int maxVisitors = 0;
    int currentVisitors = 0;
    int maxStartTime = 0;
    int maxEndTime = 0;

    int i = 0, j = 0;

    // Проходим по событиям и находим максимальное количество посетителей
    while (i < N && j < N) {
        if (arrivals[i] <= departures[j]) {
            currentVisitors++;
            if (currentVisitors > maxVisitors) {
                maxVisitors = currentVisitors;
                maxStartTime = arrivals[i];
                maxEndTime = departures[j];
            }
            i++;
        } else {
            currentVisitors--;
            j++;
        }
    }

    // Преобразуем время обратно в формат ЧЧ:ММ
    char startTime[6], endTime[6];
    minutesToTime(maxStartTime, startTime);
    minutesToTime(maxEndTime, endTime);

    // Выводим результат
    std::cout << maxVisitors << " " << startTime << " " << endTime << std::endl;

    return 0;
}
