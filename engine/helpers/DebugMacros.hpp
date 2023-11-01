#pragma once
#include<iostream>
#ifdef DEBUG
#define DEBUG_ERROR(x) (std::cerr << (x))
#define DEBUG_LOG(x) (std::cout << (x))
#else 
#define DEBUG_ERROR(x)
#define DEBUG_LOG(x)
#endif



