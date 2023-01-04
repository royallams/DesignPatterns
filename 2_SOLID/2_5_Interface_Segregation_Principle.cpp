/*
    Interface Segregation Principle

    - not Create interface that is too large - goal 
    - Example of multi function printer
     
    idea 1 : interface with print , scan and fax function
            - all the child is forced to have all these functions
            - but what if you want to create a new printer without scanning
            - even it we leave it empty
            - still a wrong indication to the client
            - wrong signal in the api to use the function not required

    
    idea 2 : Lets seperate the interface itself
            - Iprinter  has print method
            - IScanner has scanner method
            - IFax has fax method

            Now if we want to make 
            - a new printer ( posssible)
            - a new printer with scanner ( possible by inheriting both the parent)
            - will be used in decorator pattern later


            we can take the reference of printer and scanner
            and then call print and scan function through the concrete objects directly



*/


#include <vector>
#include <string>
#include <iostream>


struct Document{
    std::string data;
};

//struct IMachine
//{
//  virtual void print(Document& doc) = 0;
//  virtual void fax(Document& doc) = 0;
//  virtual void scan(Document& doc) = 0;
//};
//
//struct MFP : IMachine
//{
//  void print(Document& doc) override;
//  void fax(Document& doc) override;
//  void scan(Document& doc) override;
//};

// 1. Recompile
// 2. Client does not need this
// 3. Forcing implementors to implement too much

struct IPrinter
{
  virtual void print(Document& doc) = 0;
};

struct IScanner
{
  virtual void scan(Document& doc) = 0;
};

struct Printer : IPrinter
{
  void print(Document& doc) override{
        std::cout<<("\nPrinting--->"+doc.data);
  }
};

struct Scanner : IScanner
{
  void scan(Document& doc) override{
        std::cout<<("\nScanning--->"+doc.data);

  }
};

struct IMachine: IPrinter, IScanner
{
};

struct Machine : IMachine
{
  IPrinter& printer;
  IScanner& scanner;

  Machine(IPrinter& printer, IScanner& scanner)
    : printer{printer},
      scanner{scanner}
  {
  }

  void print(Document& doc) override {
    printer.print(doc);
  }
  void scan(Document& doc) override{
    scanner.scan(doc);
  }
};

// IPrinter --> Printer
// everything --> Machine



// int main(){
//     Printer printer;
//     Scanner scanner;

//     Machine machine(printer,scanner);
//     Document doc{"Hi I am a document"};

//     machine.print(doc);
//     machine.scan(doc);
//     return 0;
// }