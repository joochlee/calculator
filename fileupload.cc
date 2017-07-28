#include <iostream>


/*
 * 2017/7/28 -jclee
 */

int UploadFile(String filename)
{
	int fd, read;
	char buf[100];

	if ((fd = Open(filename))<0) {
		cout << "file open error" << endl;
		return -1;
	}

	while (read != EOF) {
		read = Read(fd, buf);
		if (read < 0) continue;
		cout << buf << endl;
	}
	
	return 1;
}
