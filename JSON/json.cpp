#include "json.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

namespace json
{

bool
is_eof(const char* first, const char* last)
{
  return first == last;
}

bool
is_punctuation(const char* first, const char* last)
{
  if (is_eof(first, last))
    return false;
  switch (*first) {
  default:
    return false;    
  case '[':
  case ']':
  case '{':
  case '}':
  case ':':
  case ',':
    return true;
  }
}

bool
is_space(const char* first, const char* last)
{
  if (is_eof(first, last))
    return false;
  return std::isspace(*first);
}

bool
is_delimiter(const char* first, const char* last)
{
  return is_eof(first, last) 
      || is_space(first, last)
      || is_punctuation(first, last);
}

bool
match_literal(const char*& first, const char* last, const char* word)
{
  auto q = word;
  while (!is_eof(first, last) && *q != '\0' && *first == *q) {
    ++first;
    ++q;
  }
  if (*q != '\0')
    throw std::runtime_error("invalid literal");
  if (!is_delimiter(first, last))
    throw std::runtime_error("invalid literal");
  return true;
}

void
skip_space(const char*& first, const char* last)
{
  while (is_space(first, last))
    ++first;
}

struct space_guard
{
  space_guard(const char*& f, const char* l)
    : first(f), last(l)
  {
    skip_space(first, last);
  }

  ~space_guard()
  {
    skip_space(first, last);
  }

  const char*& first;
  const char* last;
};

Value* parse_value(const char*& first, const char* last);

Bool*
parse_true(const char*& first, const char* last)
{
  match_literal(first, last, "true");
  return new Bool(true);
}

Bool*
parse_false(const char*& first, const char* last)
{
  match_literal(first, last, "false");
  return new Bool(false);
}

Null*
parse_null(const char*& first, const char* last)
{
  match_literal(first, last, "null");
  return new Null();
}

String*
parse_string(const char*& first, const char* last)
{
  const char* start = first++;
  while (!is_eof(first, last) && *first != '"') {
    if (*first == '\\')
      ++first;
    ++first;
  }
  assert(*first == '"');
  ++first;
  return new String(start, first);
}

Number*
parse_number(const char*& first, const char* last)
{
  const char* start = first++;
  while (!is_eof(first, last) && !is_delimiter(first, last))
    ++first;

  std::string str(start, first);
  std::stringstream ss(str);
  double d;
  ss >> d;
  if (!ss)
    throw std::runtime_error("invalid number");
  return new Number(d);
}

Array*
parse_array(const char*& first, const char* last)
{
  Array* arr = new Array();

  ++first;
  space_guard g1(first, last);

  if (*first == ']') {
    ++first;
    return arr;
  }

  while (true) {

    Value* v = parse_value(first, last);
    arr->push_back(v);

    if (first == last)
      throw std::runtime_error("invalid array");
    if (*first == ',') {
      ++first;
      continue;
    }
    if (*first == ']')
      break;
  }
  assert(*first == ']');
  ++first;

  return arr;
}


String*
parse_key(const char*& first, const char* last)
{
  space_guard g(first, last);
  return parse_string(first, last);
}

Object*
parse_object(const char*& first, const char* last)
{
  Object* obj = new Object();

  ++first;
  space_guard g1(first, last);

  if (*first == '}') {
    ++first;
    return obj;
  }

  while (true) {

    String* k = parse_key(first, last);

    if (first == last)
      throw std::runtime_error("invalid object");
    if (*first != ':')
      throw std::runtime_error("expected ':'");
    ++first;

    Value* v = parse_value(first, last);

    obj->emplace(*k, v);

    if (first == last)
      throw std::runtime_error("invalid array");
    if (*first == ',') {
      ++first;
      continue;
    }
    if (*first == '}')
      break;
  }
  assert(*first == '}');
  ++first;

  return obj;
}

Value*
parse_value(const char*& first, const char* last)
{
  if (is_eof(first, last))
    return nullptr;

  space_guard g(first, last);
  
  switch (*first) {
    case 't':
      return parse_true(first, last);
    case 'f':
      return parse_false(first, last);
    case 'n':
      return parse_null(first, last);
    case '"':
      return parse_string(first, last);
    case '[':
      return parse_array(first, last);
    case '{':
      return parse_object(first, last);
    case '0': case '1': case '2': case '3': case '4': 
    case '5': case '6': case '7': case '8': case '9':
    case '-':
      return parse_number(first, last);
    default:
      throw std::runtime_error("invalid error");
  }
}

Value* 
parse(const std::string& str)
{
  const char* first = str.c_str();
  const char* last = first + str.size();
  return parse_value(first, last);
}


int
size(Value const* v)
{

  return v->size();
}

int
height(Value const* v)
{
  return v->height();
}

struct indentation
{
  indentation(int lev, bool inl)
    : level(lev), inl(inl)
  { }

  int level;
  bool inl;
};

struct trailer
{
  trailer(bool c)
    : cont(c)
  { }

  bool cont;
};

indentation
indent(int level, bool inl)
{
  return indentation(level, inl);
}

trailer
comma(bool c)
{
  return trailer(c);
}

std::ostream&
operator<<(std::ostream& os, indentation in)
{
  if (!in.inl)
    os << std::string(2 * in.level, ' ');
  return os;
}

std::ostream&
operator<<(std::ostream& os, trailer trail)
{
  if (trail.cont)
    os << ',';
  return os;
}

void
Null::print(std::ostream& os, int level, bool inl, bool cont) const
{
  os << indent(level, inl) 
     << "null"
     << comma(cont);
}

void
Bool::print(std::ostream& os, int level, bool inl, bool cont) const
{
  os << indent(level, inl) 
     << (value ? "true" : "false")
     << comma(cont);
}

void
Number::print(std::ostream& os, int level, bool inl, bool cont) const
{ 
  os << indent(level, inl) 
     << value
     << comma(cont);
}

void
String::print(std::ostream& os, int level, bool inl, bool cont) const
{
  os << indent(level, inl) 
     << c_str()
     << comma(cont);
}

void
Array::print(std::ostream& os, int level, bool inl, bool cont) const
{
  if (empty()) {
    os << indent(level, inl) 
       << "[]"
       << comma(cont);
    return;
  }

  os << indent(level, inl) << '[' << '\n';

  inl = false;

  ++level;
  for (auto i = begin(); i != end(); ++i) {
    Value* v = *i;
    bool next = (std::next(i) != end());
    v->print(os, level, inl, next);
    os << '\n';
  }
  --level;

  os << indent(level, inl) << ']'<< comma(cont);
}

void
Object::print(std::ostream& os, int level, bool inl, bool cont) const
{ 
  if (empty()) {
    os << indent(level, inl) 
       << "{}"
       << comma(cont);
    return;
  }

  os << indent(level, inl) << '{' << '\n';

  inl = false;

  ++level;
  for (auto i = begin(); i != end(); ++i) {
    value_type const& kv = *i;
    bool next = (std::next(i) != end());
    os << indent(level, inl) << kv.first << " : ";
    kv.second->print(os, level, true, next);
    os << '\n';
  }
  --level;

  os << indent(level, inl) << '}' << comma(cont);
}

std::ostream&
operator<<(std::ostream& os, Value const& v)
{
  v.print(os, 0, false, false);
}


}
