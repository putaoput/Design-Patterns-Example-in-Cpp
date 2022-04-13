#include <string>


class BeverageInterface{
 public:
    virtual std::string GetDescription(){
        return description;
    }
    virtual double cost() = 0;

 public:
    std::string description = "Unknown Beverage";
};

//装饰者类
class CondimentDecoratorInterface: public BeverageInterface{
 public:
    virtual std::string GetDescription() = 0;
}

//浓缩咖啡
class Espresso: public BeverageInterface{
 public:
    Espresso(){
        description = "Espresso";
    }
    double cost(){
        return 1.99;
    }
}

//
class HouseBlend: public BeverageInterface{
 public:
    HouseBlend(){
        description = "HouseBlend";
    }
    double cost(){
        return 0.99;
    }
}

//摩卡类：装饰者
class Mocha: CondimentDecoratorInterface{
    
}