#include "parser.h"

#include <boost/regex.hpp>
#include <array>
#include <sstream>

using namespace andromeda;
using namespace andromeda::effect;

void Parser::parse(const std::string& fileContents)
{
	// Strip Multiline comments first :)
	std::string copy(fileContents);

	stripMultiLineComment(copy);

	// Split into Lines
	std::stringstream contents(fileContents);
	std::vector<std::string> lines;
	std::string line;

	while (std::getline(contents, line, '\n'))
	{
		// Strip Whitespace and Single Line comments from the line
		stripWhitespace(line);
		
		if (line.size() == 0)
			continue;
	
		// Strip Single Line Comments from the line
		stripSingleLineComment(line);

		if (! includeFile(line))
			lines.push_back(line);
	}


	// Iterate through every line. Determine what the line is [Uniform, Function, Code]
	
	// TODO:
	// 1. Determine if line is a uniform or function declaration
	//		- Uniform declarations exist on a single line and contain  a ';' character as the last character
	//		- Function declarations exist potentially over multiple lines :(

	
	
	// TODO: Division of Logic
	// Separate all functions, and declarations [uniforms]

	/*
		Declarations:	
		uniform  <type> <var> : ATTRIBUTE;
		<return> <fn>([in|out] <type> <arg> [: ATTRIBUTE] ...) [: INTENT]
		{

		}
	*/


}



void Parser::stripWhitespace(std::string& line)
{
	
	std::vector<char> whitespace = { '\t', ' ', '\n', '\r' };
	std::string whitespaceChars = "\t\n\r ";
	/*
	for (auto ch : line)
	{
		bool validChar = true;
		for (char whCh : whitespace)
		{
			if (ch == whCh)
			{
				validChar = false;
				break;
			}
		}
		if (validChar)
			return false;
	}
	*/
	std::string::iterator firstChar = line.end();

	while (firstChar != line.begin())
	{
		firstChar--;

		if (whitespaceChars.find(*firstChar) != std::string::npos)
			break;
	}

	line.erase(firstChar, line.end());
	
	return;
}

void Parser::stripSingleLineComment(std::string& line)
{
	// Single Line: Contains // somewhere in a line
	if (size_t pos = line.find('//') != std::string::npos)
	{
		line = line.substr(0, pos);
	}
}

void Parser::stripMultiLineComment(std::string& line)
{
	// Multi Line: Contains /* and */ somewhere further along
	if (size_t start = line.find("/*") != std::string::npos)
	{
		if (size_t end = line.find("*/") != std::string::npos)
		{
			line = line.replace(start, end, "");
			stripMultiLineComment(line);
		}
	}
}

bool Parser::includeFile(std::string& line)
{
	boost::regex expr(R"(include(?:path (\S+[/|\\])*(\S+).?(\S*);)");

	if (boost::regex_match(line, expr, boost::match_extra))
	{
		boost::smatch what;
		boost::regex_search(line, what, expr);

		// Parse the File
		
		// Only include functions. Uniforms shouldn't be included?

		return true;
	}

	return false;
}