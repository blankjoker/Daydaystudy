/**
 * Copyright @ 2018 - 2020 Suntec Software(Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * Suntec Software(Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */
#include "DoipManagerTest.h"
#include "servicebase/Process.h"
#include "binder/IBinder.h"
#include "binder/IServiceManager.h"

#define LOG_TAG "DoipManagerTest"
const android::String16 SRV_NAME_DOIPMANAGER_TEST("DoipManagerTest");

namespace nesat
{

DoipManagerTest::DoipManagerTest()
    : ServiceBase(SRV_NAME_DOIPMANAGER_TEST){
    ALOGI("%s, %d", __FUNCTION__, __LINE__);
}

DoipManagerTest::~DoipManagerTest()
{
    ALOGI("%s, %d", __FUNCTION__, __LINE__);
}

void DoipManagerTest::doInitStart(int reason)
{
    ALOGI("%s, %d", __FUNCTION__, __LINE__);
    bindService(android::String16("diagd"), this);
    started();
    ALOGI("%s, %d", __FUNCTION__, __LINE__);
}

void DoipManagerTest::doInitSuspend(int action)
{
    suspended();
}

void DoipManagerTest::doInitAwake(int reason)
{
    awaked();
}

void DoipManagerTest::doStart(int reason)
{
    started();
}

void DoipManagerTest::doSuspend(int action)
{
    suspended();
}

void DoipManagerTest::doAwake(int reason)
{
    awaked();
}

void DoipManagerTest::onServiceConnected(android::sp<android::IBinder> binder, android::String16 name)
{
    ALOGI("%s, %d, %s is connected.", __FUNCTION__, __LINE__, android::String8(name).string());
}

void DoipManagerTest::onServiceDisconnected(android::String16 name)
{
    ALOGI("%s, %d, %s is disconnected.", __FUNCTION__, __LINE__, android::String8(name).string());
}

}

int main()
{
    ALOGI("%s, %d", __FUNCTION__, __LINE__);
    nesat::Process process;
    android::sp<nesat::DoipManagerTest> client = new nesat::DoipManagerTest;
    process.run();

    return 0;
}
/* EOF */
