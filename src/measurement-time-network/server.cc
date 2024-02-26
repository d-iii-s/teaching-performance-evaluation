#include <iostream>

using namespace std;

#include <grpc++/grpc++.h>
using namespace grpc;

#include "clock.grpc.pb.h"

#include "shared.h"


#define SERVER_ADDR "[::]:8888"


class MyClockService : public ClockService::Service {
    Status GetTime (ServerContext *context, const google::protobuf::Empty *request, Stamp *response) override {
        response->set_time (get_time ());
        return (Status::OK);
    }
};


int main () {
    MyClockService service;
    ServerBuilder builder;
    builder.AddListeningPort (SERVER_ADDR, InsecureServerCredentials ());
    builder.RegisterService (&service);
    unique_ptr<Server> server (builder.BuildAndStart ());

    server->Wait ();

    return (0);
}
