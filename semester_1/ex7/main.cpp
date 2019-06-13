#include <iostream>
#include <list>
#include <zconf.h>
#include <cstring>

//17
//Создать следующие классы. В каждом классе должны быть наборы
//конструкторов (в том числе по умолчанию и копирования), деструктор.
//Для хранения дополнительной информации произвольного объема должен
//быть использован контейнер (например Array из лекции 13).

//Класс "Детская игрушка".

//Должны быть перегружены операции: =, ==, !=, <<.

//Объект данного класса должны содержать:
//название игрушки, цена, наименьший возраст, наибольший возраст, список
//магазинов (район, адрес).

//Должен быть написан метод(ы) корректировки.
//Должны быть написаны методы, приведенные после строки
//  //----------------It must be write -----------------------------  в приложении 08.


struct AddrInfo{
    char district[20];
    char address[20];
};

class ChildrensToy{
    private:
    int min_age;
        int max_age;
        float price;
        const char *name;
        std::list<AddrInfo> shop_list;

    public:
        ChildrensToy (std::list<AddrInfo> ShopList, int MinAge=0, int MaxAge=1, float Price=0,  const char *Name=NULL){
            max_age = MaxAge;
            min_age = MinAge;
            price = Price;
            name = Name;
            shop_list = ShopList;
        };

         // Конструктор копирования
b

        ChildrensToy & operator = ( const ChildrensToy &toy2){
                max_age   = toy2.max_age;
                min_age   = toy2.min_age;
                price     = toy2.price;
                name      = toy2.name;
                shop_list = toy2.shop_list;
                return *this;
        }

        const bool operator == (const ChildrensToy &toy){
            return (max_age == toy.max_age) &&
                   (min_age == toy.min_age) &&
                   (price == toy.price) &&
                   (strcmp(name, toy.name) == 0);
        }

        const bool operator != (const ChildrensToy &toy){
            return (max_age != toy.max_age) &&
                   (min_age != toy.min_age) &&
                   (price != toy.price) &&
                   (strcmp(name, toy.name) != 0);
        }

//        std::ostream& operator << (std::ostream &s){
//            s << '(' << name << ", " << price << ')';
//            return s;
//        }

    ~ChildrensToy(){};

        int getMaxAge(void){
            return this->max_age;
        };

        void setMaxAge(int x){
            this->max_age = x;
        };

        void AddAddInf(AddrInfo NewRecord){
            this->shop_list.push_back(NewRecord);
        };

        void CorrectAddInf(int NumberRecord, AddrInfo NewRecord){
            if (shop_list.size() >= NumberRecord) {
                std::list<AddrInfo>::iterator iter = shop_list.begin();
                std::advance(iter, NumberRecord-1);
                *iter = NewRecord;
            }
        };


};

std::ostream& operator << (std::ostream &s, ChildrensToy toy){
            s << '(' << toy.getMaxAge() << ')';
            return s;
        }


int main() {
    std::list<AddrInfo> init_list;

    AddrInfo addr_info  = {"district", "address"};
    AddrInfo addr_info2 = {"district2", "address2"};
    AddrInfo addr_info3 = {"district3", "address3"};
    AddrInfo addr_info4 = {"district4", "address4"};

    init_list.push_back(addr_info);
    ChildrensToy ct(init_list);

    ct.AddAddInf(addr_info2);
    ct.CorrectAddInf(2, addr_info3);

    init_list.push_back(addr_info4);
    ChildrensToy ct1(init_list, 5);

    std::cout << "Hello, World!" << std::endl;
    ct = ct1;
    std::cout << ct << std::endl;

    std::cout << "Hello, World!" << std::endl;

    return 0;
}