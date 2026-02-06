#include <memory> //include per smart ptr
#include <iostream>


void memleak(){
    int* ptr = new int(10);

    //int* distrutto
    // MA l'intero allocato, rimane li 
    delete ptr; //in questo modo puliamo l'intero allocato
}

void problem2(){
    int* ptr = new int(42);
    int* ptr2 = ptr;
    //1000 righe di funzione dopo 
    delete ptr;
    //delete ptr2; la memoria e` gia` stata cancellata
    
}

int* problem3(){ //dangling pointer
    int x = 10;
    return &x;
    // x viene distrutto
}
// puntatori -> raw pointers

// SMART POINTER
// RAII -> ResourceAcquisitionIsInitialization


// unique_ptr
void unique_one(){
    std::unique_ptr<int> ptr(new int(42));

    // non si puo` copiare 
    //std::unique_ptr<int> ptr2 = ptr;

    std::unique_ptr<int> ptr3 = std::move(ptr);
    // ora ptr e` un nullptr;

    std::cout<< *ptr3<<std::endl;
}
void unique_two(){
    std::unique_ptr<int[]> arr( new int[3]{2,3,4});

    std::cout<<arr[2]<<std::endl;

}

struct foo{
    int bar;
};


foo* factory(int val){
    return new foo{val};
}

std::unique_ptr<foo> factory_unique(int val){
    return std::unique_ptr<foo>(new foo{val});
}


// Shared_ptr
// tiene il conto di quanti oggetti puntano a quell'indirizzo
// il conteggio arriva a zero-> delete 

void shared_1(){
    std::shared_ptr<int> ptr1 = std::make_shared<int>(42);

    {
        std::shared_ptr<int> ptr2 = ptr1;
        std::cout<< ptr1.use_count()<<std::endl;
        *ptr2 = 100;
        std::cout<< *ptr1<<std::endl;
    }
    std::cout<< ptr1.use_count()<<std::endl;
    
    std::cout<< *ptr1<<std::endl;
}

// weak ptr

struct Node{
    std::shared_ptr<Node> next_node;
    ~Node(){ std::cout<<"Node destroyed"<<std::endl;}
};

void loop_prbl(){
    std::shared_ptr<Node> nodo1 = std::make_shared<Node>();
    std::shared_ptr<Node> nodo2 = std::make_shared<Node>();

    nodo1->next_node= nodo2;
    nodo2->next_node= nodo1;

}

struct SafeNode{
    std::shared_ptr<SafeNode> next;
    std::weak_ptr<SafeNode> prev;

    ~SafeNode(){
        std::cout<<"Safe node destroyed"<<std::endl;
    }
};


void weak_1(){
    auto nodo1 = std::make_shared<SafeNode>();
    auto nodo2 = std::make_shared<SafeNode>();

    nodo1->next = nodo2;
    nodo2->prev = nodo1;

    auto sharedPrev = nodo2->prev.lock();
    if(sharedPrev){
        //daje
    }
    else{
        //mannaggia 
    }
}
int main(){
    
    //unique_one();
    // cpp 14 
    //auto ptr = std::make_unique<foo>(200);

    //shared_1();
    //loop_prbl();

    weak_1();
    return 0;
}