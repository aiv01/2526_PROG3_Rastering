#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
#include <map>
#include <string>
bool isEven(int n) {
    return n%2 ==0;
}

// operator ()
struct IsGreaterThan
{
    int soglia;
    IsGreaterThan(int n): soglia(n){}

    bool operator()(int n) const{
        return n> soglia;
    }
};
void lambda_1(){
      auto lambda_is_even = [](int n){return n%2==0;}; 

    auto lambda_explicit = [](int n) -> bool {return n>5;};


    int result = [](int a, int b){return a+b;}(2,3);


    std::cout<<result<<std::endl;
    lambda_is_even(4);

    // struttura lambda
    // []        capture list === tutte le variabili esterne che devo prendere (E COME PRENDERLE) e usare nella lambda
    // ()        parametri 
    // -> void   Tipo di ritorno 
    // {}        corpo funzione

    int soglia = 5;

    auto lambda_soglia = [soglia](int n) -> bool { 
        return n > soglia;
    };


    //esempietti fighi 

    std::vector<int> numeri = {1,2,3,4,5,6,7,8,9,10};

    std::for_each(numeri.begin(), numeri.end(),
        [](int n)->void {
            if(n%2 == 0){
                std::cout<<n <<" pari"<<std::endl;
            }
        } 
    );


    std::sort(numeri.begin(), numeri.end(), [](int a, int b)->bool{
        return a>b;
    } );
    std::for_each(numeri.begin(), numeri.end(),
        [](int n)->void {
           std::cout<<n << " ";
        } 
    );
    std::cout<<std::endl;

    // vantaggi lambda;
    // 1- locale: definita solo dove serve, non e` dispersa
    // 2- ha una sintassi (per quanto brutta) molto concisa
    // 3- leggibile
    // 4- l'esistenza della capture list la rende flessibile, prendo le variabili che mi servono 
    // 5- il compilatore le ottimizza

    // CAPTURE LIST 

    //[] lo strumento piu` utile delle lambda 
    // permette di prendere valori dallo scope e portarli nella lambda 

    int x = 10;
    int y = 20;
    int z = 30;
    int w = 40;

    //capture by value 
    auto lambda_value = [x](){
        std::cout<<x<<std::endl;
        //x = 2; // const-by-copy 
    };

    // capture by reference
    auto lambda_ref = [&x](){
        x=3;
    };


    // capture default by value
    auto lambda_all = [=](){ 
        std::cout<<x<<y<<z<<w<<std::endl;
    
    };

    // capture default by reference 
    auto lambda_all_ref = [&](){ 
        x++;
        std::cout<<x<<y<<z<<w<<std::endl;
    
    };

    auto lambda_mixed = [x, &y](){
        y++;
    };

    //capture with initializer 
    auto lambda_init = [val = x  ] () mutable    {
        val++;
        std::cout<<val<<std::endl;
    };

    // move capture
    auto lambda_move= [data = std::vector<int>{1,2,3}]()mutable{
        data.push_back(4);
    };

    lambda_init();
}

void lambda_2(){
    std::function<void()> lambda;

    {
        int localVar = 42;
        lambda = [&localVar](){
            localVar = 43;
        };
        lambda();

    }

    lambda(); //UNDEFINED BEHAVIOUR

    
    {
        int localVar = 42;
        lambda = [localVar](){
            
        };
    }


    std::shared_ptr<int> sharedData = std::make_shared<int>(100);

    auto lambda_2 = [sharedData](){

    };
    lambda_2();// tiene in vita lo shared ptr 


    //generic lambda 
    std::vector<int> numeri = {1,2,3,4,5,6,7,8,9,10};
    std::vector<double> numeri_d={1.1,2.3,3.4,5.6};


    auto l_sort = [](auto a, auto b){
        return a>b;
    };


    std::sort(numeri.begin(), numeri.end(), l_sort);

    std::sort(numeri_d.begin(),numeri_d.end(), l_sort);
}

//[this]

struct  GameEntity
{

    int hp = 100;

public: 
    auto getHealthLambda(){
        return [this](){
            std::cout<<hp<<std::endl;
        };
    }

    // auto getHealthLambdaCpy(){
    //     return [*this](){ //copy this (cpp 17)
    //         std::cout<<hp<<std::endl;
    //     };
    // }


};

int add(int a, int b){return a+b;}
struct FunctorSub{
    int operator()(int a, int b){
        return a-b;
    }
};


void functional_1(){

    std::function<void()> fn;
    std::function<int(int,int)> op; 

    op = add;

    op(2,3); 

    op = [](int a, int b ){return a *b;};
    
    op(2,3); 

    FunctorSub fnsub; 
    op = fnsub;


    std::map<std::string, std::function<void()>> spellbook;



}

class Button{

    std::function<void()> OnClick;
};

void printStuff(const std::string& name, int age, const std::string& city){
        std::cout<<name<<":"<<age<<"-"<<city<<std::endl;
    };

void printFoo(){
    printStuff( "foo", 42, "bar");
}

void bind_1(){

    auto print = [](const std::string& name, int age, const std::string& city){
        std::cout<<name<<":"<<age<<"-"<<city<<std::endl;
    };

    // std::bind

    auto printFoo = std::bind(print, "foo", 42, "bar");
    std::function<void()> OnClick;
    printFoo(); //print("foo", 42, "bar");

    OnClick= printFoo;


    using namespace std::placeholders;
    // Roma
    auto printRomani = std::bind(print, _1, 42, _2);
    printRomani("foo", "bar");

}

// metodi membro 

struct Player {

    void attack(/*  Player* this,*/int dmg){
        std::cout<<dmg<<" damage"<<std::endl;
    }
};

void scoped(){
    using namespace std::placeholders;

    Player player; 

    auto playerAttack = std::bind(&Player::attack, &player, _1);
std::unique_ptr<std::function<void(int)>> atk = 
    std::make_unique<std::function<void(int)>>(playerAttack);

    // atk(40);
}
int main(){

    bind_1();


    return 0;
}