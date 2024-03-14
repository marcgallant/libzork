#include <algorithm>
#include <fstream>
#include <iostream>
#include <libzork/exceptions.hh>
#include <libzork/runner/choice.hh>
#include <libzork/runner/html.hh>
#include <libzork/runner/smart.hh>
#include <libzork/store/store.hh>

#include "../../src/store/store_impl.hh"
#include "options.hh"

std::unique_ptr<libzork::story::Story> get_story(const Config& config)
{
    return libzork::story::make_story(config.story_path);
}

std::unique_ptr<libzork::runner::Runner>
get_runner(const Config& config, std::unique_ptr<libzork::story::Story> story)
{
    switch (config.story_type)
    {
    case StoryType::Choice:
        return libzork::runner::make_choice_runner(std::move(story));
    case StoryType::Smart:
        return libzork::runner::make_smart_runner(std::move(story),
                                                  config.story_arg);
    case StoryType::HTML:
        return libzork::runner::make_html_runner(std::move(story),
                                                 config.story_arg);
    default:
        return nullptr;
    }
}

int main(int argc, char** argv)
{
    Config config;
    try
    {
        config = parse_options(argc, argv);
    }
    catch (const std::invalid_argument& exc)
    {
        std::cerr << "invalid options: " << exc.what() << "\n";
        return 1;
    }

    std::unique_ptr<libzork::runner::Runner> runner;

    auto story = get_story(config);

    /*runner = get_runner(config, std::move(story));
    try
    {
        runner->run();
    }
    catch (const libzork::RunnerQuit&)
    {}*/

    auto* store = story->get_store();
    const auto* store_impl =
        dynamic_cast<const libzork::store::StoreImpl*>(store);
    store_impl->save(std::cout);

    return 0;
}
