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
 * @file SysD.h
 * @brief Doclaration file of class SysD.
 *
 * This file includes the declaration of class SysD.
 *
 * @attention used for c++ only.
*/
#ifndef DIAGD_H
#define DIAGD_H

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <binder/BinderService.h>
#include <binder/IBinder.h>
#include <binder/IPCThreadState.h>
#include "servicebase/ServiceBase.h"
#include "nesat/BnDoipManagerService.h"
#include "nesat/IDoipManagerListener.h"
#include "nesat/BnNetworkState.h"
#include "nesat/INetworkManager.h"
// #include "nesat/BnUComDiagListener.h"
// #include "nesat/IUComDiagServer.h"
// #include "nesat/BnNMEventObserver.h"
// #include "nesat/BnNMCommandReply.h"

#include "DoipManager.h"
#include "ne_doip_server.h"


namespace nutshell
{
/**
  * class DiagD.
  *
  * This class use to manage system info.
*/
class DiagD : public nesat::ServiceBase, public nesat::ServiceConnection
{

public:
    DiagD();
    ~DiagD();

public:
    static DiagD* instantiate();

private:
    DiagD(const DiagD& other);
    DiagD& operator=(const DiagD& other);

private:
    static android::sp<DiagD> s_instance;

    virtual void doInitStart(int reason);
    virtual void doInitSuspend(int action);
    virtual void doInitAwake(int reason);
    virtual void doStart(int reason);
    virtual void doSuspend(int action);
    virtual void doAwake(int reason);

private:
    virtual void onServiceConnected(android::sp<android::IBinder> binder, android::String16 name);
    virtual void onServiceDisconnected(android::String16 name);

private:
    android::sp<DoipManager> m_doipManager;

// private:
//     /**
//       * class DoipDiagClientListener.
//       *
//       * This class use to BnUComDiagListener.
//     */
//     class DoipDiagClientListener : public nesat::BnUComDiagListener
//     {
//     public:
//         DoipDiagClientListener();
//         ~DoipDiagClientListener();
//         virtual android::binder::Status getVinCfm(const android::String16& vin, int32_t len);
//         virtual android::binder::Status getEIDCfm(const android::String16& eid, int32_t len);
//         virtual android::binder::Status getGIDCfm(const android::String16& gid, int32_t len);
//         virtual android::binder::Status activationLineInd(int32_t line);
//         virtual android::binder::Status mcuStateInd(int32_t sts);
//     };

// private:
//     /**
//       * class DiagDNetEventListener.
//       *
//       * This class use to BnNMEventObserver.
//     */
//     class DiagDNetEventListener : public nesat::BnNMEventObserver
//     {
//     public:
//         DiagDNetEventListener();
//         ~DiagDNetEventListener();

//         android::binder::Status interfaceStatusChanged(const ::android::String16& iface, bool up, const ::android::String16& ip);
//         android::binder::Status interfaceLinkStateChanged(const ::android::String16& iface, bool up);
//         android::binder::Status interfaceAdded(const ::android::String16& iface);
//         android::binder::Status interfaceRemoved(const ::android::String16& iface);
//         android::binder::Status addressUpdated(const ::android::String16& iface, const ::nesat::LinkAddress& address);
//         android::binder::Status addressRemoved(const ::android::String16& iface, const ::nesat::LinkAddress& address);
//         android::binder::Status limitReached(const ::android::String16& limitName, const ::android::String16& iface);
//         android::binder::Status interfaceClassDataActivityChanged(const ::android::String16& label, bool active, int64_t tsNanos);
//         android::binder::Status interfaceDnsServerInfo(const ::android::String16& iface, int64_t lifetime, const ::std::vector<::android::String16>& servers);
//         android::binder::Status routeUpdated(const ::nesat::RouteInfo& route);
//         android::binder::Status routeRemoved(const ::nesat::RouteInfo& route);
//         android::binder::Status idleInterfaceInform(const ::std::vector<::android::String16>& iface);

//     };

// private:
//     /**
//       * class DiagDCmdCfmListener.
//       *
//       * This class use to BnNMCommandReply.
//     */
//     class DiagDCmdCfmListener : public  nesat::BnNMCommandReply
//     {
//     public:
//         DiagDCmdCfmListener();
//         ~DiagDCmdCfmListener();
//         android::binder::Status replyGetInterfaceConfig(const ::nesat::InterfaceConfiguration& ifaceCfg);
//         android::binder::Status replylistInterfaces(const ::std::vector<::android::String16>& ifaceList);
//         android::binder::Status replySetIpForwardingEnabled(bool result);
//         android::binder::Status replyGetIpForwardingEnabled(bool result);
//         android::binder::Status replyStartInterfaceForwarding(bool result);
//         android::binder::Status replyStopInterfaceForwarding(bool result);
//         android::binder::Status replyAddIfaceToLocalNetwork(bool result);
//         android::binder::Status replyRemoveIfaceToLocalNetwork(bool result);
//         android::binder::Status replyAddInterfaceToNetwork(bool result);
//         android::binder::Status replyRemoveInterfaceToNetwork(bool result);
//         android::binder::Status replyAddRoute(bool result);
//         android::binder::Status replyRemoveRoute(bool result);
//         android::binder::Status replyRemoveRoutesFrLocalNet(bool result);
//         android::binder::Status replySetDefaultNetId(bool result);
//         android::binder::Status replyClearDefaultNetId(bool result);
//         android::binder::Status replyEnableNat(bool result);
//         android::binder::Status replyDisableNat(bool result);
//         android::binder::Status replySetBlackListUid(bool result);
//         android::binder::Status replyGetIfQuota(int64_t result);
//         android::binder::Status replyGetIfQuotaAlert(int64_t result);
//         android::binder::Status replySetIfQuota(bool result);
//         android::binder::Status replySetIfAlert(bool result);
//         android::binder::Status replySetGlobalAlert(bool result);
//         android::binder::Status replyRmIfQuota(bool result);
//         android::binder::Status replyRmIfAlert(bool result);
//         android::binder::Status replyRmGlobalAlert(bool result);
//         android::binder::Status dataConnectConfirm(bool result, int32_t errCode, int32_t apnIndex);
//         android::binder::Status dataDisconnectConfirm(bool result, int32_t errCode, int32_t apnIndex);
//         android::binder::Status replySetOemRules(bool result);
//         android::binder::Status replySetWhiteListUid(bool result);
//         android::binder::Status replyEnableWhiteListPort(bool result, const ::nesat::WhiteListPortConfig& cfg);
//         android::binder::Status replyDisableWhiteListPort(bool result, const ::nesat::WhiteListPortConfig& cfg);

//     };

// private:
//     android::sp<DoipDiagClientListener> m_diag_listener;
//     android::sp<nesat::IUComDiagServer> m_diag_server;

//     android::sp<nesat::INetworkManager> m_diagd_net_server;
//     android::sp<DiagDNetEventListener> m_NetEventListener;

//     android::sp<DiagDCmdCfmListener> m_DiagDCmdCfmListener;


};



}
#endif // DIAGD_H
/* EOF */
