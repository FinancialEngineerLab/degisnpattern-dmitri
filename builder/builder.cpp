// Online C++ compiler to run C++ program online
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <tuple>
#include <sstream>
#include <memory>

using namespace std;

struct HtmlElement
{
    std::string name, text;
    std::vector<HtmlElement> elements;
    
    const size_t indent_size = 2;

    HtmlElement() {}
    HtmlElement(const std::string& name, const string& text) : name(name), text(text) {}
    
    std::string str(int indent = 0) const 
    {
        osstringstream oss;
        string i(indent_size * indent, ' ');
        oss << i<< "<" << name << ">" << std::endl;
        if (text.size() > 0)
        {
            oss << string(indent_size * (indent +1) , ' ') << std::endl;
        }
    }
};


struct HtmlBUilder
{
    HtmlElement root;
    HtmlBuilder(std::string root_name)
    {
        root.name = root_name;
    }
    
    void add_child(std::string child_name, std::string child_text)
    {
        HtmlElement e { child_name, child_text};
        root.elements.emplace_back(e);
    }
    
    std::string str() const { return root.str(); }
};



int main() {
    // Write C++ code here
    auto text = "hello";
    std::string output;
    
    output += "<p>";
    output += text;
    output += "</p>";
    
    std::cout << output << std::endl;
    
    std::string words[] = {"hello", "world"};
    ostringstream oss;
    
    oss<<"<ul>";
    for(auto w : words)
    {
        oss << "  <li>" << w << "</li>";
    }
    oss << "</ul>";
    std::cout << oss.str() << std::endl;
    
    HtmlBuilder bulilder{"ul"};
    builder.add_child("li", "hello");
    builder.add_child("li", "world");
    std::cout << builder.str() << std::endl;
    
    return 0;
}
