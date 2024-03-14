#pragma once

#include <functional>
#include <libzork/vars/condition.hh>

namespace libzork::vars
{
    class ConditionImpl : public Condition
    {
    public:
        ConditionImpl(const store::Store& store, const std::string& variable,
                      std::function<bool(int, int)> condition, int value);

        ~ConditionImpl() override = default;

        bool apply() const override;

    private:
        const store::Store& store_;
        const std::string variable_;
        std::function<bool(int, int)> condition_;
        int value_;
    };

} // namespace libzork::vars
