#include <iomanip>
#include "mydatastore.h"
#include "util.h"

MyDataStore::MyDataStore()
{

}

MyDataStore::~MyDataStore()
{
    std::set<Product*>::iterator it;
    for(it = products_.begin(); it != products_.end(); ++it)
    {
        delete *it;
    }
    std::map<std::string, User*>::iterator it2;
    for(it2 = users_.begin(); it2 != users_.end(); ++it2)
    {
        delete it2->second;
    }
}

void MyDataStore::addProduct(Product* p)
{
    products_.insert(p);
}

void MyDataStore::addUser(User* u)
{
    users_.insert(std::pair<std::string, User*>(u->getName(), u));
    carts_.insert(std::pair<std::string, std::queue<Product*>>(u->getName(), std::queue<Product*>()));
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) 
{
    std::set<std::string> set(terms.begin(), terms.end());
    std::vector<Product*> hits;

    std::set<Product*>::iterator it;
    for (it = products_.begin(); it != products_.end(); ++it) {
        std::set<std::string> keywords = (*it)->keywords();
        if (type) {
            if (setUnion(keywords, set).size() < set.size() + keywords.size()) {
                hits.push_back(*it);
            }
        } else {
            if (setIntersection(keywords, set).size() == set.size()) {
                hits.push_back(*it);
            }
        }
    }

    return hits;
}

void MyDataStore::addCart(std::string username, Product* hit)
{
    std::map<std::string, std::queue<Product*>>::iterator cart = carts_.find(username);
    if (cart != carts_.end()) {
        cart->second.push(hit);
    } else {
        std::cout << "Invalid request" << std::endl;
    }
}

void MyDataStore::viewCart(std::string username)
{
    std::map<std::string, std::queue<Product*>>::iterator cart = carts_.find(username);
    if (cart != carts_.end()) {
        std::queue<Product*> temp = cart->second;
        int count = 1;
        while (!temp.empty()) {
            std::cout << "Item: " << count++ << std::endl;
            std::cout << temp.front()->displayString() << std::endl;
            temp.pop();
            std::cout << std::endl;
        }
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::buyCart(std::string username) {
    std::map<std::string, std::queue<Product*>>::iterator cart = carts_.find(username);
    if (cart != carts_.end()) {
        std::queue<Product*> temp = cart->second;
        while (!temp.empty()) {
            if (temp.front()->getQty() > 0 && users_.find(username)->second->getBalance() >= temp.front()->getPrice()) {
                temp.front()->subtractQty(1);
                users_.find(username)->second->deductAmount(temp.front()->getPrice());
                temp.pop();
            } else {
                break;
            }
        }
        carts_.find(username)->second = temp;
    } else {
        std::cout << "Invalid username" << std::endl;
    }
}

void MyDataStore::dump(std::ostream& ofile)
{
    ofile << std::fixed << std::setprecision(2);
    ofile << "<products>" << std::endl;
    std::set<Product*>::iterator it1;
    for (it1 = products_.begin(); it1 != products_.end(); ++it1) {
        (*it1)->dump(ofile);
    }
    ofile << "</products> \n<users>" << std::endl;
    std::set<User*>::iterator it2;

    std::map<std::string, User*>::iterator it;
    for (it = users_.begin(); it != users_.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}