#pragma once

#include <atomic>
#include <memory>
#include <mutex>
#include <thread>

template <typename T>
class ConcurrentElement {
    ConcurrentElement(T elem);
    
};
