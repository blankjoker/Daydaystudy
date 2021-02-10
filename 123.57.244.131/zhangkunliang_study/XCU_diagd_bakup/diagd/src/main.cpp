/**
 * Copyright @ 2019 iAuto (Shanghai) Co., Ltd.
 * All Rights Reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are NOT permitted except as agreed by
 * iAuto (Shanghai) Co., Ltd.
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 */

#include "ncore/NCProcess.h"
#include "diagd/diagd.h"

using namespace nutshell;

class DiagdServer :public NCProcess
{
public:
    DiagdServer(INT argc, CHAR** argv)
    :   NCProcess(argc, argv)
    {

    }
    ~DiagdServer() {}

    /**
     * callback , which is called after Initialize
     */
    virtual VOID OnInitialize() { m_cDiagD.init(); }

    /**
     * callback , which is called after Start
     */
    virtual VOID OnStart() { m_cDiagD.start(); }

    /**
     * callback , which is called after stop
     */
    virtual VOID OnStop() { m_cDiagD.stop(); }

    /**
     * callback , which is called after Deinitialize
     */
    virtual VOID OnDeinitialize() { m_cDiagD.deinit(); }

private:
    DiagD m_cDiagD;
    DiagdServer();

    DiagdServer(const DiagdServer&);
    DiagdServer& operator=(const DiagdServer&);
};

int main(int argc, char ** argv)
{
    DiagdServer diagdserver(argc, argv);
    
    diagdserver.initialize();

    diagdserver.start();

    diagdserver.enterloop();

    diagdserver.stop();

    diagdserver.deinitialize();

    return 0;
}

/* EOF */