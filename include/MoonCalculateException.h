#include <stdexcept>
class MoonCalculateException : public std::runtime_error{
    public:
        MoonCalculateException(const std::string& expText) : runtime_error(expText){}

};