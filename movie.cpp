#include <sstream>
#include "movie.h"
#include "util.h"

using namespace std;

Movie::Movie(const std::string category, const std::string name, double price, int qty, const std::string genre, const std::string rating) : 
    Product("movie", name, price, qty), 
    genre_(genre),
    rating_(rating) 
{

}

Movie::~Movie()
{

}

std::set<std::string> Movie::keywords() const
{
    std::set<std::string> name = parseStringToWords(name_);
    std::set<std::string> author = parseStringToWords(genre_);

    std::set<std::string> keywords = setUnion(name, author);
    keywords.insert(convToLower(rating_));

    return keywords;
}

// bool Movie::isMatch(std::vector<std::string>& searchTerms) const
// {
//     return 
// }

std::string Movie::displayString() const
{
    stringstream ss;
    ss << name_ << "\n" << "Genre: " << genre_ << " Rating: " << rating_ << "\n" << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const
{
    os << "movie" << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}