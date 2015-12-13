#include "socket.h"
#include <cassert>

namespace tcp {

bool Socket::RecvFully(char* buf, int len, int flags) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return false;
    }

    int offset = 0;
    int size;
    while ((size = Recv(&buf[offset], len - offset, flags)) > 0) {
        offset += size;
        if (offset >= len) {
            return true;
        }
    }
    return false;
}

bool Socket::SendFully(const char* buf, int len, int flags) {
    if (IsClosed()) {
        assert(0 && "Already closed");
        return false;
    }

    int offset = 0;
    int size;
    while ((size = Send(&buf[offset], len - offset, flags)) > 0) {
        offset += size;
        if (offset >= len) {
            return true;
        }
    }
    return false;
}

} // namespace tcp
