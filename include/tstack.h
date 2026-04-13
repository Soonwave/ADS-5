// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TSTACK_H_
#define INCLUDE_TSTACK_H_

template<typename T, int SIZE>
class TStack {
 private:
  T data[SIZE];
  int head;

 public:
  TStack() : head(-1) {}

  bool isEmpty() const {
    return head == -1;
  }

  bool isFull() const {
    return head == SIZE - 1;
  }

  void push(const T& item) {
    if (!isFull()) {
      data[++head] = item;
    }
  }

  void pop() {
    if (!isEmpty()) {
      head--;
    }
  }

  T top() const {
    if (!isEmpty()) {
      return data[head];
    }
    return T();
  }
};

#endif  // INCLUDE_TSTACK_H_
