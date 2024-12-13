#pragma once
#include <string>
#include <memory>
#include <SimpleTaskManager/Task.h>

namespace gbg {

struct Generator {
    Generator() = default;
    virtual ~Generator() = default;

    virtual std::shared_ptr<stm::Task<void>> generate(
        std::shared_ptr<stm::Task<void>> dependency = nullptr
    ) = 0;
};

} 
