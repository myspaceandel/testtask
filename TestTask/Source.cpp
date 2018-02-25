#include<iostream>
#include<string>
#include<vector>
#include "sha256.h"
#include<ctime>
using namespace std;

string current_time() {
	time_t rawtime;
	struct tm * timeinfo;
	char buffer[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(buffer, sizeof(buffer), "%d-%m-%Y %I:%M:%S", timeinfo);
	string str(buffer);
	return str;
}

template <typename T>
ostream& operator<<(std::ostream& os, const vector<T>& pr)
{
	for(vector<Block>::const_iterator _block = pr.begin(); _block != pr.end(); ++_block)
	{
		os << "Block index: " << _block->index << "\n";
		os << "Block date: " << _block->date << "\n";
		os << "Block data: " << _block->Data<< "\n";
		os << "Block hash: " << _block->hash << "\n";
		os << "Previous block hash: " << _block->prev_hash << "\n";
	}
	return os;
}

class Block {
public:
	string Data;
	int index;
	string hash;
	string prev_hash;
	string date;
	Block(int _index, string _Data, string _date) {
		this->index = _index;
		this->Data = _Data;
		this->date = _date;
		this->hash = "";
		this->prev_hash = "";
	}
	string generate_hash(Block *current) {
		string _hash = "";
		_hash += current->Data;
		_hash += current->date;
		_hash += current->prev_hash;
		return sha256(_hash);
	}
	
};
class Blockchain {
private:
	vector<Block> list_bloks;
public:
	void Output() {
		cout << list_bloks;
	}
	void Add_Block(Block current) {	
		if (!list_bloks.empty()) {
			current.prev_hash = list_bloks.back().hash;
		}
		else {
			current.prev_hash = "";
		}
		current.hash = current.generate_hash(&current);
		list_bloks.push_back(current);
	}
};

void main() {
	Blockchain block_chain;
	block_chain.Add_Block(Block(1, "Data1", current_time()));
	block_chain.Add_Block(Block(2, "Data2", current_time()));
	block_chain.Add_Block(Block(3, "Data3", current_time()));
	block_chain.Add_Block(Block(4, "Data4", current_time()));
	block_chain.Add_Block(Block(5, "Data5", current_time()));
	block_chain.Add_Block(Block(6, "Data6", current_time()));

	block_chain.Output();
}