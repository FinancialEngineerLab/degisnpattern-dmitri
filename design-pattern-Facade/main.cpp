

struct Generator
{
    virtual std::vector<int> generate(const int count) const
    {
        std::vector<int> result(count);
        generate(result.beign(), result.end(), [&]() { return 1 + rand()%9; });

        return result;
    }
};

struct Splitter
{
    std::vector<std::vector<int> > split(std::vector<std::vector<int> > array) const
    {
        // implemantion omitted
    }
};

struct Verifier
{
    bool verify(std::vector<std::vector<int> > array) const
    {
        if (array.empty()) return false;

        auto expected = std::accumulate(array[0].begin(), array[0].end(), 0);
        
        return all_of(array.begin(), array.end(), [=](auto& inner)
        {
            return std::accumulate(inner.begin(), inner.end(), 0 ) == expected;
        }
        );
    }
};



struct MagicSquareGenerator
{
    std::vector<std::vector<int> > generate(int size)
    {
        Generator g;
        Splitter s;
        Verifier v;

        std::vector<std::vector<int> > square;

        do
        {
            square.clear();
            for(int i= 0; i <size; ++i)
            {
                square.emplace_back(g.generate(size));
            } while( !v.verify(s.split(square)));
        }
        return square;
    }
};

template <typename G = Generator, typename S = Splitter, typename V = Verifier>
struct MagicSquareGenerator
{
    std::vector<std::vector<int> > generate(int size)
    {
        G g;
        S s;
        V v;
        // rest ! //
    }
};


struct UniqueGenerator :  Generator
{
    virtual std::vector<int> generate(const int count) const
    {
        std::vector<int> result;
        do
        {
            result = Generator::generate(count);
        } while (set<int>(result.begin(), result.end()).size() != result.size());
    }
};


struct TableBuffer : IBuffer
{
    TableBuffer(std::vector<TableColumnSpec> spec, int totalHeight) { ... }

    struct TableColumnSpec
    {
        std::string header;
        int width;
        enum class TableColumnAlignment
        {
            Left, Center, Right
        } alignment;
    }
};


struct Console
{
    std::vector<Viewport*> viewports;
    Size charSize, gridSize;
    ...
};

Console::Console(bool fullscreen, int char_width, int char_height, int width, int height, optional<Size> client_size)
{
}
Console::Console(const ConsoleCreationParameters& ccp)
{
    ...
}


struct ConsoleCreationParameters
{
    optional<Size> client_size;
    int character_width{10};
    int character_height{14};
    int width{20};
    int height{30};
    bool fullscreen {false};
    bool create_default_view_and_buffer{true};
};


