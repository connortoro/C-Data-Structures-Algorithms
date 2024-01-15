/**********************************
CS311 Kazumi Slott

Your name: Connor Toro
Your program number: 31
Hours spent: 2
Describe any difficulties here: no major difficulties
*********************************/

/********************************************************************
//Make your own test client and test your functions thorougly.
//You will submit this header file only. My test client will test your functions.
********************************************************************/


//What is the runtime complexity of this algorithm? O(n^3)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above.
int algoA(const int a[], int sz)//Don't change the function headers
{
    int max = 0;
    int sum = 0;

    //loop through all sub array sizes
    for(int subArrSize = 1; subArrSize <= sz; subArrSize++) {

        //loop through all start indexes
        for(int start = 0; start <= sz - subArrSize; start++) {
            sum = 0;

            //sum subarr from start to start+subarrsize
            for(int i = start; i < start + subArrSize; i++) {
                sum += a[i];
            }
            if(sum > max) {
                max = sum;
            }
        }
    }
    return max;
}

//What is the runtime complexity of this algorithm? O(n^2)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoB(const int a[], int sz)
{
    int max = 0;
    int sum = 0;

    //loop over all starting indexes
    for(int start = 0; start < sz; start++) {
        sum = 0;

        //loop from start index to end of array
        for(int i = start; i < sz; i++) {
            sum += a[i];
            if(sum > max) {
                max = sum;
            }
        }
    }
    return max;
}

//What is the runtime complexity of this algorithm? O(n)
//Even if you cannot get this function to work, you may guess the complexity and provide your answer above..
int algoC(const int a[], int sz)
{
    int max = 0;
    int sum = 0;

    //loop over all starting indexes
    for(int start = 0; start < sz; start++) {
        sum = 0;

        //loop from start index to end of array
        for(int i = start; i < sz; i++) {
            sum += a[i];
            if(sum < 0) break;
            if(sum > max) max = sum;
        }
    }
    return max;
}
