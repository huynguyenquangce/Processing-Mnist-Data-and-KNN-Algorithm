#include "kNN.hpp"
// #include "kNN.cpp"
void tc1(){
    Dataset dataset;
    dataset.loadFromCSV("mnist.csv");
    // // dataset.extract(0,0).printHead();
    // dataset.printHead();
    // cout<<"\n";
    // dataset.drop(1,0,"1x1");
    // dataset.printHead();

    // dataset.printHead();
    // dataset.printTail();
    // int nRows, nCols;
    // dataset.getShape(nRows, nCols);
    // cout << "Shape: " << nRows << "x" << nCols << endl;
    // dataset.extract(0,1,0,1).printHead();
    // dataset.columns();
    // dataset.printHead();
    kNN knn;
    Dataset X_train, X_test, y_train, y_test;
    Dataset feature = dataset.extract(0, -1, 1, -1);
    feature.printHead();
    cout<<"\n"; 
    Dataset label = dataset.extract(0, -1, 0, 0);
    label.printHead();
    cout<<"\n"; 
    cout<<"-----------";
    train_test_split(feature, label, 0.2, X_train, X_test, y_train, y_test);
    cout<<endl;
    int x,y;
    y_train.getShape(x,y);
    cout << "Shape: " << x << "x" << y << endl;
    int l,r;
    y_test.getShape(l,r);
    cout << "Shape: " << l << "x" << r << endl;
    // X_train.printHead();
    // X_test.printHead();
    // y_train.printHead();
    // y_test.printHead();
    // knn.fit(X_train, y_train);
    // Dataset y_pred = knn.predict(X_test); 
    // double accuracy = knn.score(y_test, y_pred);
    // cout << "Accuracy: " << accuracy << endl;

/////////////////////////////// Tests //////////////////////////
    
}
int main() {
    tc1();
    return 0;
}

