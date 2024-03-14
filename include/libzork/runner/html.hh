#pragma once

#include <libzork/runner/runner.hh>

namespace libzork::runner
{

    class HTMLRunner : public Runner
    {
    public:
        using Runner::Runner;

        ~HTMLRunner() override = default;
    };

    std::unique_ptr<HTMLRunner>
    make_html_runner(std::unique_ptr<story::Story> story,
                     const fs::path& output_dir);

} // namespace libzork::runner
