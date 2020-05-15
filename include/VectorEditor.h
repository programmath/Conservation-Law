#pragma once

#include <algorithm> //std::remove

#include <vector>

class VectorEditor
{
public:

	template <typename T>
	static void remove(std::vector<T>& vec, const T& value_to_remove);

};

template <typename T>
void VectorEditor::remove(std::vector<T>& vec, const T& value_to_remove)
{
	vec.erase(std::remove(vec.begin(), vec.end(), value_to_remove), vec.end());
}


