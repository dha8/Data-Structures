/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */
#include <iostream>
/**
 * Destroys the current List. This function should ensure that
 * memory does not leak on destruction of a list.
 */
template <class T>
List<T>::~List() {
  /// @todo Graded in MP3.1
  clear();

}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <class T>
void List<T>::clear() {
  while(head_!=NULL){
    ListNode * temp = head_;
    head_ = head_->next;
    delete(temp);    
    --length_;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
    if(head_ == NULL){
        head_ = new ListNode(ndata);
        tail_ = head_;
        head_->next = NULL;
        head_->prev = NULL;
        ++length_;
        return;
    }
    ListNode * n = new ListNode(ndata);
    n->next = head_;
    head_->prev = n;
    head_ = n;
    head_->prev = NULL;
    ++length_;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
    if(head_ == NULL){
        head_ = new ListNode(ndata);
        tail_ = head_;
        head_->next = NULL;
        head_->prev = NULL;
        ++length_;
        return;
    }
    ListNode * n = new ListNode(ndata); 
    tail_->next = n;
    n->prev = tail_;
    tail_ = n;
    tail_->next = NULL;
    ++length_;
}

/**
 * Reverses the current List.
 */
template <class T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <class T>
void List<T>::reverse(ListNode*& startPoint, ListNode*& endPoint) {
    //defend against fucky inputs
    if(startPoint == NULL || endPoint == NULL) return;

    //setting correct ptrs for end assignment 
    bool h = false;
    if(startPoint==head_) h=true;
    ListNode * initStart = startPoint;
    ListNode * initEnd = endPoint;

    //what start & end points to on other side
    ListNode * endWall = endPoint->next;
    ListNode * startWall = startPoint->prev;

    //get the endpoint connections
    if(startWall!=NULL) startWall->next = endPoint;
    if(endWall!=NULL) endWall->prev = startPoint;
    startPoint->prev = startPoint->next;
    startPoint->next = endWall;

    //set sentinel and reassign ptrs
    ListNode * curr = endPoint;
    if(curr->prev==NULL)
    std::cout << "curr->prev is null?" << endl;
    curr->next = curr->prev;
    curr->prev = startWall;
    ListNode * temp = curr;
    curr = curr->next;
    while(curr->next!=endWall){
        curr->next = curr->prev;
        curr->prev = temp;
        ListNode * temp = curr;
        curr = curr->next;
    }

    //update pointers to correct spots
    startPoint = initEnd;
    endPoint = initStart;
    if(h) head_ = initEnd;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
    // defend against fucky inputs
    if(n<=1) return;
    
    // for blocks over n
    if(n>=length_){
       reverse(head_,tail_);
       return;
    }

    // regular cases
    ListNode * start = head_;
    ListNode * end = head_;

    while(end!=NULL){
        for(int i=1;i<n;++i){
            end = end->next; 
            if(end->next==NULL) break;
        }
        reverse(start, end);
        start = end->next;
        end = start;
    }
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <class T>
void List<T>::waterfall() {
    // defend against bad inputs
    if(length_==0 || length_==1) return;

    ListNode * curr = head_;
    while(!(curr->next==NULL || curr->next==tail_)){
        ListNode * temp = curr->next;
        curr->next = temp->next;
        curr->next->prev = curr; 
        tail_->next = temp; 
        temp->prev = tail_;
        tail_ = temp;
        tail_->next = NULL;
        curr = curr->next;
    }
}

/**
 * Splits the given list into two parts by dividing it at the splitPoint.
 *
 * @param splitPoint Point at which the list should be split into two.
 * @return The second list created from the split.
 */
template <class T>
List<T> List<T>::split(int splitPoint) {
    if (splitPoint > length_)
        return List<T>();

    if (splitPoint < 0)
        splitPoint = 0;

    ListNode* secondHead = split(head_, splitPoint);

    int oldLength = length_;
    if (secondHead == head_) {
        // current list is going to be empty
        head_ = NULL;
        tail_ = NULL;
        length_ = 0;
    } else {
        // set up current list
        tail_ = head_;
        while (tail_->next != NULL)
            tail_ = tail_->next;
        length_ = splitPoint;
    }

    // set up the returned list
    List<T> ret;
    ret.head_ = secondHead;
    ret.tail_ = secondHead;
    if (ret.tail_ != NULL) {
        while (ret.tail_->next != NULL)
            ret.tail_ = ret.tail_->next;
    }
    ret.length_ = oldLength - splitPoint;
    return ret;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List objects!
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <class T>
typename List<T>::ListNode* List<T>::split(ListNode* start, int splitPoint) {
    if(length_<splitPoint || splitPoint<=0) return head_;
    ListNode * newhead = start;
    for(int i=0;i<splitPoint;++i) 
        newhead = newhead->next; 
    tail_ = newhead->prev;
    tail_->next = NULL;
    newhead->prev = NULL;
    return newhead;
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <class T>
void List<T>::mergeWith(List<T>& otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <class T>
typename List<T>::ListNode* List<T>::merge(ListNode* first, ListNode* second) {
    // handling special cases:
    if(first == NULL) return second;
    if(second == NULL) return first;

    // change first and second so second always starts greater than 1st
    if(second->data < first->data){
        ListNode * temp = second;
        second = first;
        first = temp;
    }

    // general cases
    ListNode * currSec = second;
    ListNode * currFirst = first;

    // continue until secondlist is null
    while(currSec!=NULL){
        // move first cursor to the point of insertion
        if(currFirst != NULL && currFirst->next!=NULL && currSec != NULL){
            while((currFirst != NULL && currFirst->next!=NULL 
                        && currSec != NULL) &&
                    (currFirst->next->data < currSec->data)){
                currFirst = currFirst->next;
            }
        }
        // insert
        ListNode * temp = currSec->next;
        if(currFirst->next!=NULL)
            currFirst->next->prev = currSec; 
        currSec->next = currFirst->next;
        currFirst->next = currSec;
        currSec->prev = currFirst; 
        currSec = temp;
    }
    return first;
}

/**
 * Sorts the current list by applying the Mergesort algorithm.
 */
template <class T>
void List<T>::sort() {
    if (empty())
        return;
    head_ = mergesort(head_, length_);
    tail_ = head_;
    while (tail_->next != NULL)
        tail_ = tail_->next;
}

/**
 * Sorts a chain of linked memory given a start node and a size.  * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    if(chainLength<=1) return start;
    ListNode* ctr = split(start, chainLength/2);
    start = mergesort(start, chainLength/2);
    head_ = ctr;
    ctr = mergesort(ctr, chainLength - chainLength/2);
    return merge(start, ctr);
}
