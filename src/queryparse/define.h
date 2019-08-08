#pragma once

// thread
#include <thread>
#include <xcall_once.h>
#include <mutex>

// container
#include <tuple>
#include <vector>

// io
#include <iostream>
#include <malloc.h>

// string
#include <string>
#include <cstring> 
#include <sstream>
#include "StringConverter.hpp"

// debug
#include <cassert>
#ifdef _DEBUG
// 메모리릭이 발생하면 이 주석을 풀어서 확인하세요.
// Visual Leak Detector는 단순히 헤더파일을 하나 추가하는 것 만으로 쉽게 메모리 누수가 발생한 블록을 선언한 라인을 잡아줍니다.
// Reference : https://hoororyn.tistory.com/2
//#include <VLD/vld.h>
#endif