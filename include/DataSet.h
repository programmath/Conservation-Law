#pragma once
#include <vector>
#include <string>

class ConfigData
{
public:

	std::string name_;

	std::vector<std::string> values_;
	
	ConfigData() {};

	ConfigData(const std::string& name, const std::vector<std::string>& values) { name_ = name; values_ = values; };

	~ConfigData() {};
};