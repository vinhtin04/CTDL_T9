#include <iostream>
#include <string>
#include <ctime>
using namespace std;

struct FileNode {
    string fileName;
    long long fileSize;       
    time_t createdTime;  
    FileNode* next;

    FileNode(string name, long size, time_t time)
        : fileName(name), fileSize(size), createdTime(time), next(0) {}
};

void insertFile(FileNode*& head, const string& name, long long size, time_t time) {
    FileNode* newFile = new FileNode(name, size, time);
    if (!head || head->createdTime > time) { 
        newFile->next = head;
        head = newFile;
    } else {
        FileNode* current = head;
        while (current->next && current->next->createdTime <= time) {
            current = current->next;
        }
        newFile->next = current->next;
        current->next = newFile;
    }
}

long calculateTotalSize(FileNode* head) {
    long long totalSize = 0;
    FileNode* current = head;
    while (current) {
        totalSize += current->fileSize;
        current = current->next;
    }
    return totalSize;
}

void removeSmallFiles(FileNode*& head, long maxSize) {
    while (calculateTotalSize(head) > maxSize && head) {
        FileNode* smallest = head;
        FileNode* current = head->next;
        FileNode* prev = 0;
        FileNode* prevSmallest = 0;

        while (current) {
            if (current->fileSize < smallest->fileSize) {
                smallest = current;
                prevSmallest = prev;
            }
            prev = current;
            current = current->next;
        }

        if (prevSmallest) {
            prevSmallest->next = smallest->next;
        } else {
            head = head->next;
        }
        delete smallest;
    }
}

void printFiles(FileNode* head) {
    FileNode* current = head;
    while (current) {
        cout << "File: " << current->fileName
             << ", Size: " << current->fileSize
             << " bytes, Created Time: " << ctime(&current->createdTime);
        current = current->next;
    }
}

void freeList(FileNode* head) {
    while (head) {
        FileNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void nhap(FileNode*& fileList)
{
	string c;
	while (1)
	{
		string s;
		long long size;
		cout << "Ten file: "; 
		cin.ignore();
		getline(cin,s);
		cout << "Size: "; cin >> size;
	    insertFile(fileList, s+".txt", size, time(0));
		cout << "Tiep tuc(y/n): ";
		cin >> c;
		if (c=="n") break;
	}
}

int main() {
	string c="y";
	while (1)
	{
		FileNode* fileList = 0;
		if (c=="y") nhap(fileList);
		
		cout << "Danh sach file trong thu muc D:\\Document:\n";
		printFiles(fileList);
		
		long long totalSize = calculateTotalSize(fileList);
		cout << "\nTong kich thuoc cua file: " << totalSize << " bytes\n";
		
		long long usbSize = 32 * 1024 * 1024 * 1024; 
		removeSmallFiles(fileList, usbSize);
		
		cout << "\nDanh sach file bi loai bo de phu hop voi USB:\n";
		printFiles(fileList);
		
		freeList(fileList);
		cout << "Nhap file(y/n): "; cin >> c;
	}
    return 0;
}

