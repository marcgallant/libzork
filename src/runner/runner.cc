#include <libzork/runner/runner.hh>

#include "exceptions.hh"

namespace libzork::runner
{

    Runner::Runner(std::unique_ptr<story::Story> story)
        : story_(std::move(story))
    {}

} // namespace libzork::runner
