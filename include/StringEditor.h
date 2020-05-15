#pragma once

#include <algorithm>	//std::transform
#include <cctype>		//std::toupper
#include <iomanip>		//std::setprecision & std::noshowpoint
#include <type_traits>	//std::is_same_v

#include <string>
#include <vector>
#include <sstream>		//std::ostringstream

#include "Header.h"

class StringEditor
{
public:

	static std::string toUpperCase(std::string& text)
	{
		std::transform(text.begin(), text.end(), text.begin(), ::toupper);
		return text;
	}

	template <typename T>
	static void replace(std::string& text, const T& old_value, const T& new_value);

	template<typename T>
	static std::string toString(const T& arg);

	template<typename T>
	static T toValue(const std::string& texts);

	template<typename T>
	static T toValues(const std::vector<std::string>& texts);
};

template<typename T>
void StringEditor::replace(std::string& text, const T& old_value, const T& new_value)
{
	if (old_value == new_value) return;

	std::string old_string = StringEditor::toString(old_value);
	std::string new_string = StringEditor::toString(new_value);

	size_t num_replace = old_string.size();
	while (text.find(old_string) != std::string::npos)
	{
		size_t position = text.find(old_string);

		text.replace(text.find(old_string), num_replace, new_string);
	}
}

template<typename T>
std::string StringEditor::toString(const T& arg)
{
	std::ostringstream out;
	out << std::setprecision(16) << std::noshowpoint << arg;
	return out.str();
}


template<typename T>
T StringEditor::toValue(const std::string& text)
{
	T value;

	if constexpr	  (std::is_same_v<T, int>)							value = std::stoi(text);
	else if constexpr (std::is_same_v<T, int*>)							*value = std::stoi(text);
	else if constexpr (std::is_same_v<T, double>)						value = std::stod(text);
	else if constexpr (std::is_same_v<T, double*>)						*value = std::stod(text);
	else if constexpr (std::is_same_v<T, std::string>)					value = text;
	else
		MASTER_ERROR(StringEditor::toString(typeid(T).name()) + "type is not supported", __FILE__, __LINE__);

	return value;
}

template<typename T>
T StringEditor::toValues(const std::vector<std::string>& texts)
{
	size_t num_value = texts.size();
	
	T values;
	values.reserve(num_value);
	
	if constexpr (std::is_same_v < T, std::vector<int>>)
	{
		for (const std::string& text : texts)
			values.emplace_back(std::stoi(text));
	}
	else if constexpr (std::is_same_v < T, std::vector<double>>)
	{
		for (const std::string& text : texts)
			values.emplace_back(std::stod(text));
	}
	else if constexpr (std::is_same_v < T, std::vector<std::string>>)
	{
		for (const std::string& text : texts)
			values.emplace_back(text);
	}
	else
		MASTER_ERROR(StringEditor::toString(typeid(T).name()) + "type is not supported", __FILE__, __LINE__);

	return values;
}
