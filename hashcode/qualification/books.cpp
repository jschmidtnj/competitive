#include <bits/stdc++.h>

using namespace std;

int num_books, num_libraries, num_days;
int* scores;

struct library {
  int num_books = 0, signup_time = 0, books_per_day = 0;
  vector<int> books;
  library() {}
};

library * libraries;

void solve() {
  // per library
  vector<int> books_sent;
}

void swapInts(int &elem1, int &elem2)
{
  int temp = elem1;
  elem1 = elem2;
  elem2 = temp;
}

std::default_random_engine generator;

/**
 * partitionKeys
 * 
 * partitions keys using Lomuto with
 * random partition index
 */
int partitionIndexes(int indexes[], long left, long right)
{
  std::uniform_int_distribution<long> dist(left, right);
  unsigned long randIndex = dist(generator);
  swapInts(indexes[randIndex], indexes[left]);
  int pivot = scores[indexes[left]];
  long s = left;
  for (long i = left + 1; i <= right; i++)
    if (scores[indexes[i]] < pivot)
      swapInts(indexes[++s], indexes[i]);
  swapInts(indexes[left], indexes[s]);
  return s;
}

/**
 * quickSortKeys
 * 
 * quick sort the array based on first element in words
 */
void quickSortBooks(int indexes[], int left, int right)
{
  if (left < right)
  {
    int partition = partitionIndexes(indexes, left, right);
    quickSortBooks(indexes, left, partition - 1);
    quickSortBooks(indexes, partition + 1, right);
  }
}

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
    // cout << current_book_score << endl;
  }
  libraries = new library[num_libraries];
  for (int i = 0; i < num_libraries; i++) {
    libraries[i] = library();
    file >> libraries[i].num_books;
    file >> libraries[i].signup_time;
    file >> libraries[i].books_per_day;
    libraries[i].books.reserve(libraries[i].num_books);
    for (int j = 0; j < libraries[i].num_books; j++) {
      int current_book;
      file >> current_book;
      libraries[i].books.push_back(current_book);
    }
    if (libraries[i].books.size() > 0) {
      quickSortBooks(&libraries[i].books[0], 0, libraries[i].books.size() - 1);
    }
    // for (const int & book : libraries[i].books) {
    //   cout << book << ' ';
    // }
    // cout << '\n';
  }
  file.close();
  solve();
  delete[] libraries;
  delete[] scores;
}
