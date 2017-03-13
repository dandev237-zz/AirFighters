#include "Command.h"

Command::Command()
	: category(static_cast<unsigned int>(Category::Type::None)), action()
{
}
