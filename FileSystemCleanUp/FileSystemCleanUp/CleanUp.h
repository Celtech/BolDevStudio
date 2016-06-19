#pragma once
#include "Includes.h"

#define STRTOLOWER(x) transform (x.begin(), x.end(), x.begin(), ::tolower)
#define STRTOUPPER(x) transform (x.begin(), x.end(), x.begin(), ::toupper)

class CleanUp
{
public:
	CleanUp(string desktop, string documents, string pictures, string videos, string music);
	~CleanUp();
	vector<string> getFiles(string folder);

	void PrintFileList();

	int DeterminFolderType();
	void SortFiles();
	void SortFolders();
	void DeleteShortcuts();
	

private:
	string MyDesktop = "";
	string MyDocuments = "";
	string MyPictures = "";
	string MyMusic = "";
	string MyVideos = "";

	string LowerCase(string s);
	string SplitFilename(const string str);
	string makeFolder(const string path, string tag, bool isRoot);

	const string currentDateTime();
	bool dirExists(const char *path);
	void MoveFiles(vector<string> items, string dir, string tag, string caption);

	vector<string> fileWhiteList;
	vector<string> fileList;
	vector<string> fileNameList;

	vector<string> shortcuts	= { ".lnk", ".ink" };

	vector<string> pictures		= { ".ANI", ".BMP", ".CAL", ".FAX", ".GIF", ".IMG", ".JBG", ".JPE", ".JPEG", ".JPG", 
									".MAC", ".PBM", ".PCD", ".PCX", ".PCT", ".PGM", ".PNG", ".PPM", ".PSD", ".RAS", 
									".TGA", ".TIFF", ".WMF", ".AI", ".SVG" };

	vector<string> videos		= { ".3G2", ".3GP", ".ASF", ".AVI", ".FLV", ".M4V", ".MOV", ".MP4", ".MPG", ".RM", ".SRT", ".SWF", ".VOB", ".WMV" };
	vector<string> office		= { ".DOC", ".DOCX", ".LOG", ".MSG", ".ODT", ".PAGES", ".RTF", ".TEX", ".TXT", ".WPD", ".WPS", ".CSV", ".DAT", ".GED",
									".KEY", ".KEYCHAIN", ".PPS", ".PPT", ".PPTX", ".SDF", ".TAR", ".TAX2014", ".TAX2015", ".VCF", ".XML", ".INDD", 
									".PCT", ".PDF", ".XLR", ".XLS", ".XLSX", ".ACCDB", ".JNT" };

	vector<string> programming  = { ".C", ".CLASS", ".CPP", ".CS", ".DTD", ".FLA", ".H", ".JAVA", ".LUA", ".M", ".PL", ".PY", ".SH", ".SLN", ".SWIFT", 
									".VB", ".VCXPROJ", ".XCODEPROJ", ".ASP", ".ASPX", ".CER", ".CFM", ".CSR", ".CSS", ".HTM", ".HTML", ".JS", ".JSP", ".PHP", ".RSS", ".XHTML",
									".DB", ".DBF", ".MDB", ".PDB", ".SQL" };

	vector<string> archive		= { ".7Z", ".CBR", ".DEB", ".GZ", ".PKG", ".RAR", ".RPM", ".SITX", ".TAR.GZ", ".ZIP", ".ZIPX" };

	vector<string> music		= { ".AIF", ".IFF", ".M3U", ".M4A", ".MID", ".MP3", ".MPA", ".WAV", ".WMA" };

	vector<string> misc			= { ".3DM", ".3DS", ".MAX", ".OBJ", ".APK", ".APP", ".BAT", ".CGI", ".COM", ".EXE", ".GADGET", ".JAR", ".PIF", ".WSF", ".DEM", ".GAM", ".NES",
									".ROM", ".SAV", ".DWG", ".DXF", ".GPX", ".KML", ".KMZ", ".CRX", ".PLUGIN", ".FNT", ".FON", ".OTF", ".TTF", ".CAB", ".CPL", ".CUR", ".DESKTHEMEPACK",
									".DLL", ".DMP", ".DRV", ".ICNS", ".ICO", ".LNK", ".SYS", ".CFG", ".INI", ".PRF", ".HQX", ".MIM", ".UUE", ".BIN", ".CUE", ".DMG", ".ISO", ".MDF", ".TOAST",
									".VCD", ".BAK", ".TMP", ".CRDOWNLOAD", ".ICS", ".MSI", ".PART", ".TORRENT", ".JAR"};
};

