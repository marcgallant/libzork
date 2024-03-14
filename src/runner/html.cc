#include <libzork/runner/html.hh>

#include "exceptions.hh"
#include "runner/html_impl.hh"

namespace libzork::runner
{

    std::unique_ptr<HTMLRunner>
    make_html_runner(std::unique_ptr<story::Story> story,
                     const fs::path& output_dir)
    {
        return std::make_unique<HTMLRunnerImpl>(std::move(story), output_dir);
    }

} // namespace libzork::runner
