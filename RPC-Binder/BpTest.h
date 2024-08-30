/*
 * @Source: https://github.com/Jonny-hzy/IPC-DEMO/tree/main/RPC-Binder
 * @LastEdit: 2024-08-30
 * @FilePath: BpTest.h
 * @Description: Binder客户端接口
 */
 #include "ITest.h"

namespace android {

class BpTest : public BpInterface<ITest>
{
public:
    explicit BpTest(const sp<IBinder> &impl)
        : BpInterface<ITest>(impl)
    {
    }

    virtual ~BpTest();

    virtual void testFuncSet(int val)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ITest::getInterfaceDescriptor());
        data.writeInt32(val);
        remote()->transact(TEST_SET, data, &reply);
    }

    virtual int testFuncGet(void)
    {
        Parcel data, reply;
        data.writeInterfaceToken(ITest::getInterfaceDescriptor());
        remote()->transact(TEST_GET, data, &reply);
        return reply.readInt32();
    }
};

}