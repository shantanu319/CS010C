#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
using std::cout;
using std::endl;
using std::sort;

using std::clock_t;
const int CLOCKS_PER_MS = CLOCKS_PER_SEC / 1000; // clock per milliseconds

// This is the more modern way to do timings with the high resolution clock
// I'll provide an example
#include <chrono>
using std::chrono::duration_cast;
using std::chrono::high_resolution_clock;
using std::chrono::microseconds;
using std::chrono::steady_clock;
using std::chrono::time_point;

// If using C++ 14, this is better as constexpr
const int NUMBERS_SIZE = 50000;

// Provided by zybooks
int genRandInt(int low, int high)
{
  return low + rand() % (high - low + 1);
}

// Provided by zybooks
void fillArrays(int arr1[], int arr2[], int arr3[])
{
  for (int i = 0; i < NUMBERS_SIZE; ++i)
  {
    arr1[i] = genRandInt(0, NUMBERS_SIZE);
    arr2[i] = arr1[i];
    arr3[i] = arr1[i];
  }
}

int QPartition(int numbers[], int low, int high) //midpoint partition algorithm
{
  int midpoint = low + (high - low) / 2; 
  int pivot = numbers[midpoint]; 

  bool done = false;
  while (!done)
  {
    while (numbers[low] < pivot) //increment low index until it reaches the pivot
    {
      low++;
    }

    while (pivot < numbers[high]) //increment the high index until it reaches the pivot 
    {
      high--;
    }

    if (low >= high) //end loop if when low >= high 
    {
      done = true;
    }
    else //swapping numbers to sort them 
    {
      int swapHelper = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = swapHelper;

      low++;
      high--;
    }
  }
  return high;
}

int median(int a, int b, int c) //finds the median of the three numbers for quicksort median of three
{
  if ((b < a && a < c) || (c < a && a < b)) //checks if first param is median (middle of range)
  {
    return a;
  }
  else if ((a < b && b < c) || (c < b && b < a)) //if second param is median
  {
    return b;
  }
  else //otherwise third param is median
  {
    return c;
  }
}

int QPartitionM3(int numbers[], int low, int high) //partition using the median helper function and the median of the low, midpoint and high as the pivot 
{
  int midpoint = low + (high - low) / 2;
  int pivot = median(numbers[low], numbers[midpoint], numbers[high]);

  //process is the same as for midpoint quicksort (unsure how to combine both into one function), just using a difference pivot
  bool done = false;
  while (!done)
  {
    while (numbers[low] < pivot)
    {
      low++;
    }

    while (pivot < numbers[high])
    {
      high--;
    }

    if (low >= high)
    {
      done = true;
    }
    else
    {
      int swapHelper = numbers[low];
      numbers[low] = numbers[high];
      numbers[high] = swapHelper;

      low++;
      high--;
    }
  }
  return low;
}

void Quicksort_midpoint(int numbers[], int i, int k) //quicksort using midpoint partition
{
  if (i >= k) //base case, low >= high
  {
    return;
  }
  int partition = QPartition(numbers, i, k);
  Quicksort_midpoint(numbers, i, partition); //recursive call with partition
  Quicksort_midpoint(numbers, partition + 1, k); //recursive call with partition
}

void Quicksort_medianOfThree(int numbers[], int i, int k) //quicksort using median of three partition
{
  if (i >= k) //base case, low >= high
  {
    return;
  }
  int partition = QPartitionM3(numbers, i, k);
  Quicksort_medianOfThree(numbers, i, partition - 1); //recursive call with partition, using -1 scheme here because it would segfault if I used the same format as midpoint quicksort
  Quicksort_medianOfThree(numbers, partition, k); //recursive call with partition
}

void InsertionSort(int numbers[], int numbersSize) //insertion sort
{
  int i = 0;
  int j = 0;
  int swapVar = 0;

  for (i = 1; i < numbersSize; i++) //outer loop to set current element
  {
    j = i;
    while (j > 0 && numbers[j] < numbers[j - 1]) //inner loop to move to its correct spot in the sorted portion of array, swapping as needed 
    {
      swapVar = numbers[j];
      numbers[j] = numbers[j - 1];
      numbers[j - 1] = swapVar;
      j--;
    }
  }
}

// We can compare other sorts we've talked about
static void BubbleSort(int numbers[], int n);

static void MergeSort(int numbers[], int left, int right);

// A helper function that will let us know if we have sorted
// everything
static bool is_sorted(int numbers[], int numbersSize)
{
  if (numbersSize <= 0)
    return true;
  int last = numbers[0];
  for (int i = 0; i < numbersSize; ++i)
  {
    int curr = numbers[i];
    if (curr < last)
      return false;
    last = curr;
  }
  return true;
}

static void copy_vector_into_array(const std::vector<int> &source, int array[])
{
  for (int i = 0; i < static_cast<int>(source.size()); ++i)
  {
    array[i] = source[i];
  }
}

static void RadixSort(int numbers[], int size);

int main()
{
  std::vector<int> sample;
  sample.reserve(NUMBERS_SIZE);
  for (int i = 0; i < NUMBERS_SIZE; ++i)
  {
    sample.push_back(rand() % (NUMBERS_SIZE + 1));
  }

  int test_sizes[4] = {10, 100, 1000, 50000};
  int test_array[NUMBERS_SIZE];
  for (int i = 0; i < 4; ++i)
  {
    int size = test_sizes[i];
    cout << endl;
    cout << "-------------------- size " << size << " --------------------" << endl;

    //for all of the timing schemes, I used clock() since high_resolution_clock was causing problems

    // BUBBLE SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      BubbleSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start) / CLOCKS_PER_MS;
      cout << elapsedTime << " ms for bubble sort" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size)) ? "GOOD" : "BAD") << endl;
    }

    // MERGE SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      MergeSort(test_array, 0, size - 1);
      clock_t End = clock();
      int elapsedTime = (End - Start) / CLOCKS_PER_MS;
      cout << elapsedTime << " ms for merge sort" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size)) ? "GOOD" : "BAD") << endl;
    }

    // RADIX SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      RadixSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start) / CLOCKS_PER_MS;
      cout << elapsedTime << " ms for radix sort" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size)) ? "GOOD" : "BAD") << endl;
    }

    // QUICK SORT MIDPOINT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      Quicksort_midpoint(test_array, 0, size - 1);
      clock_t End = clock();
      int elapsedTime = (End - Start) / CLOCKS_PER_MS;
      cout << elapsedTime << " ms for quick sort using midpoints" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size)) ? "GOOD" : "BAD") << endl;
    }

    // QUICK SORT MEDIAN OF 3
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      Quicksort_medianOfThree(test_array, 0, size - 1);
      clock_t End = clock();
      int elapsedTime = (End - Start) / CLOCKS_PER_MS;
      cout << elapsedTime << " ms for quicksort using median of 3" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size)) ? "GOOD" : "BAD") << endl;
    }

    // INSERTION SORT
    {
      copy_vector_into_array(sample, test_array);
      clock_t Start = clock();
      InsertionSort(test_array, size);
      clock_t End = clock();
      int elapsedTime = (End - Start) / CLOCKS_PER_MS;
      cout << elapsedTime << " ms for insertion sort" << endl;

      cout << "Sort is " << ((is_sorted(test_array, size)) ? "GOOD" : "BAD") << endl;
    }

  }

  return 0;
}

static void BubbleSort(int numbers[], int n) //provided by profpat
{
  for (int i = 0; i < n - 1; ++i)
  {
    for (int j = 0; j < n - i - 1; ++j)
    {
      if (numbers[j] > numbers[j + 1])
      {
        std::swap(numbers[j], numbers[j + 1]);
      }
    }
  }
}

static void merge(int numbers[], int start, int mid, int end) //provided by profpat
{
  int start2 = mid + 1;

  // If the direct merge is already sorted
  if (numbers[mid] <= numbers[start2])
  {
    return;
  }

  // Two pointers to maintain start of both sub-arrays to merge
  while (start <= mid && start2 <= end)
  {

    // If element 1 is in right place
    if (numbers[start] <= numbers[start2])
    {
      start++;
    }
    else
    {
      int value = numbers[start2];
      int index = start2;

      // Shift all the elements between element 1
      // element 2, right by 1.
      while (index != start)
      {
        numbers[index] = numbers[index - 1];
        index--;
      }
      numbers[start] = value;

      // Update all the pointers
      start++;
      mid++;
      start2++;
    }
  }
}

static void MergeSort(int numbers[], int left, int right) //provided by profpat
{
  if (left < right)
  {
    int mid = (left + right) / 2;
    MergeSort(numbers, left, mid);
    MergeSort(numbers, mid + 1, right);
    merge(numbers, left, mid, right);
  }
}

static void RadixSort(int numbers[], int size) //provided by profpat
{
  // LOTS of assumptions here.  I assume all data are
  // postive integers;

  // I have to do passes based on the digits.  I stop
  // when I extract the largest digit
  int divisor = 1;
  bool more = true;
  for (int pass = 0; more; pass++)
  {
    // I need 10 buckets with a lot of room in them
    std::vector<std::vector<int>> buckets(10);
    for (int i = 0; i < 10; ++i)
      buckets[i].reserve(NUMBERS_SIZE);

    // I pull off the pass'th digit and use it to put a number
    // into a bucket.  To get it, I divide by 1, 10, 100, 1000
    // and then do a modulo
    more = false;
    for (int i = 0; i < size; ++i)
    {
      int digit = (numbers[i] / divisor) % 10;
      if (numbers[i] / divisor / 10 > 0)
        more = true;
      buckets[digit].push_back(numbers[i]);
    }
    divisor *= 10;

    // Copy the buckets back into numbers
    int index = 0;
    for (int i = 0; i < 10; ++i)
    {
      const std::vector<int> &bucket = buckets[i];
      for (int j = 0; j < static_cast<int>(bucket.size()); ++j)
      {
        numbers[index++] = bucket[j];
      }
    }
  }
}
