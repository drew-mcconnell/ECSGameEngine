#pragma once
#include <stdint.h>
#include <bitset>

using Entity = std::uint8_t;
const uint8_t maxEntities = 10;

const uint8_t maxComponents = 32;
using Signature = std::bitset<maxComponents>;

const uint8_t maxInputContexts = 10;