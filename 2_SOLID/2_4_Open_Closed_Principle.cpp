


/*
    Product 
    Filter for that product 
    Filter by some specification 

    test 1 : make a filter and all the filtering is a function of a single filter. 
            - not extendible 
            - for every specification we need to edit the same class
            - Not scalable

    test 2 : 
            - to add new Specification - Make it a interface
            - to add new filter - Make it an interface
            - Specification can take any item and provides an interface for doessatisfy method?
            - Filter has an filter interface that can be extended with inheritance
            - filter takes list of items as argument and specification .
            -
    addition : 
            - operator can be overloaded to make it easier for combining the specification.


*/
#include <iostream>
#include <string>
#include <vector>

using namespace std;



enum class Color{red, green , blue};// To be part of the product
enum class Size {small, medium  , large};// sizes of different products

struct Product // Any product with name color and sizes. 
{
    /* data */
    string name;
    Color color;
    Size size;
};

struct ProductFilter{// A filter that can have multiple filter functions based on different specification

    vector<Product*> FilterByColor(vector<Product*>items, Color color){
        vector<Product*> result;
        for(auto const & item : items){
            if(item->color == color){
                result.push_back(item);
            }
        }
        return result;
    }

    // If in case next time we need more filter we will have to keep on adding new funciton to this.. 
    // This is bad for exmaple , filter by size, filter by color && size .. 
    // Open to Extension 
    // But closed for modification .. 
    // How to do it.. 
    // Specification pattern or enterprise pattern


    // We will define interface called specification . 



 };


// The idea is to build interfaces for the things that are to be extended . 
 
template <typename T> struct AndSpecification;


template <typename T> struct Specification{// Instead a specification as an interface
    virtual ~Specification() = default;// this can be extended to number of specification
    virtual bool is_satisfied(T* item) const = 0; // takes the product/item , provides check and logic 

  
};
 

template<typename T> struct AndSpecification: public Specification<T>// A specification that checks combined specification
{
    const Specification<T> &first; // takes two specs and then see if both satisfies.
    const Specification<T> &second;

    AndSpecification(const Specification<T> &first,const Specification<T> &second):
    first(first),second(second){}

    bool is_satisfied(T *item)const override{
        return first.is_satisfied(item)&& second.is_satisfied(item);
    }

};


  template <typename T> AndSpecification<T> operator && // To make it easier to work with
  (const Specification<T>&first, const Specification<T>&second){
        return {first,second};
}


template <typename T> struct Filter // FIlter interface, make any number of interface later
{
    virtual vector<T*> filter (vector<T*>items, Specification<T> &spec)=0;
    // any new filter will take number of items and 
    // specification based on which it can filter.
};


struct BetterFilter : Filter<Product>
{
    vector<Product*> filter(vector<Product*> items, Specification<Product> &spec)override
    {

        vector<Product*>result;
        for(auto &item : items){
            if(spec.is_satisfied(item)){
                result.push_back(item);
            }
        }
        return result;
    }
};


struct ColorSpecification : Specification<Product>
{
    Color color;
    ColorSpecification(Color color): color(color){}


    bool is_satisfied(Product *item)const override{
        return item->color == color;
    }

};

struct SizeSpecification : Specification<Product>
{
    Size size;
    explicit SizeSpecification(const Size size): size(size){}


    bool is_satisfied(Product *item) const override{
        return item->size == size;
    }

};











// int main(){

//     cout<<"Open Closed Principle Example"<<endl;

//     Product apple{"Apple",Color::green,Size::small};
//     Product tree{"Tree",Color::green,Size::large};
//     Product house{"House",Color::green,Size::large};

//     vector<Product*>items {&apple, &tree, &house};
// //     ProductFilter pf;
// //     auto green_things = pf.FilterByColor(items,Color::green);
// // for(auto const &item : green_things){
// //     cout<<item->name <<" is Green\n";
// // }


// // INSTEAD WE CAN USE NOW BETTER FILTER 

//     BetterFilter bf;
//     ColorSpecification green_spec(Color::green);

//     for(auto &item : bf.filter(items, green_spec)){
//             cout<<item->name <<" is Green\n";

//     }


//     SizeSpecification size_spec(Size::large);
//     AndSpecification<Product> green_and_large(green_spec,size_spec);

//      for(auto &item : bf.filter(items, green_and_large)){
//             cout<<item->name <<" is Green and Large\n";

//     }


//     //Lets do it more compact way 
//     // auto combined_spec = ColorSpecification(Color::green)
//     //             && SizeSpecification(Size::large);// wil not work


// \


//     auto new_spec = green_spec && size_spec;
//     for(auto &item : bf.filter(items, new_spec)){
//             cout<<item->name <<" is Green and Large\n";

//     }
  
//     return 0;
// }