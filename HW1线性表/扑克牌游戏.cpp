#include<iostream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;

static string rankToString(int rank) {
    if (rank == 1) return "A";
    if (rank == 11) return "J";
    if (rank == 12) return "Q";
    if (rank == 13) return "K";
    return to_string(rank);
}

static int stringToRank(const string& rankStr) {
    if (rankStr == "A") return 1;
    if (rankStr == "J") return 11;
    if (rankStr == "Q") return 12;
    if (rankStr == "K") return 13;
    return stoi(rankStr);
}

struct Poker
{
    string suit;
    int rank;

    Poker(string s = "", int r = 0) : suit(s), rank(r) {}
};

struct Node
{
    Poker data;
    Node* next;

    Node(Poker p = Poker(), Node* n = nullptr) : data(p), next(n) {}
};

class LinkList
{
public:
    Node* head;

    LinkList() : head(new Node()) {}
    ~LinkList()
    {
        for (Node* p = head; p != nullptr;)
        {
            Node* q = p->next;
            delete p;
            p = q;
        }
    }

    void append(Poker p) const
    {
        Node* newNode = new Node(p);
        Node* ptr = head;

        while (ptr->next != nullptr)
            ptr = ptr->next;

        ptr->next = newNode;
    }

    void pop()
    {
        if (head->next == nullptr)
        {
            cout << "NULL" << endl;
            return;
        }

        Node* ptr = head->next;
        cout << ptr->data.suit << " " << rankToString(ptr->data.rank) << endl;

        head->next = ptr->next;
        delete ptr;
    }

    void revert()
    {
        if (head->next == nullptr || head->next->next == nullptr)
            return;

        Node* prev = nullptr;
        Node* curr = head->next;
        Node* next = nullptr;

        while (curr != nullptr)
        {
            next = curr->next;
            curr->next = prev;
            prev = curr;
            curr = next;
        }

        head->next = prev;
    }

    void extract(const string& suit)
    {
        Node* ptr = head;
        vector<Node*> extracted;

        while (ptr->next != nullptr)
        {
            if (ptr->next->data.suit == suit)
            {
                extracted.push_back(ptr->next);
                ptr->next = ptr->next->next;
            }
            else
            {
                ptr = ptr->next;
            }
        }

        sort(extracted.begin(), extracted.end(), [](Node* a, Node* b) {
            return a->data.rank > b->data.rank;
            });

        for (int i = 0; i < extracted.size(); i++)
        {
            extracted[i]->next = head->next;
            head->next = extracted[i];
        }
    }

    void print() const
    {
        if (head->next == nullptr)
        {
            cout << "NULL" << endl;
            return;
        }

        Node* ptr = head->next;
        while (ptr != nullptr)
        {
            cout << ptr->data.suit << " " << rankToString(ptr->data.rank) << endl;
            ptr = ptr->next;
        }
    }
};

int main()
{
    int n;
    cin >> n;
    LinkList list;

    string cmd;
    for (int i = 0; i < n; i++)
    {
        cin >> cmd;

        if (cmd == "Append")
        {
            string suit;
            string rank_str;
            cin >> suit >> rank_str;

			int rank = stringToRank(rank_str);
            list.append(Poker(suit, rank));
        }
        else if (cmd == "Pop")
        {
            list.pop();
        }
        else if (cmd == "Revert")
        {
            list.revert();
        }
        else if (cmd == "Extract")
        {
            string suit;
            cin >> suit;
            list.extract(suit);
        }
    }

    list.print();

    return 0;
}