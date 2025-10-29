#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

struct freqDict
{
	char data;
	int freq;
	freqDict(char c, int f) : data(c), freq(f) {}
};

struct codeDict
{
	char data;
	string code;
	codeDict(char c, string s) : data(c), code(s) {}
};

struct Node
{
	char data;
	Node* left, * right;
	Node(char c) : data(c), left(nullptr), right(nullptr) {}
};

Node* copyTree(Node* tree);

class HuffmanTree
{
private:
	void deleteTree(Node* node)
	{
		if (node)
		{
			deleteTree(node->left);
			deleteTree(node->right);
			delete node;
		}
	}

public:
	Node* root;
	int weight;

	HuffmanTree() : root(nullptr), weight(0) {}
	~HuffmanTree()
	{
		if (root)
			deleteTree(root);
	}

	HuffmanTree(const HuffmanTree& other) : root(nullptr), weight(other.weight)
	{
		root = copyTree(other.root);
	}

	HuffmanTree& operator=(const HuffmanTree& other)
	{
		if (this != &other)
		{
			deleteTree(root);
			root = copyTree(other.root);
			weight = other.weight;
		}
		return *this;
	}

	string decode(const string& bitString)
	{
		string result;
		Node* current = root;
		for (char bit : bitString)
		{
			if (bit == '0')
			{
				if (!current->left)
				{
					cout << "错误：无效的比特串" << endl;
					return "";
				}
				current = current->left;
			}
			else if (bit == '1')
			{
				if (!current->right)
				{
					cout << "错误：无效的比特串" << endl;
					return "";
				}
				current = current->right;
			}
			else
			{
				cout << "错误：包含非法字符" << endl;
				return "";
			}
			if (!current->left && !current->right)
			{
				result += current->data;
				current = root;
			}
		}
		if (current != root)
		{
			cout << "错误：无效的比特串" << endl;
			return "";
		}
		return result;
	}

	void encode(Node* node, string& path, vector<codeDict>& codeTable)
	{
		if (!node)
			return;

		if (!node->left && !node->right)
		{
			codeTable.push_back(codeDict(node->data, path));
			return;
		}

		path.push_back('0');
		encode(node->left, path, codeTable);
		path.pop_back();

		path.push_back('1');
		encode(node->right, path, codeTable);
		path.pop_back();
	}
};

Node* copyTree(Node* tree)
{
	if (!tree)
		return nullptr;
	Node* newNode = new Node(tree->data);
	newNode->left = copyTree(tree->left);
	newNode->right = copyTree(tree->right);
	return newNode;
}

void mergeTrees(HuffmanTree& tree1, HuffmanTree& tree2, HuffmanTree& mergedTree)
{
	mergedTree.root = new Node('\0');
	mergedTree.root->left = tree1.root;
	mergedTree.root->right = tree2.root;
	mergedTree.weight = tree1.weight + tree2.weight;
	tree1.root = nullptr;
	tree2.root = nullptr;
}

int main()
{
	// Encoding
	string input;
	cout << "请输入要编码的字符串：" << endl;
	getline(cin, input);

	if (input.empty())
	{
		cout << "错误：输入字符串不能为空" << endl;
		return 1;
	}

	vector<freqDict> freqTable;
	for (char c : input)
	{
		auto it = find_if(freqTable.begin(), freqTable.end(),
			[c](const freqDict& fd) { return fd.data == c; });
		if (it != freqTable.end())
			it->freq++;
		else
			freqTable.push_back(freqDict(c, 1));
	}

	vector<HuffmanTree> forest;
	for (const auto& fd : freqTable)
	{
		HuffmanTree tree;
		tree.root = new Node(fd.data);
		tree.weight = fd.freq;
		forest.push_back(tree);
	}

	if (forest.size() == 1)
	{
		Node* r = forest[0].root;
		if (!r->left && !r->right)
		{
			Node* newRoot = new Node('\0');
			newRoot->left = r;
			forest[0].root = newRoot;
		}
	}

	while (forest.size() > 1)
	{
		sort(forest.begin(), forest.end(),
			[](const HuffmanTree& t1, const HuffmanTree& t2)
			{ return t1.weight < t2.weight; });
		HuffmanTree mergedTree;
		mergeTrees(forest[0], forest[1], mergedTree);
		forest.erase(forest.begin());
		forest.erase(forest.begin());
		forest.push_back(mergedTree);
	}

	HuffmanTree& huffmanTree = forest[0];
	vector<codeDict> codeTable;
	string path;
	huffmanTree.encode(huffmanTree.root, path, codeTable);

	string encodedString;
	for (char c : input)
	{
		auto it = find_if(codeTable.begin(), codeTable.end(),
			[c](const codeDict& cd) { return cd.data == c; });
		if (it != codeTable.end())
			encodedString += it->code;
	}

	cout << "编码后的比特串：" << encodedString << endl;
	cout << "编码表：" << endl;
	for (const auto& cd : codeTable)
	{
		cout << cd.data << "-" << cd.code << endl;
	}

	// Decoding
	string bitString;
	cout << "请输入要解码的比特串：" << endl;
	cin >> bitString;

	string decodedString = huffmanTree.decode(bitString);
	if (!decodedString.empty())
	{
		cout << "解码后的字符串：" << decodedString << endl;
	}

	return 0;
}