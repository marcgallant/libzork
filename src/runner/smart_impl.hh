#pragma once

#include <libzork/runner/smart.hh>
#include <map>

namespace libzork::runner
{
    using synonyms_type = std::map<std::string, std::vector<std::string>>;

    class SmartRunnerImpl : public SmartRunner
    {
    public:
        SmartRunnerImpl(std::unique_ptr<story::Story> story,
                        synonyms_type synonyms, std::istream& is,
                        std::ostream& os);
        void process_input() override;
        int count_synonyms(const std::string& left,
                           const std::string& right) const override;

    private:
        synonyms_type synonyms_;
    };

} // namespace libzork::runner
