// mytests.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"

#include <iostream>
#include <cassert>

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

int main() {
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

