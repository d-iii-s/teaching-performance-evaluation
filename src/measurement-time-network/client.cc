#include <assert.h>
#include <iostream>

using namespace std;

#include <grpc++/grpc++.h>
using namespace grpc;

#include "clock.grpc.pb.h"

#include "shared.h"


#define CYCLES 10000


uint64_t local_clock_array [CYCLES];
uint64_t remote_clock_array [CYCLES];


int main (int argc, char *argv [])
{
    // Expects server address.
    assert (argc == 2);
    char *server_addr = argv [1];

    shared_ptr<Channel> channel = CreateChannel (server_addr, InsecureChannelCredentials ());
    shared_ptr<ClockService::Stub> stub = ClockService::NewStub (channel);

    google::protobuf::Empty request;
    Stamp response;

    std::cout << "index,local,remote" << std::endl;

    for (int i = 0 ; i < CYCLES ; i ++) {
        local_clock_array [i] = get_time ();
        ClientContext context;
        Status status = stub->GetTime (&context, request, &response);
        assert (status.ok ());
        remote_clock_array [i] = response.time ();
    }

    for (int i = 0 ; i < CYCLES ; i ++) {
        cout << i <<
         "," << local_clock_array [i] - local_clock_array [0] <<
         "," << remote_clock_array [i] - remote_clock_array [0] <<
         endl;
    }

    return (0);
}
