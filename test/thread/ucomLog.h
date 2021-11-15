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
#ifndef UCOM_LOG_H
#define UCOM_LOG_H

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif




enum UComLogTag {
    UCOM_LOG_V,
    UCOM_LOG_D,
    UCOM_LOG_I,
    UCOM_LOG_W,
    UCOM_LOG_E,
};


#ifndef LOG_LEVEL
#define LOG_LEVEL UCOM_LOG_V
#endif

void UComLog(const char* log_tag, UComLogTag tag, const char* func, int line, const char* format, ...);





#endif // UCOM_LOG_H
/* EOF */
