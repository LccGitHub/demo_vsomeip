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
 * @file Message.h
 *
 * @brief define class Message
 *
 */

#ifndef MESSAGE_H
#define MESSAGE_H

#include <memory>

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

namespace nutshell
{
    class Message: public std::enable_shared_from_this<Message>
    {
    public:
        Message(int what);
        virtual ~Message();

        int what();
        void setWhat(int what);

    private:
        int m_what;

    };
}

#endif
/* EOF */