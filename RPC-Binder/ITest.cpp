/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/RPC-Binder
 * @LastEdit: 2024-08-30
 * @FilePath: ITest.h
 * @Description: Binder基类实现
 */
 #include "BpTest.h"

using namespace android;


BpTest::~BpTest() {}
IMPLEMENT_META_INTERFACE(Test, "android.TestServer.ITest");
