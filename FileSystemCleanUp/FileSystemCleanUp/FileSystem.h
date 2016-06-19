#pragma once
#include "Includes.h"

class FileSystem
{
public:
	FileSystem();
	~FileSystem();
	string GetDesktop();
	string GetDocuments();
	string GetPictures();
	string GetVideos();
	string GetMusic();
};

