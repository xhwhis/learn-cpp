#include <haizei_util.h>
#include <string>
#include <stdexcept>

namespace haizei {

std::string ConverStringToCString(const std::string &tmp) {
    std::string ret = "";
    int i = 0;
    while (tmp[i]) {
        switch (tmp[i]) {
            case '\\': {
                i++;
                switch (tmp[i]) {
                    case 'n': ret += '\n'; break;
                    case 't': ret += '\t'; break;
                    case 'r': ret += '\r'; break;
                    case 'a': ret += '\a'; break;
                    case 'b': ret += '\b'; break;
                    case 'f': ret += '\f'; break;
                    case 'v': ret += '\v'; break;
                    case '\\': ret += '\\'; break;
                    case '\'': ret += '\\'; break;
                    case '\"': ret += '\"'; break;
                    default: throw std::runtime_error(std::string("string format is wrong:") + tmp);
                }
            } break;
            default: ret += tmp[i]; break;
        }
    }
    return ret;
}

}
