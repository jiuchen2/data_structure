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
  /// @todo Graded in MP3.1
  if (this->empty()) {
    return;
  }
  ListNode * temp;
  while (head_ != tail_) {
    temp = head_;
    head_ = head_->next;
    delete temp;
  }
  delete head_;
  head_ = NULL;
  tail_ = NULL;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertFront(T const& ndata) {
  /// @todo Graded in MP3.1
  if (this->empty() == true) {
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_ = 1;
  }else{
    ListNode * temp = new ListNode(ndata);
    temp->next = head_;
    head_->prev = temp;
    head_ = temp;
    length_++;
  }
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <class T>
void List<T>::insertBack(const T& ndata) {
  /// @todo Graded in MP3.1
  if (this->empty() == true) {
    head_ = new ListNode(ndata);
    tail_ = head_;
    length_ = 1;
  }else{
    ListNode * temp = new ListNode(ndata);
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
    length_++;
  }
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
    /// @todo Graded in MP3.1
    //std::cout<<startPoint<<" "<<endPoint<<" "<<head_<<std::endl;
    if (startPoint==endPoint || startPoint == NULL || endPoint == NULL) {
      return;
    }
    ListNode * prevStart = startPoint->prev;
    ListNode * nextEnd = endPoint->next;
    startPoint->prev = startPoint->next;
    if (prevStart != NULL){
      prevStart->next = endPoint;
    }
    ListNode * curr = startPoint->next;
    ListNode * currp = curr->next;
    ListNode * currn = startPoint;
    startPoint->next = nextEnd;
    while (curr != endPoint) {
      curr->prev = currp;
      curr->next = currn;
      currn = curr;
      curr = currp;
      currp = curr->next;
    }
    endPoint->next = currn;
    endPoint->prev = prevStart;
    if (nextEnd != NULL) {
      nextEnd->prev = startPoint;
    }
    ListNode * temp = startPoint;
    startPoint = endPoint;
    endPoint = temp;
    if (startPoint->prev == NULL) {
      head_ = startPoint;
    }
    if (endPoint->next == NULL) {
      tail_ = endPoint;
    }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <class T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.1
  if (head_ == NULL) {
    return;
  } else {
    ListNode * startPoint = head_;
    ListNode * endPoint;
    while (startPoint != NULL) {
      endPoint = startPoint;
      for (int i = 0; i < n - 1; i++) {
        if (endPoint->next != NULL) {
          endPoint = endPoint->next;
        }
      }
      reverse(startPoint, endPoint);
      startPoint = endPoint->next;
    }
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
  /// @todo Graded in MP3.1
  if (head_ == NULL || head_->next == tail_) {
    return;
  }
  ListNode * curr = head_;
  ListNode * temp;
  while (curr->next != tail_) {
    temp = curr->next;
    temp->next->prev = curr;
    curr->next = temp->next;
    temp->next = NULL;
    temp->prev = tail_;
    tail_->next = temp;
    tail_ = temp;
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
    /// @todo Graded in MP3.2
    if (splitPoint == 0) {
      return start;
    }
    ListNode * second = start;
    for (int i=0; i < splitPoint - 1; i++) {
      if (second != NULL) {
        second = second->next;
      } else {
        return NULL;
      }
    }
    ListNode * temp = second->next;
    second->next = NULL;
    second = temp;
    return second;
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
  /// @todo Graded in MP3.2
  if (first == NULL) {
    return second;
  }
  if (second == NULL) {
    return first;
  }
  ListNode *res;
  ListNode *temp;
  ListNode *curr;
  if (first->data < second->data) {
    res = first;
    first = first->next;
  } else {
    res = second;
    second = first;
    first = res;
    first = first->next;
  }
  curr = res;
  while (first != NULL) {
    if (second != NULL) {
      if (first->data < second->data) {
        curr = first;
        first = first->next;
      } else {
        curr->next = second;
        second->prev = curr;
        temp = second->next;
        second->next = first;
        first->prev = second;
        curr = second;
        second = temp;
      }
    } else {
      break;
    }
  }
  if (second != NULL) {
    curr->next = second;
    second->prev = curr;
  }
  return res;
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
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <class T>
typename List<T>::ListNode* List<T>::mergesort(ListNode* start, int chainLength) {
    /// @todo Graded in MP3.2
    if (chainLength <= 1) {
      return start;
    }

    int splitPoint = chainLength/2;
    ListNode * second = split(start, splitPoint);

    start = mergesort(start, splitPoint);
    second = mergesort(second, chainLength - splitPoint);

    return merge(start, second);
}
