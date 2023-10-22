#include <string>

using namespace std;

struct Logger
{
    virtual ~Logger() = default;
    virtual void info(const string& s) = 0;
    virtual void warn(const string& s) = 0;
};

struct BankAccount
{
    std::shared_ptr<Logger> log;
    string name;
    int balance = 0;

    BankAccount(const std::shared_ptr<Logger>& logger,
    const string& name, int balance) : log{logger}, name{name}, balance{balance} {}

    void BankAccount::deposit(int amount)
    {
        balance += amount;
        log->info("Deposited $" + lexical_cast<string>(amount) + " to " + name + ", balance is now $" 
        + lexical_cast<string>(balance));)
    }
};

struct ConsoleLogger : Logger
{
    void info(const string& s) override
    {
        std::cout << "info : " << s << std::endl;
    }
    void warn(const string& s) override
    {
        std::cout << "waring : " << s << std::endl;
    }
};


struct NullLogger : Logger
{
    void info(const string& s) override{}
    void warn(const string& s) override{}
};


struct OptionalLogger : Logger
{
    shared_ptr<Logger> impl;
    static shared_ptr<Logger> no_logging;
    Logger(const shared_ptr<Logger>& logger) : impl{logger} {}
    virtual void info(const string& s) override
    {
        if(impl)
        {
            impl->info(s);
        }
    }
};

// static member containing Null Object //
shared_ptr<Logger> BankAccount::no_logging{};

shared_ptr<OptionalLogger> logger;
BankAccount(const string& name, int balance, const shared_ptr<Logger>& logger = no_logging):
log{make_shared<OptionalLogger>(logger)}, name{name}, balance{balance} { }


