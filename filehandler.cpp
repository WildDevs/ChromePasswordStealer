/* Copyright (C) 2017 Eray Sönmez, www.ray-works.de
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your option)
 * any later version.

 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License along with this program;
 * if not, see <http://www.gnu.org/licenses/>.
 */
#include "filehandler.h"
#include <experimental/filesystem>
using namespace std;
namespace fs = experimental::filesystem;

FileHandler::FileHandler()
{

}

bool FileHandler::createDir(LPCSTR dir)
{
    return CreateDirectoryA(dir, NULL);
}

bool FileHandler::deleteDir(LPCSTR dir)
{
    return RemoveDirectoryA(dir);
}

bool FileHandler::deleteFile(LPCSTR file)
{
    return DeleteFileA(file);
    //return (remove(file) != 0);
}

bool FileHandler::copyFile(LPCSTR src, LPCSTR dest)
{
    return CopyFileA(src, dest, false);
}

vector<string>* FileHandler::getDirContent(LPCSTR dir)
{
    vector<string>* files = new vector<string>;

    fs::path directory(dir);
    fs::directory_iterator iter(directory), end;

    for(;iter != end; ++iter)
        files->push_back(iter->path().filename().string());

    return files;
}


