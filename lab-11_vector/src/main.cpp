#include <iostream>
#include <cstring>

#include "my_vector.hpp"

namespace product {
    class Product {
    public:
        Product(const char* name, int quantity, double price) 
            : name_(new char[strlen(name) + 1]), quantity_(quantity), price_(price) {
                strcpy(name_, name);
            }

        ~Product() {
            delete[] name_;
        }

        friend std::ostream& operator<<(std::ostream& os, const Product& product) {
            os << product.name_ << " " << product.quantity_ << " " << product.price_;
            return os;
        }

        Product(const Product& other) : name_(new char[strlen(other.name_) + 1]), quantity_(other.quantity_), price_(other.price_) {
            strcpy(name_, other.name_); 
        }

        Product& operator=(const Product& other) {
            if (this != &other) {
                delete[] name_;
                name_ = new char[strlen(other.name_) + 1];
                strcpy(name_, other.name_);
                quantity_ = other.quantity_;
                price_ = other.price_;
            }
            return *this;
        }
    private:
        char *name_;
        int quantity_;
        double price_;
    };

}  // namespace product

int main() {
	containers::my_vector<int> v;
	v.push_back(2);
	const int n{3};
	v.push_back(n);
	std::cout << v << std::endl;

    product::Product p1("Product1", 4, 12.0);
    product::Product p2("Product2", 2, 7.5);

    containers::my_vector<product::Product> pVec;

    pVec.push_back(p1);
    pVec.push_back(p2);

    //std::cout << pVec << std::endl;
    containers::test_my_vector<int>(5, 10);    
    containers::test_my_vector<product::Product>(product::Product("asdf", 4, 12.0), product::Product("qwe", -1, 7.5));
    return 0;
}
