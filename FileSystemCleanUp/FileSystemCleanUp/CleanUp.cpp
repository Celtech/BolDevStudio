#include "CleanUp.h"

CleanUp::CleanUp(string desktop, string documents, string pictures, string videos, string music)
{
	MyDesktop = desktop;
	MyDocuments = documents;
	MyPictures = pictures;
	MyMusic = music;
	MyVideos = videos;

	fileWhiteList.push_back("desktop.ini");
	fileList = getFiles(desktop);
}


CleanUp::~CleanUp()
{
}

string CleanUp::SplitFilename(const string str)
{
	std::size_t found = str.find_last_of("/\\");
	return str.substr(found + 1);
}

bool CleanUp::dirExists(const char *path)
{
	struct stat info;

	if (stat(path, &info) != 0)
		return 0;
	else if (info.st_mode & S_IFDIR)
		return 1;
	else
		return 0;
}

const string CleanUp::currentDateTime() {
	time_t     now = time(0);
	struct tm  tstruct;
	char       buf[80];
	tstruct = *localtime(&now);
	strftime(buf, sizeof(buf), "%Y-%m-%d ", &tstruct);

	return buf;
}

string CleanUp::makeFolder(const string path, string tag, bool isRoot)
{
	string time;
	if(!isRoot)
		time = path + "/CleanUp/" + currentDateTime() + tag;
	else
		time = path + "/" + tag;

	const char* finalFolder = time.c_str();
	if (!dirExists(finalFolder))
		mkdir(finalFolder);

	return finalFolder;
}

vector<string> CleanUp::getFiles(string folder)
{
	vector<string> names;
	char search_path[200];
	sprintf(search_path, "%s/*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(search_path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(folder + "/" + fd.cFileName);
			}
		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}
	return names;
}

void CleanUp::PrintFileList() {
	for (int i = 0; i < fileList.size(); i++) {
		cout << "  " << fileList[i] << endl;
	}
}

int CleanUp::DeterminFolderType()
{
	return 0;
}

void CleanUp::SortFiles()
{
	DeleteShortcuts();

	MoveFiles(pictures, MyPictures, "Pictures", "Cleaning Photo Files:");
	MoveFiles(programming, MyDocuments, "Developer", "Cleaning Developer Files:");
	MoveFiles(archive, MyDocuments, "Archive", "Cleaning Archive Files:");
	MoveFiles(office, MyDocuments, "Office", "Cleaning Office Files:");
	MoveFiles(music, MyMusic, "Music", "Cleaning Music Files:");
	MoveFiles(videos, MyVideos, "Video", "Cleaning Video Files:");
	MoveFiles(misc, MyDocuments, "Misc", "Cleaning Misc. Files:");
}

void CleanUp::SortFolders()
{
	
}

string CleanUp::LowerCase(string s)
{
	int dif = 'a' - 'A';
	for (int i = 0; i<s.length(); i++)
	{
		if ((s[i] >= 'A') && (s[i] <= 'Z'))
			s[i] += dif;
	}
	return s;
}

void CleanUp::DeleteShortcuts()
{
	int count = 0;
	cout << "Cleaning Shortcuts:" << endl;
	for (int i = 0; i < fileList.size(); i++) {
		count++;
		for (int j = 0; j < shortcuts.size(); j++) {
			if (strstr(fileList[i].c_str(), shortcuts[j].c_str())) {
				cout << " -Deleting " << fileList[i] << endl;
				remove(fileList[i].c_str());
			}
		}
	}
	if (count == 0)
		cout << "  No Files Found!" << endl;
}


void CleanUp::MoveFiles(vector<string> items, string dir, string tag, string caption)
{
	int count = 0;
	cout << caption << endl;
	makeFolder(dir, "CleanUp", true);
	for (int i = 0; i < fileList.size(); i++) {
		count++;
		for (int j = 0; j < items.size(); j++) {
			if (strstr(LowerCase(fileList[i]).c_str(), LowerCase(items[j]).c_str())) {
				string movePath = makeFolder(dir, tag, false) + "/" + SplitFilename(fileList[i]);
				cout << " ~Moving " << fileList[i] << " to " << movePath << endl;
				rename(fileList[i].c_str(), movePath.c_str());
			}
		}
	}
	if (count == 0)
		cout << "  No Files Found!" << endl;
}