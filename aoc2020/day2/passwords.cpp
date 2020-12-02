#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

#define RESERVE_SIZE 10000

struct password_data
{
  vector<size_t> nums;
  char character;
  string password;
  password_data(vector<size_t> _nums, char _character, string _password)
      : nums{_nums}, character{_character}, password{_password} {};
  string to_string() const;
};

string password_data::to_string() const {
  stringstream str_stream;
  str_stream << (*this).character << ": " << (*this).nums[0] << "&" << (*this).nums[1] << "; " << (*this).password;
  return str_stream.str();
}

size_t solution_1(vector<password_data> &data)
{
  size_t valid_count = 0;
  for (password_data &elem : data)
  {
    // run check
    // cout << elem.to_string() << endl;
    size_t num_chars = count(elem.password.begin(), elem.password.end(), elem.character);
    if (num_chars >= elem.nums[0] && num_chars <= elem.nums[1]) {
      valid_count++;
    }
  }
  return valid_count;
}

size_t solution_2(vector<password_data> &data)
{
  size_t valid_count = 0;
  for (password_data &elem : data)
  {
    int count_position = 0;
    for (size_t num : elem.nums) {
      num--; // index starts at 1
      if (num >= 0 && num < elem.password.size() && elem.password[num] == elem.character) {
        count_position++;
      }
    }
    if (count_position == 1) {
      valid_count++;
    }
  }
  return valid_count;
}

int main()
{
  string line;
  ifstream thefile("input.txt");
  stringstream str_stream, int_stream;
  vector<password_data> data;
  data.reserve(RESERVE_SIZE);
  while (getline(thefile, line))
  {
    str_stream.str(line);
    string split_elem;
    string password;
    int i = 0;
    while (getline(str_stream, split_elem, ':'))
    {
      trim(split_elem);
      switch (i)
      {
      case 0:
        line = split_elem;
        break;
      case 1:
        password = split_elem;
        break;
      default:
        cout << "too many colons found" << endl;
        return -1;
      }
      i++;
    }
    i = 0;
    str_stream.clear();

    str_stream.str(line);
    char character = ';';
    while (getline(str_stream, split_elem, ' '))
    {
      trim(split_elem);
      switch (i)
      {
      case 0:
        line = split_elem;
        break;
      case 1:
        character = split_elem[0];
        break;
      default:
        cout << "too many spaces found" << endl;
        return -1;
      }
      i++;
    }
    i = 0;
    str_stream.clear();

    str_stream.str(line);
    vector<size_t> curr_nums;
    while (getline(str_stream, split_elem, '-'))
    {
      trim(split_elem);
      int_stream.str(split_elem);
      size_t curr_cast;
      if (!(int_stream >> curr_cast))
      {
        cout << "cannot cast " << split_elem << " to int" << endl;
        return -1;
      }
      curr_nums.push_back(curr_cast);
      if (curr_nums.size() > 2) {
        cout << "too many dashes found" << endl;
        return -1;
      }
      int_stream.clear();
    }
    str_stream.clear();

    data.push_back(password_data(curr_nums, character, password));
  }
  size_t res_1 = solution_1(data);
  cout << "part 1 output: " << res_1 << endl;
  size_t res_2 = solution_2(data);
  cout << "part 2 output: " << res_2 << endl;
}
