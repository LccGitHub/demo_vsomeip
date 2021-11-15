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
 * @file LooperThreadBase.h
 *
 * @brief define class LooperThreadBase
 *
 */

#ifndef LOOPERTHREADBASE_H
#define LOOPERTHREADBASE_H

#include "Message.h"
#include "MessageHandler.h"

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

namespace nutshell
{

class LooperThreadImpl;

class LooperThreadBase
{
public:
    LooperThreadBase(const MessageHandler* msgHandler);
    virtual ~LooperThreadBase();

    int startThread(const char* const name);
    int stopThread();

    int postMessage(std::shared_ptr<Message> msg);
    int cancelMessage(int what);

 private:
    LooperThreadImpl* m_impl;
};

}

#endif
/* EOF */