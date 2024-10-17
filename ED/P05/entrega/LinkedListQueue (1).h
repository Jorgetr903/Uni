#ifndef linked_list_Queue_h
#define linked_list_Queue_h
#include<stdexcept>
#include"linked_list_ed.h"
using namespace std;

template<typename L, typename Prioridad>
class queue {

protected:

	linked_list_ed<L> list;
    Prioridad pr;

public: 

    
    queue(Prioridad p) : pr(p) {}
    void push(L const& elem) {
        
        if (pr(elem)) {
            list.push_back_prioritario(elem);   //O(1)
        }
        else
        {
            list.push_back(elem);   //O(1)
        }
    }

    void pop() {
        list.pop_front(); //O(1)
    }

    L front() {
        if (list.empty()) {
            throw domain_error("Cola vacia");
        }
        return list.primerElem(); //O(1)
    }


};
#endif