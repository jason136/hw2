#include <queue>
#include <map>
#include "datastore.h"

class MyDataStore : public DataStore {
public:
    MyDataStore();
    ~MyDataStore();

    void addProduct(Product* p);
    void addUser(User* u);
    std::vector<Product*> search(std::vector<std::string>& terms, int type);
    void addCart(std::string username, Product* hit);
    void viewCart(std::string username);
    void buyCart(std::string username);
    void dump(std::ostream& ofile);
private:
    std::set<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::queue<Product*>> carts_;
};