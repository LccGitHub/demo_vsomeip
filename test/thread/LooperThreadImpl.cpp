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


#include "LooperThreadImpl.h"
#include "ThreadLog.h"

namespace nutshell
{

#define REQUEST_LIST_MAX_SIZE 500*1000


LooperThreadImpl::LooperThreadImpl()
    : m_reqList()
    , m_reqListSize(0)
    , m_msgHandler(NULL)
    , thread_mutex_()
    , thread_condition_()
    , thread_blocked_()
    , thread_running_(true)
    , loop_thread_()
{
    HU_THREAD_D("[LooperThreadImpl::LooperThreadImpl] [%p] ", this);
}

LooperThreadImpl::~LooperThreadImpl()
{
    HU_THREAD_D("[LooperThreadImpl::~LooperThreadImpl] [%p] ", this);
    std::lock_guard<std::mutex> its_lock(m_syncObj);
    m_reqList.clear();
}

void LooperThreadImpl::start(const char* const name)
{
    HU_THREAD_D("Thread::run, start at [%s]", name);
    startThread(name);
}

void LooperThreadImpl::stop()
{
    stopThread();
    {
        std::lock_guard<std::mutex> its_lock(m_syncObj);
        std::list<std::shared_ptr<Message>>::iterator it = m_reqList.begin();
        for (; it != m_reqList.end(); ) {
            *it = NULL;
            m_reqList.erase(it);
            --m_reqListSize;
        }
    }
}

int LooperThreadImpl::postMessage(const std::shared_ptr<Message> msg)
{
    {
        std::lock_guard<std::mutex> its_lock(m_syncObj);
        if (checkQuit()) {
            HU_THREAD_E("rLooperThreadImpl::postMessage thread have exist\n");
            return -1;
        }

        if (m_reqListSize > REQUEST_LIST_MAX_SIZE) {
            HU_THREAD_E("request list is full!\n");
            return -1;
        }

        m_reqList.push_back(msg);
        ++m_reqListSize;
    }


    notify();
    return 0;
}

int LooperThreadImpl::cancelMessage(int what)
{
    {
        std::lock_guard<std::mutex> its_lock(m_syncObj);
        if (checkQuit() || m_reqList.empty()) {
            HU_THREAD_E("cancelMessage invalid!\n");
            return -1;
        }

        std::list<std::shared_ptr<Message>>::iterator it = m_reqList.begin();
        for (; it != m_reqList.end(); ) {
            if ((*it)->what() == what) {
                m_reqList.erase(it);
                --m_reqListSize;
            }
        }
    }
    return 0;
}

void LooperThreadImpl::registerHandler(const MessageHandler* msgHandler)
{
    m_msgHandler = const_cast<MessageHandler*>(msgHandler);
}

void LooperThreadImpl::startThread(const char* const name)
{
    HU_THREAD_D("Thread::run, start at [%s]", name);
    thread_name_ = std::string(name);
    loop_thread_ = std::make_shared<std::thread>(&LooperThreadImpl::run, this);
#if 0    
    int32_t ret = pthread_setname_np( loop_thread_->get_id(), name );
    if (0 != ret ) {
        HU_THREAD_D("[pthread_setname_np failed] [%d] ", ret);
    }
#endif    
}

void LooperThreadImpl::stopThread()
{
    thread_running_ = false;
    notify();
}

bool LooperThreadImpl::join( uint32_t msec ) 
{
    loop_thread_->join();
    return true;
}


void LooperThreadImpl::notify()
{
    std::lock_guard<std::mutex> its_lock(thread_mutex_);
    thread_condition_.notify_one();
}

bool LooperThreadImpl::checkQuit()
{
    bool res = !thread_running_;
    return res;
}

bool LooperThreadImpl::waitTime(uint32_t msec )
{
    std::unique_lock<std::mutex> its_lock(thread_mutex_);
    thread_condition_.wait(its_lock);
    return true;
}

void LooperThreadImpl::run()
{
    HU_THREAD_D("LooperThreadImpl::run checkQuit(%d)", checkQuit());
    int res = pthread_setname_np(pthread_self(), thread_name_.c_str());
    HU_THREAD_D("LooperThreadImpl::pthread_setname_np res(%d)", res);

    std::shared_ptr<Message> m_curReq = NULL;
    while (!checkQuit()) {
        bool isListEmpty = true;
        {
            std::lock_guard<std::mutex> its_lock(m_syncObj);
            isListEmpty = m_reqList.empty();
        }
        if (isListEmpty) {
            bool ret = waitTime();
            if (!ret) {
                HU_THREAD_E("NCIpcWorkThread::run, call wait failed\n");
            }
        }
        else {
            {
                std::lock_guard<std::mutex> its_lock(m_syncObj);
                m_curReq = *(m_reqList.begin());
                m_reqList.erase(m_reqList.begin());
                --m_reqListSize;
                const uint8_t LIST_SIZE_WARNNING = 30;
                static uint8_t printFlag = 0;
                if ((m_reqListSize >= LIST_SIZE_WARNNING) && (printFlag == 0)) {
                    printFlag = 1;
                    HU_THREAD_W("warnning:there are %d messages in list.",m_reqListSize);
                }
                else if ((m_reqListSize < LIST_SIZE_WARNNING) && (printFlag == 1)) {
                    HU_THREAD_W("warnning:there are %d messages in list.", m_reqListSize);
                    printFlag = 0; // reset printf flag
                }
                else {
                    // no printf debug log
                }
            }

            // HU_THREAD_D("Message:what = %d\n", m_curReq->what());
            if (m_msgHandler != NULL) {
                m_msgHandler->onReceiveMessage(m_curReq);
            }
        }
    }
    HU_THREAD_D("finish ");

}

}
/* EOF */
