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
// �޸𸮸��� �߻��ϸ� �� �ּ��� Ǯ� Ȯ���ϼ���.
// Visual Leak Detector�� �ܼ��� ��������� �ϳ� �߰��ϴ� �� ������ ���� �޸� ������ �߻��� ����� ������ ������ ����ݴϴ�.
// Reference : https://hoororyn.tistory.com/2
//#include <VLD/vld.h>
#endif