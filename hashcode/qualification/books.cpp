#include <bits/stdc++.h>

using namespace std;

long long num_books, num_libraries, num_days;
long long* scores;
long long current_day = 0;
std::unordered_set<long long> books_used;

struct library {
  long long num_books = 0, signup_time = 0, books_per_day = 0;
  vector<long long> books;
  library() {}
  pair<long long, vector<long long>> getPotential() {
    long long days_left = num_days - current_day;
    long long score = 0;
    vector<long long> books_to_use;
    long long max_books = (days_left - signup_time) * books_per_day;
    for (long long max_books_index = max_books - 1, current_book_index = num_books - 1; max_books_index >= 0 && current_book_index >= 0; max_books_index--, current_book_index--) {
      long long current_book = books[current_book_index];
      if (books_used.find(current_book) == books_used.end()) {
        score += scores[current_book];
        books_to_use.push_back(current_book);
      }
    }
    return pair<long long, vector<long long>>(score, books_to_use);
  }
};

library * libraries;

bool * libraries_remaining;
long long num_libraries_remaining;

struct library_res {
  long long library_num;
  library_res() {}
  vector<long long> books_used;
};

vector<library_res> libraries_used;

void solve() {
  while (current_day < num_days && num_libraries_remaining > 0) {
    // if I am selecting library:
    long long use_index = 0;
    pair<long long, vector<long long>> use_potential;
    for (long long j = 0; j < num_libraries; j++) {
      if (libraries_remaining[j]) {
        pair<long long, vector<long long>> current_potential = libraries[j].getPotential();
        if (current_potential.first >= use_potential.first) {
          use_potential = current_potential;
          use_index = j;
        }
      }
    }
    // cout << use_potential.first << endl;
    library_res current_library;
    current_library.books_used = use_potential.second;
    current_library.library_num = use_index;
    libraries_remaining[use_index] = false;
    num_libraries_remaining--;
    if (current_library.books_used.size() == 0) {
      continue;
    }
    current_day += libraries[use_index].signup_time;
    for (const long long & book : current_library.books_used) {
      books_used.insert(book);
    }
    libraries_used.push_back(current_library);
  }
}

void print_soln() {
  cout << libraries_used.size() << endl;
  for (size_t i = 0; i < libraries_used.size(); i++) {
    cout << libraries_used[i].library_num << ' ' << libraries_used[i].books_used.size() << '\n';
    if (libraries_used[i].books_used.size() > 0) {
      cout << libraries_used[i].books_used[0];
    }
    for (size_t j = 1; j < libraries_used[i].books_used.size(); j++) {
      cout << ' ' << libraries_used[i].books_used[j];
    }
    if (i < libraries_used.size() - 1) {
      cout << '\n';
    }
  }
}

void swapLongs(long long &elem1, long long &elem2)
{
  long long temp = elem1;
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
long long partitionIndexes(long long indexes[], long long left, long long right)
{
  std::uniform_int_distribution<long long> dist(left, right);
  unsigned long long randIndex = dist(generator);
  swapLongs(indexes[randIndex], indexes[left]);
  int pivot = scores[indexes[left]];
  long long s = left;
  for (long long i = left + 1; i <= right; i++)
    if (scores[indexes[i]] < pivot)
      swapLongs(indexes[++s], indexes[i]);
  swapLongs(indexes[left], indexes[s]);
  return s;
}

/**
 * quickSortKeys
 * 
 * quick sort the array based on first element in words
 */
void quickSortBooks(long long indexes[], long long left, long long right)
{
  if (left < right)
  {
    long long partition = partitionIndexes(indexes, left, right);
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
  books_used.reserve(num_books);
  // cout << "num days: " << num_days << endl;
  scores = new long long[num_books];
  for (long long i = 0; i < num_books; i++) {
    long long current_book_score;
    file >> current_book_score;
    scores[i] = current_book_score;
    // cout << current_book_score << endl;
  }
  libraries = new library[num_libraries];
  libraries_remaining = new bool[num_libraries];
  num_libraries_remaining = num_libraries;
  for (long long i = 0; i < num_libraries; i++) {
    libraries[i] = library();
    file >> libraries[i].num_books;
    file >> libraries[i].signup_time;
    file >> libraries[i].books_per_day;
    libraries[i].books.reserve(libraries[i].num_books);
    for (long long j = 0; j < libraries[i].num_books; j++) {
      long long current_book;
      file >> current_book;
      libraries[i].books.push_back(current_book);
    }
    if (libraries[i].books.size() > 0) {
      quickSortBooks(&libraries[i].books[0], 0, libraries[i].books.size() - 1);
    }
    libraries_remaining[i] = true;
    // cout << "signup time: " << libraries[i].signup_time << endl;
    // cout << "books per day: " << libraries[i].books_per_day << endl;
    // for (const int & book : libraries[i].books) {
    //   cout << book << ' ';
    // }
    // cout << '\n';
  }
  file.close();
  solve();
  print_soln();
  delete[] libraries;
  delete[] libraries_remaining;
  delete[] scores;
}
