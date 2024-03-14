#pragma once

#include <filesystem>
#include <optional>

namespace fs = std::filesystem;

enum class StoryType
{
    Choice,
    Smart,
    HTML,
};

struct Config
{
    std::filesystem::path story_path;
    StoryType story_type = StoryType::Choice;
    fs::path story_arg; /** Undefined if story_type is StoryType::BASIC */
};

Config parse_options(int argc, char** argv);
