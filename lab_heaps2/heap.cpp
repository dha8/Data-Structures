
/**
 * @file heap.cpp
 * Implementation of a heap class.
 */

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
    return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
    return (currentIdx*2)+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
    return (currentIdx+1)*2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
    // ret 0 if calling parent of root
    return (currentIdx==0)? 0 : (currentIdx-1)/2;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
    // heap fills from L to R. 
    return leftChild(currentIdx) < _elems.size();
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
    unsigned l = leftChild(currentIdx);
    unsigned r = rightChild(currentIdx);
    // check to see if right child even exists
    if(r >= _elems.size()) return l;
    return (higherPriority(_elems[l],_elems[r]))? l : r;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
    // base case: reached leaf
    if(!hasAChild(currentIdx)) return; 
    
    // otherwise swap and recurse
    size_t childIdx = maxPriorityChild(currentIdx);
    if(higherPriority(_elems[childIdx],_elems[currentIdx])){
        std::swap(_elems[currentIdx], _elems[childIdx]);
        heapifyDown(childIdx);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
    if (currentIdx == root())
        return;
    size_t parentIdx = parent(currentIdx);
    if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
        std::swap(_elems[currentIdx], _elems[parentIdx]);
        heapifyUp(parentIdx);
    }
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
    /// @todo Depending on your implementation, this function may or may
    ///   not need modifying
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& elems)
{
    // while simpler code, the second way is more efficient
    /*
    for(unsigned i=0;i<elems.size();++i){
        this->push(elems[i]);
    }*/
    for(unsigned i=0;i<elems.size();++i)
        _elems.push_back(elems[i]);
    for(int i=parent(_elems.size()-1);i>=0;--i)
        heapifyDown(i);
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
    // case of empty heap
    if(_elems.empty()) return 0;

    T retVal = _elems[0];
    std::swap(_elems[0],_elems[_elems.size()-1]);
    _elems.pop_back();
    heapifyDown(0);
    return retVal;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
    // if empty, return NULL. othersise root
    return (_elems.empty())? NULL : _elems[root()];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
    _elems.push_back(elem);
    heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
    /// @todo Determine if the heap is empty
    return _elems.empty();
}

template <class T, class Compare>
void heap<T, Compare>::getElems(std::vector<T> & heaped) const
{
    for (size_t i = root(); i < _elems.size(); i++) {
        heaped.push_back(_elems[i]);
    }
}
