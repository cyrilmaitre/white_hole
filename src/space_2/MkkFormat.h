#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <map>

#define DAT_HEADER_ID "MKKSDAT"
#define DAT_HEADER_ID_L 7			// length of header ID
#define DAT_HEADER_VERSION "1.0"
#define DAT_HEADER_VERSION_L 3		// length of header version
#define DAT_MAX_PATH_LENGTH 300

//Header del file dat
struct sDATHeader
{
	char uniqueID[DAT_HEADER_ID_L]; /// Unique ID used to know if this file is a DAT File from this class
	char version[DAT_HEADER_VERSION_L]; /// Version of the DAT file format
	unsigned int nb_files; /// Number of files in the DAT file
};
//Informazioni sul file salvato
struct sFileEntry
{
	char name[DAT_MAX_PATH_LENGTH]; /// Name of the data file
	long size; /// Size of the data file
	long offset; /// Offset, in the DAT file where the file is
};
//Dato che dobbiamo salvare
class cDAT
{ 
	private :
		std::string m_datfile; /// name of the DAT file
		sDATHeader m_header; /// file header
		std::vector<sFileEntry> m_entries; /// vector of files entries
		std::map<std::string, char*> m_buffers;
	public :
		cDAT (void);
		~cDAT (void);
		bool Create (std::vector<std::string> files, std::string destination, bool withoutDirname);
		bool Read (std::string source);
		char* GetFile (std::string filename);
		long int GetFileSize (std::string filename);
		std::vector<sFileEntry>* getEntries();
};