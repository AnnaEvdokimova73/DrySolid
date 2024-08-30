#include <fstream>
#include <iostream>

enum class Format
{
    kText,
    kHtml,
    kJson
};

class Data
{
public:

    Data(std::string data, Format format)
        : data_(std::move(data)), format_(format) {}

    virtual void print(std::ofstream& file) const = 0;

protected:
    std::string data_;
    Format format_;
};

class HtmlData : public Data
{
public:

    HtmlData(std::string data, Format format)
        : Data(data, format) {}

    void print(std::ofstream& file) const override
    {
        file << getHtml();
    }

    std::string getHtml() const 
    {
        if (format_ != Format::kHtml) {
            throw std::runtime_error("Invalid format in Html!");
        }
        return "<html>" + data_ + "<html/>";
    }
};

class JsonData : public Data
{
public:

    JsonData(std::string data, Format format)
        : Data(data, format) {}

    void print(std::ofstream& file) const override
    {
        file << getJson();
    }

    std::string getJson() const
    {
        if (format_ != Format::kJson) {
            throw std::runtime_error("Invalid format in Json!");
        }
        return "{ \"data\": \"" + data_ + "\"}";
    }
};

class TextData : public Data
{
public:

    TextData(std::string data, Format format)
        : Data(data, format) {}

    void print(std::ofstream& file) const override
    {
        file << getText();
    }

    std::string getText() const
    {
        if (format_ != Format::kText) {
            throw std::runtime_error("Invalid format in Text!");
        }
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
    try
    {
        HtmlData htmlData("Some html information", Format::kHtml);
        JsonData jsonData("Some json information", Format::kJson);
        TextData textData("Some text information", Format::kText);

        saveTo("HtmlData.txt", htmlData);
        saveTo("JsonData.txt", jsonData);
        saveTo("TextData.txt", textData);
    }
    catch (const std::runtime_error& err)
    {
        std::cout << err.what() << std::endl;
    }
}