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


#include "LooperThreadBase.h"
#include "LooperThreadImpl.h"

#include "ThreadLog.h"

namespace nutshell
{

LooperThreadBase::LooperThreadBase(const MessageHandler* msgHandler)
{
    HU_THREAD_D("[LooperThreadBase::LooperThreadBase] [%p] ", this);
    m_impl = new LooperThreadImpl();
    if (m_impl != NULL) {
        m_impl->registerHandler(msgHandler);
    }
}

LooperThreadBase::~LooperThreadBase()
{
    HU_THREAD_D("[LooperThreadBase::~LooperThreadBase] [%p] ", this);
    stopThread();
}

int LooperThreadBase::startThread(const char* const name)
{
    int ret = -1;
    if (m_impl != NULL) {
        ret = 0;
        m_impl->start(name);
    }
    return ret;
}

int LooperThreadBase::stopThread()
{
    int ret = -1;
    if (m_impl != NULL) {
        ret = 0;
        m_impl->stop();
        m_impl->join();
    }
    return ret;
}

int LooperThreadBase::postMessage(std::shared_ptr<Message> msg)
{
    int ret = -1;
    if (m_impl != NULL) {
        ret = m_impl->postMessage(msg);
    }
    return ret;
}

int LooperThreadBase::cancelMessage(int what)
{
    int ret = -1;
    if (m_impl != NULL) {
        ret = m_impl->cancelMessage(what);
    }
    return ret;
}

}
/* EOF */
