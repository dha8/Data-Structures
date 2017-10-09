/**
 * @file quackfun.cpp
 * This is where you will implement the required functions for the
 *  stacks and queues portion of the lab.
 */

namespace QuackFun {

/**
 * Sums items in a stack.
 * @param s A stack holding values to sum.
 * @return The sum of all the elements in the stack, leaving the original
 *  stack in the same state (unchanged).
 *
 * @note You may modify the stack as long as you restore it to its original
 *  values.
 * @note You may use only two local variables of type T in your function.
 *  Note that this function is templatized on the stack's type, so stacks of
 *  objects overloading the + operator can be summed.
 * @note We are using the Standard Template Library (STL) stack in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint Think recursively!
 */
template <typename T>
T sum(stack<T>& s)
{
    if(s.empty()) return 0;
    T temp = s.top();
    s.pop();
    T ret = sum(s)+temp;
    s.push(temp);
    return ret;
}

/**
 * Reverses even sized blocks of items in the queue. Blocks start at size
 * one and increase for each subsequent block.
 * @param q A queue of items to be scrambled
 *
 * @note Any "leftover" numbers should be handled as if their block was
 *  complete.
 * @note We are using the Standard Template Library (STL) queue in this
 *  problem. Its pop function works a bit differently from the stack we
 *  built. Try searching for "stl stack" to learn how to use it.
 * @hint You'll want to make a local stack variable.
 */
template <typename T>
void scramble(queue<T>& q)
{
    stack<T> s;
    unsigned numPopped = 0;
    unsigned blockNum = 1;
    unsigned size_ = q.size();
    while(numPopped<size_){
        if(blockNum%2==0){
            for(unsigned j=0;((j<blockNum)&&(numPopped<size_));++j){
                T temp = q.front();
                q.pop();
                numPopped++;
                s.push(temp);
            }
            while(!s.empty()){
                T temp = s.top();
                s.pop();
                q.push(temp);
            }
        blockNum++;
        }
        if(blockNum%2==1){
            for(unsigned j=0;((j<blockNum)&&(numPopped<q.size()));++j){
                T temp = q.front();
                q.pop();
                numPopped++;
                q.push(temp);
            }
            blockNum++;
        }
    }
}

/**
 * @return true if the parameter stack and queue contain only elements of
 *  exactly the same values in exactly the same order; false, otherwise.
 *
 * @note You may assume the stack and queue contain the same number of items!
 * @note There are restrictions for writing this function.
 * - Your function may not use any loops
 * - In your function you may only declare ONE local boolean variable to use in
 *   your return statement, and you may only declare TWO local variables of
 *   parametrized type T to use however you wish.
 * - No other local variables can be used.
 * - After execution of verifySame, the stack and queue must be unchanged. Be
 *   sure to comment your code VERY well.
 */
template <typename T>
bool verifySame(stack<T>& s, queue<T>& q)
{
    //prevent against null stacks
    if(s.empty()) return true; // assumes q & s has same size

    //pop from the stack to compare
    T stack_temp = s.top();
    s.pop();
    bool retval = verifySame(s, q); //pops until basecase

    //since stack fully popped, starts comparing from bottom of stack to queue front
    if (stack_temp != q.front()) retval = false;

    //restore stack
    s.push(stack_temp);

    //traversing through queue item for comparison
    T queue_temp = q.front();
    q.pop();
    q.push(queue_temp);
    return retval;
}

}
