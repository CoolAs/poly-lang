#include "ParseException.h"
#include "ParseSentenceType.h"

void ParseSentenceType::setInt(std::string tag, int value, const ParserIO& io, Language& lang)
{
	throw ParseException(std::string("Invalid int-tag \"") + tag + "\"",io.getInput(),io.getCurPos());
}
void ParseSentenceType::setBool(std::string tag, bool value, const ParserIO& io, Language& lang)
{
	if (tag=="neg")
	{
		lang.Negate = value;
	}
	else if (tag=="question")
	{
		lang.Question = value ? 1 : 0;
	}
	else
		throw ParseException(std::string("Invalid bool-tag \"") + tag + "\"",io.getInput(),io.getCurPos());
}

void ParseSentenceType::setString(std::string tag, std::string value, const ParserIO& io, Language& lang)
{
	throw ParseException(std::string("Invalid string-tag \"") + tag + "\"",io.getInput(),io.getCurPos()-value.length()-tag.length()-3);
}


bool ParseSentenceType::match(std::string name)
{
	if (name == "st")
		return true;
	else if (name == "SentenceType")
		return true;
	return false;
}

void ParseSentenceType::parse(ParserIO& io, Language& lang)
{
	beginParse(io);

	lang.st = parseInt(io);
	
	parseArgs(io,lang);

	endParse(io);
}