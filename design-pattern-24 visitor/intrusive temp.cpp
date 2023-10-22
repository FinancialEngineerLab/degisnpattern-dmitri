#include <sstream>
#include <string>
#include <iostream>

using namespace std;

struct Expression
{
  virtual void print(ostringstream& oss) = 0;
};

struct DoubleExpression : Expression
{
  double value;

  explicit DoubleExpression(const double value)
    : value{value} {}

  void print(ostringstream& oss) override // for virtual
  {
    oss << value;
  }
};

struct AdditionExpression : Expression
{
    // *** //
  Expression *left, *right;

  AdditionExpression(Expression* const left,
  Expression* const right)
    : left{left}, right{right} {}

  ~AdditionExpression()
  {
    delete left;
    delete right;
  }
