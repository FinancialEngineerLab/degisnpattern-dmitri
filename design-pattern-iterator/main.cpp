
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> names { "A" , " B"};
std::vector<std::string>::iterator it = names.begin();


for (auto ri = rbegin(names); ri != rend(names); ++ri)
{
    std::cout << *ri;

    if(ri+1 != rend(names))
    {
        std::cout << ", ";
    }
};

std::vector<std::string>::const_reverse_iterator jack = crbegin(names);

*jack += "read";

