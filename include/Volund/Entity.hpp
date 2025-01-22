#pragma once

#include <cstdint>

#define VOLUND_ENTITY_NULL (Volund::Entity(0, 0))

namespace Volund
{
    struct Entity
    {
        uint32_t index;
        uint32_t generation;
        uint64_t AsInt() {return (((uint64_t)index) << 32 | generation);}
        bool operator==(Entity other) {return this->index == other.index && this->generation && other.generation;}
    };
}