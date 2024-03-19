#include "main.hpp"

/* TODO: Please design your data structure carefully so that you can work with the given dataset
 *       in this assignment. The below structures are just some suggestions.
 */

template <typename T>
class SinglyLinkedList;

template <typename T>
class ArrList;

template <typename T>
class List
{
public:
    virtual ~List() = default;
    virtual void push_back(T value) = 0;
    virtual void push_front(T value) = 0;
    virtual void insert(int index, T value) = 0;
    virtual void remove(int index) = 0;
    virtual T &get(int index) const = 0;
    virtual int length() const = 0;
    virtual void clear() = 0;
    virtual void print() const = 0;
    virtual void reverse() = 0;
    // virtual void selectionSort() = 0;
    // virtual bool contain(T value) = 0;
    // virtual bool contains(const T &value) const = 0;
    virtual bool find(const T &val) = 0;
    virtual ArrList<T> *_to_Array() = 0;
    virtual SinglyLinkedList<T> *_to_SLinkedList() = 0;
};

class Dataset
{
private:
    List<List<int> *> *data;
    int numRows;
    int numCols;
    List<string> *header_name;
    // You may need to define more
public:
    Dataset();
    ~Dataset();
    Dataset(const Dataset &other);
    Dataset &operator=(const Dataset &other);
    bool loadFromCSV(const char *fileName);
    void printHead(int nRows = 5, int nCols = 5) const;
    void printTail(int nRows = 5, int nCols = 5) const;
    void getShape(int &nRows, int &nCols) const;
    void columns() const;
    bool drop(int axis = 0, int index = 0, std::string columns = "");
    Dataset extract(int startRow = 0, int endRow = -1, int startCol = 0, int endCol = -1) const;
    List<List<int> *> *getData() const;
    List<string> *getHeaderName() const;
};

class kNN
{
private:
    int k;
    Dataset X_train, y_train;
    int train_row, train_col;
    // You may need to define more
public:
    kNN(int k = 5);
    void fit(const Dataset &X_train, const Dataset &y_train);
    Dataset predict(const Dataset &X_test);
    double score(const Dataset &y_test, const Dataset &y_pred);
    // double EuclideanDistance(const Dataset &X_test,const Dataset &Y);
};

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test);

// Please add more or modify as needed
// Implement ArrayList

template <typename T>
class ArrList : public List<T>
{
private:
    T *pD;
    int count, cap;

public:
    ArrList() : count(0), cap(5), pD(new T[5]) {};
    ArrList(int count, int cap)
    {
        this->count = count;
        this->cap = cap;
        pD = new T[cap];
    }
    ArrList(List<T> *other)
    {
        count = other->length();
        cap = count * 1.5;
        pD = new T[cap];
        for (int i = 0; i < other->length(); i++)
        {
            pD[i] = other->get(i);
        }
    };
    ~ArrList() { clear(); };
    void resize(int n)
    {
        if (n >= cap)
        {
            cap *= 1.5;
            T *temp = new T[cap];
            for (int i = 0; i < count; i++)
            {
                temp[i] = pD[i];
            }
            delete[] pD;
            pD = temp;
            temp = nullptr;
        }
    };
    bool find(const T &val)
    {
        for (int i = 0; i < count; i++)
        {
            if (pD[i] == val)
                return true;
        }
        return false;
    }
    void push_back(T value)
    {
        if (isFull())
        {
            resize(count);
        }
        pD[count] = value;
        count++;
    };
    bool isFull() { return count == cap; };
    void push_front(T value)
    {
        if (isFull())
        {
            resize(count);
        }
        count++;
        for (int i = count; i > 0; i--)
        {
            pD[i] = pD[i - 1];
        }
        pD[0] = value;
    };
    void insert(int index, T value)
    {
        if (index < 0 || index > count)
        {
            return;
        }
        if (index == 0)
        {
            push_front(value);
            return;
        }
        if (index == count)
        {
            push_back(value);
            return;
        }
        if (isFull())
        {
            resize(count);
        }
        count++;
        for (int i = count; i > index; i--)
        {
            pD[i] = pD[i - 1];
        }
        pD[index] = value;
    };
    void remove(int index)
    {
        if (index < 0 || index >= count)
            return;
        for (int i = index; i < count - 1; i++)
            pD[i] = pD[i + 1];
        count--;
    };
    T &get(int index) const
    {
        return pD[index];
    };
    int length() const { return count; };
    void clear()
    {
        if (count != 0)
        {
            delete[] pD;
            pD = new T[5];
            count = 0;
            cap = 5;
        }
    };
    void print() const
    {
        if (count == 0)
            return;
        int i = 0;
        for (i; i < count - 1; i++)
        {
            cout << pD[i] << " ";
        }
        cout << pD[i];
    };
    void print(int start_idx, int end_idx) const
    {
        if (count == 0)
            return;
        if (start_idx > end_idx)
            return;
        if (start_idx < 0)
            start_idx = 0;
        if (end_idx > count)
            end_idx = count - 1;
        for (int i = start_idx; i < end_idx; i++)
        {
            cout << pD[i] << " ";
        }
        cout << pD[end_idx];
    }
    void reverse()
    {
        T *pL = pD, *pR = pD + count - 1;
        while (pL < pR)
        {
            std::swap(*pL, *pR);
            pL++;
            pR--;
        }
    };
    ArrList<T> *_to_Array()
    {
        ArrList<T> *p = new ArrList<T>(0, cap);
        for (int i = 0; i < count; i++)
        {
            p->push_back(pD[i]);
        }
        return p;
    };
    SinglyLinkedList<T> *_to_SLinkedList()
    {
        SinglyLinkedList<T> *p = new SinglyLinkedList<T>();
        for (int i = 0; i < count; i++)
        {
            p->push_back(this->get(i));
        }
        return p;
    };
};

////////////////////////////////////////////////////////////////////////////////////////
// Implement for class List
template <typename T>
class SinglyLinkedList : public List<T>
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &value) : data(value), next(nullptr) {};
        Node(const T &value, Node *next) : data(value), next(next) {};
    };
    Node *head;
    int size;

public:
    SinglyLinkedList() : head(nullptr), size(0) {}

    ~SinglyLinkedList()
    {
        clear();
    }
    bool find(const T &val)
    {
        Node *tmp = head;
        int i = 0;
        while (tmp)
        {
            if (tmp->data == val)
                return true;
            tmp = tmp->next;
            i++;
        }
        return false;
    }
    ArrList<T> *_to_Array()
    {
        ArrList<T> *p = new ArrList<T>(0, size);
        for (int i = 0; i < size; i++)
        {
            p->push_back(this->get(i));
        }
        return p;
    };
    SinglyLinkedList<T> *_to_SLinkedList()
    {
        SinglyLinkedList<T> *p = new SinglyLinkedList();
        for (int i = 0; i < size; i++)
        {
            p->push_back(this->get(i));
        }
        return p;
    };
    // Insertion from back
    void push_back(T value)
    {
        Node *new_node = new Node(value);
        if (head == nullptr)
        {
            head = new_node;
        }
        else
        {
            Node *current = head;
            while (current->next != nullptr)
            {
                current = current->next;
            }
            current->next = new_node;
        }
        size++;
    }
    // Insertion from front
    void push_front(T value)
    {
        Node *new_node = new Node(value);
        if (head == nullptr)
        {
            head = new_node;
        }
        else
        {
            new_node->next = head;
            head = new_node;
        }
        size++;
    }
    // Insertion at index
    void insert(int index, T value)
    {
        // Node *new_node = new Node(value);
        // if (index < 0 || index > size)
        // {
        //     return;
        // }

        // if (size == 0)
        // {
        //     head = new_node;
        // }
        // if (index == 0)
        // {
        //     push_front(value);
        //     return;
        // }

        // Node *current = head;
        // for (int i = 0; i < index - 1; ++i)
        // {
        //     current = current->next;
        // }
        // new_node->next = current->next;
        // current->next = new_node;
        // size++;
        // Test
        if (index < 0) index = 0;
            else if (index > size) index = size;
            Node** pp = &head;
            while (index)
            {
                pp = &((*pp)->next);
                index--;
            }
            *pp = new Node(value,*pp);
            size++;
    }
    // Remove at index
    void remove(int index)
    {
        if (index < 0 || index >= size)
        {
            return;
        }

        if (index == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node *current = head;
            for (int i = 0; i < index - 1; ++i)
            {
                current = current->next;
            }
            Node *temp = current->next;
            current->next = temp->next;
            delete temp;
        }
        size--;
    }

    // Access Method
    T &get(int index) const
    {
        if (index < 0 || index >= size)
        {
            throw std::out_of_range("get(): Out of range");
        }

        Node *current = head;
        for (int i = 0; i < index; ++i)
        {
            current = current->next;
        }
        return current->data;
    }

    bool contains(const T &value) const
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->data == value)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    int length() const
    {
        return size;
    }

    // Other operations
    void clear()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }

    void print() const
    {
        if (head == nullptr)
        {
            return;
        }

        Node *current = head;
        cout << current->data;
        current = current->next;
        while (current != nullptr)
        { // Iterate until the end of the list
            cout << " " << current->data;
            current = current->next;
        }
    }

    void reverse()
    {
        Node *current = head;
        Node *prev = NULL, *next = NULL;

        while (current != NULL)
        {
            // Store next
            next = current->next;
            // Reverse current node's pointer
            current->next = prev;
            // Move pointers one position ahead.
            prev = current;
            current = next;
        }
        head = prev;
    }

    void selectionSort()
    {
        if (size <= 1)
        {
            return; // List is already sorted or empty
        }

        Node *current = head;
        while (current != nullptr)
        {
            Node *minNode = current;
            Node *nextNode = current->next;
            while (nextNode != nullptr)
            {
                if (nextNode->data < minNode->data)
                {
                    minNode = nextNode;
                }
                nextNode = nextNode->next;
            }
            // Swap data between current node and minNode
            T temp = current->data;
            current->data = minNode->data;
            minNode->data = temp;

            current = current->next;
        }
    }
};