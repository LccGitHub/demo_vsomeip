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

#include "Message.h"

namespace nutshell
{
    Message::Message(int what)
    : m_what(what)
    {

    }

    Message::~Message()
    {

    }

    int Message::what()
    {
        return m_what;
    }

    void Message::setWhat(int what)
    {
        m_what = what;
    }
}
/* EOF */
