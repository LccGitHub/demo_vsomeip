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
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

using namespace nutshell;

class TestMessageHandler: public MessageHandler
{
public:
    TestMessageHandler()
    {

    }

    virtual ~TestMessageHandler()
    {

    }

    virtual void onReceiveMessage(std::shared_ptr<Message> msg)
    {
        printf("onReceiveMessage msg->what = %d\n", msg->what());
    }
};

static LooperThreadBase* m_thread = NULL;

static void* pthread(void* arg)
{
    printf("child thread!\n");
    int i = 1000;
    while (1) {
        int num = i++;
        std::shared_ptr<Message> message = std::make_shared<Message>(num);
        m_thread->postMessage(message);
        usleep(200*1000);
    }
}

static void* pthread1(void* arg)
{
    printf("child thread!\n");
    int i = 2000;
    while (1) {
        int num = i++;
        std::shared_ptr<Message> message = std::make_shared<Message>(num);
        m_thread->postMessage(message);
        usleep(100*1000);
    }
}

static void* pthread2(void* arg)
{
    printf("child thread!\n");
    int i = 3000;
    while (1) {
        int num = i++;
        std::shared_ptr<Message> message = std::make_shared<Message>(num);
        m_thread->postMessage(message);
        usleep(50*1000);
    }
}

int main()
{
    TestMessageHandler msgHandler;
    m_thread = new LooperThreadBase(&msgHandler);
    m_thread->startThread("Test");

    pthread_t tidp;
    pthread_create(&tidp, NULL, pthread, NULL);
    pthread_t tidp1;
    pthread_create(&tidp1, NULL, pthread1, NULL);
    pthread_t tidp2;
    pthread_create(&tidp2, NULL, pthread2, NULL);

    int num = 0;
    while (num <= 5) {
        std::shared_ptr<Message> message = std::make_shared<Message>(num);
        m_thread->postMessage(message);
        sleep(1);
        num ++;
    }
    m_thread->stopThread();

    pthread_join(tidp, NULL);
    pthread_join(tidp1, NULL);
    pthread_join(tidp2, NULL);
    m_thread->stopThread();
    
    return 0;
}
/* EOF */
