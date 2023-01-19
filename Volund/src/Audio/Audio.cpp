#include "PCH/PCH.h"

#include "Audio.h"

namespace Volund
{
    bool CheckALCErrors(const std::string& FileName, const std::uint_fast32_t Line, ALCdevice* Device)
    {
        ALCenum ERR = alcGetError(Device);
        switch (ERR)
        {
        case ALC_INVALID_VALUE:
        {
            VOLUND_WARNING("ALC_INVALID_VALUE: an invalid value was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case ALC_INVALID_DEVICE:
        {
            VOLUND_WARNING("ALC_INVALID_DEVICE: a bad device was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case ALC_INVALID_CONTEXT:
        {
            VOLUND_WARNING("ALC_INVALID_CONTEXT: a bad context was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case ALC_INVALID_ENUM:
        {
            VOLUND_WARNING("ALC_INVALID_ENUM: an unknown enum value was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case ALC_OUT_OF_MEMORY:
        {
            VOLUND_WARNING("ALC_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case ALC_NO_ERROR:
        {
            return true;
        }
        break;
        default:
        {
            VOLUND_WARNING("Unknown ALC Error: %d, (%s, %d)", ERR, FileName.c_str(), Line);
        }
        break;
        }

        return false;
    }

    bool CheckALErrors(const std::string& FileName, const std::uint_fast32_t Line)
    {
        ALenum ERR = alGetError();
        switch (ERR)
        {
        case AL_INVALID_VALUE:
        {
            VOLUND_WARNING("AL_INVALID_VALUE: an invalid value was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case AL_INVALID_OPERATION:
        {
            VOLUND_WARNING("AL_INVALID_OPERATION: an invalid OpenAL operation was attempted, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case AL_INVALID_ENUM:
        {
            VOLUND_WARNING("AL_INVALID_ENUM: an unknown enum value was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case AL_OUT_OF_MEMORY:
        {
            VOLUND_WARNING("AL_OUT_OF_MEMORY: an unknown enum value was passed to an OpenAL function, (%s, %d)", FileName.c_str(), Line);
        }
        break;
        case AL_NO_ERROR:
        {
            return true;
        }
        break;
        default:
        {
            VOLUND_WARNING("Unknown AL Error: %d, (%s, %d)", ERR, FileName.c_str(), Line);
        }
        break;
        }

        return false;
    }
}