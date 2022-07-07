#ifndef FILES_H
#define FILES_H

#include <fstream>
#include <iostream>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __linux__
#include <libgen.h> //For dirname()
#include <unistd.h> //For readlink()
#include <linux/limits.h> //For MAX_PATH
#endif

/**
 * Return a file contained in the root folder of game
 */ 
void getLocalFile(std::string pathToFile, std::ios_base::openmode __mode, std::fstream** file);

/**
 * Return a file contained in the resource folder.
 * Notice that a file inside resource folder cannot be created programmaticaly
 * So use it only to get a resource file (texture, lang file, sound, recipe json ecc...)
 */ 
void getInternalFile(std::string pathToFile, std::ios_base::openmode _mode, std::fstream** file);

/**
 * Return the path where game is installed
 */ 
std::string* getRootPath();

/**
 * Read INTERNAL file and store chars read inside returned string.
 * A NULL value can be returned if file could not be opened or could not read whole (in this case, 
 * it will print the chars read 'till error occurred)
 */ 
std::string* readFile(std::string pathToFile);
std::string* readFile(std::fstream* file);

/**
 * Return the given path inside the resource folder
 */ 
std::string* getInternalPath(std::string path);

/**
 * Return the given path inside the root folder
 */ 
std::string* getLocalFile(std::string path);

#endif