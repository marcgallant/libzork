#pragma once

#include <libzork/store/store.hh>
#include <memory>
#include <string>

namespace libzork::vars
{

    class Condition
    {
    public:
        virtual bool apply() const = 0;

        virtual ~Condition() = default;
    };

    std::unique_ptr<Condition> make_condition(const store::Store& store,
                                              const std::string& variable,
                                              const std::string& comparison,
                                              int value);

} // namespace libzork::vars
