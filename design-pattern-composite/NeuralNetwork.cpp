#include <vector>

struct Neuron
{
    std::vector<Neuron*> in, out;
    unsigned int id;

    Neuron()
    {
        static int id = 1;
        this->id = id++;
    }
};


template<> void connect_to<Neuron>(Neuron& other)
{
    out.push_back(&other);
    other.in.push_back(this);
}


// Multiple Inheritance //

template <typename Self>
struct SomeNeurons
{
    template <typename T> void connect_to(T& other)
    {
        for(Neuron& from: *static_cast<Self*>(this))
        {
            for(Neuron& to : other)
            {
                from.out.push_back(&to);
                to.in.push_back(&from);
            }
        }
    }
};

Neuron* begin() override { return this;}
Neuron* end() override { return this +1 ;}


// Shrhik-Warpping the Composite

template <typename T> class Scalar : public SomeNuerons<T>
{
    public:
    T* begin() { return reinterpret_cast<T*> (this);}
    T* end() { return reinterpret_cast<T*> (this)+1;}
};

// Conceptual Improvements //

template <typename T> concept Iterable = requires(T& t) { t.begin(); t.end(); } ||  requires(T& t) { begin(t); end(t); };


//

template <Iterable T> class Scalar : public SomeNeurons<T>
{
};


template <Iterable T> ConnectionProxy<T> operator--(T&& item, int)
{
    return ConnectionProxy<T> {item};
}

template <Iterable T> class ConnectionProxy
{
    T& item;

    public:
        explicit ConnectionProxy(T& item) : item{item} {}

        template<Iterable U> void operator>(U& other)
        {
            for(Neuron& from : item)
            {
                for(Neuron& to : other)
                {
                    from.out.push_back(&to);
                    to.in.push_back(&from);
                }
            }
        }
};

//

template <typename T> struct CompositeSpecification : Specification<T>
{
    protected:
        std::vector<unique_ptr<Specification<T> > > > specs;

        template<typename... Specs> CompositeSpecification(specs...specs)
        {
            this->specs.reserve(sizeof...(Specs));
            (this->specs.push_back(make_unique<Specs>(move(specs))), ... );
        }
};

template <typename T> struct AndSpecification : CompositeSpecification<T>
{
    template <typename... Specs> AndSpecification(Sepcs... specs):CompositeSpecification<T>{specs...} {}

    bool is_statisfied(T* item) const override
    {
        return all_of(this->specs.begin(), this->sepecs.end(),[=](const auto& s)
        { 
            return s->is_satisfied(item);
        }
        );
    }
};

auto spec = AndSpecification<Product>  { green, large, cheap };






//











// execution //

Neuron neuron, neuron2;
NeuronLayer layer, layer2;
neuron.connect_to(neuron2);
neuron.connect_to(layer);
layer.connect_to(neuron);
layer.connect_to(layer2);