#include "Main.h"

int main() {
	cout << "Building Directory Path's:" << endl;
	cout << "  " << DESKTOP << endl;
	cout << "  " << DOCUMENTS << endl;
	cout << "  " << PICTURES << endl;
	cout << "  " << VIDEO << endl;
	cout << "  " << MUSIC << endl << endl;

	cout << "Building File List:" << endl;
	clean->PrintFileList();

	cout << endl << endl << "Starting Cleanup..." << endl << endl << endl;
	clean->SortFiles();
	clean->SortFolders();
}