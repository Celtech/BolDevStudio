#include "FileSystem.h"

FileSystem::FileSystem()
{
}

FileSystem::~FileSystem()
{
}

string FileSystem::GetDesktop() {
	TCHAR appData[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_DESKTOPDIRECTORY | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, appData)))
		return appData;
	return 0;
}

string FileSystem::GetDocuments()
{
	TCHAR appData[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYDOCUMENTS | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, appData)))
		return appData;
	return 0;
}

string FileSystem::GetPictures()
{
	TCHAR appData[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYPICTURES | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, appData)))
		return appData;
	return 0;
}

string FileSystem::GetVideos()
{
	TCHAR appData[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYVIDEO | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, appData)))
		return appData;
	return 0;
}

string FileSystem::GetMusic()
{
	TCHAR appData[MAX_PATH];
	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_MYMUSIC | CSIDL_FLAG_CREATE, NULL, SHGFP_TYPE_CURRENT, appData)))
		return appData;
	return 0;
}
