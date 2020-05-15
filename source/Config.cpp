
#include <Config.h>

void Config::readConfigFile(const std::string& config_file_path)
{
	FileReader::ConfigFileReadingStrategy reading_strategy;
	std::vector<std::string> config_texts = FileReader::read(reading_strategy, config_file_path);	

	TextEditor::ConfigTextEditingStrategy editing_strategy;
	std::vector<ConfigData> config_data_set = TextEditor::edit(editing_strategy, config_texts);
	
	for (const ConfigData& data : config_data_set)
		config_data_[data.name_] = data.values_;
	
	MASTER_MESSAGE("Config data is initialized");
}