#include <string>

using namespace std;

struct User2
{
    flyweight<string> first_name, last_name;

    User2(const string& first_name, const string& last_name) : first_name(first_name), last_name(last_name) {}
};


class FormattedText
{
    string plainText;
    bool *caps;

    public:
    explicit FormattedText(const string& plainText) : plainText{plainText}
    {
        caps = new bool[plainText.length()];
    }
    ~FormattedText()
    {
        delete[] caps;
    }
};

void capitalize(int start, int end)
{
    for(int i = start; i<=end;++i)
    {
        caps[i] = true;
    }
}

friend std::ostream& operator<<(std::ostream& os, const FormattedText& obj)
{
    string s;
    for(int i = 0; i<obj.plainText.length(); ++i)
    {
        char c = obj.plainText[i];
        s += (obj.caps[i] ? toupper(c) : c);
    }
    return os << s;
}

class BetterFormattedText
{
    public:
        struct TextRange
        {
            int start, end;
            bool capitalize;
            bool covers(int position) const
            {
                return postion >= start&& position <= end;
            }
        };

    private:
        string plain_text;
        std::vector<TextRange> formatting;
};


TextRange& get_range(int start, int end)
{
    formatting.emplace_back(TextRange {start, end });
    return *formatting.rbegin();
}

friend std::ostream& operator<<(std::ostream& os, 
const BetterFormattedText& obj)
{
    string s;
    for(size_t i = 0; i<obj.plain_text.length();i++)
    {
        auto c = obj.plain_text[i];
        for(const auto& rng : obj.formatting)
        {
            if (rng.covers(i) && rng.capitalize)
            {
                c = toupper(c);
            }
            s += c;
        }
    }
    return os << s;
};


