#include <map>

class Database
{
    public:
    virtual int get_population(const std::string& name) = 0;
};

class SingletonDatabase: public Database
{
    SingletonDatabase() {}
    std::map<std::string, int> capitals;
    
    public:
    SingletonDatabase(SingletonDatabase const&) = delete;
    void operator=(SingletonDatabase const&) = delete;

    static SingletonDatabase& get()
    {
        static SingletonDatabase db;
        return db;
    }
    
    int get_population(const std::string& name) override
    {
        return capitals[name];
    }
}




struct SingletonRecordFinder
{
    int total_polulation(std::vector<std::string> names)
    {
        int result = 0;
        for (auto& name: names)
        {
            result += SingletonDatabase::get().get_population(name);
        }
        return result;
    }
};




TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
    SingletonRecordFinder rf;

    std::vector<std::string> names{"Tokyo", "TAIPEI"};

    int tp = rf.total_polulation(names);
    EXCEPT_EQ(18181818+19191919, tp);
}


struct ConfigurableRecordFinder
{
    explicit ConfigurableRecordFinder(Database& db): db{db} {}

    int total_population(std::vector<std::string> names)
    {
        int result = 0;
        for(auto& name: names)
        {
            result += db.get_population(name);
        }
        return result;
    }
    Database& db;
};


class DummyDatabase: public Database
{
    std::map<std::string, int> capitals;

    public:
    DummyDatabase()
    {
        capitals["alpha"]  =1 ;
        capitals["beta"]  =2 ;
        capitals["gamma"]  =3 ;

    }
    int get_population(const std::string& name) override
    {
        return capitals[name];
    }
};


TEST(RecordFinderTests, SingletonTotalPopulationTest)
{
    DummyDatabase db{};
    ConfigureableRecordFinder rf {db};

    EXCEPT_EQ(4, rf.total_population(std::vector<std::string>{"alpha", "gamma}));    
}



auto injector = di::make_injector(di::bind<IFoo>.to<Foo>.in(di::singleton), ////
);



class Printer
{
    static int id;
    public:
    int get_id() const { return id; }
    void set_id(int value) { id = value; }
}