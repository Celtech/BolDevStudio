#pragma once
#include "Includes.h"
#include "FileSystem.h"
#include "CleanUp.h"

FileSystem* fs = new FileSystem();

#define DESKTOP		fs->GetDesktop()
#define MUSIC		fs->GetMusic()
#define PICTURES	fs->GetPictures()
#define VIDEO		fs->GetVideos()
#define DOCUMENTS	fs->GetDocuments()

CleanUp* clean = new CleanUp(DESKTOP, DOCUMENTS, PICTURES, VIDEO, MUSIC);