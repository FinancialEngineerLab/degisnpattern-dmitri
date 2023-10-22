
#include <iostream>
#include <vector>

struct GraphicObject
{
    virtual void draw () = 0;
};

struct Circle: GraphicObject
{
    void draw() override
    {
        std::cout << std::endl;
    }
};



struct Group : GraphicObject
{
    std::string name;

    explicit Group(const std::string& name) : name{name} {}

    void draw() override
    {
        std::cout << name.c_str() << std::endl;

    for (auto&& o : objects)
        {
            o->draw();
        }
    }

    std::vector<GraphicObject> objects;
}