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
 * @file LooperThreadImpl.h
 *
 * @brief define class LooperThreadImpl
 *
 */

#ifndef LOOPERTHREADIMPL_H
#define LOOPERTHREADIMPL_H

#include <list>
#include <chrono>
#include <condition_variable>
#include <thread>
#include <mutex>
#include "Message.h"
#include "MessageHandler.h"

#ifndef __cplusplus
#   error ERROR: This file requires C++ compilation (use a .cpp suffix)
#endif

namespace nutshell
{

class LooperThreadImpl 
{
public:
    LooperThreadImpl();
    virtual ~LooperThreadImpl();

    void start(const char* const name);
    void stop();

    int postMessage(const std::shared_ptr<Message> msg);
    int cancelMessage(int what);
    void registerHandler(const MessageHandler* msgHandler);
    bool join( uint32_t msec = 0);

private:
    virtual void run();
    bool checkQuit();
    bool waitTime(uint32_t msec = 0);
    void notify();
    void startThread(const char* const name);
    void stopThread();

 private:
    std::list<std::shared_ptr<Message>> m_reqList;
    int m_reqListSize;
    MessageHandler* m_msgHandler;
    std::mutex m_syncObj;

    std::mutex thread_mutex_;
    std::condition_variable thread_condition_;
    bool thread_blocked_;
    bool thread_running_;
    std::shared_ptr<std::thread> loop_thread_;
    std::string thread_name_;
};

}

#endif
/* EOF */