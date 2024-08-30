/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/RPC-Binder
 * @LastEdit: 2024-08-30
 * @FilePath: test_service.cpp
 * @Description: Binder服务端应用
 */
 #include "BnTest.h"
#include <iostream>

using namespace android;


class TestService : public BnTest
{
public:
    virtual void testFuncSet(int);
    virtual int testFuncGet(void);
private:
    int value;
};

void TestService::testFuncSet(int val)
{
    std::cout << "TestService::testFuncSet" << std::endl;
    value = val;
}

int TestService::testFuncGet(void)
{
    std::cout << "TestService::testFuncGet" << std::endl;
    return value*2;
}


int main(int argc, char *argv[])
{
    sp<ProcessState> proc(ProcessState::self());
    sp<IServiceManager> sm = defaultServiceManager();
    sm->addService(String16("service.TestService"), new TestService());
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}