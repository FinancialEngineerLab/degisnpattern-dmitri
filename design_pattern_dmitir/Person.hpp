#pragma once

#include <string>
#include <iostream>


class Person
{
    // address
    std::string street_address, post_code, city;

  // employment
    std::string company_name, position;
    int annual_income{0};

     Person()
     {
        std::cout << "Person created\n";
     }
  
    public:
    ~Person()
    {
        std::cout << "Person destroyed\n";
    }

    static PersonBuilder create();




    friend class PersonBuilder;
    friend class PersonAddressBuilder;
    friend class PersonJobBuilder;
};