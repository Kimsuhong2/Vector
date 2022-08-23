//
//  main.h
//  Vector
//
//  Created by clidev-rlatnghd1236 on 2022/08/23.
//

#pragma once

#include <iostream>

class TestClass
{
public:
    int value;
    std::string name;
    
public:
    TestClass() : value(100), name("test") {}
    ~TestClass() = default;
};
