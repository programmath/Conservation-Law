#pragma once

#include "Header.h"
#include "StringEditor.h"
#include "FileReader.h"
#include "TextEditor.h"


#include <unordered_map>



class Config
{
private:
	std::unordered_map<std::string, std::vector<std::string>> config_data_;	

public:
	Config() {};

	~Config() {};

public:
	void readConfigFile(const std::string& config_file_path);

	template<typename T>
	void getConfigValue(const std::string& config_type, T& t) const;
};


template<typename T>
void Config::getConfigValue(const std::string& config_name, T& value) const
{
	std::string key = config_name;

	StringEditor::toUpperCase(key);
	
	if (config_data_.find(key) == config_data_.end())
		MASTER_ERROR(key + " is not exist in config file", __FILE__, __LINE__);

	if (config_data_.at(key).size() == 0)
		MASTER_ERROR(key + " does not have value", __FILE__, __LINE__);
	
	if constexpr (std::is_fundamental_v<T>)
	{
		for (const std::string& text : config_data_.at(key))
			value = StringEditor::toValue<T>(text);
	}
	else if constexpr (std::is_same_v<T,std::string>)
	{
		for (const std::string& text : config_data_.at(key))
			value = StringEditor::toValue<T>(text);
	}
	else
		value = StringEditor::toValues<T>(config_data_.at(key));
			
	

}