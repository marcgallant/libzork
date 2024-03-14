#include <fstream>
#include <libzork/story/node.hh>

#include "exceptions.hh"
#include "story/node_impl.hh"

namespace libzork::story
{

    std::unique_ptr<Node> make_node(const std::string& name,
                                    const fs::path& script_path)
    {
        std::string text;

        std::ifstream file_in;
        file_in.open(script_path);
        if (!file_in.is_open())
            throw std::runtime_error("Invalid script path");

        std::string token;
        while (std::getline(file_in, token))
        {
            text.append(token);
            text.append("\n");
        }

        return std::make_unique<NodeImpl>(name, text);
    }

} // namespace libzork::story
