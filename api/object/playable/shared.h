#ifndef SHARED_PLAYABLE_H
#define SHARED_PLAYABLE_H

namespace api
{
    enum Explicity {
        NOT_EXPLICIT = 0,
        EXPLICIT,
        UNKNOWN,
        EDITED,
        PARTIALLY_EXPLICIT,
        PARTIALLY_UNKNOWN,
        NO_ADVICE_AVAILABLE,
        PARTIALLY_NO_ADVICE_AVAILABLE
    };
}

#endif // SHARED_PLAYABLE_H
