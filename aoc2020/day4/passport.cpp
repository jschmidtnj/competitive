#include <bits/stdc++.h>
#include <boost/algorithm/string.hpp>

using namespace std;
using namespace boost;

#define RESERVE_SIZE 10000
// #define DEBUG

enum fields
{
  no_field,
  birth_year,
  issue_year,
  expiration_year,
  height,
  hair_color,
  eye_color,
  passport_id,
  country_id
};

unordered_set<fields> optional_fields = {country_id};

unordered_set<fields> required_fields = {birth_year, issue_year, expiration_year, height, hair_color, eye_color, passport_id};

unordered_map<fields, string> field_key_map({
    {birth_year, "byr"},
    {issue_year, "iyr"},
    {expiration_year, "eyr"},
    {height, "hgt"},
    {hair_color, "hcl"},
    {eye_color, "ecl"},
    {passport_id, "pid"},
    {country_id, "cid"},
});

enum units
{
  no_units,
  cm,
  in
};

unordered_map<units, string> units_key_map({
    {cm, "cm"},
    {in, "in"},
});

enum eye_colors
{
  no_eye_color,
  amber,
  blue,
  brown,
  gray,
  green,
  hazel,
  other
};

unordered_map<eye_colors, string> eye_colors_key_map({
    {amber, "amb"},
    {blue, "blu"},
    {brown, "brn"},
    {gray, "gry"},
    {green, "grn"},
    {hazel, "hzl"},
    {other, "oth"},
});

unordered_set<fields> numeric_fields({
    birth_year,
    issue_year,
    expiration_year,
});

unordered_map<fields, pair<size_t, size_t>> numeric_min_max({{birth_year, pair<size_t, size_t>(1920, 2002)},
                                                             {issue_year, pair<size_t, size_t>(2010, 2020)},
                                                             {expiration_year, pair<size_t, size_t>(2020, 2030)}});

unordered_map<units, pair<size_t, size_t>> height_min_max({
    {cm, pair<size_t, size_t>(150, 193)},
    {in, pair<size_t, size_t>(59, 76)},
});

unordered_set<fields> string_fields({
    hair_color,
    passport_id,
    country_id,
});

unordered_map<fields, size_t> string_length_map({
    {passport_id, 9},
});

const regex hex_code_regex = regex("^#[0-9a-f]{6}$");

struct passport_data
{
  fields invalid_field = no_field;
  size_t birth_year, issue_year, expiration_year, height;
  string hair_color, passport_id, country_id;
  eye_colors eye_color = no_eye_color;
  units height_units = no_units;
  unordered_set<fields> found_fields;
  string to_string() const;
};

string passport_data::to_string() const
{
  stringstream str_stream;
  str_stream << "invalid field: " << ((*this).invalid_field == no_field ? "none" : field_key_map[(*this).invalid_field]) << endl;
  str_stream << "birth year: " << (*this).birth_year << endl;
  str_stream << "issue year: " << (*this).issue_year << endl;
  str_stream << "expiration year: " << (*this).expiration_year << endl;
  str_stream << "height: " << (*this).height << endl;
  str_stream << "height units: " << units_key_map[(*this).height_units] << endl;
  str_stream << "hair color: " << (*this).hair_color << endl;
  str_stream << "eye color: " << ((*this).eye_color == no_eye_color ? "invalid" : eye_colors_key_map[(*this).eye_color]) << endl;
  str_stream << "passport id: " << (*this).passport_id << endl;
  str_stream << "country id: " << (*this).country_id << endl;
  return str_stream.str();
}

bool is_present(passport_data &passport)
{
  size_t num_required_fields = count_if(required_fields.begin(), required_fields.end(), [&](fields required_field) -> bool {
    bool found_required_field = passport.found_fields.find(required_field) != passport.found_fields.end();
    if (!found_required_field)
    {
      passport.invalid_field = required_field;
    }
    return found_required_field;
  });
  return num_required_fields == required_fields.size();
}

size_t solution_1(vector<passport_data> &passports)
{
  return count_if(passports.begin(), passports.end(), is_present);
}

bool is_valid(passport_data &passport)
{
  // numeric fields
  for (const fields &current_field : numeric_fields)
  {
    if (required_fields.find(current_field) != required_fields.end())
    {
      unordered_map<fields, pair<size_t, size_t>>::iterator find_min_max = numeric_min_max.find(current_field);
      if (find_min_max == numeric_min_max.end())
      {
        continue;
      }
      size_t current_value;
      switch (current_field)
      {
      case height:
        current_value = passport.height;
        break;
      case birth_year:
        current_value = passport.birth_year;
        break;
      case issue_year:
        current_value = passport.issue_year;
        break;
      case expiration_year:
        current_value = passport.expiration_year;
        break;
      default:
        cout << "unhandled field for numeric retrieval: " << field_key_map[current_field] << endl;
        exit(-1);
        return false;
      }
      pair<size_t, size_t> min_max = find_min_max->second;
      if (current_value < min_max.first || current_value > min_max.second)
      {
        passport.invalid_field = current_field;
        return false;
      }
    }
  }
  // height
  if (required_fields.find(height) != required_fields.end())
  {
    if (passport.height_units == no_units)
    {
      passport.invalid_field = height;
      return false;
    }
    unordered_map<units, pair<size_t, size_t>>::iterator find_min_max = height_min_max.find(passport.height_units);
    if (find_min_max != height_min_max.end())
    {
      pair<size_t, size_t> min_max = find_min_max->second;
      if (passport.height < min_max.first || passport.height > min_max.second)
      {
        passport.invalid_field = height;
        return false;
      }
    }
  }
  // eye color
  if (required_fields.find(eye_color) != required_fields.end())
  {
    if (passport.eye_color == no_eye_color)
    {
      passport.invalid_field = eye_color;
      return false;
    }
  }
  // string fields
  for (const fields &current_field : string_fields)
  {
    if (required_fields.find(current_field) != required_fields.end())
    {
      if (current_field == hair_color)
      {
        if (!regex_match(passport.hair_color, hex_code_regex))
        {
          passport.invalid_field = hair_color;
          return false;
        }
      }
      else if (current_field == passport_id || current_field == country_id)
      {
        string current_val;
        switch (current_field)
        {
        case passport_id:
          current_val = passport.passport_id;
          break;
        case country_id:
          current_val = passport.country_id;
          break;
        default:
          cout << "unhandled field for passport / country retrieval: " << field_key_map[current_field] << endl;
          exit(-1);
          return false;
        }
        unordered_map<fields, size_t>::iterator find_string_length = string_length_map.find(current_field);
        if (find_string_length != string_length_map.end())
        {
          if (current_val.length() != find_string_length->second)
          {
            passport.invalid_field = current_field;
            return false;
          }
          bool is_numeric = !current_val.empty() && find_if(current_val.begin(),
                                                            current_val.end(), [](unsigned char c) { return !isdigit(c); }) == current_val.end();
          if (!is_numeric)
          {
            passport.invalid_field = current_field;
            return false;
          }
        }
      }
      else
      {
        cout << "unhandled field for string retrieval: " << field_key_map[current_field] << endl;
        exit(-1);
        return false;
      }
    }
  }
  return true;
}

size_t solution_2(vector<passport_data> &passports)
{
  return count_if(passports.begin(), passports.end(), [](passport_data passport) -> bool {
    if (!is_present(passport))
    {
      return false;
    }
    bool valid = is_valid(passport);
#ifdef DEBUG
    if (!valid)
    {
      cout << (valid ? "valid" : "invalid") << "\n\n"
           << endl;
      cout << passport.to_string() << endl;
    }
#endif
    return valid;
  });
}

int main()
{
  string line;
  ifstream thefile("input.txt");
  stringstream str_stream, split_stream, int_stream;
  vector<passport_data> data;
  data.reserve(RESERVE_SIZE);
  passport_data current_passport;
  while (getline(thefile, line))
  {
    trim(line);
    if (line.length() == 0 && current_passport.found_fields.size() > 0)
    {
      data.push_back(current_passport);
      current_passport = passport_data();
    }
    str_stream.str(line);
    string split_space, split_elem;
    while (getline(str_stream, split_space, ' '))
    {
      trim(split_space);
      split_stream.str(split_space);
      int i = 0;
      fields current_field;
      while (getline(split_stream, split_elem, ':'))
      {
        if (i == 0)
        {
          // get field
          unordered_map<fields, string>::iterator find_field = find_if(field_key_map.begin(), field_key_map.end(), [&](pair<fields, string> key_val) -> bool {
            return key_val.second == split_elem;
          });
          if (find_field == field_key_map.end())
          {
            cout << "cannot find field " << split_elem << endl;
            return -1;
          }
          current_field = find_field->first;
        }
        else if (i == 1)
        {
          // get value
          if (numeric_fields.find(current_field) != numeric_fields.end() || current_field == height)
          {
            if (current_field == height)
            {
              unordered_map<units, string>::iterator find_unit = find_if(units_key_map.begin(), units_key_map.end(), [&](pair<units, string> key_val) -> bool {
                return algorithm::ends_with(split_elem, key_val.second);
              });
              if (find_unit == units_key_map.end())
              {
                cout << "cannot find units for " << split_elem << endl;
              }
              else
              {
                current_passport.height_units = find_unit->first;
                split_elem.substr(0, split_elem.length() - units_key_map[current_passport.height_units].length());
              }
            }
            int_stream.str(split_elem);
            long curr_cast;
            if (!(int_stream >> curr_cast))
            {
              cout << "cannot cast " << split_elem << " to int" << endl;
            }
            else
            {
              switch (current_field)
              {
              case height:
                if (current_passport.height_units != no_units)
                {
                  current_passport.height = curr_cast;
                }
                break;
              case birth_year:
                current_passport.birth_year = curr_cast;
                break;
              case issue_year:
                current_passport.issue_year = curr_cast;
                break;
              case expiration_year:
                current_passport.expiration_year = curr_cast;
                break;
              default:
                cout << "unhandled field for numeric cast: " << field_key_map[current_field] << endl;
                return -1;
              }
            }
            int_stream.clear();
          }
          else if (current_field == eye_color)
          {
            unordered_map<eye_colors, string>::iterator find_eye_color = find_if(eye_colors_key_map.begin(), eye_colors_key_map.end(), [&](pair<eye_colors, string> key_val) -> bool {
              return key_val.second == split_elem;
            });
            if (find_eye_color == eye_colors_key_map.end())
            {
              cout << "cannot find eye color " << split_elem << endl;
            }
            else
            {
              current_passport.eye_color = find_eye_color->first;
            }
          }
          else if (string_fields.find(current_field) != string_fields.end())
          {
            switch (current_field)
            {
            case hair_color:
              current_passport.hair_color = split_elem;
              break;
            case passport_id:
              current_passport.passport_id = split_elem;
              break;
            case country_id:
              current_passport.country_id = split_elem;
              break;
            default:
              cout << "unhandled field for string input: " << field_key_map[current_field] << endl;
              return -1;
            }
            current_passport.hair_color = split_elem;
          }
          current_passport.found_fields.insert(current_field);
        }
        else
        {
          cout << "too many key values in element" << endl;
          return -1;
        }
        i++;
      }
      split_stream.clear();
    }
    str_stream.clear();
  }
  if (current_passport.found_fields.size() > 0)
  {
    data.push_back(current_passport);
  }
  size_t res_1 = solution_1(data);
  cout << "part 1 output: " << res_1 << endl;
  size_t res_2 = solution_2(data);
  cout << "part 2 output: 1" << res_2 << endl;
}
