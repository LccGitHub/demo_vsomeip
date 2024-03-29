// Copyright (C) 2015-2017 Bayerische Motoren Werke Aktiengesellschaft (BMW AG)
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <chrono>
#include <thread>
#include <condition_variable>
#include <mutex>
#include <vsomeip/vsomeip.hpp>



#include <cstdio>
#define LOG_INF(...) fprintf(stdout, __VA_ARGS__), fprintf(stdout, "\n")
#define LOG_ERR(...) fprintf(stderr, __VA_ARGS__), fprintf(stderr, "\n")

static vsomeip::service_t service_id = 0x00F0;
static vsomeip::instance_t service_instance_id = 0x0001;
static vsomeip::method_t service_method_id = 0x8001;


#define SAMPLE_EVENT_ID         0x8778
#define SAMPLE_GET_METHOD_ID    0x0001
#define SAMPLE_SET_METHOD_ID    0x0002

#define SAMPLE_EVENTGROUP_ID    0x4465

class hello_world_service {
public:
    // Get the vSomeIP runtime and
    // create a application via the runtime, we could pass the application name
    // here otherwise the name supplied via the VSOMEIP_APPLICATION_NAME
    // environment variable is used
    hello_world_service() :
                    rtm_(vsomeip::runtime::get()),
                    app_(rtm_->create_application("service-test")),
                    stop_(false),
                    stop_thread_(std::bind(&hello_world_service::stop, this))
    {
    }

    ~hello_world_service()
    {
        stop_thread_.join();
    }

    bool init()
    {
        // init the application
        if (!app_->init()) {
            LOG_ERR("Couldn't initialize application");
            return false;
        }

        // register a message handler callback for messages sent to our service
        app_->register_message_handler(service_id, service_instance_id,
                service_method_id,
                std::bind(&hello_world_service::on_message_cbk, this,
                        std::placeholders::_1));

        // register a state handler to get called back after registration at the
        // runtime was successful
        app_->register_state_handler(
                std::bind(&hello_world_service::on_state_cbk, this,
                        std::placeholders::_1));

        std::set<vsomeip::eventgroup_t> its_groups;
        its_groups.insert(SAMPLE_EVENTGROUP_ID);
        app_->offer_event(
                service_id,
                service_instance_id,
                SAMPLE_EVENT_ID,
                its_groups,
                vsomeip::event_type_e::ET_FIELD, std::chrono::milliseconds::zero(),
                false, true, nullptr, vsomeip::reliability_type_e::RT_UNKNOWN);
        LOG_INF("offer_event finish =======\n");                        
        return true;
    }

    void start()
    {
        // start the application and wait for the on_event callback to be called
        // this method only returns when app_->stop() is called
        app_->start();
    }

    void stop()
    {
        std::unique_lock<std::mutex> its_lock(mutex_);
        while(!stop_) {
            condition_.wait(its_lock);
        }
        std::this_thread::sleep_for(std::chrono::seconds(5));
        // Stop offering the service
        app_->stop_offer_service(service_id, service_instance_id);
        // unregister the state handler
        app_->unregister_state_handler();
        // unregister the message handler
        app_->unregister_message_handler(service_id, service_instance_id,
                service_method_id);
        // shutdown the application
        app_->stop();
    }

    void terminate() {
        std::lock_guard<std::mutex> its_lock(mutex_);
        stop_ = true;
        condition_.notify_one();
    }

    void on_state_cbk(vsomeip::state_type_e _state)
    {
        if(_state == vsomeip::state_type_e::ST_REGISTERED)
        {
            LOG_INF("on_state_cbk =======\n");
            // we are registered at the runtime and can offer our service
            app_->offer_service(service_id, service_instance_id);
            LOG_INF("offer_service finish =======\n");
        }
    }

    void on_message_cbk(const std::shared_ptr<vsomeip::message> &_request)
    {
        LOG_INF("on_message_cbk =======\n");
        // Create a response based upon the request
        std::shared_ptr<vsomeip::message> resp = rtm_->create_response(_request);

        // Construct string to send back
        std::string str("Hello ");
        str.append(
                reinterpret_cast<const char*>(_request->get_payload()->get_data()),
                0, _request->get_payload()->get_length());

        // Create a payload which will be sent back to the client
        std::shared_ptr<vsomeip::payload> resp_pl = rtm_->create_payload();
        std::vector<vsomeip::byte_t> pl_data(str.begin(), str.end());
        resp_pl->set_data(pl_data);
        resp->set_payload(resp_pl);

        // Send the response back
        app_->send(resp);

        app_->notify(service_id, service_instance_id,
                     SAMPLE_EVENT_ID, resp_pl);
        LOG_INF("notify =======\n");                     
        // we have finished
        terminate();
    }

private:
    std::shared_ptr<vsomeip::runtime> rtm_;
    std::shared_ptr<vsomeip::application> app_;
    bool stop_;
    std::mutex mutex_;
    std::condition_variable condition_;
    std::thread stop_thread_;
};







int main(int argc, char **argv)
{
    (void)argc;
    (void)argv;

    hello_world_service hw_srv;
    if (hw_srv.init()) {
        hw_srv.start();
        return 0;
    } else {
        return 1;
    }
}
