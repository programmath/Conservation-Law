
#include <TextEditor.h>

std::vector<ConfigData> TextEditor::ConfigTextEditingStrategy::edit(const std::vector<std::string>& config_texts) const
{
	std::size_t num_texts = config_texts.size();

	std::vector<ConfigData> config_data_set;
	config_data_set.reserve(num_texts);

	const std::vector<char> preserving_character = { '=',',' };
	const std::string comment_tag = "//";
	const std::vector<char> delimiters = preserving_character;
	
	
	for (const std::string& config_text : config_texts)
	{
		const std::string trimmed_text = trim(config_text, preserving_character, comment_tag);
				
		std::vector<std::string> parsed_text = parse(trimmed_text, delimiters);		
		
		if (parsed_text.empty())	continue;

		ConfigData config_data;

		config_data.name_ = StringEditor::toUpperCase(parsed_text[0]);

		parsed_text.erase(parsed_text.begin());
        VectorEditor::remove(parsed_text, std::string(""));

		config_data.values_ = parsed_text;

		config_data_set.emplace_back(config_data);
	}

	

	return config_data_set;
}


std::string TextEditor::trim(const std::string& text, const std::vector<char>& preserving_characters, const std::string& comment_tag)
{
	if (text.empty())	return std::string();

	std::vector<char> trim_characters = { ' ','\t',',','=','\n','\r' };

	for (const char& preserving_character : preserving_characters)
		VectorEditor::remove(trim_characters, preserving_character);

	std::string trimmed_text = text;
	
	for (const char& character : trim_characters)
		while (trimmed_text.find(character) != std::string::npos)
			trimmed_text.erase(trimmed_text.find(character), 1);

	if (trimmed_text.find(comment_tag) != std::string::npos)
		trimmed_text.erase(trimmed_text.find(comment_tag), std::string::npos);

	return trimmed_text;
}


std::vector<std::string> TextEditor::parse(const std::string& text, const std::vector<char>& delimiters)
{
	if (text.empty())	return std::vector<std::string>();

	std::string text_object = text;

	char reference_delimiter = delimiters[0];		
	for (const char& other_delimiter : delimiters)
	{
		if (other_delimiter != reference_delimiter)
			StringEditor::replace(text_object, other_delimiter, reference_delimiter);
	}

	text_object.push_back(reference_delimiter);

	std::vector<std::string> parsed_texts;

	char* collector = &text_object[0];
	char* modifier;
	while (text_object.find(reference_delimiter) != std::string::npos)
	{
		
		modifier = &text_object[0] + text_object.find(reference_delimiter);
		
		*modifier = '\0';

		parsed_texts.emplace_back(collector);

		collector = modifier + 1;
	}	

	return parsed_texts;
}




