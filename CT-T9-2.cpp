
#include <iostream>
#include <string>
using namespace std;

struct WordNode {
    string word;         
    int count;     
	int check;      
    WordNode* next;      

    WordNode(string word) : word(word), count(1), check(0), next(0) {}
};

void insertWord(WordNode*& head, const string& word) {
    WordNode* current = head;
    WordNode* prev = 0;
	int k = 0;
    while (current != 0) {
        if (current->word == word) {
            current->count++;
            if (current->count >= 2) k = 1;
        }
        prev = current;
        current = current->next;
    }


    WordNode* newWord = new WordNode(word);
    if (prev == 0) {
        head = newWord;  
    } else {
        prev->next = newWord;
        if (k==1) 
		{
			prev->next->check = 1;
			k=0;
		}
    }
}

WordNode* timtumax(WordNode* head) {
    WordNode* mostFrequent = head;
    WordNode* current = head;

    while (current != 0) {
        if (current->count > mostFrequent->count) {
            mostFrequent = current;
        }
        current = current->next;
    }

    return mostFrequent;
}

void xoa(WordNode*& head) {
    WordNode* current = head;
    WordNode* prev = 0;
    while (current != 0 && current->next != 0) {
        if (current->word == current->next->word) {
			WordNode* current1 = head;
        	while (current1 != 0) {
		        if (current1->word == current->word) 
				{
					current1->count--;
					break; 
				}
				current1 = current1->next;
		    }
            WordNode* tulay = current->next;
            current->next = tulay->next;
            delete tulay;
        }
        prev = current;
        current = current->next;
    }
}

int dem(WordNode* head) {
    int totalCount = 0;
    WordNode* current = head;

    while (current != 0) {
        totalCount += current->count;
        current = current->next;
    }

    return totalCount;
}

void printWords(WordNode* head) {
    WordNode* current = head;
    while (current != 0 ) {
    	if (current->check == 0)
        cout << "Tu: " << current->word << ", So lan xuat hien: " << current->count << endl;
        current = current->next;
    }
}

void freeList(WordNode* head) {
    while (head != 0) {
        WordNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void display(WordNode* head)
{
    WordNode* current = head;
    while (current != 0) {
        cout << current->word << " " ;
        current = current->next;
    }
}

int main() {
    WordNode* wordList = 0;
    string cau;

    cout << "Nhap cau tieng viet: ";
    getline(cin, cau);

    size_t pos = 0;
    while ((pos = cau.find(' ')) != string::npos) {
        string word = cau.substr(0, pos);
        insertWord(wordList, word);
        cau.erase(0, pos + 1);
    }
    insertWord(wordList, cau); 

    cout << "Danh sach cac tu va so lan xuat hien:" << endl;
    printWords(wordList);

    WordNode* tumax = timtumax(wordList);
    if (tumax != 0) {
        cout << "\nTu xuat hien nhieu nhat: " << tumax->word
             << ", so lan xuat hien: " << tumax->count << endl;
    }

    xoa(wordList);
    cout << "\nDanh sách tu sau khi loai bo cac tu lay:" << endl;
    printWords(wordList);

    int totalWords = dem(wordList);
	display(wordList);
    freeList(wordList);

    return 0;
}

