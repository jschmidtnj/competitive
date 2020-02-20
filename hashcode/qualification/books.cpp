#include <bits/stdc++.h>

using namespace std;

long num_books, num_libraries, num_days;
long* scores;
long current_day = 0;
std::unordered_set<long> books_used;

const int timeout_secs = 10;

struct library {
  long num_books = 0, signup_time = 0, books_per_day = 0;
  vector<long> books;
  library() {}
  pair<long, vector<long>> getPotential() {
    long days_left = num_days - current_day;
    long score = 0;
    vector<long> books_to_use;
    long max_books = (days_left - signup_time) * books_per_day;
    for (long max_books_index = max_books - 1, current_book_index = num_books - 1; max_books_index >= 0 && current_book_index >= 0; max_books_index--, current_book_index--) {
      long current_book = books[current_book_index];
      if (books_used.find(current_book) == books_used.end()) {
        score += scores[current_book];
        books_to_use.push_back(current_book);
      }
    }
    return pair<long, vector<long>>(score, books_to_use);
  }
};

vector<library> libraries;

struct library_res {
  long library_num;
  library_res() {}
  vector<long> books_used;
};

vector<library_res> libraries_used;

void solve() {
  clock_t timeStart = clock();
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  long max_total_score = 0;
  bool * libraries_remaining = new bool[num_libraries];
  vector<library_res> current_libraries_used;
  current_libraries_used.reserve(num_libraries);
  while(true) {
    for (long i = 0; i < num_libraries; i++) {
      libraries_remaining[i] = true;
    }
    shuffle(libraries.begin(), libraries.end(), std::default_random_engine(seed));
    long current_total_score = 0;
    long num_libraries_remaining = num_libraries;
    current_day = 0;
    while (current_day < num_days && num_libraries_remaining > 0) {
      // if I am selecting library:
      long use_index = 0;
      pair<long, vector<long>> use_potential;
      for (long j = 0; j < num_libraries; j++) {
        if (libraries_remaining[j]) {
          pair<long, vector<long>> current_potential = libraries[j].getPotential();
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
        if ((clock() - timeStart) / CLOCKS_PER_SEC >= timeout_secs) {
          return;
        }
        continue;
      }
      current_day += libraries[use_index].signup_time;
      for (const long & book : current_library.books_used) {
        books_used.insert(book);
      }
      libraries_used.push_back(current_library);
      current_total_score += use_potential.first;
      if ((clock() - timeStart) / CLOCKS_PER_SEC >= timeout_secs) {
        return;
      }
    }
    if (current_total_score > max_total_score) {
      max_total_score = current_total_score;
      copy(current_libraries_used.begin(), current_libraries_used.end(), back_inserter(libraries_used)); 
    }
    current_libraries_used.clear();
  }
  delete[] libraries_remaining;
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

void swapLongs(long &elem1, long &elem2)
{
  long temp = elem1;
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
long partitionIndexes(long indexes[], long left, long right)
{
  std::uniform_int_distribution<long> dist(left, right);
  unsigned long randIndex = dist(generator);
  swapLongs(indexes[randIndex], indexes[left]);
  int pivot = scores[indexes[left]];
  long s = left;
  for (long i = left + 1; i <= right; i++)
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
void quickSortBooks(long indexes[], long left, long right)
{
  if (left < right)
  {
    long partition = partitionIndexes(indexes, left, right);
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
  scores = new long[num_books];
  for (long i = 0; i < num_books; i++) {
    long current_book_score;
    file >> current_book_score;
    scores[i] = current_book_score;
    // cout << current_book_score << endl;
  }
  for (long i = 0; i < num_libraries; i++) {
    libraries.push_back(library());
    file >> libraries[i].num_books;
    file >> libraries[i].signup_time;
    file >> libraries[i].books_per_day;
    libraries[i].books.reserve(libraries[i].num_books);
    for (long j = 0; j < libraries[i].num_books; j++) {
      long current_book;
      file >> current_book;
      libraries[i].books.push_back(current_book);
    }
    if (libraries[i].books.size() > 0) {
      quickSortBooks(&libraries[i].books[0], 0, libraries[i].books.size() - 1);
    }
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
  delete[] scores;
}
