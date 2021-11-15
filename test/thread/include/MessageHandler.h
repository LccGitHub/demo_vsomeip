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
 * @file MessageHandler.h
 *
 * @brief define class MessageHandler
 *
 */

#ifndef MESSAGEHANDLER_H
#define MESSAGEHANDLER_H

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

#include "Message.h"

namespace nutshell
{
    class MessageHandler
    {
    public:
        MessageHandler() {};
        virtual ~MessageHandler() {};

        virtual void onReceiveMessage(std::shared_ptr<Message> msg) = 0;
    };
}

#endif
/* EOF */