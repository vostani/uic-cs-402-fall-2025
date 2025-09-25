
#include "Sreten_Kljaic_project1.h"
#include "testing.h"

#include <iostream>
#include <algorithm>
#include <chrono>

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement the appropriate algorithms as described below.
 *   You must follow the specifications as written
 *   below (e.g., stability, in-place, etc.).
 *
 * - DO NOT MODIFY THE FUNCTION SIGNATURES!!!
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project1.h".
 *
 * - The file "testing.cpp" has various functions you can utilize to test
 *   your code. You can also add your own tests!
 *
 * - If you are working in a group, please modify the comments directly below.
 *
 */



/*** GROUP PROJECT ***/
// Please list ALL of your other group members as comments below.
//   Member 1
//   Member 2



/* Bubble Sort 
 *
 * 5 points
 * 
 * Algorithm: Continuously compare adjacent elements and swap them if necessary.
 *            This is a stable, in-place sorting algorithm. Your implementation must be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void bubble_sort(vector<T> &list, bool descending) {
    int size = list.size();
    if (size < 2) return;

    bool swapping = true;
    while (swapping) {
        swap = false;
        for (int i = 0; i < size-1; i++) {
            if (descending ? list[i] < list[i+1] : list[i] > [i+1]) {
                swap(list[i], list[i+1]);

                swapping = true;
            }
        }
    }
}














/* Selection Sort 
 *
 * 5 points
 * 
 * Algorithm: Continuously finds the minimium (or maximum) element in the list, 
 *            then swaps it with the first non-sorted element of the list.
 *            This is an unstable, in-place sorting algorithm. Your implementation must be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void selection_sort(vector<T> &list, bool descending) {
    int size = list.size();
    if (size < 2) return;

    for (int i = 0; i < size-1; i++) {
        int index = i;

        for (int j = i+1; i < size; j++) {
            if (descending ? list[j] > list[index] : list[j] < list[index]) {
                index = j;
            }
        }

        if (index != i) {
            swap(list[i], list[i+1]);
        }
    }
}





/* Insertion Sort 
 *
 * 5 points
 * 
 * Algorithm: Iterates through the list and inserts the current element into
 *            the correct sorted position of the prefix of the list.
 *            This is a stable, in-place sorting algorithm. Your implementation
 *            does not need to be in-place.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 * */
template<typename T>
void insertion_sort(vector<T> &list, bool descending) {
    int size = list.size();
    if (size < 2) return;

    for (int i = 1; i < size; i++) {
        T current = list[i];

        int j = i-1;
        while(j >= 0 && (descending ? list[j] < current : list[j] > current)) {
            list[j+1] = list[j];
            j--;
        }
        list[j+1] = current;
    }
}












/* Quicksort 
 *
 * 10 points
 * 
 * Algorithm: Sorts by first choosing a random pivot from the list, then 
 *            partitioning the list into two halves with respect to the 
 *            pivot, then recursing on each half.
 *            This is an unstable sorting algorithm. Not required to be
 *            implemented as an in-place sort.
 *            
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 * */
template<typename T>
void quicksort(vector<T> &list, bool descending) {
    if (list.size() < 2) return;

    unsigned int random = get_rand_index(list.size());
    swap(list[list.size()-1], list[random]);
}


/* Quick Partition
 *
 * Helper function for Quicksort. You will implement this to help with your
 * quicksort algorithm above.
 *
 */
template<typename T> 
vector<T>& quick_partition(vector<T> &list, bool descending) {
    return list;
}










/* Merge Sort 
 *
 * 10 points
 * 
 * Algorithm: Sorts the list by recursively sorting the left and right
 *            halves, then merging the two left and right halves together.
 *            This is a stable sorting algorithm. Not required to be implemented
 *            as an in-place sort.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 * */
template<typename T>
void merge_sort(vector<T> &list, bool decending) {
    int size = list.size();
    if (size < 2) return;

    int middle = size / 2;   
    vector<T> left(list.begin(),list.begin() + middle);
    vector<T> right(list.begin() + middle,list.end());
    merge_sort(left);
    merge_sort(right);

    int i = 0; j = 0; k = 0;

    while(i < left.size() && j < right.size()) {
        if (decending ? left[i] > right[j] : left[i] < right[j]) {
            list[k] = left[i];
            i++;
        } else {
            list[k] = right[j];
            j++;
        }
        k++;
    }

    while(i < size) {
        list[k] = left[i];
        i++;
        k++;
    }

    while(j < size) {
        list[k] = right[j];
        j++;
        k++;
    }
}












/* Bucket Merge Sort
 *
 * 20 points
 * 
 * Algorithm: Bucket Merge Sort we discussed in class. Works by
 *            partitioning the input list into small, fixed-length segments,
 *            sorting each of those segments using some fast algorithm, then
 *            merging each of the segments together.
 *            This is a stable, in-place sorting algorithm.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 *
 */
template<typename T>
void bucket_merge_sort(vector<T> &list, bool descending) {
    int size = list.size();
    int b_size = 16;

    for (int start = 0; start < size, start += b_size) {
        int end = min(start+b_size, size);

        for (int i = 1; i < size; i++) {
            T current = list[i];

            int j = i-1;
            while(j >= 0 && (descending ? list[j] < current : list[j] > current)) {
                list[j+1] = list[j];
                j--;
            }
            list[j+1] = current;
        }     
    }

    int step = bucket_size;
    while (step < size) {
        for (int first = 0; first + step < size; first += 2 * step) {
            int middle = first + step;
            int second = min(first + 2 * step, size);

            int i = first;
            int j = middle;

            while (i < j && j < second) {
                if (descending ? list[i] >= list[j] : list[i] <= list[j]) {
                    j++;
                } else {
                    swap(list[i], list[j]);
                    i++;
                }
            }
        }
        step *= 2;
    }
}



/* Binary Radix Sort
 *
 * 20 points
 *
 * Algorithm:
 *
 * Parameters: 
 *   vector<T> &list: reference to a list of type T.
 *                    IMPORTANT: this type T is assumed to be *integral*. It
 *                    can be any of the following integral types in C++:
 *                      - (unsigned) short int
 *                      - (unsigned) int
 *                      - (unsigned) long int
 */
template<Integral T> 
void binary_radix_sort(vector<T> &list, bool descending) {
    int size = list.size();
    if (size < 2) return;

    T max = *max_element(list.begin(), list.end());

    int n_bits = 0;
    while (max > 0) {
        max_val >>= 1;
        n_bits++;
    }

    for (int i = 0; i < n_bits; i++) {
        vector<T> zero, one;
        T mask = 1 << i;

        for (int j = 0; j < size; j++) {
            if ((list[j] & mask) == 0) { 
                zero.push_back(list[j]);
            } else {
                one.push_back(list[j]);
            }
        }

        list.clear();
        if (descending) {
            for (int k = 0; k < one.size(); k++) { 
                list.push_back(one[k]);
            }
            for (int k = 0; k < zero.size(); k++) { 
                list.push_back(zero[k]);
            }
        } else {
            for (int k = 0; k < zero.size(); k++) { 
                list.push_back(zero[k]);
            }
            for (int k = 0; k < one.size(); k++) { 
                list.push_back(one[k]);
            }
        }
    }
}


/* Your Hybrid Sort
 *
 * 25 points
 *
 * Algorithm: Your own custom Hybrid Sorting algorithm! Remember, a hybrid
 *            sort tries to take advantage of two (or more) sorting algorithms
 *            to speed up data processing.
 *
 * Parameters:
 *  vector<T> &list: reference to a list of type T. You can assume this type
 *                   has all of the normal binary comparison operators such
 *                   as <, >, ==, !=, etc.
 *  bool decending:  if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default)
 *
 */
template<typename T>
void my_hybrid_sort(vector<T> &list, bool descending) {
    int size = list.size();
    if (size < 2) return;

    if (size < 32) insertion_sort(list, descending);
    merge_sort(list, descending);
}



/* Base B Radix Sort 
 *
 * 25 Points
 *
 * Algorithm: Implement Radix Sort as discussed in class, but with
 *            respect to any unspecified base.
 *
 * Parameters: 
 *   vector<T> &list: reference to a list of type T.
 *                    IMPORTANT: this type T is assumed to be *integral*. It
 *                    can be any of the following integral types in C++:
 *                      - (unsigned) short int
 *                      - (unsigned) int
 *                      - (unsigned) long int
 *
 *   unsigned int base: the base with which to implement the radix sort. 
 *                      Note that base should be at least 2. The default
 *                      base is 10.
 *
 *   bool decending: if true, then sort in descending order; otherwise sort
 *                   in ascending order (the default).
 *
 *
 * Additional Information:
 *   - If you are enrolled in the graduate section of this course, you MUST
 *     implement this function (i.e., it counts towards your total grade).
 *
 *   - If you are enrolled in the undergraduate section of this course, this
 *     function is optional and worth extra credit.
 *
 *
 */
template<Integral T>
void radix_sort(vector<T> &list, unsigned int base, bool descending) {
    int size = list.size();
    if (size < 2) return;

    T max = *max_element(list.begin(), list.end());

    int n_digits = 0;
    while (max > 0) {
        max_val /= base;
        n_digits++;
    }

    for (int i = 0; i < n_digits; i++) {
        vector<T> buckets (base);
        T power = 1;

        for (int j = 0; i < size; j++) {
            int digit = (list[j] / power) % base;
            buckets[digit].push_back(list[j]);
        }

        list.clear();
        if (descending) {
            for (int k = base - 1; k >= 0; k--) {
                for (int v = 0; v < buckets[k].size(); v++) {
                    list.push_back(buckets[k][v]);
                }
            }
        } else {
            for (int k = 0; k < base; k++) {
                for (int v = 0; v < buckets[k].size(); v++) {
                    list.push_back(buckets[k][v]);
                }
            }
        }

        power *= base;
    }
}






int main() {
    /**** STUDENT CODE HERE ****/ 






    /**** END STUDENT CODE ****/

    /***** DO NOT MODIFY BELOW THIS LINE *****/
    /*** INSTRUCTIONS ***
     *
     * Before submitting your code: 
     *   - remove all code within the main function that you have written above the `do-not-modify` line;
     *   - uncomment all lines below that begin with "//".
     *
     */
    //vector<int> test_list {1, 2, 3, 4, 5};
    //bubble_sort(test_list);
    //selection_sort(test_list);
    //insertion_sort(test_list);
    //quicksort(test_list);
    //merge_sort(test_list);
    //bucket_merge_sort(test_list);
    //binary_radix_sort(test_list);
    //my_hybrid_sort(test_list);
    //radix_sort(test_list);


    return 0;
}









