#include <FileReader.h>

std::streampos FileReader::findPosition(const std::string& file_path, const std::string& target_string)
{
	std::streampos position;

	std::ifstream readfile(file_path);
	if (!readfile.is_open())
		MASTER_ERROR("Fail to read " + file_path, __FILE__, __LINE__);

	std::string str;
	while (std::getline(readfile, str))
	{
		if (str.find(target_string, 0) != std::string::npos)
			return position;

		position = readfile.tellg();
	}

	return -1;
}



std::vector<std::string> FileReader::ConfigFileReadingStrategy::read(const std::string& file_path, const std::streampos& start_position, const int start_line, const int end_line) const
{
	std::ifstream readfile(file_path);
	if (!readfile.is_open())
		MASTER_ERROR("Fail to read " + file_path, __FILE__, __LINE__);

	readfile.seekg(start_position);
	
	std::string tmp_text;
	if (start_line > 0)
	{
		for (int iline = 0; iline < start_line; ++iline)
			std::getline(readfile, tmp_text);
	}

	int num_line = end_line - start_line;
	if (num_line < 0)	
		MASTER_ERROR("reading start line (" + StringEditor::toString(start_line) + ") is smaller than end_line (" + StringEditor::toString(end_line) + ")", __FILE__, __LINE__);

	std::vector<std::string> words;	
	words.reserve(num_line);

	int line_count = 0;	
	while (std::getline(readfile, tmp_text))
	{
		words.emplace_back(tmp_text);
		++line_count;
		if (line_count == num_line)
			break;
	}

	return words;
}