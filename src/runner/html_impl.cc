#include "runner/html_impl.hh"

#include <fstream>

#include "exceptions.hh"
#include "story/node_impl.hh"
#include "story/story_impl.hh"

namespace libzork::runner
{

    void HTMLRunnerImpl::run()
    {
        auto* story_impl = dynamic_cast<story::StoryImpl*>(story_.get());
        std::vector<std::unique_ptr<story::Node>> nodes =
            story_impl->get_nodes();

        if (!fs::exists(output_dir_))
            fs::create_directories(output_dir_);

        for (auto i = nodes.begin(); i != nodes.end(); ++i)
        {
            story::NodeImpl* node = dynamic_cast<story::NodeImpl*>(i->get());

            std::ofstream file_out;
            file_out.open(output_dir_ / (node->get_name() + ".html"));

            file_out << "<html>\n";
            file_out << "<body>\n";
            file_out << "<p>" << node->get_text() << "</p>\n";
            file_out << "<ol>\n";

            const std::vector<story::Choice>& choices = node->get_choices();
            for (auto j = choices.begin(); j != choices.end(); ++j)
            {
                file_out << "<li><a href="
                         << (absolute(output_dir_)
                             / (j->get_target()->get_name() + ".html"))
                         << ">" << j->get_text() << "</a></li>\n";
            }

            file_out << "</ol>\n";
            file_out << "</body>\n";
            file_out << "</html>";
        }
    }

    HTMLRunnerImpl::HTMLRunnerImpl(std::unique_ptr<story::Story> story,
                                   const fs::path& output_dir)
        : HTMLRunner(std::move(story))
        , output_dir_(output_dir)
    {}

} // namespace libzork::runner
