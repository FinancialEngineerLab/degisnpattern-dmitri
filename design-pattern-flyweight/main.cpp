#include <iostream>

typedef uint32_t key;

struct User
{
    public:
    User(const string& first_name, const string& last_name) : first_name{add(first_name)}, last_name{add(last_name)} {}
    ...

    protected:
    key first_name, last_name;

    static bimap<key, string> names;
    static key seed;
    static key add(const string& s) { ... } 
};

static key add(const string& s)
{
    auto it = names.right.find(s);
    if (it == names.right.end())
    {
        names.insert({++seed, s});
        return seed;
    }
    return it->second;
}

const string& get_first_name() const 
{
    return names.left.find(last_name)->second;
}

const string& get_last_name() const
{
    return names.left.find(last_name)->second;
}

friend ostream& operator<< (ostream& os, const User& obj)
{
    return os << "first name : " << obj.get_first_name() << "last name : " << obj.get_last_name();
}

