#pragma once
#include <stdint.h>
#include <bitset>

const uint8_t maxComponents = 32;
using Signature = std::bitset<maxComponents>;
const uint8_t maxEntities = 10;