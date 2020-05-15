
#include <Config.h>

#include <StringEditor.h>


int main(void)
{
	std::string config_file_path = "config.dat";

	Config config;
	config.readConfigFile(config_file_path);


	int dimension;
	std::string grid_file_path;
	std::vector<int> element_type_indx;
	std::vector<double> x_direction_info;
	config.getConfigValue("dimension", dimension);
	config.getConfigValue("grid_file_path", grid_file_path);
	config.getConfigValue("element_type_indx", element_type_indx);
	config.getConfigValue("x_direction_info", x_direction_info);

}

