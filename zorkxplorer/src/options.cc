#include "options.hh"

#include <getopt.h>
#include <iostream>

namespace
{
    constexpr option options[] = {
        { "story", required_argument, nullptr, 's' },
        { "smart", required_argument, nullptr, 'm' },
        { "html", required_argument, nullptr, 'h' },
    };

    std::string usage(const std::string& name)
    {
        return "usage: " + name
            + " (--story <story.yml>)"
              " [--smart <synonyms.yml> | --html <directory/>]";
    };
} // namespace

Config parse_options(int argc, char** argv)
{
    Config config;
    int opt;
    while ((opt = getopt_long(argc, argv, "s:m:h:t:u:o:n:r:", options, nullptr))
           != -1)
    {
        switch (opt)
        {
        case 's': // --story
            config.story_path = optarg;
            break;
        case 'm': // --smart
            if (config.story_type == StoryType::HTML)
                throw std::invalid_argument(
                    "incompatble options: `--smart` and `--html`");
            config.story_type = StoryType::Smart;
            config.story_arg = optarg;
            break;
        case 'h': // --html
            if (config.story_type == StoryType::Smart)
                throw std::invalid_argument(
                    "incompatible options: `--smart` and `--html`");
            config.story_type = StoryType::HTML;
            config.story_arg = optarg;
            break;
        default:
            throw std::invalid_argument(usage(argv[0]));
        }
    };

    if (config.story_path.empty())
        throw std::invalid_argument("option '--story' is mandatory");

    return config;
}
