#include <bits/stdc++.h>

using namespace std;

int num_books, num_libraries, num_days;
int* scores;

struct library {
  int num_books, signup_time, books_per_day;
  int * books;
  library() {}
  ~library() {
    if (books != nullptr) {
      delete[] books;
    }
  }
};

library * libraries;

int main(int argc, const char* argv[]) {
  if (argc != 2) {
    cout << "invalid args" << endl;
    return 1;
  }
  ifstream file(argv[1]);
  file >> num_books >> num_libraries >> num_days;
  scores = new int[num_books];
  for (int i = 0; i < num_books; i++) {
    int current_book_score;
    file >> current_book_score;
    scores[i] = current_book_score;
    cout << current_book_score << endl;
  }
  libraries = new library[num_libraries];
  for (int i = 0; i < num_libraries; i++) {
    libraries[i] = library();
    file >> libraries[i].num_books;
    file >> libraries[i].signup_time;
    file >> libraries[i].books_per_day;
    libraries[i].books = new int[libraries[i].num_books];
    for (int j = 0; j < libraries[i].num_books; j++) {
      file >> libraries[i].books[j];
    }
  }
  file.close();
  if (libraries != nullptr) {
    delete[] libraries;
  }
  delete[] scores;
}
