/*
 * fibonacci1.hpp
 *
 *  Created on: Nov 17, 2022
 *      Author: xubuntu
 */

#ifndef FIBONACCI1_HPP_
#define FIBONACCI1_HPP_

#include <boost/multiprecision/cpp_int.hpp>

using fibonacciType1 = boost::multiprecision::cpp_int;  // create an alias declaration (a type alias)

fibonacciType1& fibonacci1(long subscript);

#endif /* FIBONACCI1_HPP_ */
