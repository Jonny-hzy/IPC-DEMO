/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/RPC-Binder
 * @LastEdit: 2024-08-30
 * @FilePath: BnTest.h
 * @Description: Binder服务端接口
 */
#include "ITest.h"

namespace android {


class BnTest : public BnInterface<ITest> {
public:
    virtual status_t onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags = 0);
};

status_t BnTest::onTransact(uint32_t code, const Parcel &data, Parcel *reply, uint32_t flags)
{
    switch (code)
    {
        case TEST_SET:
        {
            CHECK_INTERFACE(ITest, data, reply);
            testFuncSet(data.readInt32());
            return NO_ERROR;
        }
        case TEST_GET:
        {
            CHECK_INTERFACE(ITest, data, reply);
            reply->writeInt32(testFuncGet());
            return NO_ERROR;
        }
        default:
        {
            return BBinder::onTransact(code, data, reply, flags);
        }
    }
}


}