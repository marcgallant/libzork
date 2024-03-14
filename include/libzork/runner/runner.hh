#pragma once

#include <libzork/story/story.hh>

namespace libzork::runner
{

    class Runner
    {
    public:
        Runner(std::unique_ptr<story::Story> story);

        virtual ~Runner() = default;

        virtual void run() = 0;

    protected:
        std::unique_ptr<story::Story> story_;
    };

} // namespace libzork::runner
