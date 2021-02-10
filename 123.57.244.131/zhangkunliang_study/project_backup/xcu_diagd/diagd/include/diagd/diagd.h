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

namespace nutshell
{
/**
  * class DiagD.
  *
  * This class use to manage system info.
*/
class DiagD
{

public:
    DiagD();
    virtual ~DiagD();

    bool init();
    bool start();
    bool stop();
    bool deinit();

private:
    DiagD(const DiagD& other);
    DiagD& operator=(const DiagD& other);
};

}
#endif // DIAGD_H
/* EOF */
