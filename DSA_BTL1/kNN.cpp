#include "kNN.hpp"
const double MAX_DOUBLE = 1.7976931348623157e+308;
const int MAX_CLASSES = 1000;
/* TODO: You can implement methods, functions that support your data structures here.
 * */
//////////////////////////////////////

/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
/////////////////////////////////////////////
// Implement for class Dataset

Dataset::Dataset() : data(new ArrList<List<int> *>(0,5)), numRows(0), numCols(0), header_name(new ArrList<string>(0,5)) {}

Dataset::~Dataset()
{
    delete data;
    delete header_name;
}

Dataset::Dataset(const Dataset &other)
{
    numRows = other.numRows;
    numCols = other.numCols;
    // copy header_name
    header_name = new SinglyLinkedList<string>;
    for (int i = 0; i < other.header_name->length(); i++)
    {
        header_name->push_back(other.header_name->get(i));
    }
    // copy data
    data = new SinglyLinkedList<List<int> *>;
    for (int i = 0; i < other.data->length(); i++)
    {
        List<int> *currentList = new SinglyLinkedList<int>;
        for (int j = 0; j < other.data->get(i)->length(); ++j)
        {
            currentList->push_back(other.data->get(i)->get(j));
        }
        data->push_back(currentList);
    }
}
Dataset &Dataset::operator=(const Dataset &other)
{
    if (this == &other)
    {
        return *this;
    }
    // Delete existing data
    this->drop();
    data->clear();
    // delete header_name;
    header_name->clear();
    numCols = other.numCols;
    numRows = other.numRows;
    // copy header_name
    header_name = new SinglyLinkedList<string>;
    for (int i = 0; i < other.header_name->length(); i++)
    {
        header_name->push_back(other.header_name->get(i));
    }
    // copy data
    data = new ArrList<List<int> *>(0,5);
    for (int i = 0; i < other.data->length(); i++)
    {
        List<int> *currentList = new SinglyLinkedList<int>;
        for (int j = 0; j < other.data->get(i)->length(); ++j)
        {
            currentList->push_back(other.data->get(i)->get(j));
        }
        data->push_back(currentList);
    }
    return *this;
}
bool Dataset::loadFromCSV(const char *fileName)
{
    // Implement loadFromCSV method
    ifstream file(fileName);
    if (!file.is_open())
    {
        return false;
    }
    data->clear();
    header_name->clear();
    string line;
    getline(file, line);
    stringstream headerStream(line);
    string headerValue;
    while (getline(headerStream, headerValue, ','))
    {
        header_name->push_back(headerValue);
    }
    while (getline(file, line))
    {
        List<int> *row = new SinglyLinkedList<int>();
        stringstream ss(line);
        string value;
        while (getline(ss, value, ','))
        {
            int intValue = stoi(value);
            row->push_back(intValue);
            numCols += 1;
        }
        data->push_back(row);
    }
    file.close();
    // assign numRows and numCols
    numRows = data->length();
    numCols = header_name->length();
    return true;
}
// void Dataset::printHead(int nRows,  int nCols) const {};
// Implement of printHead
void Dataset::printHead(int nRows, int nCols) const
{
    // Print header names
    const List<string> &headerNames = *header_name;
    for (int j = 0; j < min(nCols, headerNames.length()); ++j)
    {
        cout << headerNames.get(j) << " ";
    }
    // this->columns();
    cout << endl;
    // Print data
    int totalRows = data->length();
    for (int i = 0; i < min(nRows, totalRows); ++i)
    {
        const List<int> *row = data->get(i);

        for (int j = 0; j < min(nCols, row->length()); ++j)
        {
            cout << row->get(j) << " ";
        }
        // cout << endl;
        // Check if it's not the last row before printing newline
        if (i < min(nRows, totalRows) - 1)
        {
            cout << endl;
        }
    }
    // If numberRows and Col <0
    if (numCols < 0 || numCols < 0)
    {
        return;
    }
    return;
}

// Implement of PrintTail
void Dataset::printTail(int nRows, int nCols) const
{
    // If numberRows and Col <0
    if (numCols < 0 || numCols < 0)
    {
        return;
    }
    int totalRows = data->length();
    int startRow = max(0, totalRows - nRows); // Starting row index

    // Print header names
    const List<std::string> &headerNames = *header_name;
    for (int j = max(0, headerNames.length() - nCols); j < headerNames.length(); ++j)
    {
        cout << headerNames.get(j) << " ";
    }
    cout << endl;

    // Print data
    for (int i = startRow; i < totalRows; ++i)
    {
        const List<int> *row = data->get(i);

        for (int j = max(0, row->length() - nCols); j < row->length(); ++j)
        {
            cout << row->get(j) << " ";
        }
        // cout << endl;
        // Check if it's not the last row before printing newline
        if (i < totalRows - 1)
        {
            cout << endl;
        }
    }
    return;
}
// Implement of getData() method
List<List<int> *> *Dataset::getData() const
{
    return data;
}

// Implement of getHeaderName() method
List<string> *Dataset::getHeaderName() const
{
    return header_name;
}

// Implement of getShape() method
void Dataset::getShape(int &nRows, int &nCols) const
{
    nRows = numRows;
    nCols = numCols;
}
// Implement of Column() method
void Dataset::columns() const
{
    // Print header names
    const List<string> &headerNames = *header_name;
    for (int j = 0; j < headerNames.length() - 1; ++j)
    {
        cout << headerNames.get(j) << " ";
    }
    cout << headerNames.get(header_name->length() - 1);
    // header_name->print();
}
// Implement of Axis() method
bool Dataset::drop(int axis, int index, std::string columns)
{
    if (axis != 0 && axis != 1)
    {
        return false;
    }
    // Delete by rows
    if (axis == 0)
    {
        if (index >= numRows || index < 0)
            return false;
        if (index < numRows)
        {
            delete data->get(index);
            data->remove(index);
            numRows--;
            return true;
        }
    }
    // Delete by columns
    if (axis == 1)
    {
        int columnIndexToRemove = -1;
        for (int i = 0; i < numCols; i++)
        {
            if (columns == header_name->get(i))
            {
                // Implement here
                columnIndexToRemove = i;
                break; // Found the column, exit the loop
            }
        }
        // Found a valid column to remove
        if (columnIndexToRemove != -1)
        {
            // To do here
            for (int i = 0; i < numRows; ++i)
            {
                List<int> *row = data->get(i);
                if (columnIndexToRemove < numCols)
                {
                    row->remove(columnIndexToRemove);
                }
            }
            header_name->remove(columnIndexToRemove);
            numCols--;
            return true;
        }
        // Not found a valid column to remove
        else
        {
            return false;
        }
    }
    return false; // default
}
// Implement of extract
Dataset Dataset::extract(int startRow, int endRow, int startCol, int endCol) const
{
    Dataset extractedDataset;
    // Adjust endRow and endCol if they are set to -1
    endRow = (endRow == -1) ? numRows - 1 : endRow;
    endCol = (endCol == -1) ? numCols - 1 : endCol;

    // Assign header_name to extractedDataset
    for (int i = startCol; i <= endCol; ++i)
    {
        extractedDataset.header_name->push_back(header_name->get(i));
    }
    // Assign data from range to extractedDataset
    // Extract rows and columns from the current dataset
    for (int i = startRow; i <= endRow; ++i)
    {
        List<int> *newRow = new SinglyLinkedList<int>;

        for (int j = startCol; j <= endCol; ++j)
        {
            // Assuming data is a List<List<int>*> and each element is a List<int>
            List<int> *currentRow = data->get(i);
            newRow->push_back((currentRow->get(j)));
        }
        extractedDataset.data->push_back(newRow);
    }
    // Update the number of rows and columns in the extracted dataset
    extractedDataset.numRows = endRow - startRow + 1;
    extractedDataset.numCols = endCol - startCol + 1;
    return extractedDataset;
}

//////////////////////////////////////////
/////////////////////////////////////////
////////////////////////////////////////

// Implement of class KNN
kNN::kNN(int k) : k(k), train_row(0), train_col(0), X_train(Dataset()), y_train(Dataset())
{
} // Initialize other members if needed

void kNN::fit(const Dataset &X_train, const Dataset &y_train)
{
    this->X_train = X_train;
    this->y_train = y_train;
    X_train.getShape(train_row, train_col);
}
// double kNN::EuclideanDistance(const Dataset &X, const Dataset &Y)
// {
//     double sum = 0.0;
//     for(int i = 0; i < train_col;i++)
//     {
//         sum += pow(X.getData()->get(i)- Y.getData()->get(i),2);
//     }
//     return sqrt(sum);
// };
// Implement selectionSort for List
///////////////////////
/////////////////////////////////

Dataset kNN::predict(const Dataset &X_test)
{
    Dataset y_pred;
    // Array to keep number of k smallerst distance
    int class_counts[MAX_CLASSES] = {0};

    Dataset X_save;
    // Number of dac diem X_test
    int X_test_number = X_test.getData()->length();
    int X_train_number = X_train.getData()->length();
    // Calculate distance from X_test to X_train and save in save List
    for (int i = 0; i < X_test_number; i++)
    {
        int temp_result = 0; // temp result for Euclidean distance
        // List to save data of Euclidean distance of each label
        List<double> *save = new SinglyLinkedList<double>();
        save->_to_Array();
        for (int j = 0; j < X_train_number; j++)
        {
            temp_result = 0;
            for (int k = 0; k < train_col; k++)
            {
                temp_result += pow(X_test.getData()->get(i)->get(k) - X_train.getData()->get(j)->get(k), 2);
            }
            double distance = sqrt(temp_result);
            save->push_back(distance);
        }
        // result_sort->push_back(save);
        // Now we have distances, we need to find the k nearest neighbors
        List<int> *nearest_indices = new SinglyLinkedList<int>();
        nearest_indices->_to_Array();
        for (int n = 0; n < k; n++)
        {
            double min_distance = MAX_DOUBLE;
            int min_index = -1;
            for (int j = 0; j < X_train_number; j++)
            {
                if (save->get(j) < min_distance && !nearest_indices->find(j))
                {
                    min_distance = save->get(j);
                    min_index = j;
                }
            }
            nearest_indices->push_back(min_index);
        }
        for (int n = 0; n < k; n++)
        {
            int neighbor_index = nearest_indices->get(n);
            List<int> *neighbor_labels = y_train.getData()->get(neighbor_index);
            int label = neighbor_labels->get(0); // Assuming labels are stored in y_train
            class_counts[label]++;
        }
        // Find the majority class
        int max_count = 0;
        int predicted_label = -1;
        for (int i = 0; i < MAX_CLASSES; i++)
        {
            if (class_counts[i] > max_count)
            {
                max_count = class_counts[i];
                predicted_label = i;
            }
        }
        // Save the predicted label
        List<int> *temp_list = new SinglyLinkedList<int>();
        temp_list->_to_Array();
        temp_list->push_back(predicted_label);
        y_pred.getData()->push_back(temp_list);

        // Clear class_counts
        for (int i = 0; i < MAX_CLASSES; i++)
        {
            class_counts[i] = 0;
        }
        delete save;            // Free memory
        delete nearest_indices; // Free memory
    }

    // cout << endl;
    // result_sort->get(0)->print();
    // cout << endl;
    // // result_sort->get(1)->print();
    // // cout << endl;
    // cout << "After sort:" << endl;
    // for (int i = 0; i < result_sort->length(); i++)
    // {
    //     result_sort->get(i)->selectionSort();
    //     result_sort->get(i)->print();
    //     cout << endl;
    // }
    // y_pred.printHead();
    return y_pred;
}

// Score method to evaluate the model's performance
double kNN::score(const Dataset &y_test, const Dataset &y_pred)
{
    // Implement the scoring logic here and return the accuracy or other metric

    return 0.0; // Placeholder, replace with actual value
}

void train_test_split(Dataset &X, Dataset &y, double test_size,
                      Dataset &X_train, Dataset &X_test, Dataset &y_train, Dataset &y_test)
{
    int numRowX, numColY;
    X.getShape(numRowX, numColY);
    int num_test = ceil(test_size * numRowX);
    int num_train = numRowX - num_test;

    X_train = X.extract(0, num_train - 1, 0, -1);
    y_train = y.extract(0, num_train - 1, 0, 0);
    X_test = X.extract(num_train, numRowX - 1, 0, -1);
    y_test = y.extract(num_train, numRowX - 1, 0, 0);
}