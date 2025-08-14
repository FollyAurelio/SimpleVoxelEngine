#include "rs.h"

std::string loadFile(const char *filePath)
{
	std::string content;
	std::ifstream file;
	// ensure ifstream objects can throw exceptions:
	file.exceptions (std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		file.open(filePath);
		std::stringstream fileStream;
		// read file’s buffer contents into streams
		fileStream << file.rdbuf();
		// close file handlers
		file.close();
		// convert stream into string
		content = fileStream.str();
	}
	catch(std::ifstream::failure *e)
	{
		std::cout << "ERROR::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		exit(1);
	}
	return content;
}
