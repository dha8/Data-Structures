/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */
template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    if(first[curDim]==second[curDim]) return first<second;
    return first[curDim] < second[curDim];
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    unsigned sumCur = 0;
    unsigned sumPot = 0;
    for(unsigned i=0;i<Dim;++i){
        sumCur += pow((target[i]-currentBest[i]),2);
        sumPot += pow((target[i]-potential[i]),2);
    }
    if(sumPot==sumCur) return potential < currentBest;
    return (sumPot < sumCur);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    // case 0: null points
    if(newPoints.empty()) return;
    // case 1: 
    for(auto p : newPoints) points.push_back(p);
    unsigned d = 0; // dimension
    unsigned a = 0;
    unsigned b = points.size()-1;

    // recursively calls quicksort until a==b in each call
    KD_helper(points,d,a,b);

}

// helper fxn for constructor. recursively calls quicksort until
// a>=b in each call.
template<int Dim>
void KDTree<Dim>::KD_helper(vector<Point<Dim>>& list, int d, int a, int b){
    if(a>=b) return;
    int k = (a+b)/2;  // get midpoint

    // partition to each side of median k
    quickSelect(list, d, a, b, k); 

    // recurse to the left
    KD_helper(list, (d+1)%Dim, a, k-1); 
    KD_helper(list, (d+1)%Dim, k+1, b); 
}

// helper fxn for quickSelect; refer to wikipedia quickselect page 
// returns : Idx of element @ pivotIndex
// partitions elems into 2: items left of resulting idx is smaller, and 
// right of resulting idx is bigger.
template<int Dim>
int KDTree<Dim>::partition(vector<Point<Dim>>& list, int left, int right, int pivotIndex, int d){
    Point<Dim> pivotValue = list[pivotIndex]; 
    
    // swap list[pivotIndex] and list[right]
    list[pivotIndex] = list[right];
    list[right] = pivotValue;

    int storeIndex = left;
    for(int i=left;i<right;++i){
        if(smallerDimVal(list[i], pivotValue, d)){
            // swap list[storeIndex] and list[i]
            Point<Dim> temp = list[i];
            list[i] = list[storeIndex];
            list[storeIndex] = temp;
            ++storeIndex;
        } 
    }
    // swap list[right] and list[storeIndex]
    list[right] = list[storeIndex];
    list[storeIndex] = pivotValue; // hasn't changed from line 5
    return storeIndex;
}

// returns the kth smallest element of list within range [a,b] inclusive
template<int Dim>
void KDTree<Dim>::quickSelect(vector<Point<Dim>>& list,int d, int a, int b, int k){
    if(a==b || list.empty()) return;
    
    int pivotIdx = (a+b)/2;
    pivotIdx = partition(list, a, b, pivotIdx, d);
    
    if(k < pivotIdx) quickSelect(list, d, a, pivotIdx-1, k); 
    else if(k > pivotIdx) quickSelect(list, d, pivotIdx+1, b, k); 
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    int d = 0;
    int a = 0;
    int b = points.size()-1;

    return NN_search(query,d,a,b);
}

template<int Dim>
Point<Dim> KDTree<Dim>::NN_search(const Point<Dim>& list,int d, int a, int b) const{
    if(a>=b) return points[a];
    int k = (a+b)/2;
    Point<Dim> curr = points[k];
    if(smallerDimVal(list,curr,d)){
        // now recurse
        Point<Dim> temp = NN_search(list, (d+1)%Dim, a, k-1);
        if(shouldReplace(list, temp, curr)) temp = curr;
        // calculate radius and compare w/ curr distance
        int r = 0;
        for(unsigned i=0;i<Dim;++i) r += pow((list[i] - temp[i]),2);
        int dist = pow((list[d] - curr[d]),2);
        if(dist < r){
            Point<Dim> newCurr = NN_search(list, (d+1)%Dim, k+1, b);
            if(shouldReplace(list, temp, newCurr)) temp = newCurr;
        }
        return temp;
    }else{
        Point<Dim> temp = NN_search(list, (d+1)%Dim, k+1, b); 
        if(shouldReplace(list,temp,curr)) temp = curr;
        int r = 0;
        for(unsigned i=0;i<Dim;++i) r += pow((list[i] - temp[i]),2);
        int dist = pow((list[d] - curr[d]),2);
        if(dist <= r){
            Point<Dim> newCurr = NN_search(list, (d+1)%Dim, a, k-1);
            if(shouldReplace(list, temp, newCurr)) temp = newCurr;
        }
        return temp; 
    }
}
