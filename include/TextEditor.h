#pragma once

#include "DataSet.h"
#include "Header.h"
#include "VectorEditor.h"
#include "StringEditor.h"

#include <vector>
#include <string>

class TextEditor
{

protected:

	class EditingStrategy
	{
	protected:

		EditingStrategy() {};

		~EditingStrategy() {};

	public:

		virtual std::vector<ConfigData> edit(const std::vector<std::string>& config_texts) const = 0;
	};

public:

	TextEditor() {};

	~TextEditor() {};

	static std::string trim(const std::string& text, const std::vector<char>& preserving_characters, const std::string& comment_tag ="");

	static std::vector<std::string> parse(const std::string& text, const std::vector<char>& delimiters);	
	
	static std::vector<ConfigData> edit(EditingStrategy& Editing_startegy, const std::vector<std::string>& config_texts)	{	return Editing_startegy.edit(config_texts);	};

	class ConfigTextEditingStrategy : public EditingStrategy
	{
	public:

		ConfigTextEditingStrategy() {};

		~ConfigTextEditingStrategy() {};

	public:

		std::vector<ConfigData> edit(const std::vector<std::string>& config_texts) const override;

	};

	class GmshNodeTextEditingStrategy : public EditingStrategy
	{
	public:

		GmshNodeTextEditingStrategy() {};

		~GmshNodeTextEditingStrategy() {};

	public:

		//NodeDataSet edit(std::string& text) const override;
	};

};
