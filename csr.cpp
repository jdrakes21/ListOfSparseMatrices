/*****************************************
** File:    csr.cpp
** Project: CMSC 341 Project 1, Fall 2023
** Author:  Jervon Drakes
** Date:    10/02/2023
** E-mail:  jdrakes1@umbc.edu
** 
**
** This file contains the csr.cpp file for Project 1.
** This program reads the csr.h file and its functions and
** executes those functions for implementation
**
**
**
***********************************************/

// CMSC 341 - Fall 2023 - Project 1
#include "csr.h"
///////////////CSR Class Implementation///////////////

//CSR (default constructor)
// It creates an empty object. An empty object does not hold any memory. The constructor must initialize all member variables.
CSR::CSR(){


  m_values = nullptr;
  m_col_index = nullptr;
  m_row_index = nullptr;
  m_row_index = nullptr;
  m_nonzeros = 0;
  m_m = 0;
  m_n = 0;
  m_next = nullptr;

  
}

//~CSR (destructor)
//This is the destructor and it deallocates the memory.
CSR::~CSR(){

  //clear any data
  clear();
  
}

//CSR(copy constructor)
//Copy constructor creates a deep copy of rhs.
CSR::CSR(const CSR & rhs){

  // initialize member variables to default values or nullptr
  m_values = nullptr;
  m_col_index = nullptr;
  m_row_index = nullptr;
  m_row_index = nullptr;
  m_next = nullptr;
  m_nonzeros = 0;
  m_m = 0;
  m_n = 0;

  // copy the dimensions of the matrix (number of rows and columns) from the CSR object called rhs
  m_n = rhs.m_n;
  m_m = rhs.m_m;

  // if the rhs object has non-zero values, allocate memory and copy them
  if(rhs.m_nonzeros > 0){

    m_nonzeros = rhs.m_nonzeros;
    m_col_index = new int[m_nonzeros];
    m_values = new int[m_nonzeros];

    // iterate and copy the columns and values from the CSR object, rhs, to the current object
    for(int i = 0; i < m_nonzeros; ++i){
      m_col_index[i] = rhs.m_col_index[i];
      m_values[i] = rhs.m_values[i];
    }
  }

  // if the rhs object has rows, allocate memory and copy
  if(rhs.m_m > 0){
    m_row_index = new int[m_m + 1];

    // iterate and copy the rows from the rhs source object to the current object
    for(int i = 0; i <= m_m; ++i){
      m_row_index[i] = rhs.m_row_index[i];

    }
  }   
}

// clear
// This function deallocates all memory and converts the object to an empty CSR object.
void CSR::clear(){

  // deallocate memory within m_col_index
  if(m_col_index != nullptr){

    delete[] m_col_index;
    m_col_index = nullptr;
  }

  // deallocate memory with m_row_index
  if(m_row_index != nullptr){

    delete[] m_row_index;
    m_row_index = nullptr;

  }

  // deallocate memory within m_values
  if(m_values != nullptr){

    delete[] m_values;
    m_values = nullptr;
  }


  m_n = 0;
  m_m = 0;
  m_nonzeros = 0;
  
}

// empty
// This function returns true if the object is empty, otherwise it returns false.
bool CSR::empty() const{

  // object is returned empty if any of these conditions match
  if(m_values == nullptr || m_col_index == nullptr || m_row_index == nullptr || m_m == 0 || m_n == 0){

    return true;

  }

  return false;
}

// compress(int m, int n, int array[], int arraySize)
// This function receives a sparse matrix in the form of an array and creates a compressed version of the sparse matrix. All required memory allocation happens in this function. Since the function can be re-called on the same object the function needs to re-create new memory for the new sparse matrix that is passed to the function. Moreover, the compress(...) function initializes all member variables.
void CSR::compress(int m, int n, int array[], int arraySize){

  // initialies member variables if any of these conditions are met
  if(m <= 0 || n <= 0){
    
    m_m = 0;
    m_n = 0;
    m_col_index = nullptr;   
    m_row_index = new int[m_m + 1]();
    
    return;

  }

  
  // clear any data
  clear();

  // set dimensions
  m_m = m;
  m_n = n;

  // intialize row related variables
  int gameRow = 0;
  int matrixRow = 0;
  
  m_nonzeros = 0;

  // iterate and determine the number of non-zero elements in the array
  for(int i = 0; i < arraySize; ++i){
    if(array[i] != 0){
      ++m_nonzeros;
    }
  }

  // allocate memory for arrays
  m_values = new int[m_nonzeros];
  m_row_index = new int[m_m + 1];
  m_col_index = new int[m_nonzeros];

  m_row_index[0] = 0; // initialize the first element in the row index array

  // iterate and populate the matrix from the array
  for(int i = 0; i < arraySize; ++i){

    int matrixNum = i % n;
    if(array[i] != 0){
      m_values[matrixRow] = array[i]; // store the nonzero value
      m_col_index[matrixRow] = matrixNum; // determine and place the column index
      ++matrixRow;
      

    }
  
    float num = (i + 1) / n;

    // determines if num is greater than gameRow
    if(num > gameRow){
      ++gameRow;
      m_row_index[gameRow] = matrixRow; // update the row index for the matrix
    }
    
  }
  

}

// getAt(int row, int col) const
// Returns the value of the matrix member at indices row and col. If the requested indices do not exist (they are out of range) the function throws a runtime_error exception. The exception is defined in <stdexcept> library and is available from std namespace.
int CSR::getAt(int row, int  col) const{

  // determines if the indices are out of range
  if( row >= m_m || row < 0 || col < 0 || col >= m_n){

    throw runtime_error("Indices out of range");
  }

  // determine the range for the particular row
  int startRow = m_row_index[row];
  int endRow = m_row_index[row + 1];

  // loop through and search for the column index
  for(int i = startRow; i < endRow; ++i){

    // detrmine if the column index matches col
    if(m_col_index[i] == col){

      return m_values[i];
    }
  }

  // returns 0 if the column index is not found within the row
  return 0;
} 

// Equality Operator
// Overloaded equality operator returns true if all members of two matrices are equal.
bool CSR::operator==(const CSR & rhs) const{

  // determine if the dimensions of the matrix match
  if(m_m != rhs.m_m || m_n != rhs.m_n){

    return false;

  }

  // determine if the number of non zero values is equal
  if(m_nonzeros != rhs.m_nonzeros){

    return false;

  }

  // loop and compare the elements of the values and column arrays
  for(int i = 0; i < m_nonzeros; i++){

    if(m_values[i] != rhs.m_values[i] || m_col_index != rhs.m_col_index){

      return false;
    }
  }

  // loops and compares the row arrays
  for(int i = 0; i < m_m; ++i){

    if(m_row_index[i] != rhs.m_row_index[i]){
      return false;
    }
  }

  return true;
}

// sparseRatio
// Returns the sparsity ratio for the CSR object. It returns the ratio as percentage, e.g. if the ratio is 0.656, the function returns 0.656 x 100 = 65 as integer. If the CSR object is empty this function returns zero. If all members of the matrix are zero the function returns 100.
int CSR::sparseRatio(){
  
  // deterimes if the object is empty
  if(empty()) {

    return 0;

  }
  
  // determines if there are 0 nonzero elements in the object
  if (m_nonzeros == 0){
    return 100;

  } 
  
    double sparsityRatio = static_cast<double>(m_nonzeros) / (m_m * m_n);
    
    return static_cast<int>(sparsityRatio * 100);
  
}

void CSR::dump(){
    cout << endl;
    if (!empty()){
        for (int i=0;i<m_nonzeros;i++)
            cout << m_values[i] << " ";
        cout << endl;
        for (int i=0;i<m_nonzeros;i++)
            cout << m_col_index[i] << " ";
        cout << endl;
        for (int i=0;i<m_m+1;i++)
            cout << m_row_index[i] << " ";
    }
    else
        cout << "The object is empty!";
    cout << endl;
}

//////////////CSRList Class Implementation///////////////

//CSRList(default constructor)
//This is the default constructor. It creates an empty object. An empty object does not hold any memory. The constructor must initialize all member variables.
CSRList::CSRList(){

  m_head = nullptr; // initialize the head pointer to nullptr

  m_size = 0; // initialize m_size to 0;
}

//CSRList(copy constructor)
//Copy constructor creates a new CSRList object from rhs.
//Note: If we use simply insertAtHead(...) to make insertion, the new list will be reversed. That is not what we need. Copy constructor makes an exact copy of rhs, i.e. the order of the CSR objects should be the same as rhs.
CSRList::CSRList(const CSRList & rhs){

  m_size = 0; // initialize m_size to 0
  m_head = nullptr; // intialize m_head to nullptr

  CSR* curr = rhs.m_head; // iterate through the objects in rhs and insert in the same order

  while(curr != nullptr){

    CSR* csr = new CSR(*curr); // create a csr object and assign it as a copy of curr

    // insert csr at the head of the list
    insertAtHead(*csr); 

    // move to the next object in rhs
    curr = curr->m_next;
  }
}

//~CSRList(destructor)
// This is the destructor and it deallocates the memory.
CSRList::~CSRList(){

  // iterate through the linked list once m_head is not nullptr and delete all the CSR objects
  while(m_head != nullptr){

    CSR * curr = m_head; // creat a pointer an assign it to the current object
    m_head = m_head->m_next; // move m_head to the next object

    // delete the current object
    delete curr;
  }

  m_size = 0;
}

// empty
// This function returns true if the list is empty, otherwise it returns false.
bool CSRList::empty() const{

  return m_head == nullptr;
}

// insertAtHead(const CSR & matrix)
// This function inserts the CSR object at the head of the CSRList object.
void CSRList::insertAtHead(const CSR & matrix){

  CSR* node = new CSR(matrix); // create a CSR node with a copy of the matrix

  node->m_next = m_head; // set the next pointer to the next node of the current head

  m_head = node; // assign the head pointer to the node

  m_size++;
}

// clear
// This function resets the CSRList object to its initial, empty state.
void CSRList::clear(){

  CSR* curr = m_head; // create a CSR node

  // iterate once curr is not nullptr
  while(curr != nullptr){

    CSR* nextNode = curr->m_next; // Create another CSR node and access the next node within the list

    delete curr;

    curr = nextNode;
  }

  m_size = 0;
  m_head = nullptr;
  
}

//getAt(int CSRIndex, int row, int col) const
// This function returns the value of a matrix member with row and col indices, from the matrix at the position CSRIndex in the CSRList object. If the requested indices do not exist (they are out of range in the matrix or the matrix does not exist in the list) the function throws a runtime_error exception. The exception i
// is defined in <stdexcept> library and is available from std namespace.
int CSRList::getAt(int CSRIndex, int row, int col) const{


   //determine if CSRIndex is our of range
   if(CSRIndex < 0 || CSRIndex >= m_size){

     throw runtime_error("Exception Error: Object is not in the list");

   }

   CSR* curr = m_head;  //create a new CSR node


   //iterate and find the matrix at the specifc index
   for(int i = 0; i < CSRIndex; ++i){

    curr = curr->m_next;// access the next node within the list
   } 

   //determine if the CSR matrix exists
   if(curr == nullptr){

     throw runtime_error("CSR matrix not found");
   }

  // retrieve the value at the speficied row and column within the matrix
   return curr->getAt(row, col);

}

// Equality Operator
// The overloaded equality operator returns true if both lists have the same matrices and in the same order, otherwise returns false.
bool CSRList::operator== (const CSRList & rhs) const{
      
    //comparing the size of the two lists
    if(rhs.m_size != m_size){

      return false;
    }

    CSR* curr = m_head;
    CSR* newNode = rhs.m_head;

    // Iterate through each list and compare CSR matrices
    while(curr != nullptr && newNode != nullptr){
      
      // compare the CSR matrices both lists
      if(!(*curr == *newNode)){

        return false;
      }

      curr = curr->m_next; // move to the next matrix in this list
      newNode = newNode->m_next; // move to the next matrix in this list

    }
    
    //returns true if both lists are equal
    return true;
}

// Assignment Operator
// The overloaded assignment operator creates an exact deep copy of the rhs object.
const CSRList& CSRList::operator=(const CSRList & rhs){
    
    // tests for self assignment
    if(this == &rhs){
      return *this;
    }

    // clear data within the current list
    clear();

    CSR* curr = rhs.m_head;

    // iterate through curr and create deep copies
    while(curr != nullptr){

      // create a new CSR object
      CSR* nodeCSR = new CSR(*curr);

      // insert the object at the head of the list
      insertAtHead(*nodeCSR);

      curr = curr->m_next;// move to the next node(matrix) in the list
    }

    return *this;
}

// averageSparseRatio
// This functino returns the average sparse ratio for all matrices stored in the CSRList object. It returns the ratio as percentage, e.g. if the ratio is 0.656, the function returns 0.656 x 100 = 65 as integer.
int CSRList::averageSparseRatio(){
    
    //determine if the list is empty
    if(empty()){

      // handles the case and returns - 1 if the list has no matrices
      return -1;
    }

    int matricesTotal = 0;
    int totalRatio = 0;
    int listRatio;

    CSR* curr = m_head;
    while(curr != nullptr){

      listRatio = curr->sparseRatio(); // determine the sparse ratio for the matrix of the current list

      totalRatio += listRatio; // add listRatio to the totalRatio

      curr = curr->m_next; // move to the next node(matrix) in the list

      matricesTotal++;
    }
    
    int avgRatio;
    // determine if the total number of matrices is greater than 0
    if(matricesTotal > 0){
    
    avgRatio = totalRatio / matricesTotal; // determine the average Sparse Ratio
    return avgRatio;
    } else {

      // returns -1 when there are no matrices
      return -1;
    }
}
void CSRList::dump(){
    if (!empty()){
        CSR* temp = m_head;
        while (temp != nullptr){
            temp->dump();
            temp = temp->m_next;
        }
    }
    else
        cout << "Error: List is empty!" << endl;
}
