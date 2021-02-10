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
/**
 * @file DoipManagerTest.h
 * @brief Doclaration file of class DoipManagerTest.
 *
 * This file includes the declaration of class DoipManagerTest.
 *
 * @attention used for c++ only.
*/

#ifndef DOIPMANAGERTEST_H
#define DOIPMANAGERTEST_H

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "servicebase/ServiceBase.h"

namespace nesat
{

/**
  * class DoipManagerTest.
  *
  * This class use to test TimeManager module.
*/
class DoipManagerTest : public ServiceBase, public ServiceConnection
{

public:
    DoipManagerTest();
    virtual ~DoipManagerTest();

    virtual void doInitStart(int reason);
    virtual void doInitSuspend(int action);
    virtual void doInitAwake(int reason);
    virtual void doStart(int reason);
    virtual void doSuspend(int action);
    virtual void doAwake(int reason);

    virtual void onServiceConnected(android::sp<android::IBinder> binder, android::String16 name);
    virtual void onServiceDisconnected(android::String16 name);

private:  
    
};

}

#endif // DOIPMANAGERTEST_H
/* EOF */
