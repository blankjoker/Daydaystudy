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
 * @file DoipManager.h
 * @brief Doclaration file of class DoipManager.
 *
 * This file includes the declaration of class DoipManager.
 *
 * @attention used for c++ only.
*/
#ifndef DOIPMANAGER_H
#define DOIPMANAGER_H
#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <binder/BinderService.h>
#include <binder/IBinder.h>
#include <binder/IPCThreadState.h>
#include "servicebase/ServiceBase.h"

#include "DoipCommon.h"

namespace nutshell
{

class DiagD;
/**
  * class DoipManager.
  *
  * This class use to manage DoipManager module .
*/
class DoipManager : public android::RefBase
{
public:
    DoipManager(DiagD* diagd);
    virtual ~DoipManager();
    static DoipManager* instantiate(DiagD* diagd);
    static void destroy();

    void doipServerInit();
    void doipServerDeInit();
    void setVINInfo(const android::String16& vin);
    void setEIDInfo(const android::String16& eid);
    void setGIDInfo(const android::String16& gid);
    void activationLineSwitchChange(bool bActivationFlag);
    void requestIPAddressAssignment(const android::String16& ifname);
    void releaseIPAddressAssignment(const android::String16& ifname);
    void powermodeStatusChange(bool powermodeFlag);

private:
    DoipManager(const DoipManager& other);
    DoipManager& operator=(const DoipManager& other);

private:
    static android::sp<DoipManager> s_instance;

    DiagD* m_diagd;
};



}

#endif // DOIPMANAGER_H
/* EOF */
