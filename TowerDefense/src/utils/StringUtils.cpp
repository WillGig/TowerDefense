#include "pch.h"
#include "StringUtils.h"

std::string Utils::TruncateFloat(float f, int placesAfterDecimal)
{
	static std::stringstream ss;
	ss.str("");
	ss << std::fixed << std::setprecision(placesAfterDecimal) << f;
	return ss.str();
}

int Utils::NumLines(const std::string& s)
{
	return std::count(s.begin(), s.end(), '\n');
}