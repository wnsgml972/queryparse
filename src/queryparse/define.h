#pragma once

#include <iostream>
#include <thread>
#include <string>
#include <cstring> 
#include <malloc.h>
#include <cassert>
#include <string>
#include <tuple>
#include <xcall_once.h>
#include <mutex>
#include <vector>

#ifdef _DEBUG
// 메모리릭이 발생하면 이 주석을 풀어서 확인하세요.
// Visual Leak Detector는 단순히 헤더파일을 하나 추가하는 것 만으로 쉽게 메모리 누수가 발생한 블록을 선언한 라인을 잡아줍니다.
// Reference : https://hoororyn.tistory.com/2
//#include <VLD/vld.h>
#endif