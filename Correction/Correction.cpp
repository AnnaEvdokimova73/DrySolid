#include <fstream>
#include <iostream>


class Data
{
protected:
    enum class Format
    {
        kText,
        kHtml,
        kJson
    };

public:
    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    virtual std::string print() const = 0;

    virtual ~Data() = default;

protected:
    std::string data_;
    Format format_;
};

class HtmlData : public Data
{
public:

    HtmlData(std::string data)
        : Data(data, Format::kHtml) {}

    std::string print() const override
    {
        return "<html>" + data_ + "<html/>";
    }
};

class JsonData : public Data
{
public:

    JsonData(std::string data)
        : Data(data, Format::kJson) {}

    std::string print() const override
    {
        return "{ \"data\": \"" + data_ + "\"}";
    }
};

class TextData : public Data
{
public:

    TextData(std::string data)
        : Data(data, Format::kText) {}

    std::string print() const override
    {
        return data_;
    }
};


void saveTo(const std::string& filePath, const Data& data)
{
    std::ofstream file(filePath);
    file << data.print();
}


int main()
{
    HtmlData htmlData("Some html information");
    JsonData jsonData("Some json information");
    TextData textData("Some text information");

    saveTo("HtmlData.txt", htmlData);
    saveTo("JsonData.txt", jsonData);
    saveTo("TextData.txt", textData);
}