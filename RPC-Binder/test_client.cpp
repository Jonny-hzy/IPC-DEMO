/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/RPC-Binder
 * @LastEdit: 2024-08-30
 * @FilePath: test_client.cpp
 * @Description: Binder客户端应用
 */
 #include "BpTest.h"
#include <iostream>

using namespace android;


int main(int argc, char *argv[])
{
    sp<IServiceManager> sm = defaultServiceManager();
    sp<IBinder> binder = sm->getService(String16("service.TestService"));
    sp<ITest> ts = interface_cast<ITest>(binder);
    //测试set方法
    int set = 1;
    if (argc > 1) {
        set = atoi(argv[1]);
    }
    std::cout << "Client set: " << set << std::endl;
    ts->testFuncSet(set);
    //测试get方法
    int get = ts->testFuncGet();
    std::cout << "Client get: " << get << std::endl;

    return 0;
}