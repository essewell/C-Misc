/******************************************************************************
;@
;@ Student Name 1: Emmett Sewell    
;@ Student 1 #: 301565227
;@ Student 1 userid (email): esa97@sfu.ca
;@
;@ Student Name 2: Jaiden Nadem
;@ Student 2 #: 301562466
;@ Student 2 userid (email): jon1@sfu.ca
;@
;@ Helpers: none
;@
;@ Resources: none
;@
;@ Name: templates.hpp
******************************************************************************/


#ifndef TEMPLATES_HPP_
#define TEMPLATES_HPP_

template <typename T>

T fibonacci(T number, T &previous1) {
    if (number <= 1) {
        previous1 = 0;
        return number;
    }
    T previous0 = 0;
    previous1 = fibonacci(number - 1, previous0);
    return previous0 + previous1;
}

#endif /* TEMPLATES_HPP_ */
