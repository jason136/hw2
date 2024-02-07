#include <sstream>
#include "clothing.h"
#include "util.h"

using namespace std;

Clothing::Clothing(const std::string category, const std::string name, double price, int qty, const std::string size, const std::string brand) : 
    Product("clothing", name, price, qty), 
    size_(size),
    brand_(brand)
{

}

Clothing::~Clothing()
{

}

std::set<std::string> Clothing::keywords() const
{
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> author = parseStringToWords(brand_);

    std::set<std::string> keywords = setUnion(name, author);
    keywords.insert(convToLower(size_));

    return keywords;
}

// bool Clothing::isMatch(std::vector<std::string>& searchTerms) const
// {
//     return 
// }

std::string Clothing::displayString() const
{
    stringstream ss;
    ss << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << "clothing" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}