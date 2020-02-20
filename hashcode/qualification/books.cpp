#include <bits/stdc++.h>

using namespace std;

int num_books, num_libraries, num_days;
int* scores;
int current_day = 0;
std::unordered_set<int> books_used;

struct library {
  int num_books = 0, signup_time = 0, books_per_day = 0;
  vector<int> books;
  library() {}
  pair<int, vector<int>> getPotential() {
    int days_left = num_days - current_day;
    int score = 0;
    vector<int> books_to_use;
    for (int i = (days_left - signup_time) * books_per_day - 1, num_books_looked_at = 0; i >= 0 && num_books_looked_at < num_books; i--, num_books_looked_at++) {
      if (books_used.find(books[i]) != books_used.end()) {
        score += scores[books[i]];
        books_to_use.push_back(books[i]);
      }
    }
    return pair<int, vector<int>>(score, books_to_use);
  }
};

library * libraries;

bool * libraries_remaining;
int num_libraries_remaining;

struct library_res {
  int library_num;
  library_res() {}
  vector<int> books_used;
};

vector<library_res> libraries_used;

void solve() {
  while (current_day < num_days && num_libraries_remaining > 0) {
    // if I am selecting library:
    int use_index = 0;
    pair<int, vector<int>> use_potential;
    for (int j = 0; j < num_libraries; j++) {
      if (libraries_remaining[j]) {
        pair<int, vector<int>> current_potential = libraries[j].getPotential();
        if (current_potential.first >= use_potential.first) {
          use_potential = current_potential;
          use_index = j;
        }
      }
    }
    library_res current_library;
    current_library.books_used = use_potential.second;
    for (const int & book : current_library.books_used) {
      books_used.insert(book);
    }
    current_library.library_num = use_index;
    libraries_used.push_back(current_library);
    libraries_remaining[use_index] = false;
    current_day += libraries[use_index].signup_time;
    num_libraries_remaining--;
  }
}

void print_soln() {
  cout << libraries_used.size() << endl;
  for (const library_res & lib : libraries_used) {
    cout << lib.library_num << ' ' << lib.books_used.size() << '\n';
    if (lib.books_used.size() > 0) {
      cout << lib.books_used[0];
    }
    for (size_t i = 1; i < lib.books_used.size(); i++) {
      cout << ' ' << lib.books_used[i];
    }
    cout << '\n';
  }
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
  libraries_remaining = new bool[num_libraries];
  num_libraries_remaining = num_libraries;
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
    libraries_remaining[i] = true;
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
