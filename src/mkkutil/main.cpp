#include <iostream>
#include <sstream>
#include "../space_2/MkkFormat.h"
#include "../space_2/Dirent.h"
using namespace std;

// -- prototypes
void displayHelp();
bool directoryExists( const char* pzPath );
bool createDatFile(std::string datfilename);
void list_dir (std::string dir_name, bool recursive);
void test();

// -- global variable (moche)
std::vector<std::string> FileList;


// -- MAIN
int main(int argc, char** argv) {

	//test();

	int ret = 0;
	if ( argc < 2 ) {
		displayHelp();
	}
	else {
		if(argv[1] == std::string("create")) {
			if(argc == 4) {
				if(directoryExists(argv[3])) {
					list_dir(argv[3], false);
					createDatFile(argv[2]);
				}
				else
					cout << "Invalid directory\n";
			}
			else
				displayHelp();
		}
		else if(argv[1] == std::string("read")) {
			if(argc == 3) {
				cDAT Dat;
				Dat.Read(argv[2]);
				std::vector<sFileEntry>* entries = Dat.getEntries();
				for (unsigned int i=0;i<entries->size();i++)
				{
					char* buffer;
					buffer = Dat.GetFile((*entries)[i].name );
					cout << "\t-> "<< (*entries)[i].name << endl;
				}
			}
			else
				displayHelp();
		}
		else {
			cout << "Invalid argument '"<< argv[1] << "'\n";
		}
	}
return ret;
} 



// -- fonctions
bool directoryExists( const char* pzPath )
{
    if ( pzPath == NULL) return false;

    DIR *pDir;
    bool bExists = false;

    pDir = opendir (pzPath);

    if (pDir != NULL)
    {
        bExists = true;    
        (void) closedir (pDir);
    }

    return bExists;
}

bool createDatFile(std::string datfilename)
{
	cDAT WriteFile;
	if (WriteFile.Create(FileList, datfilename.data(), true)) {
		cout << "Created " << datfilename << " with " << FileList.size() << " file(s) inside !" << endl;
		return true;
	}

	return false;
}


void displayHelp() {
	cout << "\n";
	cout<<"usage:"<< "\n";
		cout << "\t mkkutil.exe create <new .dat file> <target directory>\n";
		cout << "\t mkkutil.exe read <.dat file>\n";
	cout << "\n";
}

// http://www.lemoda.net/c/recursive-directory/
void list_dir (std::string dir_name, bool recursive)
{
    DIR * d;
    /* Open the directory specified by "dir_name". */

	d = opendir (dir_name.data());

    /* Check it was opened. */
    if (! d) {
        fprintf (stderr, "Cannot open directory '%s': %s\n", dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
    while (1) {
        struct dirent * entry;
        string d_name;

        /* "Readdir" gets subsequent entries from "d". */
        entry = readdir (d);
        if (! entry) {
            /* There are no more entries in this directory, so break
               out of the while loop. */
            break;
        }
        d_name = entry->d_name;
		std::string path = dir_name+"/"+d_name;

		if((d_name.compare(".") != 0 && d_name.compare("..") != 0) && entry->d_type != DT_DIR)
		{
			//cout << "-> " << path << endl;
			FileList.push_back(path);
		}

        if (entry->d_type & DT_DIR) {
            /* Check that the directory is not "d" or d's parent. */
			if(d_name.compare(".") != 0 && d_name.compare("..") != 0) {
                if (path.length() >= DAT_MAX_PATH_LENGTH) {
                    fprintf (stderr, "Path length has got too long.\n");
                    exit (EXIT_FAILURE);
                }
				cout << "PATH= " << path << endl ;
                /* Recursively call "list_dir" with the new path. */
                list_dir (path, true);
            }
        }
    }
    /* After going through all the entries, close the directory. */
    if (closedir (d)) {
        fprintf (stderr, "Could not close '%s': %s\n",
                 dir_name, strerror (errno));
        exit (EXIT_FAILURE);
    }
}

void test()
{

}