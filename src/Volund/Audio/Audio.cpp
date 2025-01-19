#include "Audio/Audio.h"

#include "Logger.h"

#include <AL/al.h>
#include <AL/alext.h>

namespace Volund
{
    bool CheckAlcErrors(std::string const& fileName, const std::uint_fast32_t line, ALCdevice* device)
    {
        ALCenum err = alcGetError(device);
        switch (err)
        {
        case ALC_INVALID_VALUE:
        {
            VOLUND_WARNING("ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case ALC_INVALID_DEVICE:
        {
            VOLUND_WARNING("ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case ALC_INVALID_CONTEXT:
        {
            VOLUND_WARNING("ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case ALC_INVALID_ENUM:
        {
            VOLUND_WARNING("ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case ALC_OUT_OF_MEMORY:
        {
            VOLUND_WARNING("ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case ALC_NO_ERROR:
        {
            return true;
        }
        break;
        default:
        {
            VOLUND_WARNING("Unknown ALC Error: %d, (%s, %d)", err, fileName.c_str(), line);
        }
        break;
        }

        return false;
    }

    bool CheckAlErrors(std::string const& fileName, const std::uint_fast32_t line)
    {
        ALenum err = alGetError();
        switch (err)
        {
        case AL_INVALID_VALUE:
        {
            VOLUND_WARNING("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case AL_INVALID_OPERATION:
        {
            VOLUND_WARNING("AL_INVALID_OPERATION: an invalid OpenAL operation was attempted, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case AL_INVALID_ENUM:
        {
            VOLUND_WARNING("AL_INVALID_ENUM: an unknown enum value was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case AL_OUT_OF_MEMORY:
        {
            VOLUND_WARNING("AL_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function, (%s, %d)", fileName.c_str(), line);
        }
        break;
        case AL_NO_ERROR:
        {
            return true;
        }
        break;
        default:
        {
            VOLUND_WARNING("Unknown AL Error: %d, (%s, %d)", err, fileName.c_str(), line);
        }
        break;
        }

        return false;
    }
}