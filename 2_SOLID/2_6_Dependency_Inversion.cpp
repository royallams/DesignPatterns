/*

Dependency Inversion Principle
    - Dependency injection is different
    Two ideas : 
        Idea 1 
            - High level modules should not depend on low level modules
            - Instead both of them should depend abstractions.
        Idea 2 
            - Abstractions should not depend on details 
            - But details should depend on Abstractions.


Scenerio 1 : 
Relationship class
    - There is a class called Relationship 
    - This holds the concrete implementation of maintaining the relation between two person
    
Person Struct
    - Person represents the entity 

Lets say a high level module called Research needs to find the relationship status
Research :
    - First way , it can directly take reference to the Relationship class which might be defined by someone else/
    - Here the Higher module is dependent on the lower module directly .
    - What if the lower module breaks up or changes?
    - We are  in trouble. 

Better Way : 
    - Research should instead take the inferface for the Relationship. 
    - in  this way , it is not directly depending on the lower module. 
    - But provides safer way to refer to the lower module ( Relationship in this case)


Test 1 :
    - enum Relationship specifies type of relation parent, child, sibling 
    - struct Person has a name
    - struct Relationships maintain the relation ship between the person
        - is a low level module .. 
        - has proper implementation
    - Research 
        - is a high level module 
        - we make depends on the low level module 

    Better to have dependecies on interface and not on depend on somebody else implementations

    


*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

// A. High-level modules should not depend on low-level modules.
//    Both should depend on abstractions.
// B. Abstractions should not depend on details. 
//    Details should depend on abstractions.

enum class Relationship
{
  parent,
  child,
  sibling
};

struct Person
{
  string name;
};

struct RelationshipBrowser
{
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser // low-level
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child)
  {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string &name) override
  {
    vector<Person> result;
    for (auto&& [first, rel, second] : relations)
    {
      if (first.name == name && rel == Relationship::parent)
      {
        result.push_back(second);
      }
    }
    return result;
  }
};

struct Research // high-level
{
  Research(RelationshipBrowser& browser)
  {
    for (auto& child : browser.find_all_children_of("John"))
    {
      cout << "John has a child called " << child.name << endl;
    }
  }
//  Research(const Relationships& relationships)
//  {
//    auto& relations = relationships.relations;
//    for (auto&& [first, rel, second] : relations)
//    {
//      if (first.name == "John" && rel == Relationship::parent)
//      {
//        cout << "John has a child called " << second.name << endl;
//      }
//    }
//  }
};

// int main()
// {
//   Person parent{"John"};
//   Person child1{"Chris"};
//   Person child2{"Matt"};

//   Relationships relationships;
//   relationships.add_parent_and_child(parent, child1);
//   relationships.add_parent_and_child(parent, child2);

//   Research _(relationships);

//   return 0;
// }