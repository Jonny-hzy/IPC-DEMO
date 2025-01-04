/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/RPC-Binder
 * @LastEdit: 2024-08-30
 * @FilePath: ITest.h
 * @Description: Binder基类接口定义
 */
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>


namespace android {

class ITest : public IInterface
{
public:
    DECLARE_META_INTERFACE(Test)

    enum {
        TEST_SET = IBinder::FIRST_CALL_TRANSACTION,
        TEST_GET,
    };

    virtual void testFuncSet(int val) = 0;
    virtual int testFuncGet(void) = 0;
};

}