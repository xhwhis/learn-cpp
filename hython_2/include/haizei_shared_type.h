#ifndef _HAIZEI_SHARED_TYPE_H
#define _HAIZEI_SHARED_TYPE_H

#include <memory>

namespace haizei {

class ASTree;
class Parameter;
class IValue;
class IntValue;
class FloatValue;
class StringValue;

using SIValue = std::shared_ptr<IValue>;
using SIntValue = std::shared_ptr<IntValue>;
using SFloatValue = std::shared_ptr<FloatValue>;
using SStringValue = std::shared_ptr<StringValue>;
using SParameter = std::shared_ptr<Parameter>;

}

#endif
