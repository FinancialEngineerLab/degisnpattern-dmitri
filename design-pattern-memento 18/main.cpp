#include <iostream>
#include <ostream>
#include <vector>

class Memento
{
  int balance;
public:
  Memento(int balance)
    : balance(balance)
  {
  }
  friend class BankAccount;
  friend class BankAccount2;
};



class BankAccount
{
    int balance = 0;

    public:
        explicit BankAccount(const int balance) : balance(balance) { }

    Memento deposit(int amount)
    {
        balance += amount;
        return { balance };
    }

    void restore(const Memento& m)
    {
        balance = m.balance;
    }

    friend ostream& operator<<(ostream& os, const BankAccount& obj)
    {
        return os << "balance: " << obj.balance;
    }
};


void memento()
{
    BankAccount ba { 100 } ;

    auto m1 = ba.deposit(50);
    auto m2 = ba.deposit(30);
    
    
    std::cout << std::endl;
    ba.restore(m1);
     std::cout << std::endl;
    ba.restore(m2);

     std::cout << std::endl;
};


class BankAccount2
{
    int balance = 0;
    std::vector<ext::shared_ptr<Memento> > changes;
    int current;

    public:
        explicit BankAccount2(const int balance) : balance(balance)
        {
            changes.emplace_back(ext::make_shared<Memento>(balance));
            current = 0;
        }

        
  shared_ptr<Memento> deposit(int amount)
  {
    balance += amount;
    auto m = make_shared<Memento>(balance);
    changes.push_back(m);
    ++current;
    return m;
  }

  void restore(const shared_ptr<Memento>& m)
  {
    if (m)
    {
      balance = m->balance;
      changes.push_back(m);
      current = changes.size() - 1;
    }
  }
};


ext::shared_ptr<Memento> undo()
{
    if(current >0)
    {
        --current;

        auto m = changes[current];
        balance = m->balance;
        return m;
    }
    return {};
}


ext::shared_ptr<Memento> redo()
{
    // 변경목록에 대한 현재 위치가 0보다 클떄만 실행 (book) //
    if(current + 1 < changes.size())
    {
        ++current;
        auto m = changes[current];
        balance = m->balance;
        return m;
    }
    return {};
}

