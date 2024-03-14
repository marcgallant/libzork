#pragma once

#include <libzork/runner/interactive.hh>

namespace libzork::runner
{

    class SmartRunner : public InteractiveRunner
    {
    public:
        using InteractiveRunner::InteractiveRunner;

        ~SmartRunner() override = default;

        virtual int count_synonyms(const std::string& left,
                                   const std::string& right) const = 0;
    };

    std::unique_ptr<SmartRunner> make_smart_runner(
        std::unique_ptr<story::Story> story, const fs::path& synonyms_path,
        std::istream& is = std::cin, std::ostream& os = std::cout);

} // namespace libzork::runner
