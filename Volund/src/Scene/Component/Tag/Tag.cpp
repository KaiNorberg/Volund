#include "PCH/PCH.h"

#include "Tag.h"

namespace Volund
{
	VML Tag::Serialize()
	{
		VML TagVML;

		TagVML.PushBack("Type", VMLEntry("Tag"));

		TagVML.PushBack("String", this->String);

		return TagVML;
	}

	Tag::Tag(std::string String)
	{
		this->String = String;
	}
}