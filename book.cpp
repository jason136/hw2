#include <sstream>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string category, const std::string name, double price, int qty, const std::string isbn, const std::string author) : 
    Product("book", name, price, qty), 
    isbn_(isbn), 
    author_(author) 
{

}

Book::~Book()
{

}

std::set<std::string> Book::keywords() const
{
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> author = parseStringToWords(author_);

    std::set<std::string> keywords = setUnion(name, author);
    keywords.insert(isbn_);

    return keywords;
}

// bool Book::isMatch(std::vector<std::string>& searchTerms) const
// {
//     return 
// }

std::string Book::displayString() const
{
    stringstream ss;
    ss << name_ << "\n" << "Author: " << author_ << " ISBN: " << isbn_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Book::dump(std::ostream& os) const
{
    os << "book" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << isbn_ << "\n" << author_ << endl;
}