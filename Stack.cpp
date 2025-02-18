// mytests.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <exception>

using namespace std;

struct Stack {
private:
	int maxsize_;
	int* data_;
	int size_;

public:
	Stack(int size) {
		assert(size > 0);
		maxsize_ = size;
		data_ = new int[maxsize_];
		size_ = 0;
	}

	void push(int x) {
		assert(size_ < maxsize_);
		data_[size_] = x;
		++size_;
	}

	void pop() {
		--size_;
		assert(size_ >= 0);
	}

	int top() {
		assert(size_ > 0);
		return data_[size_ - 1];
	}

	bool empty() {
		return size_ == 0;
	}

	int size() {
		return size_;
	}

	void free() {
		delete[] data_;
		data_ = nullptr;
		maxsize_ = 0;
	}

	~Stack() {
		free();
		//delete[] data_;
	}
};

template<class T, class U> 
void AssertEqual(const T& t, const U& u, const string& hint) {
	if (t != u) {
		ostringstream os;
		os  << "Assertion failed: " << t << " != " << u
			<< " Hint: " << hint;
		throw runtime_error(os.str());
	}
}


void Assert(bool b, const string& hint) {
	AssertEqual(b, true, hint);
}

void TestStackPush() {
	{
		Stack S(1);
		S.push(1);
		AssertEqual(S.top(), 1, "one element");
	}

	{
		int n = 100;
		Stack S(n);
		for (int i = 1; i <= n; ++i) {
			S.push(i);
			AssertEqual(S.top(), i, "size != i");
		}
	}
	//cout << "Test StackPush OK" << endl;
}

void TestStackSize() {
	{
		Stack S(1);
		AssertEqual(S.size(), 0, "size must be zero");
		S.push(1);
		AssertEqual(S.size(), 1, "size must be one");
	}

	{
		int n = 100;
		Stack S(n);
		for (int i = 1; i <= n; ++i) {
			S.push(i);
			AssertEqual(S.size(), i, "label zero");
		}
		AssertEqual(S.size(), n, "label 1");
	}

	//cout << "Test StackSize OK" << endl;
}

void TestStackEmpty() {
	{
		Stack S(10);
		Assert(S.empty(), "must be empty");
	}
	//cout << "Test StackEmpty OK" << endl;
}

void TestStackPop() {
	{
		Stack S(1);
		S.push(10);
		S.pop();
		AssertEqual(S.size(), 0, "S must be empty");
		Assert(S.empty(), "must be empty");
	}

	{
		int n = 100;
		Stack S(n);
		for (int i = 0; i < n; ++i) {
			S.push(i+1);
		}
		for (int i = n; i >0 ; --i) {
			AssertEqual(S.top(), i, "size must be i");
			S.pop();
			
		}
		Assert(S.empty(), "must be empty");
		AssertEqual(S.size(), 0, "size = 0");

	}
	//cout << "Test StackPop OK" << endl;
}

void TestStackPushPop() {
	int n = 100;
	Stack S(n);
	for(int i = 0; i < n; ++i) {
		S.push(i);
		AssertEqual(S.top(), i, "top must be i");
		S.pop();
		Assert(S.empty(), "must be empty");
	}
	//cout << "Test StackPushPop OK" << endl;
}

class TestRunner {
private:
	int fail_count = 0;
public:
	template<class TestFunc>
	void RunTest(TestFunc func, const string& test_name) {
		try {
			func();
			cerr << "Test " << test_name << " OK" << endl;
		}
		catch (runtime_error & e) {
			cerr << "Test "<< test_name << " fail. " << e.what() << endl;
			++fail_count;
		}
	}
	~TestRunner() {
		if (fail_count != 0) {
			cerr << fail_count << " tests failed. Terminate";
			exit(1);
		}
	}
};


void TestAll() {
	TestRunner tr;
	tr.RunTest(TestStackEmpty, "StackEmpty");
	tr.RunTest(TestStackSize, "StackSize");
	tr.RunTest(TestStackPop, "StackPop");
	tr.RunTest(TestStackPush, "StackPush");
	tr.RunTest(TestStackPushPop, "StackPushPop");
	
}

int main() {
//#ifndef NDEBUG
//	TestAll();
//#endif // !NDEBUG
	TestAll();
	

	cout << "size: ";
	int n;
	cin >> n;
	assert(n > 0);
	Stack S(n);

	//добавление элементов в стек
	for (int i = 0; i < n; ++i) {
		S.push(i + 1);
	}

	//извлечение элементов из стека
	while (!S.empty()) {
		cout << S.top() << ' ';
		S.pop();
	}

    return 0;
}

#include <iostream>
#include <fstream>
#include <algorithm>

struct Event {
    int time;
    int type; // +1 for arrival, -1 for departure
};

bool compareEvents(const Event &a, const Event &b) {
    if (a.time == b.time) {
        return a.type < b.type; // Departure first if time is equal
    }
    return a.time < b.time;
}

int timeToMinutes(const std::string &time) {
    int hh = std::stoi(time.substr(0, 2));
    int mm = std::stoi(time.substr(3, 2));
    return hh * 60 + mm;
}

std::string minutesToTime(int minutes) {
    int hh = minutes / 60;
    int mm = minutes % 60;
    char buffer[6];
    sprintf(buffer, "%02d:%02d", hh, mm);
    return std::string(buffer);
}

int main(int argc, char *argv[]) {
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

    Event events[2 * N];
    int index = 0;

    for (int i = 0; i < N; ++i) {
        std::string arrival, departure;
        inputFile >> arrival >> departure;
        events[index++] = {timeToMinutes(arrival), 1};
        events[index++] = {timeToMinutes(departure), -1};
    }

    std::sort(events, events + 2 * N, compareEvents);

    int maxVisitors = 0;
    int currentVisitors = 0;
    int maxStartTime = 0;
    int maxEndTime = 0;

    for (int i = 0; i < 2 * N; ++i) {
        currentVisitors += events[i].type;
        if (currentVisitors > maxVisitors) {
            maxVisitors = currentVisitors;
            maxStartTime = events[i].time;
            maxEndTime = events[i + 1].time;
        }
    }

    std::cout << maxVisitors << " " << minutesToTime(maxStartTime) << " " << minutesToTime(maxEndTime) << std::endl;

    return 0;
}

