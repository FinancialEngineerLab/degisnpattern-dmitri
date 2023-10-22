#include "PersonBuilder.hpp"
#include "PersonAddressBuilder.hp"
#include "PersonJobBuilder.hpp"

PersonAddressBuilder PersonBuilderBase::lives() const
{
  return PersonAddressBuilder{ person };
}

PersonJobBuilder PersonBuilderBase::works() const
{
  return PersonJobBuilder{ person };
}
