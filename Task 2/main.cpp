#include "BST.h"

#include <iostream>
#include <iomanip>
#include <vector>
#include <map>
#include <algorithm>

constexpr int vecPrintWidth = 4;
constexpr char line[] = "=====================================";
constexpr int sections = 8;
constexpr int totalTests = 30;


void printSectionHead(int sectionNo)
{
    std::cout << std::endl << line << " Section " << sectionNo << "/" << sections << " " << line << std::endl;
}

void insertValues(BST<int>& bst, std::vector<int> values)
{
    std::cout << "Inserting values: ";
    for (int v : values)
    {
        std::cout << std::setw(vecPrintWidth) << v;
        bst.insert(v);
    }
    std::cout << std::endl;
}

int testGetMinMax(int sectionNo)
{
    printSectionHead(sectionNo);
    // Insert{0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15}; -> getMin() == -71 -> getMax() == 61
    constexpr int expectedMin = -71;
    constexpr int expectedMax = 61;

    int result = 0;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst;
    insertValues(bst, { 0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15 });

    std::cout << "Testing getMin()... ";
    int bstMin = bst.getMin();
    if (bstMin == expectedMin)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\tgetMin returned " << bstMin << ". " << expectedMin << " expected.";
    }

    std::cout << std::endl << "Testing getMax()... ";
    int bstMax = bst.getMax();
    if (bstMax == expectedMax)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\tgetMax returned " << bstMax << ". " << expectedMax << " expected.";
    }
    std::cout << std::endl;

    return result;  // Tests in function: 2
}

int testFind(int sectionNo)
{
    printSectionHead(sectionNo);
    // Insert{0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15}; -> find(5) == True -> find(-72) == False
    constexpr int shouldExist = 5;
    constexpr int shouldNotExist = -72;

    int result = 0;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst;
    insertValues(bst, { 0, 5, 3, 41, 61, -6, -1, -71, -12, -51, 1, 51, -15 });

    std::cout << "Testing find(" << shouldExist << ")... ";
    if (bst.find(shouldExist) == true)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t" << shouldExist << " not found.";
    }

    std::cout << std::endl << "Testing find(" << shouldNotExist << ")... ";
    if (bst.find(shouldNotExist) == false)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t" << shouldNotExist << " found but not expected.";
    }
    std::cout << std::endl;

    return result;  // Tests in function: 2
}

int testGetHeight(int sectionNo)
{
    printSectionHead(sectionNo);
    int result = 0;

    // Tomt träd -> getHeight() == -1

    std::cout << "Creating new BST" << std::endl;
    constexpr int heightEmpty = -1;
    BST<int> bst;

    std::cout << "Testing getTreeHeight() on empty BST... ";
    if (bst.getTreeHeight() == heightEmpty)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\tempty BST should return " << heightEmpty << ".";
    }
    std::cout << std::endl;

    // Insert{3, 2, 1, 4, 5, 6, 7} -> getHeight() == 4
    constexpr int heightInsert1 = 4;
    insertValues(bst, { 3, 2, 1, 4, 5, 6, 7 });

    std::cout << "Testing getTreeHeight() after insert... ";
    int bstHeight = bst.getTreeHeight();
    if (bstHeight == heightInsert1)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t returned " << bstHeight << " but should return " << heightInsert1 << ".";
    }
    std::cout << std::endl;

    // -> Insert{16, 15, 14, 13, 12, 11, 10, 8, 9} -> getHeight() == 13
    constexpr int heightInsert2 = 13;
    insertValues(bst, { 16, 15, 14, 13, 12, 11, 10, 8, 9 });

    std::cout << "Testing getTreeHeight() after additional insert... ";
    bstHeight = bst.getTreeHeight();
    if (bstHeight == heightInsert2)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t returned " << bstHeight << " but should return " << heightInsert2 << ".";
    }
    std::cout << std::endl;

    return result;  // Tests in function: 3
}

bool walkingTest(std::string order, std::vector<int> walk)
{
    int result = 0;
    std::cout << "Testing " << order << " on empty BST... ";
    if (walk.empty() == true)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t" << order << " on empty BST should return empty vector.";
    }
    std::cout << std::endl;
    return result;  // Tests in function: 1 (accounted for in testTreeTraversal)
}

bool walkingTest(std::string order, std::vector<int> walk, std::vector<int> correct)
{
    int result = 0;
    std::cout << "Testing " << order << "... ";
    if (walk == correct)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t" << order << " should return";  // width 8 and 14
        for (int e : correct)
            std::cout << std::setw(vecPrintWidth) << e;
        constexpr size_t baseWidth = 8 + 14;  // to line up output of vectors
        std::cout << std::endl << std::setw(baseWidth + order.size()) << "but your implementation returned";
        for (int e : walk)
            std::cout << std::setw(vecPrintWidth) << e;
    }
    std::cout << std::endl;
    return result;  // Tests in function: 1 (accounted for in testTreeTraversal)
}

// Test: PreOrderWalk
// Test: InOrderWalk
// Test: PostOrderWalk
int testTreeTraversal(int sectionNo)
{
    printSectionHead(sectionNo);
    int result = 0;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst;
    // Tomt träd -> PreOrderWalk() == empty list/vector
    result += walkingTest("preOrderWalk()", bst.preOrderWalk());
    // Tomt träd -> InOrderWalk() == empty list/vector
    result += walkingTest("inOrderWalk()", bst.inOrderWalk());
    // Tomt träd -> PostOrderWalk() == empty list/vector
    result += walkingTest("postOrderWalk()", bst.postOrderWalk());

    // Insert{3, 2, 1, 4, 5, 6, 7} -> PreOrderWalk() == {3, 2, 1, 4, 5, 6, 7}
    insertValues(bst, { 3, 2, 1, 4, 5, 6, 7 });
    result += walkingTest("preOrderWalk()", bst.preOrderWalk(), { 3, 2, 1, 4, 5, 6, 7 });
    // Insert{3, 2, 1, 4, 5, 6, 7} -> InOrderWalk() == {1, 2, 3, 4, 5, 6, 7}
    result += walkingTest("inOrderWalk()", bst.inOrderWalk(), { 1, 2, 3, 4, 5, 6, 7 });
    // Insert{3, 2, 1, 4, 5, 6, 7} -> PostOrderWalk() == {1, 2, 7, 6, 5, 4, 3}
    result += walkingTest("postOrderWalk()", bst.postOrderWalk(), { 1, 2, 7, 6, 5, 4, 3 });


    // -> Insert{16, 15, 14, 13, 12, 11, 10, 8, 9} -> PreOrderWalk() == {3, 2, 1, 4, 5, 6, 7,16, 15, 14, 13, 12, 11, 10, 8, 9}
    insertValues(bst, { 16, 15, 14, 13, 12, 11, 10, 8, 9 });
    result += walkingTest("preOrderWalk()", bst.preOrderWalk(), { 3, 2, 1, 4, 5, 6, 7,16, 15, 14, 13, 12, 11, 10, 8, 9 });
    // -> Insert{16, 15, 14, 13, 12, 11, 10, 8, 9} -> InOrderWalk() == {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}
    result += walkingTest("inOrderWalk()", bst.inOrderWalk(), { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 });
    // -> Insert{16, 15, 14, 13, 12, 11, 10, 8, 9} -> PostOrderWalk() == {1, 2, 9, 8, 10, 11, 12, 13, 14, 15, 16, 7, 6, 5, 4, 3}
    result += walkingTest("postOrderWalk()", bst.postOrderWalk(), { 1, 2, 9, 8, 10, 11, 12, 13, 14, 15, 16, 7, 6, 5, 4, 3 });

    return result;  // Tests in function: 9
}


// Test: Remove
int testRemove(int sectionNo)
{
    printSectionHead(sectionNo);
    int result = 0;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst;

    /* Insert{3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9}
        -> Remove(12)
        -> PreOrderWalk() == {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 11, 10, 8, 9} AND PostOrderWalk() == {1, 2, 9, 8, 10, 11, 13, 14, 15, 16, 7, 6, 5, 4, 3} */
    insertValues(bst, { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 12, 11, 10, 8, 9 });
    constexpr int value1 = 12;
    std::cout << "Calling remove(" << value1 << ")... " << std::endl;
    bst.remove(value1);
    result += walkingTest("preOrderWalk()", bst.preOrderWalk(), { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 11, 10, 8, 9 });
    result += walkingTest("postOrderWalk()", bst.postOrderWalk(), { 1, 2, 9, 8, 10, 11, 13, 14, 15, 16, 7, 6, 5, 4, 3 });

    /* -> Remove(8)
        -> PreOrderWalk() == {3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 11, 10, 9} AND PostOrderWalk() == {1, 2, 9, 10, 11, 13, 14, 15, 16, 7, 6, 5, 4, 3} */
    constexpr int value2 = 8;
    std::cout << "Calling remove(" << value2 << ")... " << std::endl;
    bst.remove(value2);
    result += walkingTest("preOrderWalk()", bst.preOrderWalk(), { 3, 2, 1, 4, 5, 6, 7, 16, 15, 14, 13, 11, 10, 9 });
    result += walkingTest("postOrderWalk()", bst.postOrderWalk(), { 1, 2, 9, 10, 11, 13, 14, 15, 16, 7, 6, 5, 4, 3 });

    // For toRemove in {1, 3, 2, 5, 6, 4, 9, 11, 10, 14, 16, 15, 13, 7}:
    // 	Remove(toRemove)
    // GetHeight() == -1
    std::cout << "Now removing:";
    std::vector<int> toRemove = { 1, 3, 2, 5, 6, 4, 9, 11, 10, 14, 16, 15, 13, 7 };
    for (int rm : toRemove)
    {
        std::cout << std::setw(vecPrintWidth) << rm;
        bst.remove(rm);
    }
    constexpr int correctHeight = -1;
    std::cout << std::endl << "Calling getTreeHeight()... ";
    int height = bst.getTreeHeight();
    bool heightIsCorrect = (height == correctHeight);
    if (heightIsCorrect)
    {
        std::cout << "success!";
        result++;
    }
    else
        std::cout << "failed:" << std::endl << "\tgetTreeHeight() returned " << height << " but expected value is " << correctHeight;
    std::cout << std::endl;

    return result;  // Tests in function: 5
}

int testLargeInsertAndHeight(int sectionNo)
{
    printSectionHead(sectionNo);

    int result = 0;

    std::vector<std::vector<int>> unique_collections = {
        {
            114, 88, 104, 9, 54, 38, 90, 62, 119, 7, 102, 73, 20, 2, 6, 99, 126, 76, 92, 53, 83, 36, 18, 16, 58, 91, 63, 25, 93, 49, 42,
            121, 11, 65, 37, 47, 125, 124, 105, 51, 48, 28, 120, 30, 71, 12, 122, 68, 79, 111, 35, 55, 14, 31, 10, 82, 45, 13, 116, 118,
            41, 101, 96, 78, 95, 15, 123, 0, 23, 4, 66, 43, 60, 110, 80, 64, 5, 106, 56, 72, 67, 59, 117, 17, 61, 19, 32, 81, 85, 86, 22,
            98, 26, 113, 87, 44, 69, 50, 74, 84, 46, 40, 89, 115, 109, 34, 77, 107, 21, 1, 112, 103, 52, 94, 100, 33, 24, 27, 8, 75, 29,
            97, 108, 39, 57, 3, 70
        },
        {
            120, 8, 24, 42, 60, 136, 137, 35, 141, 109, 28, 87, 146, 31, 12, 64, 118, 17, 101, 98, 65, 39, 34, 80, 95, 5, 27, 36, 15, 112,
            25, 110, 59, 128, 94, 19, 129, 103, 140, 14, 32, 127, 67, 111, 2, 131, 102, 55, 135, 121, 70, 107, 145, 29, 117, 21, 6, 105,
            126, 16, 9, 96, 85, 75, 83, 33, 10, 143, 44, 66, 138, 125, 116, 63, 22, 37, 1, 74, 50, 92, 81, 51, 26, 0, 52, 144, 38, 93, 106,
            119, 99, 90, 108, 88, 53, 62, 115, 54, 130, 114, 79, 43, 18, 30, 40, 61, 69, 123, 47, 78, 134, 46, 4, 3, 86, 41, 84, 56, 23, 82,
            58, 20, 124, 113, 11, 132, 89, 97, 142, 57, 7, 48, 76, 139, 91, 77, 73, 45, 49, 100, 122, 133, 68, 104, 13, 71, 72
        },
        {
            125, 102, 141, 107, 76, 86, 27, 105, 147, 127, 88, 3, 108, 62, 103, 82, 155, 4, 78, 71, 61, 2, 40, 39, 11, 22, 16, 99, 28, 96,
            100, 111, 136, 158, 75, 42, 12, 98, 44, 48, 132, 14, 68, 31, 56, 120, 58, 60, 161, 10, 144, 17, 52, 166, 49, 117, 23, 101, 13,
            32, 43, 35, 150, 18, 55, 112, 137, 59, 146, 119, 149, 47, 64, 7, 104, 33, 142, 159, 97, 46, 80, 6, 5, 83, 94, 57, 121, 37, 15,
            8, 66, 30, 160, 19, 134, 38, 20, 72, 130, 153, 118, 157, 29, 89, 163, 69, 92, 50, 95, 113, 131, 138, 51, 73, 151, 87, 162, 93,
            156, 122, 34, 79, 123, 140, 109, 110, 63, 143, 148, 115, 91, 135, 165, 164, 85, 129, 1, 41, 124, 84, 74, 36, 0, 26, 152, 53, 67,
            24, 90, 70, 54, 126, 116, 133, 114, 139, 77, 65, 145, 9, 106, 25, 128, 154, 45, 81, 21
        },
        {
            130, 178, 107, 116, 93, 52, 35, 146, 21, 137, 64, 28, 1, 91, 33, 131, 90, 87, 32, 158, 54, 167, 73, 45, 82, 7, 120, 14, 95, 118,
            84, 67, 43, 172, 175, 96, 18, 174, 162, 65, 94, 68, 36, 115, 49, 88, 38, 176, 156, 6, 169, 40, 26, 100, 63, 122, 15, 109, 165,
            184, 2, 143, 103, 121, 80, 61, 148, 170, 152, 97, 42, 99, 150, 24, 66, 136, 160, 105, 44, 182, 60, 154, 25, 59, 124, 57, 168,
            177, 117, 145, 9, 157, 129, 69, 102, 125, 46, 111, 19, 30, 79, 17, 127, 39, 186, 161, 76, 153, 163, 81, 180, 155, 151, 126, 72,
            85, 20, 37, 135, 112, 22, 31, 185, 138, 179, 113, 16, 71, 83, 86, 10, 55, 110, 119, 106, 89, 77, 4, 134, 171, 139, 51, 123, 142,
            29, 74, 27, 53, 92, 104, 3, 132, 75, 141, 108, 181, 183, 159, 78, 149, 5, 140, 114, 8, 0, 47, 128, 62, 23, 56, 13, 12, 147, 58,
            133, 11, 48, 98, 34, 144, 70, 101, 166, 173, 164, 50, 41
        },
        {
            136, 31, 152, 18, 95, 111, 8, 113, 163, 204, 79, 55, 89, 120, 26, 106, 42, 119, 143, 17, 183, 108, 94, 38, 49, 28, 60, 123, 145,
            150, 168, 98, 34, 156, 100, 112, 170, 88, 109, 147, 84, 97, 184, 144, 37, 56, 187, 1, 76, 3, 180, 59, 63, 157, 4, 162, 185, 46,
            64, 68, 203, 12, 146, 82, 85, 51, 47, 58, 174, 102, 48, 10, 127, 125, 166, 92, 154, 198, 78, 148, 0, 53, 132, 90, 128, 107, 121,
            189, 93, 129, 193, 27, 179, 20, 137, 196, 131, 139, 195, 77, 200, 57, 9, 205, 33, 2, 140, 67, 87, 29, 178, 201, 61, 133, 181, 16,
            91, 194, 36, 86, 72, 83, 11, 62, 135, 172, 105, 197, 19, 153, 188, 30, 15, 50, 32, 41, 65, 164, 159, 199, 45, 134, 160, 126, 6, 7,
            116, 191, 13, 141, 169, 165, 35, 110, 71, 23, 5, 24, 75, 80, 167, 202, 130, 117, 81, 124, 115, 99, 44, 186, 142, 103, 74, 43, 52,
            73, 54, 173, 22, 151, 190, 21, 40, 176, 101, 149, 206, 192, 104, 158, 25, 114, 161, 182, 66, 14, 155, 70, 96, 177, 175, 118, 122,
            69, 39, 138, 171
        }
    };

    std::map<int, int> heights{ {127, 14}, {147, 16}, {167, 14}, {187, 14}, {207, 13} };

    for (std::vector<int> unique : unique_collections)
    {
        std::cout << "Creating new BST" << std::endl;
        BST<int> bst;
        insertValues(bst, unique);

        std::cout << "Testing getTreeHeight() after insert... ";
        int bstHeight = bst.getTreeHeight();
        if (bstHeight == heights[unique.size()])
        {
            std::cout << "success!";
            result++;
        }
        else
        {
            std::cout << "failed:" << std::endl << "\t returned " << bstHeight << " but should return " << heights[unique.size()] << ".";
        }
        std::cout << std::endl;
    }

    return result;  // Tests in function: 5  (= unique_collection.size())
}

int testDuplicates(int sectionNo)
{
    printSectionHead(sectionNo);
    std::cout << "Testing if BST rejects duplicates" << std::endl;
    int result = 0;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst1;

    insertValues(bst1, { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 });

    constexpr int correctHeight1 = 0;
    std::cout << std::endl << "Calling getTreeHeight()... ";
    int height = bst1.getTreeHeight();
    bool heightIsCorrect = (height == correctHeight1);
    if (heightIsCorrect)
    {
        std::cout << "success!";
        result++;
    }
    else
        std::cout << "failed:" << std::endl << "\tgetTreeHeight() returned " << height << " but expected value is " << correctHeight1;
    std::cout << std::endl;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst2;

    std::vector<int> unique{ 32, 43, 35, 150, 18, 55, 112, 137, 59, 146, 119, 149, 47, 64, 7, 104, 33, 142, 159, 97, 46, 80, 6, 5, 83, 94, 57, 121, 37, 15 };
    insertValues(bst2, unique);
    std::cout << "Inserting duplicates" << std::endl;
    insertValues(bst2, { 43, 146, 97, 59, 18 });

    int correctSize = unique.size();
    std::cout << std::endl << "Calling inOrderWalk()... ";
    int size = bst2.inOrderWalk().size();
    bool sizeIsCorrect = (size == correctSize);
    if (sizeIsCorrect)
    {
        std::cout << "success!";
        result++;
    }
    else
        std::cout << "failed:" << std::endl << "\t size of vector returned by inOrderWalk() was " << size << " but expected value is " << correctSize;
    std::cout << std::endl;

    return result;  // Tests in function: 2
}


int testOneLeg(int sectionNo)
{
    printSectionHead(sectionNo);
    std::cout << "Testing if BST handles decending and ascendign values correctly" << std::endl;
    int result = 0;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst1;

    std::vector<int> data{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    int heightSorted = data.size() - 1;
    insertValues(bst1, data);

    std::cout << "Testing getTreeHeight() after inserting decending numbers... ";
    int bstHeight = bst1.getTreeHeight();
    if (bstHeight == heightSorted)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t returned " << bstHeight << " but should return " << heightSorted << ".";
    }
    std::cout << std::endl;

    std::cout << "Creating new BST" << std::endl;
    BST<int> bst2;

    std::reverse(data.begin(), data.end());
    insertValues(bst2, data);

    std::cout << "Testing getTreeHeight() after inserting decending numbers... ";
    bstHeight = bst2.getTreeHeight();
    if (bstHeight == heightSorted)
    {
        std::cout << "success!";
        result++;
    }
    else
    {
        std::cout << "failed:" << std::endl << "\t returned " << bstHeight << " but should return " << heightSorted << ".";
    }
    std::cout << std::endl;

    return result;  // Tests in function: 2
}


int main()
{
    int testSuccesses = 0;

    std::cout << "+--------------------------------------------------------------------------------+" << std::endl;
    std::cout << "|                                   Testing BST                                  |" << std::endl;
    std::cout << "+--------------------------------------------------------------------------------+" << std::endl;


    testSuccesses += testGetMinMax(1);
    testSuccesses += testFind(2);
    testSuccesses += testGetHeight(3);
    testSuccesses += testOneLeg(4);
    testSuccesses += testDuplicates(5);
    testSuccesses += testTreeTraversal(6);
    testSuccesses += testRemove(7);
    testSuccesses += testLargeInsertAndHeight(8);


    std::cout << std::endl << line << " Summary " << line << std::endl;
    std::cout << testSuccesses << "/" << totalTests << " tests succeeded." << std::endl;

    return totalTests - testSuccesses;
}