



template<typename T> struct Maybe
{
    T* context;
    Maybe(T* context) : context(context) {}
};

template<typename T> Maybe<T> maybe(T* context)
{
    return Maybe<T>(context);
};

template <typename Func>
auto With(Func evaluator)
{
    return context != nullptr ? maybe(evaluator(context)) : nullptr;
}

template<typename TFunc>
auto Do(TFunc action)
{
    if (context != nullptr)
    {
        action(context);
    }

    return *this;
}

void print_name(Person* p)
{
    auto z = maybe(p)
        .With([](auto x) { return x->adress; })
        .With([](auto x) { return x->house_name; })
        .Do([](auto x) { std::cout << std::endl; })
        
}