#include <fstream>
#include <iostream>

class Data
{
public:

    Data(std::string data)
        : data_(std::move(data)) {}

    virtual void print(std::ofstream& file) const = 0;

protected:
    std::string data_;
};

class HtmlData : public Data
{
public:

    HtmlData(std::string data)
        : Data(data) {}

    void print(std::ofstream& file) const override
    {
        file << getHtml();
    }

    std::string getHtml() const 
    {
        return "<html>" + data_ + "<html/>";
    }
};

class JsonData : public Data
{
public:

    JsonData(std::string data)
        : Data(data) {}

    void print(std::ofstream& file) const override
    {
        file << getJson();
    }

    std::string getJson() const
    {
        return "{ \"data\": \"" + data_ + "\"}";
    }
};

class TextData : public Data
{
public:

    TextData(std::string data)
        : Data(data) {}

    void print(std::ofstream& file) const override
    {
        file << getText();
    }

    std::string getText() const
    {
        return data_;
    }
};


void saveTo(const std::string& filePath, const Data& data)
{
    std::ofstream file(filePath);
    data.print(file);
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