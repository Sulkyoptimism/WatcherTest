#include "message.h"


class RPCtransport;

size_t send(RPCtransport* t, const void* buffer, size_t size);

void message::sendPacket(RPCtransport* t, void* buffer, size_t bufferSize)
{
    const size_t packetSize = makePacket(buffer, bufferSize);
    send(t, buffer, packetSize);
}

void message::activate() {
    started = true;
}

size_t message::makePacket(void* buffer, size_t size)
{
    // Construct a packet
    OSCPP::Client::Packet packet(buffer, size);
    packet
        // Open a bundle with a timetag
        .openBundle(1234ULL)
        // Add a message with two arguments and an array with 6 elements;
        // for efficiency this needs to be known in advance.
        .openMessage("/s_new", 2 + OSCPP::Tags::array(6))
        // Write the arguments
        .string("Note")
        .int32(2)
        // Every `open` needs a corresponding `close`
        .closeMessage()
        .closeBundle();

    return packet.size();
};

