/**
 * Copyright @ 2013 - 2014 Suntec Software(Shanghai) Co., Ltd.
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

#include <stdio.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stddef.h>
#include <unistd.h>

#ifndef NCLOGPUBDEF_H
#    include "ncore/NCLogPubDef.h"
#endif

#ifndef NCLOG_H
#    include "ncore/NCLog.h"
#endif

#ifndef NCLOGSETTING_H
#    include "ncore/NCLogSetting.h"
#endif

#include <cutils/log.h>

using namespace nutshell;

#define LOG_CFG_FILTER_GAP " "
#define LOG_CFG_PROCESS_FILTER_GAP "|"
#define NC_LOG_FILTER_WRITER_SOCKET_PATH_SRV  "/dev/socket/socket.nclog.LOG_FILTER_WRITER_SRV"

enum OptionsType
{
    OptionsType_None = 0,
    OptionsType_LogcatFilter,
    OptionsType_LogfileFilter,
    OptionsType_ProcessID,
    OptionsType_ProcessName
};

struct ProcessFilterInfo
{
    NCLogFilterInfo filterInfo;
    ProcessFilterInfo* next;
};

/*
    logFilterDefault: using for default filter
    logcatFilter: logcat default filter
    fileFilter: log file default filter
*/
struct logFilterDefault
{
    char logcatFilter[NC_LOG_MAX_FILTER_SIZE];
    char fileFilter[NC_LOG_MAX_FILTER_SIZE];
};

static struct logFilterDefault dFilter;

NC_BOOL isMemMode()
{
    NC_BOOL bMemMode = NC_FALSE;
    CHAR* modeenv = NULL;
    modeenv = getenv("LOGD_FILTER_MEM_MODE");
    if (modeenv) {
        if (0 == strcmp(modeenv, "1")) {
            bMemMode = NC_TRUE;
        }
    }

    return bMemMode;
}

#define NC_LOG_CFG_DEFAULT_NCLOG_FILTER  "*:E"
#define NC_LOG_CFG_DEFAULT_FILE_FILTER   "*:S"

#define NC_LOG_CFG_DEFAULT_FILTER_UPDATE "*:I"

#define DEVICE_NAME_LEN 10

bool getDefaultFilter();

const CHAR* getDefaultNCLogCfgFilter()
{
    if (isMemMode()) {
        return NC_LOG_CFG_DEFAULT_FILTER_UPDATE;
    }

    getDefaultFilter();
    if (dFilter.logcatFilter != NULL) {
        return dFilter.logcatFilter;
    }

    return NC_LOG_CFG_DEFAULT_NCLOG_FILTER;
}

const CHAR* getDefaultFileCfgFilter()
{
    if (isMemMode()) {
        return NC_LOG_CFG_DEFAULT_FILTER_UPDATE;
    }

    getDefaultFilter();
    if (dFilter.fileFilter != NULL) {
        return dFilter.fileFilter;
    }

    return NC_LOG_CFG_DEFAULT_FILE_FILTER;
}

const CHAR* getDefaultCfgFilePath()
{
    if (isMemMode()) {
        return "/tmp/nclogDefault.cfg";
    }

    return "/etc/nclog.cfg";
}

const CHAR* getCfgFilePath()
{
    if (isMemMode()) {
        return "/tmp/nclog.cfg";
    }

    return "/var/system/nclog.cfg";
}


VOID addProcessFilterInfo(ProcessFilterInfo** header, ProcessFilterInfo* info)
{
    if (!header || !info) {
        return;
    }

    if (!(*header)) {
        *header = info;
        return;
    }

    ProcessFilterInfo* curInfo = *header;
    while (curInfo) {
        if (!curInfo->next) {
            info->next = NULL;
            curInfo->next = info;
            break;
        }

        curInfo = curInfo->next;
    }
}

bool getDefaultFilter()
{
    const CHAR* path = getDefaultCfgFilePath();
    if (NULL == path) {
        return false;
    }

    FILE* fp = NULL;
    fp = fopen(path, "r");
    if (!fp) {
        printf("%s: fopen cfg file failed, path is [%s]! err is: %s\n", __FUNCTION__, path, strerror(errno));
        return false;
    }

    char* line = NULL;
    size_t len = 0;
    int i = 0;

    while (getline(&line, &len, fp) > 0) {

        char* pos = strchr(line, '\n');
        if (pos != NULL) {
            int lenTemp = pos - line;
            line[lenTemp] = '\0';
        }

        switch (++i) {
        case 1:
            {
                strncpy(dFilter.logcatFilter, line, NC_LOG_MAX_FILTER_SIZE);
                break;
            }
        case 2:
            {
                strncpy(dFilter.fileFilter, line, NC_LOG_MAX_FILTER_SIZE);
                break;
            }
        default:
            break;
        }

        free(line);
        line = NULL;
    }

    fclose(fp);
    return true;
}

VOID freeAllFilter(ProcessFilterInfo** header)
{
    if (!header) {
        return;
    }

    ProcessFilterInfo* curInfo = *header;
    ProcessFilterInfo* next = NULL;
    while (curInfo) {
        next = curInfo->next;
        delete(curInfo);
        curInfo = next;
    }

    *header = NULL;
}

NC_BOOL showcCurFilters()
{
    // Socket
    INT fd = 0;
    INT len = 0;

    // Creata a UNIX domain stream socket
    fd = socket(AF_UNIX, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("logcfg:send_msg socket error!");
        return NC_FALSE;
    }

    struct sockaddr_un un;
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strncpy(un.sun_path, NC_LOG_FILTER_WRITER_SOCKET_PATH_SRV, sizeof(un.sun_path));
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    // connect
    if (connect(fd, (struct sockaddr*)&un, len) < 0) {
        perror("logcfg:send_msg connect error!");
        close(fd);
        return NC_FALSE;
    }

    NCLogMsgHeader msg;
    memset(&msg, 0, sizeof(NCLogMsgHeader));
    strncpy(msg.cmd, NCLOG_MSG_CMD_SHOWC, NCLOG_MSG_CMD_MAX_SIZE);

    INT msgSize = sizeof(NCLogMsgHeader);
    // send requirment to logd

    INT ret = 0;

    ret = TEMP_FAILURE_RETRY(send(fd, (void*)(&msg), msgSize, 0));
    if (ret != msgSize) {
        close(fd);
        return NC_FALSE;
    }

    INT dataLen = 0;

    dataLen = TEMP_FAILURE_RETRY(recv(fd, (VOID *)(&msg), sizeof(NCLogMsgHeader), 0));
    if (dataLen < 0) {
        perror("logcfg: recv error\n");
        close(fd);
        fd = -1;
        return NC_FALSE;
    }

    NCShowcInfo showcInfo;

    dataLen = TEMP_FAILURE_RETRY(recv(fd, (VOID *)(&showcInfo), sizeof(NCShowcInfo), 0));
    if (dataLen < 0) {
        perror("logcfg: recv error\n");
        close(fd);
        fd = -1;
        return NC_FALSE;
    }

    INT variantSize = msg.dataSize - sizeof(NCShowcInfo);
    CHAR *pAllProcFilters = new CHAR[variantSize];

    dataLen = TEMP_FAILURE_RETRY(recv(fd, (VOID *)pAllProcFilters, variantSize, 0));
    if (dataLen < 0) {
        perror("logcfg: recv error\n");
        close(fd);
        fd = -1;
        delete[] pAllProcFilters;
        return NC_FALSE;
    }

    printf("======= Current filter is: ========\n");
    printf("<NCLog   Filter> %s\n", showcInfo.nclogFilter.filter);
    printf("<File    Filter> %s\n", showcInfo.fileFilter.filter);
    printf("<Radio   Filter> %s\n", showcInfo.radioFilter.filter);
    if (0 != strncmp(pAllProcFilters, "", variantSize)) {
        printf("<Process Filter> :\n");
        printf("%s\n", pAllProcFilters);
    }
    printf("=============  END  ===============\n");

    close(fd);
    delete[] pAllProcFilters;
    return NC_TRUE;
}


VOID showHelp()
{
    fprintf(stdout, "===========================logcfg Help=============================\n");
    fprintf(stdout, "Usage: [options] [specs]\n");
    fprintf(stdout, "options include:\n"
                    "  -d                           Set default nclog filter(%s) and file filter (%s).\n"
                    "  -c [tag:priority]            Set nclog filter.\n"
                    "  -a [tag:priority]            append filter to nclog or file.\n"
                    "  -f [tag:priority]            Set file filter.\n"
                    "  -b [device type]             Set specified device filter, default is radio device.\n"
                    "  -p [PID tag:priority]        Set process nclog filter by PID.\n"
                    "  -n [ProcessName tag:priority]Set process nclog filter by process name.\n"

                    "  -r [PID]                     Remove the process nclog filter by PID.(PID will be insteaded of process name.)\n"
                    "  -m [ProcessName]             Remove the process nclog filter by process name('*' means all processes.).\n"

                    "  --showd                      Show default configure file.\n"
                    "  --showc                      Show current configure file.\n"
                    "  --help                       Help information.\n"
                    "  --reconfig                   Reconfig logd after /var mount\n",
            getDefaultNCLogCfgFilter(), getDefaultFileCfgFilter());

    fprintf(stdout, "\n<tag> is a log component tag (or * for all) and priority is:\n"
                    "  D    Debug\n"
                    "  I    Info\n"
                    "  W    Warn\n"
                    "  E    Error\n"
                    "  S    Silent (supress all output)\n"
                    "\n'*' means '*:d' and <tag> by itself means <tag>:v\n"
                    "If no filterspec is found, nclog filter defaults to '%s', file filter defaults to '%s'\n"
                    "The max size of filterspec is 1023!!!"
                    "\n\n",
            getDefaultNCLogCfgFilter(), getDefaultFileCfgFilter());

    fprintf(stdout, "\nexamples:\n"
        "  example 1: Set default filter.\n"
        "  logcfg -d\n\n"

        "  example 2: To dump all log entries with 'D' priority and higher from all processes.\n"
        "  logcfg -c *:D\n\n"

        "  example 3: To dump all log entries with tag 'dalvikvm', 'D' priority and higher from all processes.\n"
        "  logcfg -c dalvikvm:D\n\n"

        "  example 4: To save all log entries into file with 'D' priority and higher from all processes.\n"
        "  logcfg -f *:D\n\n"

        "  example 5: To dump all log entries into file with tag 'dalvikvm', 'D' priority and higher from all processes.\n"
        "  logcfg -f dalvikvm:D\n\n"

        "  example 6: To dump all log entries with tag 'dalvikvm', 'D' priority and higher from process that PID is 200.\n"
        "  logcfg -p 200 dalvikvm:D\n\n"

        "  example 7: To dump all log entries with tag 'dalvikvm', 'D' priority and higher from process that name is 'btd'.\n"
        "  logcfg -n btd dalvikvm:D\n\n"

        "  example 8: To remove the filter of process that PID is 200.\n"
        "  logcfg -r 200\n\n"

        "  example 9: To remove the filter of process that name is 'btd'.\n"
        "  logcfg -m btd\n\n"

        "  example 10: To remove all processes filter.\n"
        "  logcfg -m \"*\"\n\n"

        "  example 11: Add filter to nclog.\n"
        "  logcfg -c -a dalvikvm:D\n\n"

        "  example 12: Add filter to file.\n"
        "  logcfg -f -a dalvikvm:D\n\n"

        "  example 13: Add filter to nclog and file.\n"
        "  logcfg -c -f -a dalvikvm:D\n\n"

        "  example 14: reconfig logd after /var mount \n"
        "  logcfg --reconfig\n\n"

        "  example 15: To dump all log entries with tag 'dalvikvm' in radio log device.\n"
        "  logcfg -b radio -c dalvikvm\n\n"


        );

    fprintf(stdout, "=================================================================\n");
}

BOOL checkFilter(const CHAR* filter)
{
    if (!filter) {
        return NC_FALSE;
    }

    INT len = strlen(filter);
    if (3 > len) {
        return NC_FALSE;
    }

    INT num = 0;
    INT pos = 0;
    for (INT i = 0; i < len; i++) {
        if (':' == filter[i]) {
            pos = i;
            num++;
        }

        if (num > 1 || i > (len - 2)) {
            return NC_TRUE;
        }
    }

    switch (toupper(filter[pos + 1])) {
    case 'D':
    case 'I':
    case 'W':
    case 'E':
    case 'S':
        break;
    default:
        return NC_FALSE;
    }

    return NC_TRUE;
}

BOOL getProcessName(pid_t pid, CHAR* outName, INT len)
{
    if (!outName || len < 2 || pid < 1) {
        return NC_FALSE;
    }

    CHAR pathName[NC_LOG_FILTER_PROCESS_NAME_LEN] = { 0 };
    snprintf(pathName, NC_LOG_FILTER_PROCESS_NAME_LEN, "/proc/%d/stat", pid);

    FILE *file = NULL;
    file = fopen(pathName, "r");
    if (!file) {
        return NC_FALSE;
    }

    CHAR line[NC_LOG_FILTER_PROCESS_NAME_LEN] = { 0 };
    CHAR *openParen = NULL;
    CHAR *closeParen = NULL;

    fgets(line, sizeof(line), file);
    fclose(file);

    /* Split at first '(' and last ')' to get process name. */
    openParen = strchr(line, '(');
    closeParen = strrchr(line, ')');

    if (!openParen || !closeParen) {
        return NC_FALSE;
    }

    *openParen = *closeParen = '\0';
    strncpy(outName, openParen + 1, len);

    return NC_TRUE;
}

NC_BOOL changeFilter(NCLogFilterInfo& filter)
{
    return NCLogSetting::changeFilter(filter);
}

NC_BOOL appendFilter(NCLogFilterInfo& filter)
{
    return NCLogSetting::appendFilter(filter);
}

NC_BOOL changeProcessFilter(NCLogFilterInfo& filter)
{
    return NCLogSetting::changeFilter(filter);
}

NC_BOOL readAndShowCfg(const CHAR* pathName)
{
    FILE *file = NULL;
    CHAR line[NC_LOG_FILTER_PROCESS_NAME_LEN] = { 0 };

    file = fopen(pathName, "r");
    if (!file) {
        return NC_FALSE;
    }

    fprintf(stdout, "======configure file[%s]=========\n", pathName);
    while (fgets(line, sizeof(line), file)) {
        fprintf(stdout, "%s", line);
    }
    fprintf(stdout, "======configure file=========\n");
    fclose(file);
    return NC_TRUE;
}

const CHAR* shortOptions = "dcfbap:n:rm";
const INT OPERATION_MASK_D = 0x1;
const INT OPERATION_MASK_C = 0x2;
const INT OPERATION_MASK_F = 0x4;
const INT OPERATION_MASK_P = 0x8;
const INT OPERATION_MASK_N = 0x10;
const INT OPERATION_MASK_R = 0x20;
const INT OPERATION_MASK_M = 0x40;
const INT OPERATION_MASK_A = 0x80;
const INT OPERATION_MASK_B = 0x100;

INT main(INT argc, CHAR **argv)
{
    // test synclog
    if (argc == 2 && 0 == strcmp(argv[1], "--synclog")) {
        if (NCLogSetting::syncLog()) {
            fprintf(stdout, "==========synclog successfully==========.\n");
            exit(0);
        } else {
            fprintf(stderr, "==========synclog failed==========.\n");
            exit(-1);
        }
    }

    if (argc == 2 && 0 == strcmp(argv[1], "--showd")) {
        if(!readAndShowCfg(getDefaultCfgFilePath())) {
            fprintf(stderr, "===========failed============\n");
            exit(-1);
        } else {
            exit(0);
        }
    }

    if (argc == 2 && 0 == strcmp(argv[1], "--showc")) {
        if(!showcCurFilters()) {
            fprintf(stderr, "===========failed============\n");
            exit(-1);
        } else {
            exit(0);
        }
    }

    if (argc == 2 && 0 == strcmp(argv[1], "--reconfig")) {
        if (!NCLogSetting::reconfig()) {
            fprintf(stderr, "reconfig error\n");
            exit(-1);
        } else {
            exit(0);
        }
    }

    if (argc == 1 || (argc == 2 && 0 == strcmp(argv[1], "--help"))) {
        showHelp();
        exit(0);
    }

    fprintf(stdout, "=========Input arguments[%d]===========\n", argc);
    for (INT i = 0; i < argc; i++) {
        fprintf(stdout, "%d:[%s]\n", i, argv[i]);
    }
    fprintf(stdout, "=======================================\n");

    INT result = 0;
    INT operations = 0;
    opterr = 0;

    NCLogFilterInfo fileFilter;
    memset(&fileFilter, 0, sizeof(fileFilter));
    fileFilter.type = NC_LOGFILTER_TYPE_LOGFILE;

    NCLogFilterInfo newFilter;
    memset(&newFilter, 0, sizeof(newFilter));

    NCLogFilterInfo logcatTempFilter;
    memset(&logcatTempFilter, 0, sizeof(logcatTempFilter));
    logcatTempFilter.type = NC_LOGFILTER_TYPE_LOGCAT;
    logcatTempFilter.bufID = LOG_ID_RADIO;

    ProcessFilterInfo *filterInfoList = NULL;

    CHAR deviceName[DEVICE_NAME_LEN] = { 0 };

    while ((result = getopt(argc, argv, shortOptions)) != -1) {
        INT tind = optind;

        switch (result) {
        case 'd':
            {
                operations = operations | OPERATION_MASK_D;
                break;
            }

        case 'c':
            {
                operations = operations | OPERATION_MASK_C;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    UINT tmpLen = strlen(logcatTempFilter.filter) + strlen(argv[tind]);
                    if (tmpLen < (sizeof(logcatTempFilter.filter) - strlen(LOG_CFG_FILTER_GAP))) {
                        if (!checkFilter(argv[tind])) {
                            fprintf(stderr, "'%s' filterspecs format error!\n", argv[tind]);
                            showHelp();
                            goto doexit;
                        }
                        if (strlen(logcatTempFilter.filter) > 0) {
                            strncat(logcatTempFilter.filter, LOG_CFG_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                        }
                        strncat(logcatTempFilter.filter, argv[tind], NC_LOG_MAX_FILTER_SIZE);
                    }
                    else {
                        fprintf(stderr, "Filterspecs too long. Max length is (%d)!\n", sizeof(logcatTempFilter.filter));
                        goto doexit;
                    }
                    tind++;
                }
            }
            break;

        case 'a':
            {
                operations = operations | OPERATION_MASK_A;
                while (tind < argc) {
                    UINT tmpLen = strlen(newFilter.filter) + strlen(argv[tind]);
                    if (tmpLen < (sizeof(newFilter.filter) - strlen(LOG_CFG_FILTER_GAP))) {
                        if (!checkFilter(argv[tind])) {
                            fprintf(stderr, "'%s' filterspecs format error!\n", argv[tind]);
                            showHelp();
                            goto doexit;
                        }
                        if (strlen(newFilter.filter) > 0) {
                            strncat(newFilter.filter, LOG_CFG_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                        }
                        strncat(newFilter.filter, argv[tind], NC_LOG_MAX_FILTER_SIZE);
                    }
                    else {
                        fprintf(stderr, "Filterspecs too long. Max length is (%d)!\n", sizeof(newFilter.filter));
                        goto doexit;
                    }
                    tind++;
                }
            }
            break;

        case 'f':
            {
                operations = operations | OPERATION_MASK_F;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    UINT tmpLen = strlen(fileFilter.filter) + strlen(argv[tind]);
                    if (tmpLen < (sizeof(fileFilter.filter) - strlen(LOG_CFG_FILTER_GAP))) {
                        if (!checkFilter(argv[tind])) {
                            fprintf(stderr, "'%s' filterspecs format error!\n", argv[tind]);
                            showHelp();
                            goto doexit;
                        }
                        if (strlen(fileFilter.filter) > 0) {
                            strncat(fileFilter.filter, LOG_CFG_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                        }
                        strncat(fileFilter.filter, argv[tind], NC_LOG_MAX_FILTER_SIZE);
                    }
                    else {
                        fprintf(stderr, "Filterspecs too long. Max length is (%d)!\n", sizeof(fileFilter.filter));
                        goto doexit;
                    }
                    tind++;
                }
            }
            break;

        case 'b':
            {
                operations = operations | OPERATION_MASK_B;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    if (strlen(argv[tind]) + 1 > sizeof(deviceName)) {
                        printf("Invalid device name!!!\n");
                        goto doexit;
                    }
                    strncpy(deviceName, argv[tind], DEVICE_NAME_LEN);
                    tind++;
                }
            }
            break;

        case 'p':
            {
                operations = operations | OPERATION_MASK_P;
                INT optionNum = 0;
                ProcessFilterInfo *filterInfo = new ProcessFilterInfo;
                filterInfo->next = NULL;
                memset(filterInfo->filterInfo.filter, 0, sizeof(filterInfo->filterInfo.filter));
                filterInfo->filterInfo.type = NC_LOGFILTER_TYPE_PROCESS_ADD;
                tind--;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    // process id
                    if (0 == optionNum) {
                        if (!getProcessName(atoi(argv[tind]), filterInfo->filterInfo.filter, sizeof(filterInfo->filterInfo.filter))) {
                            delete filterInfo;
                            filterInfo = NULL;
                            fprintf(stderr, "can't get the process name, please check the PID[%d]!\n", atoi(argv[tind]));
                            goto doexit;
                        }
                        fprintf(stdout, "PID[%d]->Name[%s]\n", atoi(argv[tind]), filterInfo->filterInfo.filter);
                        strncat(filterInfo->filterInfo.filter, LOG_CFG_PROCESS_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                    }
                    else {
                        if (!checkFilter(argv[tind])) {
                            fprintf(stderr, "'%s' filterspecs format error!\n", argv[tind]);
                            showHelp();
                            delete filterInfo;
                            filterInfo = NULL;
                            goto doexit;
                        }
                        if ((strlen(argv[tind]) + strlen(filterInfo->filterInfo.filter) + 2) > sizeof(filterInfo->filterInfo.filter)) {
                            fprintf(stderr, "Process filterspecs too long!\n");
                            showHelp();
                            delete filterInfo;
                            filterInfo = NULL;
                            goto doexit;
                        }
                        strncat(filterInfo->filterInfo.filter, argv[tind], NC_LOG_MAX_FILTER_SIZE);
                        strncat(filterInfo->filterInfo.filter, LOG_CFG_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                    }
                    tind++;
                    optionNum++;
                }
                if (optionNum > 1) {
                    addProcessFilterInfo(&filterInfoList, filterInfo);
                }
                else {
                    fprintf(stderr, "Filterspecs format error!\n");
                    showHelp();
                    delete filterInfo;
                    filterInfo = NULL;
                }
            }
            break;

        case 'n':
            {
                operations = operations | OPERATION_MASK_N;
                INT optionNum = 0;
                ProcessFilterInfo *filterInfo = new ProcessFilterInfo;
                filterInfo->next = NULL;
                memset(filterInfo->filterInfo.filter, 0, sizeof(filterInfo->filterInfo.filter));
                filterInfo->filterInfo.type = NC_LOGFILTER_TYPE_PROCESS_ADD;
                tind--;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    // process id
                    if (0 == optionNum) {
                        if ((strlen(argv[tind]) + 2) > sizeof(filterInfo->filterInfo.filter)) {
                            fprintf(stderr, "Process name too long!\n");
                            showHelp();
                            delete filterInfo;
                            filterInfo = NULL;
                            goto doexit;
                        }
                        strncat(filterInfo->filterInfo.filter, argv[tind], NC_LOG_MAX_FILTER_SIZE);
                        strncat(filterInfo->filterInfo.filter, LOG_CFG_PROCESS_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                    }
                    else {
                        if (!checkFilter(argv[tind])) {
                            fprintf(stderr, "'%s' filterspecs format error!\n", argv[tind]);
                            showHelp();
                            delete filterInfo;
                            filterInfo = NULL;
                            goto doexit;
                        }
                        if ((strlen(argv[tind]) + strlen(filterInfo->filterInfo.filter) + 2) > sizeof(filterInfo->filterInfo.filter)) {
                            fprintf(stderr, "Process filterspecs too long!\n");
                            showHelp();
                            delete filterInfo;
                            filterInfo = NULL;
                            goto doexit;
                        }
                        strncat(filterInfo->filterInfo.filter, argv[tind], NC_LOG_MAX_FILTER_SIZE);
                        strncat(filterInfo->filterInfo.filter, LOG_CFG_FILTER_GAP, NC_LOG_MAX_FILTER_SIZE);
                    }
                    tind++;
                    optionNum++;
                }
                if (optionNum > 1) {
                    addProcessFilterInfo(&filterInfoList, filterInfo);
                }
                else {
                    fprintf(stderr, "Filterspecs format error!\n");
                    showHelp();
                    delete filterInfo;
                    filterInfo = NULL;
                }
            }
            break;

        case 'r':
            {
                operations = operations | OPERATION_MASK_R;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    CHAR pidstr[32] = { 0 };
                    if (sizeof(pidstr) < strlen(argv[tind])) {
                        fprintf(stderr, "'%s' filterspecs too long!\n", argv[tind]);
                        showHelp();
                        goto doexit;
                    }
                    strncpy(pidstr, argv[tind], strlen(argv[tind]));
                    ProcessFilterInfo *filterInfo = new ProcessFilterInfo;
                    filterInfo->next = NULL;
                    memset(filterInfo->filterInfo.filter, 0, sizeof(filterInfo->filterInfo.filter));
                    filterInfo->filterInfo.type = NC_LOGFILTER_TYPE_PROCESS_DEL;
                    if (!getProcessName(atoi(pidstr), filterInfo->filterInfo.filter, sizeof(filterInfo->filterInfo.filter))) {
                        delete filterInfo;
                        filterInfo = NULL;
                        fprintf(stderr, "can't get the process name, please check the PID[%d]!\n", atoi(pidstr));
                        goto doexit;
                    }
                    fprintf(stdout, "PID[%d]->Name[%s]\n", atoi(pidstr), filterInfo->filterInfo.filter);
                    addProcessFilterInfo(&filterInfoList, filterInfo);
                    tind++;
                }
            }
            break;

        case 'm':
            {
                operations = operations | OPERATION_MASK_M;
                while (tind < argc) {
                    if (0 == strncmp(argv[tind], "-", 1)) {
                        break;
                    }
                    if (0 == strncmp(argv[tind], "*", 1)) {
                        if (1 != strlen(argv[tind])) {
                            fprintf(stderr, "'%s' filterspecs format error!\n", argv[tind]);
                            showHelp();
                            goto doexit;
                        }
                    }
                    else {
                        if (strlen(argv[tind]) >= sizeof(NCLogFilterInfo::filter)) {
                            fprintf(stderr, "'%s' filterspecs too long!\n", argv[tind]);
                            showHelp();
                            goto doexit;
                        }
                    }
                    ProcessFilterInfo *filterInfo = new ProcessFilterInfo;
                    filterInfo->next = NULL;
                    memset(filterInfo->filterInfo.filter, 0, sizeof(filterInfo->filterInfo.filter));
                    filterInfo->filterInfo.type = NC_LOGFILTER_TYPE_PROCESS_DEL;
                    strncpy(filterInfo->filterInfo.filter, argv[tind], sizeof(filterInfo->filterInfo.filter));
                    addProcessFilterInfo(&filterInfoList, filterInfo);
                    tind++;
                }
            }
            break;

        default:
            {
                printf("Invalid arguments! \n");
                printf("Try `logcfg --help' for more information.\n");
                goto doexit;
            }
        }
    }

    // default
    if (0 != (operations & OPERATION_MASK_D)) {
        NCLogFilterInfo defaultFilter;
        memset(&defaultFilter, 0, sizeof(defaultFilter));
        strncpy(defaultFilter.filter, getDefaultNCLogCfgFilter(), NC_LOG_MAX_FILTER_SIZE);
        defaultFilter.type = NC_LOGFILTER_TYPE_LOGCAT;
        changeFilter(defaultFilter);

        strncpy(defaultFilter.filter, getDefaultFileCfgFilter(), NC_LOG_MAX_FILTER_SIZE);
        defaultFilter.type = NC_LOGFILTER_TYPE_LOGFILE;
        changeFilter(defaultFilter);

        defaultFilter.type = NC_LOGFILTER_TYPE_PROCESS_DEL;
        strncpy(defaultFilter.filter, "*", NC_LOG_MAX_FILTER_SIZE);
        changeProcessFilter(defaultFilter);
    }

    if (0 != ((operations & OPERATION_MASK_C) && !(operations & OPERATION_MASK_A)
        && !(operations & OPERATION_MASK_B))) {
        if (0 == strlen(logcatTempFilter.filter)) {
            strncpy(logcatTempFilter.filter, getDefaultNCLogCfgFilter(), NC_LOG_MAX_FILTER_SIZE);
        }

        logcatTempFilter.type = NC_LOGFILTER_TYPE_LOGCAT;
        logcatTempFilter.bufID = LOG_ID_MAIN;
        changeFilter(logcatTempFilter);
    }

    if (0 != ((operations & OPERATION_MASK_F) && !(operations & OPERATION_MASK_A))) {
        if (0 == strlen(fileFilter.filter)) {
            strncpy(fileFilter.filter, getDefaultFileCfgFilter(), NC_LOG_MAX_FILTER_SIZE);
        }

        changeFilter(fileFilter);
    }

    if (0 != (((operations & OPERATION_MASK_C) && (operations & OPERATION_MASK_A))
        || ((operations & OPERATION_MASK_F) && (operations & OPERATION_MASK_A)))) {

        if (0 != strlen(newFilter.filter)) {

            BOOL ret = NC_FALSE;
            if (operations & OPERATION_MASK_C) {
                newFilter.type = NC_LOGFILTER_TYPE_LOGCAT;
                appendFilter(newFilter);
            }

            if (operations & OPERATION_MASK_F) {
                newFilter.type = NC_LOGFILTER_TYPE_LOGFILE;
                appendFilter(newFilter);
            }
        }
    }

    if (0 != (operations & OPERATION_MASK_P) || 0 != (operations & OPERATION_MASK_R)
        || 0 != (operations & OPERATION_MASK_N) || 0 != (operations & OPERATION_MASK_M)) {
        ProcessFilterInfo* curInfo = filterInfoList;
        while (curInfo) {
            changeProcessFilter(curInfo->filterInfo);
            curInfo = curInfo->next;
        }
    }

    if (0 != ((operations & OPERATION_MASK_B) && (operations & OPERATION_MASK_C))) {
        if (0 == strlen(logcatTempFilter.filter)) {
            strncpy(logcatTempFilter.filter, getDefaultNCLogCfgFilter(), NC_LOG_MAX_FILTER_SIZE);
        }

        if (0 == strncmp("main", deviceName, DEVICE_NAME_LEN)) {
            logcatTempFilter.type = NC_LOGFILTER_TYPE_LOGCAT;
            logcatTempFilter.bufID = LOG_ID_MAIN;
        }
        else if (0 == strncmp("radio", deviceName, DEVICE_NAME_LEN)) {
            logcatTempFilter.type = NC_LOGFILTER_TYPE_LOGCAT;
            logcatTempFilter.bufID = LOG_ID_RADIO;
        }
        changeFilter(logcatTempFilter);
    }
    printf("!!!!Done!!!!\n");

doexit:
    freeAllFilter(&filterInfoList);
    exit(0);

    return 0;
}

/* EOF */
