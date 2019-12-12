void update(int idx, int val) 
{ 
    int blockNumber = idx / blk_sz; 
    block[blockNumber] += val - arr[idx]; 
    arr[idx] = val; 
} 
  
// Time Complexity : O(sqrt(n)) 
int query(int l, int r) 
{ 
    int sum = 0; 
    while (l<r and l%blk_sz!=0 and l!=0) 
    { 
        // traversing first block in range 
        sum += arr[l]; 
        l++; 
    } 
    while (l+blk_sz <= r) 
    { 
        // traversing completely overlapped blocks in range 
        sum += block[l/blk_sz]; 
        l += blk_sz; 
    } 
    while (l<=r) 
    { 
        // traversing last block in range 
        sum += arr[l]; 
        l++; 
    } 
    return sum; 
} 
  
// Fills values in input[] 
void preprocess(int input[], int n) 
{ 
    // initiating block pointer 
    int blk_idx = -1; 
  
    // calculating size of block 
    blk_sz = sqrt(n); 
  
    // building the decomposed array 
    for (int i=0; i<n; i++) 
    { 
        arr[i] = input[i]; 
        if (i%blk_sz == 0) 
        { 
            // entering next block 
            // incementing block pointer 
            blk_idx++; 
        } 
        block[blk_idx] += arr[i]; 
    } 
} 
 
