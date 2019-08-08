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
// �޸𸮸��� �߻��ϸ� �� �ּ��� Ǯ� Ȯ���ϼ���.
// Visual Leak Detector�� �ܼ��� ��������� �ϳ� �߰��ϴ� �� ������ ���� �޸� ������ �߻��� ����� ������ ������ ����ݴϴ�.
// Reference : https://hoororyn.tistory.com/2
//#include <VLD/vld.h>
#endif