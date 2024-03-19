#include "kNN.hpp"

void tc1()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    int nRows, nCols;

    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    Dataset label = dataset.extract(0, -1, 0, 0);

    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    knn.fit(X_train, y_train);
    Dataset y_pred = knn.predict(X_test);

    cout << "y_pred" << endl;
    y_pred.printHead(10, 10);
    cout << endl;
    cout << "y_test" << endl;
    y_test.printHead(10, 10);
    cout << endl;
}
void tc2()
{
    List<int> *p1 = new SinglyLinkedList<int>();
    p1->_to_Array();
    p1->push_back(1);
    p1->push_back(2);
    p1->push_back(3);
    p1->print();
    cout<<endl;
    cout<< p1->find(5);
}

void tc3()
{
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    List<int>* row = dataset.getData()->get(0);
    for(int j = 0; j < 35; j++){
        for(int i = 0; i < 10000000; i++){
            row->insert(0, 1);
        }
        for(int i = 0; i < 10000000; i++){
            row->remove(0);
        }
    }
    cout << row->length();
}
int main()
{
    tc1();
    // tc2();
    // tc3();
    return 0;
}
