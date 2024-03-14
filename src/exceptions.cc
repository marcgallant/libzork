#include "exceptions.hh"

namespace libzork
{

    NotImplemented::NotImplemented(const std::source_location location)
        : std::runtime_error(std::string{ "Unimplemented function: " }
                             + location.function_name() + " in "
                             + location.file_name() + ":"
                             + std::to_string(location.line()))
    {}

    InvalidVariable::InvalidVariable(const std::string& name,
                                     const std::source_location location)
        : std::runtime_error(std::string{ "invalid variable " + name + ": " }
                             + location.function_name() + " in "
                             + location.file_name() + ":"
                             + std::to_string(location.line()))
    {}

    InvalidComparison::InvalidComparison(const std::string& name,
                                         const std::source_location location)
        : std::runtime_error(std::string{ "invalid condition " + name + ": " }
                             + location.function_name() + " in "
                             + location.file_name() + ":"
                             + std::to_string(location.line()))
    {}

} // namespace libzork
