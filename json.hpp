#pragma once

#include <algorithm>
#include <string>
#include <vector>
#include <unordered_map>

namespace json
{

  struct PrintContext
  {
    std::ostream& os;
    int level;
    bool inl;
    bool cont;
  };

  struct Value
  {
    virtual ~Value() = default;

    virtual int size() const { return 1; }

    virtual int height() const { return 0; }

    
    virtual void print(std::ostream& os, int level, bool inl, bool cont) const = 0;

    virtual void print(PrintContext& cxt) { }

    virtual Value* find_key(std::string const&) { return nullptr; }

    virtual Value* find_key_value(std::string const&, std::string const&) { return nullptr; }
  };

  struct Null : Value
  {
    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };

  struct Bool : Value
  {
    Bool(bool v) : value(v) { }
    
    void print(std::ostream& os, int level, bool inl, bool cont) const override;

  
    bool value;
  };

  struct Number : Value
  {
    Number(double v) : value(v) { }

    void print(std::ostream& os, int level, bool inl, bool cont) const override;

    double value;
  };


  struct String : Value, std::string
  {
    using std::string::string;

    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };


  struct Array : Value, std::vector<Value*>
  {
    using std::vector<Value*>::vector;

    int size() const override {
      int n = 1;
      for (Value* v : *this)
        n += v->size();
      return n;
    }

    int height() const override {
      Value* v = *std::max_element(begin(), end(),
        [](Value* a, Value* b) {
          return a->height() < b->height();
        });
      return v->height() + 1;
    }

    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };

  struct Object 
    : Value, std::unordered_map<std::string, Value*>
  {
    using std::unordered_map<std::string, Value*>::unordered_map;

    int size() const override {
      int n = 1;
      for (value_type const& kv : *this)
        n += kv.second->size();
      return n;
    }

    int height() const override {
      return 0;

    }

    void print(std::ostream& os, int level, bool inl, bool cont) const override;
  };



  Value* parse(std::string const& str);

  int size(Value const* val);
  
  int height(Value const* val);


  std::ostream& operator<<(std::ostream& os, Value const& v);

}
