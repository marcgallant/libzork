#include <libzork/runner/smart.hh>
#include <map>

#include "exceptions.hh"
#include "runner/smart_impl.hh"
#include "yaml-cpp/node/node.h"
#include "yaml-cpp/node/parse.h"
#include "yaml-cpp/parser.h"
#include "yaml-cpp/yaml.h"

namespace libzork::runner
{

    std::unique_ptr<SmartRunner>
    make_smart_runner(std::unique_ptr<story::Story> story,
                      const fs::path& synonyms_path, std::istream& is,
                      std::ostream& os)
    {
        std::map<std::string, std::vector<std::string>> synonyms_map;

        YAML::Node doc = YAML::LoadFile(synonyms_path);

        if (doc.IsNull())
            throw std::runtime_error("Invalid synonyms path");

        for (auto i = doc.begin(); i != doc.end(); ++i)
        {
            auto word = (*i)["word"].as<std::string>();
            auto synonyms = (*i)["synonyms"].as<std::vector<std::string>>();

            synonyms_map.emplace(word, synonyms);
        }

        return std::make_unique<SmartRunnerImpl>(std::move(story), synonyms_map,
                                                 is, os);
    }

} // namespace libzork::runner
