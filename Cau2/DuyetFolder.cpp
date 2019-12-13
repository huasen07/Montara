#include "DuyetFolder.h"

vector<string> DuyetFolder(const char * parent)
{
	WIN32_FIND_DATAA fd;
	vector<string> list;
	char folder[MAX_PATH];
	sprintf(folder, "%s\\*.*", parent);
	HANDLE hFind = FindFirstFileA(folder, &fd);
	if (hFind != INVALID_HANDLE_VALUE)
	{
		do {
			if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(fd.cFileName, ".") && strcmp(fd.cFileName, ".."))
				{
					char child[MAX_PATH];
					sprintf(child, "%s\\%s", parent, fd.cFileName);
					DuyetFolder(child);
				}
			}
			else
			{
				char buff[1000];
				int n;
				sprintf(buff, "%s\\%s", parent, fd.cFileName);
				printf("%s\n", buff);
				list.push_back(fd.cFileName);
			}
		} while (FindNextFileA(hFind, &fd));
		FindClose(hFind);
	}
	return list;
}
