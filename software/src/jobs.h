#pragma once

#include <functional>

void transcribe(std::function<void()> syncStart, std::function<void()> syncEnd);