#pragma once

#include <vector>
#include <string>
#include <fstream>

#include "Header.h"
#include "StringEditor.h"

class FileReader
{

protected:

	class ReadingStrategy
	{
	protected:
		
		ReadingStrategy() {};

		~ReadingStrategy() {};

		friend FileReader;

	protected:

		virtual std::vector<std::string> read(const std::string& file_path, const std::streampos& start_position, const int start_line, const int end_line) const = 0;

	};

	FileReader() {};

	~FileReader() {};

public:

	static std::streampos findPosition(const std::string& file_path, const std::string& target_string);

	static std::vector<std::string> read(const ReadingStrategy& reading_startegy, const std::string& file_path, const std::streampos& start_position = 0, const int start_line = -1, const int end_line = -1)
	{
		return reading_startegy.read(file_path, start_position, start_line, end_line);
	};


	class ConfigFileReadingStrategy : public ReadingStrategy
	{
	public:

		ConfigFileReadingStrategy() {};

		~ConfigFileReadingStrategy() {};

	private:
		std::vector<std::string> read(const std::string& file_path, const std::streampos& start_position, const int start_line, const int end_line) const override;
	};

	class GmshFileReadingStrategy : public ReadingStrategy
	{
	public:

		GmshFileReadingStrategy() {};

		~GmshFileReadingStrategy() {};

	private:
		//std::vector<std::string> read(const std::string& file_path, const std::streampos& start_location, const int start_line, const int end_line) const override;

	};

};



