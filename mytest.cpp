/*****************************************
** File:    mytest.cpp
** Project: CMSC 341 Project 1, Fall 2023
** Author:  Jervon Drakes
** Date:    10/02/2023
** E-mail:  jdrakes1@umbc.edu
** 
**
** This file contains the mytest.cpp file for Project 1.
** This program implements functions for the tester class to 
** implement numerous test cases for the functions in bingo.cpp
**
**
**
***********************************************/
#include "csr.h"

class Tester{

public:
   
  // Function: CSR::compress(int m, int n, int array[], int arraySize)
  // Case: Tests the compress function for an normal case 
  //(populates the member variables of the class with the expected values for an array of data)
  // Expected Result: Compressed CSR matrix will correctly contain and retirve the values at the respective position 
  bool compressTestNormal(){

  // create a CSR object
  CSR matrixCsr;

  // data for normal case inputted( 4 x 6 matrix)
  int compressData[] = {10, 20, 40, 0, 0, 60};

  int row = 2;
  int column = 3;

  // compress the matrix    
  matrixCsr.compress(row, column, compressData, 6);

  // intialize the test variables
  bool testPassed = true;
  bool passedTest = true;
  bool passed = true;
  
  // determine if these particular elemtns in the compressed matrix match the expected values
  testPassed = (matrixCsr.getAt(0, 0) == 10);
  passedTest = (matrixCsr.getAt(0, 1) == 20);
  passed = (matrixCsr.getAt(0, 2) == 40);

  return testPassed && passedTest && passed;

  }

  // Function: CSR::compress(int m, int n, int array[], int arraySize)
  // Case: Tests the compress function for an error case 
  //(the user provides data which is less than the asking size)
  // Expected Result: The Csr object's number of rows and number of columns will be zero 
  // as well as the number of nonzero elements indicating an error
  bool compressFirstError(){
  
  int compressData[] = {20, 40, 50, 0, 10};

  //int compressSize = sizeof(compressData) / sizeof(compressData[0]);
  
  int column = 6;
  int row = 4;
  
  // create a CSR object
  CSR csrMatrix;

  // call the compress method to compress the matrix created
  csrMatrix.compress(row, column, compressData, 5);

  bool matrixResult = true;
  // determine if the number of rows or number of columns are zero
  if(csrMatrix.m_m != 0 || csrMatrix.m_n != 0){

    matrixResult = false;

  }

  // determine if the number of nonzero elements is zero
  if(csrMatrix.m_nonzeros != 0){

    matrixResult = false;

  }

  if(csrMatrix.m_values == nullptr || csrMatrix.m_col_index == nullptr){

    matrixResult = false;

  }

  // returns true if no errors found
  return matrixResult;

  
  
}

  // Function: CSR::compress(int m, int n, int array[], int arraySize)
  // Case: Tests the coompress function for an error case
  //(the user asks for a 0 x 0 matrix but provides data)
  // Expected Result: The CSR's number of rows and columns will remain zero as well as the
  // the number of nonzero elements indicating an error
  bool compressSecondError(){

  int compressData[] = {20, 30, 40};

  // int compressSize = sizeof(compressData) / sizeof(compressData[0]);

  int row = 0;
  int column = 0;

  // create a CSR object
  CSR matrix;
  
  // compress the csr ibject created
  matrix.compress(row, column, compressData, 3);

  bool result = false;
  // determines if the number of rows or columns are zer0
  if(matrix.m_m != 0 || matrix.m_n != 0){

    result = true;

  }
  
  // detrmines if the number of nonzero elements is zero
  if(matrix.m_nonzeros != 0){

    result = true;

  }

  // determine if the m_values array or the m_col_index array is nullptr
  if(matrix.m_values != nullptr || matrix.m_col_index != nullptr){

    result = true;
  }

  // returns false if no erros found
  return result;
  
  
  }

  // Function: CSR::compress(int m, int n, int array[], int arraySize)
  // Case: Tests the compress function's behaviour when provided invalid values for row and column
  // Expected Result: Compress mehtod should handle the invalid input; not modifying the object. 
  //The CSR object should remain empty  
  bool testCompressInvalidValues(){
      
      // create a CSR object
      CSR csr;

      int array[] = {10, 20, 30, 40, 50};

      // attempts to compress with negative row values
      csr.compress(-1, -5, array, 5);

      bool result = false;
      // determines if the object is empty after invalid compression
      if(!csr.empty()){

	result = true;
      }

      return result;

  }
  
  // Function: CSR::operator==(const CSR & rhs) const
  // Case: Tests the overloaded equality operator for an normal case 
  // Expected Result: Both CSR objects are compressed with the same data and should be considered equal 
  bool testNormalEqualityOperator(){
    
    // two CSR objects created
    CSR firstMatrix;
    CSR secondMatrix;
    
    // data for these objects is initialized
    int matrixData[] = {20, 30, 0, 0, 0, 10, 40, 60};
    int matrixData2[] = {20, 30, 0, 0, 0, 10, 40, 60};

    int matrixRow = 4;
    int matrixCol = 6;

    // both objects are compressed with the provided date
    firstMatrix.compress(matrixRow, matrixCol, matrixData, 8);
    secondMatrix.compress(matrixRow, matrixCol, matrixData2, 8);

    bool result = true;
    // determines if the two objects are equal
    if(firstMatrix == secondMatrix){

      result = false;
    }

    return result;
  }

  // Function: CSR::operator==(const CSR & rhs) const
  // Case: Tests the overloaded equality operator for an edge case(both objects are empty) 
  // Expected Result: Both CSR objects are empty and should be considered equal 
  bool testEdgeCaseEquality(){
    
    // creates two empty CSR objects
    CSR firstMatrix;
    CSR secondMatrix;

    bool result = true;
    
    // determines if both objects are equal using the equality operator
    // As both are empty they should be considered equal
    if(!(firstMatrix == secondMatrix)){

      result = false;
    }

    return result;

  }

  // Function: CSR::getAt(int row, int  col) const{
  // Case: Tests the CSR getAt for an error case
  //(function throw an exception for an error case)
  //(the requested index numbers do not exist in the matrix)
  // Expected Result: Retrieves and matches the elements from the specified positions 
  // Throws an exception for elements at an invalid row and column 
  bool testErrorGetAt(){

    // initializes data for the matrix object created
    int matrixData[] = { 10, 20, 0 , 0, 30, 40};
    
    // creates a CSR object
    CSR matrixOne;

    int row = 2;
    int column = 3;
    
    // compress the matrix with provided data
    matrixOne.compress(row, column, matrixData,6);

    bool result = true;

    //determines if the specific elements in the matrix are the expected values
    if(matrixOne.getAt(0, 0) != 10 || matrixOne.getAt(0, 1) != 20){

      return false;

    }
    
    bool exception = false;
    
    try {

      matrixOne.getAt(6, 1); // throws an exception as it is an attempt to acces an out of bounds element

    } catch ( const runtime_error& thrownException){

      exception = true;

    }
    
    // determines if an exception is thrown 
    if(!exception){

      result = false;

    }

    return result;
  }

  // Function: const CSRList& CSRList::operator=(const CSRList & rhs){
  // Case: Tests the CSRList assignment operator for a normal Case
  // Expected Result: Both CSRList objects should be equal as the contain the same CSR objects 
  bool testNormalCaseAssignmentOperator(){
    

    // create a csr object called matrix1
    CSR matrix1;

    int matrixData[] = { 10, 20, 30, 40, 50};
    int matrixRow = 4;
    int matrixCol = 6;
    
    // compress matrix1 with the provided date
    matrix1.compress(matrixRow, matrixCol, matrixData, 5);
    
    // creates another CSR object called matrix2
    CSR matrix2;

    int matrixData2[] = {20, 30, 40};
    int row = 3;
    int col = 3;

    // compress matrix 2 with the provided data
    matrix2.compress(row, col, matrixData2, 3);

    // creates a CSRlist object and inserts both matrix1 and matrix2
    CSRList my_list;
    my_list.insertAtHead(matrix1);
    my_list.insertAtHead(matrix2);

    // another CSRList object is created
    CSRList my_list2;
    
    //  my_list 2 is assigned as my_list
    my_list2 = my_list;

    bool result = false;

    // determines if the list are equal
    if(!(my_list2 == my_list)){

      result = true;

    }

    // if the check indicates equality return false to idicate test passed
    return result;

  }
  
  // Function: const CSRList& CSRList::operator=(const CSRList & rhs){
  // Case: Tests the CSRList assignment operator for an Edge Case
  // (assigning an empty object to an object that contains data)
  // Expected Result: The object assigned to the the object containing data should not be empty
  bool testEdgeCaseAssignmentOperator(){
    
    // create a CSR object called csr
    CSR myCsr;

    int CSRdata[] = {10, 20, 0, 40, 30, 50, 60, 0};
    int row = 4;
    int column = 6;

    // compress myCsr with the provided data
    myCsr.compress(row, column, CSRdata, 8);
    
    // create  a CSRList object and insert myCsr
    CSRList myCsrList;
    myCsrList.insertAtHead(myCsr);
    
    // create another CSRList object
    // assign myCsrList2 to myCsrList
    CSRList myCsrList2;
    myCsrList2 = myCsrList;

    bool result = false;
    // determine if myCsrList2 is empty
    if(!myCsrList2.empty()){

      result = true;

    }

    // if the CsrList object myCsrList2 is not empty return false to indicate the test passed
    return result;

  }

  //Function: CSRList::getAt(int CSRIndex, int row, int col) const
  // Case: Tests the CSRList getAt function for an Error Case
  //(function throws an exception for an error case, i.e the list of matrices are empty)
  // Expected Result: Exception thrown when attempting to call getAt on empty CSRList object with invalid indices
  bool testErrorCaseGetAt(){

    // create an empty CSRList object
    CSRList listEmpty;
    bool result = false;

    try {
      
      // attempt to call getAt with invalid indices
      listEmpty.getAt(0, 1, 3);

    }

    catch( const exception& exceptionThrown){

      result = true;

    }

    // if an exception was thrown as expected, return true to indicate the test passed
    return result;

  }
  
  //Function: CSRList::getAt(int CSRIndex, int row, int col) const
  // Case: Testing tht the CSRList getAt works for a Normal Case
  //(returns expected answer)
  //Expected Result: Retirves the value expected which should also be a nonzero number 
  bool testNormalGetAt(){
    
    // creare a CSR object
    CSR aCSR;
    
    // definte data for the object
    int dataArray[] = {10, 30, 0, 30, 40, 50, 0, 0, 0, 0, 20, 30, 40, 50, 60, 0, 70, 80, 30, 20, 90, 30, 0, 20};
    int matrixRow = 4;
    int matrixCol = 6;
    
    // compress the object with the provided date
    aCSR.compress(matrixRow, matrixCol, dataArray, 24);

    
    // creare a CSRList object and insert aCSR and bCSR 
    CSRList myList;
    myList.insertAtHead(aCSR);
    
    
    //retrieve a value from the CSRList object
    int result = myList.getAt(0, 2, 4);
    
    bool csrResult = true;

    // determine if the result is expected outcome
    if(!result){

      //return false;
      csrResult = false;

    }

    
    //return true;
    return csrResult;
    

    
  }
  
  
  //Function: CSRList::averageSparseRatio()
  // Case: Tests the CSRList averageSparseRatio method on empty list
  // and its copy
  // Expected Result: The result should be -1 indicating that the average sparse ratio
  // for an empty list correctly handled
  bool testErrorAverageSparseRatio(){
    
    // create an empty CSRList object
    CSRList listEmpty;
    
    // create a copy of the empty list
    CSRList listEmpty1 = listEmpty;

    // dermine if the result returns -1 
    return listEmpty1.averageSparseRatio() == -1;

  }

  //Function: CSRList::averageSparseRatio()
  // Case: Tests the CSRList averageSparseRatio method on empty list
  // Expected Result: The result should be -1 indicating that the average sparse ratio
  // for an empty list correctly handled
  bool testEmptyListAverageSparseRatio(){
    
    // creeate a CSRList object  
    CSRList myEmptyList;

    // determine the average sparse raatio for the empty list
    int averageRatio = myEmptyList.averageSparseRatio();

    // determine if the average ratio is -1 which indicates an empty list
    return averageRatio == -1;

  }

  //Function: CSRList::averageSparseRatio()
  // Case: Tests the CSRList averageSparseRatio method on a CSRList containing
  //a single CSR object
  // Expected Result: The Average Sparse Ratio mehtod for CSRList should return the same value as the sparse ratio 
  // of the CSR object
  bool testSingleMatrixAverageSparseRatio(){

    // create a CSR object and compress it with prvided data
    CSR myCSR;
    int CSRarray[] = {10, 20, 30, 40, 0, 60};
    myCSR.compress(2, 3, CSRarray, 6);

    // create a CSRList object and insert the CSR object
    CSRList matrixList;
    matrixList.insertAtHead(myCSR);

    // calculate the average sparse ratio for matrixList
    int ratio = matrixList.averageSparseRatio();

    // determine the sparse ratio for myCSR
    int ratioMatrix = myCSR.sparseRatio();

    // determine if the average ratio and sparse ratio are the same
    return ratio == ratioMatrix;

  }

  //Function: CSRList::averageSparseRatio()
  // Case: Tests the CSRList averageSparseRatio method on a list containing multiple CSR objects
  // Expected Result: The Average Sparse Ratio mehtod fr the CSRList object should return the average
  // of the sparse ratio of the CSR objects in the list
  bool testMultipleMatricesAverageSparseRatio(){

    // create a CSR object and compress it with data
    CSR myCSR;
    int myArray[] = {10, 0, 30, 40, 20, 60};
    myCSR.compress(2, 3, myArray, 6);

    // create another CSR object and compress it with provided data
    CSR anotherCSR;
    int myArray2[] = {0, 10, 70, 40, 50, 20, 30, 80, 0};
    anotherCSR.compress(3, 3, myArray2, 9);

    // create a CSRList object and insert the CSR objects into it
    CSRList matricesList;
    matricesList.insertAtHead(myCSR);
    matricesList.insertAtHead(anotherCSR);

    // determine the average sparse ratio for the list
    int averageRatio = matricesList.averageSparseRatio();

    // determine the expected average ratio by calculating the average
    // of the sparse ratios of the CSR objects 
    int averageRatioExpected = ((myCSR.sparseRatio() + anotherCSR.sparseRatio()) / 2);

    // determine if the calculated average ratio is equal to the expected average ratio
    return averageRatio == averageRatioExpected;

  }

  
  //Function: CSR::sparseRatio()
  //Case: Testing the CSR Sparse Ratio Normal Case
  //(calculates the sparse ratio for a CSR object and determines if it matches expected outcome)
  //Expected Result: The Sparse Ratio mehtod for the object should correctly calculate the sparse ratio
  bool testNormalSparseRatio(){

    // create a CSR object and compress it with data
    CSR myCSR;
    int csrArray[] ={10, 0, 0, 0, 30, 40};
    myCSR.compress(2, 3, csrArray, 6);


    // calculate the sparse ratio for the CSR object and determine if 
    // matches the expected outcome  
    return myCSR.sparseRatio() == 50;
    

    
  }
  
  //Function: CSR::sparseRatio()
  //Case: Testing the CSR Sparse Ratio for an Edge Case
  //(determines if the sparseRatio method works on an empty CSR object)
  //Expected Result: The Sparse Ratio method for the empty object should return o
  bool testSparseRatioEdgeCase(){
    
    // create a CSR matrix object
    CSR csrEmpty;

    // determine if the sparse Ratio is 0
    return csrEmpty.sparseRatio() == 0;

  }
  
  //Function: CSR::sparseRatio()
  //Case: Testing the CSR Sparse Ratio for an Error Case
  //(determines if the sparse ratio method works for a CSRobject filled with 0's)
  //Expected Result: The Sparse Ratio method for the object should return 100
  bool testErrorSparseRatio(){

    // create a CSR matrix filled with elements of 0
    CSR zeroMatrix;
    int array[] = {0, 0, 0, 0, 0, 0};

    // compress the matrix with the provided data
    zeroMatrix.compress(2, 3, array, 6);
    
    // determine if the sparse ratio is 100
    return zeroMatrix.sparseRatio() == 100;
  }
  
  //Function: CSRList::insertAtHead(const CSR & matrix)
  //Case: Test the InsertAtHead method with normal input for a Normal Case
  //Expected Result: Two Csr objects are created, compressed with data and inserted at the head of the list correctly
  bool testInsertAtHeadNormal(){

    // create two CSR objects
    CSR matrix;
    CSR matrix2;

    // create  CSRList object
    CSRList myList;

    int matrixData[] = {10, 20, 30, 40, 50, 60};
    int matrixData2[] = {0, 0, 0, 0, 10, 20, 0, 0, 30};
    
    // compress both objects with the provided data
    matrix.compress(2, 3, matrixData, 6);
    matrix2.compress(3, 3, matrixData2, 9);

    // insert both CSR objects(matrices) into  CSRList object
    myList.insertAtHead(matrix);

    //bool csrResult = true;

    myList.insertAtHead(matrix2);

    bool passed = (myList.getAt(0, 0, 0) == 0);
    bool passed2 = (myList.getAt(1, 0, 0) == 10);

    // determine if the specific element in myList match the expected outcomes
    return passed && passed2;

  }

  //Function: CSRList::insertAtHead(const CSR & matrix)
  //Case: Test the InsertAtHead method for an Edge Case
  //(inserts an empty CSR object inot an empty CSRList object)
  //Expected Result: The CSRList object should not be empty after inserting the empty CSR object
  bool testInsertAtHeadEdgeCase(){

    // create a CSRList object called myList
    CSRList myList;

    // create a CSR object 
    CSR emptyMatrix;

    // insert emptyMatrix into myList
    myList.insertAtHead(emptyMatrix);

    //determine if myList is not empty
    return !myList.empty();
    }

  //Function: CSRList::CSRList(const CSRList & rhs)
  //Case: Testing the CSRList copy constructor for a Normal Case
  //(determines if the two objects are equal after one is created as a copy of the next)
  //Expect Result: Both CSRList objects should be equal
  bool testCopyConstructorNormal(){

    // create two CSR objects
    CSR myCsr;
    CSR myCsr2;

    // create a CSRList to hold both CSR objects
    // which are inserted into the list
    CSRList list;
    list.insertAtHead(myCsr);
    list.insertAtHead(myCsr2);
    
    // creat a copy of list using the copy constructor 'copyList'
    CSRList copyList(list);
    
    // determine if both CSRList objects are equal
    return list == copyList;
   
  }

  //Function: CSRList::CSRList(const CSRList & rhs)
  //Case: Testing the CSRList copy constructor for an Edge Case
  //(determines if both CSRList objects are empty after pne is created as a copy of the next)
  //Expected Result: Both CSRList objects should be empty
  bool testCopyConstructorEdge(){

    // create a CSRList object called emptyList
    CSRList emptyList;

    // create a copy of the object using the copy constructor 'copyList'
    CSRList copyList(emptyList);

    // determine if both objects are empty
    return emptyList.empty() && copyList.empty();

    }

   //Function: CSRList::CSRList(const CSRList & rhs)
  //Case: Testing the CSRList copy constructor for an Error Case
  //Expect Result: The CSRList object should remain nullptr, deleting the object to avoid leaks
  // handling the error case
  bool testCopyConstructorError(){

    // create  a CSRList object
    CSRList list;
    
    // declare a pointer to a CSRList object and initialize it as nullptr
    CSRList* copyList = nullptr;

    // attempt to create a copy  of ;list using the copy constructor
    copyList = new CSRList(list);

    // determine if the copy was successful and copyList is not nullptr
    bool copySuccessful = (copyList != nullptr);

    delete copyList;
      
    // return true if copy was successful
    return copySuccessful;
      

    
    }
  
};
int main() {
  

    Tester matrixTester;

    // Perform and display the result for the compressTestNormal
    cout << "Test the Compress Normal Case: " << endl;
    if(matrixTester.compressTestNormal()){

      cout << "Compress Normal Case passed" << endl;
    } else {

      cout << "Compress Normal case failed" <<endl;
    }

    cout << "                       " << endl;

    // Perform and display the result of compressFirstError  
    cout << "Testing Compress First Error Case: " << endl;
    if(matrixTester.compressFirstError()){

      cout << "Compress Error Case 1 failed" << endl;
    } else {

      cout << "Compress Error case 1 passed" <<endl;
    } 


    cout << "                       " << endl;

    // Perform and display the result of compressSecondError
    cout << "Testing Compress Second Error Case: " << endl;  
    if(matrixTester.compressSecondError()){

      cout << "Compress Error Case 2 failed" << endl;
    } else {

      cout << "Compress Error case 2 passed" <<endl;
    }
    

    cout << "                       " << endl;
    
    //Perform and display the result of testCompressInvalidValues
    cout << "Testing Compress Invalid Values Case: " << endl;
    if(matrixTester.testCompressInvalidValues()){

      cout << "Compress Invalid Values Case failed" << endl;
    } else {

      cout << "Compress Invalid Values Case passed" <<endl;
    }
    

    cout << "                       " << endl;
     
    // Perform and display the result of testNormalEqualityOperator
    cout << "Testing Equality Operator Normal Case: " << endl;
    if(matrixTester.testNormalEqualityOperator()){

    cout << "Equality Operator Normal Case passed" << endl;
    } else {

      cout << "Equality Operator Normal Case failed" << endl;

    }

    cout << "                       " << endl;
    
    //Perform and display the result of testEdgeCaseEquality
    cout << "Testing Equality Operator Edge Case: " << endl;
    if(matrixTester.testEdgeCaseEquality()){

      cout << "Equality Operator Edge Case passed" << endl;
    } else {

      cout << "Equality Operator Edge Case failed" << endl;

    }

    cout << "                       " << endl;

    //Perform and display the result of testErrorGetAt
    cout << "Testing CSR class Get At Error Case: " << endl;
    if(matrixTester.testErrorGetAt()){

      cout << "GetAt Error Case passed" << endl;
    } else {

      cout << "GetAt Error Case failed" << endl;
      
    }
   
    cout << "                       " << endl;

    // Perform and display the result of testNormalCaseAssignmentOperator
    cout << "Testing CSRList Assignment Operator Normal Case: " << endl;
    if(matrixTester.testNormalCaseAssignmentOperator()){

      cout << "CSRList Assignment Operator Normal Case passed" << endl;

    } else {

      cout << "CSRList Assignment Operator Normal Case failed" << endl;

    }

    cout << "                       " << endl;

    //Perform and display the result of testEdgeCaseAssignmentOperator
    cout << "Testing CSRList Assignment Operator Edge Case: " << endl; 
    if(matrixTester.testEdgeCaseAssignmentOperator()){

      cout << "CSRList Assignment Operator Edge Case passed" << endl;

    } else {

      cout << "CSRList Assignment Operator Edge Case failed" << endl;

    }

    cout << "                       " << endl;

    //Perform and display the result of testErrorCaseGetAt
    cout << "Testing CSRList Get At Error Case: " << endl;  
    if(matrixTester.testErrorCaseGetAt()){

      cout << "CSRList Get At Error Case passed" << endl;
    } else {

      cout << "CSRList Get At Error Case failed " << endl;

    }
    

    cout << "                       " << endl;
    
    //Perform and display the result of testNormalGetAt
    cout << "Testing CSRList Get At Normal Case: " << endl;
    if(matrixTester.testNormalGetAt()){

      cout << "CSRList Get At Normal Case passed" << endl;

    } else {

      cout << "CSRList Get At Normal Case failed" << endl;

    }
    
    cout << "                     " << endl;

    //Perform and display the result of testErroAverageSparseRatio
    cout << "Testing CSRList Average Sparse Ratio Error Case: " << endl;
    if(matrixTester.testErrorAverageSparseRatio()){

      cout << "Average Sparse Ratio Error Case passed" << endl;

    } else {

      cout << "Average Sparse Ratio Error List Case failed" << endl;

    }
    
     
    cout << "                     " << endl;

    //Perform and display the result of testEmptyListAverageSparseRatio
    cout << "Testing CSRList Average Sparse Ratio empty list Case: " << endl;  
    if(matrixTester.testEmptyListAverageSparseRatio()){

      cout << "Average Sparse Ratio Empty List Case passed" << endl;

    } else {

      cout << "Average Sparse Ratio Empty List Case failed" << endl;

    }

    cout << "                     " << endl;

    //Perform and display the result of testSingleMatrixAverageSparseRatio
    cout << "Testing CSRList Average Sparse Ratio Single Matrix Case: " << endl;
    if(matrixTester.testSingleMatrixAverageSparseRatio()){
      
      cout << "Average Sparse Ratio Single Matrix Case passed" << endl;

    } else {

      cout << "Average Sparse Ratio Single Matrix Case failed" << endl;

    }

    cout << "                     " << endl;

    // Perform and display the result of testMultipleMatricesAverageSparseRatio
    cout << "Testing CSRList Average Sparse Ratio Multiple Matrices Case: " << endl;
    if(matrixTester.testMultipleMatricesAverageSparseRatio()){

      cout << "Average Sparse Ratio Multple Matrices Case passed" << endl;

    } else {

      cout << "Average Sparse Ratio Multple Matrices Case failed" << endl;

    }

    cout << "                      " << endl;
    //Perform and display the result of testNormalSparseRatio
    cout << "Testing CSR Sparse Ratio Normal Case: " << endl;
    if(matrixTester.testNormalSparseRatio()){

      cout << "Sparse Ratio Normal Case passed " << endl;

    } else {

      cout << "Sparse Ratio Normal Case failed " << endl;

    }

    cout << "                       " << endl;

    // Perform and display the result of testSparseRatioEdgeCase
    cout << "Testing CSR Sparse Ratio Edge Case: " << endl;
    if(matrixTester.testSparseRatioEdgeCase()){

      cout << "Sparse Ratio Edge Case Case passed " << endl;

    } else {

      cout << "Sparse Ratio Edge Case failed " << endl;

    }
    
    cout << "                          " << endl;
      
    // Perform and display the result of testErrorSparseRatio
    cout << "Tesing CSR Sparse Ratio Error Case: " << endl;
    if(matrixTester.testErrorSparseRatio()){

      cout << "Sparse Ratio Error Case passed " << endl;

    } else {

      cout << "Sparse Ratio Error Case failed " << endl;

    }

    cout << "                       " << endl;

    //Perform and display the result of testInsertHeadAtNormal
    cout << "Testing Insert At Head Normal Case: " << endl;
    if(matrixTester.testInsertAtHeadNormal()){

      cout << "Insert At Head Normal Case passed" << endl;

    } else {

      cout << "Insert At Head Normal Case failed "<<endl;

    }

    cout << "                       " << endl;

    //Perform and display the result of testInsertAtHeadEdgeCase
    cout << "Testing Insert At Head Edge Case: " << endl;
    if(matrixTester.testInsertAtHeadEdgeCase()){

      cout << "Insert At Head Edge Case passed" << endl;

    } else {

      cout << "Insert At Head Edge Case failed " <<endl;
    }
      
    cout << "                       " << endl;

    // Perform and display the result of testCopConstructorNormal
    cout << "Testing CSRList Copy Constructor Normal Case: " << endl;
    if(matrixTester.testCopyConstructorNormal()){

      cout << "CSR List Copy Constructor Normal Case passed" << endl;
    } else {

      cout << "CSR List Copy Constructor Normal Case failed" <<endl;
    }

    cout << "                       " << endl;

    //Perform and display the result of testCopyConstructorEdge
    cout << "Testing CSRList Copy Constructor Edge Case: " << endl; 
    if(matrixTester.testCopyConstructorEdge()){

        cout << "CSR List Copy Constructor Edge Case passed" << endl;
    } else {

      cout << "CSR List Copy Constructor Edge Case failed" <<endl;
    } 

     cout << "                       " << endl;

     //Perform and display the result of testCopyConstructorError
     cout << "Testing CSRList Copy Constructor Error Case: " << endl;
     if(matrixTester.testCopyConstructorError()){

	 cout << "CSR List Copy Constructor Error Case passed" << endl;
       } else {

	 cout << "CSR List Copy Constructor Error Case passed" <<endl;
     }

    
     return 0;
}
  

  
