#include "RPCtransport.h"



size_t RPCtransport::send(const void* buffer, size_t size)
{
    size_t n = std::min(m_buffer.size(), size);
    std::memcpy(m_buffer.data(), buffer, n);
    m_message = n;
    return n;
}

size_t RPCtransport::recv(void* buffer, size_t size)
{
    if (m_message > 0) {
        size_t n = std::min(m_message, size);
        std::memcpy(buffer, m_buffer.data(), n);
        m_message = 0;
        return n;
    }
    return 0;
}

RPCtransport* newTransport()
{
    return new RPCtransport;
}

size_t send(RPCtransport* t, const void* buffer, size_t size)
{
    return t->send(buffer, size);
}

size_t recv(RPCtransport* t, void* buffer, size_t size)
{
    return t->recv(buffer, size);
}