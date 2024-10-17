#ifndef parQueue_h
#define parQueue_h
#include<stdexcept>
#include"queue_eda.h"
using namespace std;

template<typename L, typename Prioridad>
class queue2 {

protected:

    queue<L> cola1;
    queue<L> cola2;
    Prioridad pr;

public:


    queue2(Prioridad p) : pr(p) {}

    void push(L const& elem) {
        if (pr(elem)) {
            cola1.push(elem);
        }
        else {
            cola2.push(elem);
        }
    }

    void pop() {
        if (cola2.empty() && cola1.empty()) {
            throw domain_error("Cola vacia");
        }
        if (cola1.empty()) {
            cola2.pop();
        }
        else {
            cola1.pop();
        }
    }

    L front() {
        if (cola2.empty() && cola1.empty()) {
            throw domain_error("Cola vacia");
        }
        else {
            if (cola1.empty()) {
                return cola2.front();
            }
            else {
                return cola1.front();
            }
        }
    }
};
#endif
