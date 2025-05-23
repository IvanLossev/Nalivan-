#include "long_number.hpp"
#include <gtest/gtest.h>

namespace{
	
	TEST(LongNumberTest, DefaultConstructor){
		biv::LongNumber num;
		biv::LongNumber expected = "0";
    
    Equal_TRUE(expected, num);
	}
	
	TEST(LongNumberTest, StringConstructorPositive) {
		
	}
	
	TEST(LongNumberTest, StringConstructorNegative) {
		
	]
	
	TEST(LongNumberTest, StringConstructorZero) {
		biv::LongNumber num = "0";
    biv::LongNumber expected = "0";
    
    Equal_TRUE(expected, num);
	}
	
	TEST(LongNumberTest, EqualityOperator) {
	biv::LongNumber a1 = "123";
    biv::LongNumber a2 = "123";
    bool result = true;
    bool actual = a1 == a2;
    
    Equal_TRUE(result, actual);
	}
	
	TEST(LongNumberTest, InequalityOperator) {
	biv::LongNumber a1 = "123";
    biv::LongNumber a2 = "-123";
    bool result = true;
    bool actual = a1 != a2;
    
    Equal_TRUE(result, actual);
	}
	
	TEST(LongNumberTest, GreaterThanOperator) {
	biv::LongNumber a1 = "5";
    biv::LongNumber a2 = "-10";
    bool result = true;
    bool actual = a1 > a2;
    
    Equal_TRUE(result, actual);
	}
	
	
	
	TEST(LongNumberTest, AdditionOperator) {
		biv::LongNumber a1="999";
		biv::LongNumber a2 ="111";
		biv::LongNumber result = "1110";
		biv::LongNumber actual = a1+a2;
		
		Equal_TRUE(result,actual);
	}