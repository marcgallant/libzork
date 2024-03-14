#include "runner/smart_impl.hh"

#include <fstream>
#include <functional>
#include <iostream>
#include <libzork/exceptions.hh>
#include <regex>
#include <set>

#include "store/store_impl.hh"
#include "yaml-cpp/yaml.h"

//#include "constants.hh"

namespace libzork::runner
{

    void SmartRunnerImpl::process_input()
    {
        try
        {
            std::string token;
            getline(is_, token);

            std::vector<std::string> choices =
                story_->get_current()->list_choices();

            unsigned long n; // Get sentence with max
            int max = 0;

            for (auto i = choices.begin(); i != choices.end(); ++i)
            {
                int tmp = count_synonyms(token, *i);
                if (tmp > max)
                {
                    n = std::distance(choices.begin(), i);
                    max = tmp;
                }
            }

            if (max == 0)
            {
                if (token.compare(".quit") == 0)
                    throw RunnerQuit();
                else if (token.compare(".brief") == 0)
                    return;
                else if (token.compare(".jump") == 0)
                    throw RunnerInterrupt("whee!");
                else if (token.compare(".shout") == 0)
                    throw RunnerInterrupt("Aaaarrrrgggghhhh!");
                else
                {
                    std::stringstream ss(token);
                    std::getline(ss, token, ' ');
                    if (token.compare(".save") == 0)
                    {
                        std::string file;
                        std::getline(ss, file, ' ');

                        const auto* store_impl =
                            dynamic_cast<const store::StoreImpl*>(
                                story_->get_store());
                        std::ofstream file_out;
                        file_out.open(file);
                        store_impl->save(file_out);

                        throw RunnerInterrupt("Saved the game to " + file);
                    }
                    else if (token.compare(".restore") == 0)
                    {
                        std::string file;
                        std::getline(ss, file, ' ');

                        const auto* tmp = dynamic_cast<const store::StoreImpl*>(
                            story_->get_store());
                        auto* store_impl = const_cast<store::StoreImpl*>(tmp);

                        std::ifstream file_in;
                        file_in.open(file);

                        if (!file_in.is_open())
                            throw RunnerInterrupt("Invalid path to restore: "
                                                  + file);
                        store_impl->restore(file_in, *story_);

                        return;
                    }
                    else
                        throw RunnerInterrupt("I beg your pardon?");
                }
            }

            const story::Node* node = story_->get_current()->make_choice(n);

            story_->set_current(node);
        }
        catch (const RunnerInterrupt& e)
        {
            std::string tmp = e.what();
            throw;
        }
    }

    std::set<std::string> split_sentence(const std::string& sentence)
    {
        std::string delimiter = " ,;!?’-.:";
        std::set<std::string> words;
        std::string tmp;

        for (char c : sentence)
        {
            if (delimiter.find(c) != std::string::npos)
            {
                if (!tmp.empty())
                {
                    words.emplace(tmp);
                    tmp.clear();
                }
            }
            else
                tmp.push_back(std::tolower(c));
        }
        if (!tmp.empty())
            words.emplace(tmp);

        return words;
    }

    int SmartRunnerImpl::count_synonyms(const std::string& left,
                                        const std::string& right) const
    {
        if (left.empty() && right.empty())
            return 0;

        std::set<std::string> first = split_sentence(left);
        std::set<std::string> second = split_sentence(right);

        int c = 0;
        for (auto i = second.begin(); i != second.end(); ++i)
        {
            auto tmp = synonyms_.find(*i);
            for (auto j = first.begin(); j != first.end(); ++j)
            {
                if (*j == *i
                    || (tmp != synonyms_.end()
                        && std::find(tmp->second.begin(), tmp->second.end(), *j)
                            != tmp->second.end()))
                    c++;
            }
        }

        return c;
    }

    SmartRunnerImpl::SmartRunnerImpl(std::unique_ptr<story::Story> story,
                                     synonyms_type synonyms, std::istream& is,
                                     std::ostream& os)
        : SmartRunner(std::move(story), is, os)
        , synonyms_(std::move(synonyms))
    {}

} // namespace libzork::runner
