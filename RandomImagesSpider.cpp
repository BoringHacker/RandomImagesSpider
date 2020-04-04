#include <windows.h>
#include <string.h>
#include <string>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <io.h>

const std::string URL_TABLE[] = {
	"https://api.dujin.org/pic/",
	"https://api.ixiaowai.cn/mcapi/mcapi.php",
	"https://api.ixiaowai.cn/api/api.php",
	"http://img.xjh.me/random_img.php?tctype=acg&return=302",
	"http://img.xjh.me/random_img.php?type=bg&ctype=acg&return=302",
	"http://api.mtyqx.cn/tapi/random.php",
	"http://www.dmoe.cc/random.php",
	"https://img.paulzzh.tech/touhou/random"
};

void URLImageDownloadToFile(std::string url, int identity) {
	std::string command;
	command += "certutil -urlcache -split -f ";
	command += url;
	command += " \"";
	command += std::to_string(identity); 
	command += ".png\"";
	std::cout << command << std::endl;
	system(command.c_str());
}

int GetImageFileSizeToCheckDelete(std::string filename) {
	FILE *fp = fopen(filename.c_str(), "r");
	if (!fp) return -1;
	fseek(fp, 0L, SEEK_END);
	int filesize = ftell(fp);
	fclose(fp);
	return filesize / 1024;
}

int main() {
	srand(time(0));
	int beginID, imagesNumber;
	puts("Input beginID and imagesNumber:");
	std::cin >> beginID >> imagesNumber;
	for (int i = beginID; i <= beginID + imagesNumber; ++i) {
		URLImageDownloadToFile(URL_TABLE[rand() % 8], i);
		std::string filename = std::to_string(i);
		filename += ".png";
		if (GetImageFileSizeToCheckDelete(filename) <= 50) {
			std::string command = "del ";
			command += filename;
			system(command.c_str());
			--i;
			puts("log:Download failed,retried");
		}
	}
}
