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
/**
 * @file uComLog.h
 * @brief Declaration file of class uComLog.
 *
 * This file includes the declaration of class uComLog, and
 * the definitions of the macros, struct, enum and so on.
 *
 * @attention used for C++ only.
 */
#ifndef THREAD_LOG_H
#define THREAD_LOG_H

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include <stdio.h>


#ifdef UCOM_LOG_TAG
#undef UCOM_LOG_TAG
#endif

#define UCOM_LOG_TAG "thread"

#define LOG_HEAD(fmt) "[%s:%d] " fmt
#define HU_THREAD_E(fmt, ...) printf(LOG_HEAD(fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__), printf("\n")
#define HU_THREAD_W(fmt, ...) printf(LOG_HEAD(fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__), printf("\n")
#define HU_THREAD_I(fmt, ...) printf(LOG_HEAD(fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__), printf("\n")
#define HU_THREAD_D(fmt, ...) printf(LOG_HEAD(fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__), printf("\n")
#define HU_THREAD_V(fmt, ...) printf(LOG_HEAD(fmt), __FUNCTION__, __LINE__, ##__VA_ARGS__), printf("\n")





#endif // THREAD_LOG_H
/* EOF */
