#include "../Headers/DragonException.h"
#include <sstream>

DragonException::DragonException(int line, const char* file) noexcept
    :
    line(line),
    file(file)
{
}

const char* DragonException::what() const noexcept
{
    std::ostringstream oss;
    oss << GetType() << std::endl << GetOrginString();
    whatBuffer = oss.str();
    return whatBuffer.c_str();
}

const char* DragonException::GetType() const noexcept
{
    return "Dragon EXCEPTION";
}

int DragonException::GetLine() const noexcept
{
    return line;
}

const std::string& DragonException::GetFile() const noexcept
{
    return file;
}

std::string DragonException::GetOrginString() const noexcept
{
    std::ostringstream oss;
    oss << "[File] " << file << std::endl << "[line] " << line;

    return oss.str();
}
