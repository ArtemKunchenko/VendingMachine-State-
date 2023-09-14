#include <iostream>
#include<string>
using namespace std;

class Product
{
public:
    Product(string name, double price)
    {
        _name = name;
        _price = price;
    }
    string getName() { return _name; }
    double getPrice() { return _price; }
private:
    string _name;
    double _price;
};

template <class T>
class VendingMachineState
{
public:
    virtual void changeState(T value) = 0;
    virtual T getValue()=0;
};

template <class T>
class VendingDepositeState :public VendingMachineState <T>
{
public:
    VendingDepositeState() { _deposite = 0; }
    void changeState(T value) override { _deposite = value; }
    T getValue() override { return _deposite; }
private:
    double _deposite;
};

template <class T>
class VendingStockState :public VendingMachineState <T>
{
public:
    VendingStockState() { _stock = 0; }
    void changeState(T value) override { _stock = value; }
    T getValue() override { return _stock; }
private:
    int _stock;
};

class VendingMachine
{
public:
    VendingMachine(Product& product)
    {
        _product = &product;
        _deposite = new VendingDepositeState <double>();
        _stock = new VendingStockState<int>();
    }
    ~VendingMachine()
    {
        delete _product;
        delete _deposite;
        delete _stock;
    }
    void addInDeposite(double value) { _deposite->changeState(value); }
    void addInStock(double value) { _stock->changeState(value); }
    void showMachine()
    {
        cout << "\nVENDING MACHINE\t\tMachine deposite: " << _deposite->getValue() << " $" << endl
            << "Product: " << _product->getName() << "\t\tPrice: " << _product->getPrice() << " $\t\t"
            << "Quantity: " << _stock->getValue() << "\n\n";
           
    }
    int canIBuy(double money)
    {
        if (_stock->getValue() <= 0) return 1;//not enough product
        else if ((money - _product->getPrice()) > _deposite->getValue()) return 2;//not enough change
        else if (money < _product->getPrice()) return 3;//not enough money
        else return 4; //successful parchasing

    }
    void buy()
    {
        int condition;
        double money;
        cout << "Put money: ";
        cin >> money;
        condition = canIBuy(money);
        switch (condition)
        {
        case 1:
            cout << "Sorry " << _product->getName() << " isn't in the stock\n\n";
            break;
        case 2:
            cout << "Sorry machine can't give a change\n\n";
            break;
        case 3:
            cout << "Sorry you put not enough money\n\n";
            break;
        case 4:
            _deposite->changeState(_deposite->getValue() + _product->getPrice());
            _stock->changeState(_stock->getValue() -1);
            cout << "Take " << _product->getName() << endl
                << "Your change is " << money - _product->getPrice() << "$\n\n";
            break;
        }
    }
private:
    VendingMachineState<double>* _deposite;
    VendingMachineState<int>* _stock;
    Product* _product;
};


int main() {
    Product crisps("CRISPS", 2.5);
    VendingMachine machine (crisps);
    /*cout << "TEST 1: Machine is empty\n";
    machine.showMachine();
    cout << "\nTEST 2: Product isn't in the stock\n";
    machine.showMachine();
    machine.buy();*/ 
    machine.addInDeposite(2);
    machine.addInStock(10);
    /*cout << "\nTEST 3: Machine can't give a change\n";
    machine.showMachine();
    machine.buy();*/
    /*cout << "\nTEST 4: Not enough money\n";
    machine.showMachine();
    machine.buy();*/
    cout << "\nTEST 5: Successful purchasing\n";
    machine.showMachine();
    machine.buy();
    machine.showMachine();
    system("pause");
    return 0;
}