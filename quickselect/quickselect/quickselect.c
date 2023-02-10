#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

// A translation from pseudocode to C code
// https://en.wikipedia.org/wiki/Quicksort
// Hoare's partition scheme
// Divides array into two partitions
int partition ( int size, int array[size] ) {

    // Pivot value
    int pivot = array[ (size-1)/2 ]; // The value in the middle of the array

    // Left index
    int left = -1;

    // Right index
    int right = size;

    while (true) {

        // Move the left index to the right at least once and while the element at
        // the left index is less than the pivot
        do left++; while (array[left] < pivot);

        // Move the right index to the left at least once and while the element at
        // the right index is greater than the pivot
        do right--; while (pivot < array[right]);

        // If the indices crossed, return
        if ( right<=left ) return right;

        // Swap the elements at the left and right indices
        int temp = array[left];
        array[left] = array[right];
        array[right] = temp;

    }
}

/*Making method for quick_select
    "The algorithm is similar to QuickSort. The difference is, instead of recurring for both sides (after finding pivot), 
    it recurs only for the part that contains the k-th smallest element. The logic is simple, if index of the partitioned 
    element is more than k, then we recur for the left part. If index is the same as k, we have found the k-th smallest 
    element and we return. If index is less than k, then we recur for the right part. This reduces the expected complexity 
    from O(n log n) to O(n), with a worst-case of O(n^2)."
    https://www.geeksforgeeks.org/quickselect-algorithm/
*/ 

int quickselect (int length, int array[length], int target_loc){
    //find the partition index
    int part_index = partition(length, array);

    //return the partition if it equals the target
    if(part_index == target_loc){
        return array[part_index];

    //search the left if the partition is greater than the target
    } else if(part_index>target_loc){
        return quickselect(part_index+1, array, target_loc);

    //search the right if the partition is less than the target
    } else {
        return quickselect(length-(part_index+1), array+(part_index+1), target_loc-(part_index+1));
    }
}

//I hate this but I couldnt figure out the edge case
void quicksort (int size, int array[size]){
    	if(size==1)
		    return;
	    else {
		int pivot_index = partition ( size, array);
		quicksort(pivot_index+1, array); //left half
		quicksort(size-(pivot_index+1), array+pivot_index+1); //right half
		//array+pivot_index+1 is the same as &array[pivot_index+1];
	}

}

//using quicksort and returning the element 
int lazy_quickselect (int length, int array[length], int target_loc){
    quicksort(length, array);
    return array[target_loc];
}

int main(int argc, char* argv[])
{

    FILE* inputFile = fopen(argv[1], "r");
    if (!inputFile) {
        perror("fopen failed");
        return EXIT_FAILURE;
    }

    char buf[256];

    char* len_string = fgets(buf, 256, inputFile);
    int len = atoi(len_string);
    char* kth_string = fgets(buf, 256, inputFile);
    int kth = atoi(kth_string);
    fgets(buf, 256, inputFile);

    int* array = calloc( len, sizeof(int) );

    for (int i=0; i<len; i++) {
        char* int_string = fgets(buf, 256, inputFile);
        array[i] = atoi(int_string);
    }
    //all of the the stuff above is taking in the text file and reading in the file 


    printf("%d", quickselect ( len, array, kth ));

    free(array);

    return EXIT_SUCCESS;

}
