#pragma once

#include <libzork/runner/html.hh>

namespace libzork::runner
{

    class HTMLRunnerImpl : public HTMLRunner
    {
    public:
        HTMLRunnerImpl(std::unique_ptr<story::Story> story,
                       const fs::path& output_dir);

        ~HTMLRunnerImpl() override = default;

        void run() override;

    private:
        const fs::path output_dir_;
    };

} // namespace libzork::runner
