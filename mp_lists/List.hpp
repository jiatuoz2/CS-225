#include <iostream>
/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}

/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in MP3.1
  ListNode* temp;
  while (head_) {
    temp = head_;
    head_ = head_->next;
    delete temp;
  }
  head_ = tail_ = temp = nullptr;
  length_ = 0;
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  if (head_) {
    head_->prev = new ListNode(ndata);
    head_->prev->next = head_;
    head_ = head_->prev;
  } else {
    head_ = tail_ = new ListNode(ndata); 
  }
  length_++;
}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in MP3.1
  if (tail_) {
    tail_->next = new ListNode(ndata);
    tail_->next->prev = tail_;
    tail_ = tail_->next;
  } else {
    head_ = tail_ = new ListNode(ndata);
  }
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */

template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in MP3.1
  ListNode* new_head = start; 
  for (int i = 0; i < splitPoint && new_head; i++) {
    new_head = new_head->next;
  }
  if (new_head) {
    if (new_head->prev) {
      new_head->prev->next = nullptr;
    }
    new_head->prev = nullptr;
  }
  return new_head;
}

/**
  * Modifies List using the rules for a TripleRotate.
  *
  * This function will to a wrapped rotation to the left on every three 
  * elements in the list starting for the first three elements. If the 
  * end of the list has a set of 1 or 2 elements, no rotation all be done 
  * on the last 1 or 2 elements.
  * 
  * You may NOT allocate ANY new ListNodes!
  */
template <typename T>
void List<T>::tripleRotate() {
  // @todo Graded in MP3.1
  ListNode* cur1 = head_;
  ListNode* cur2 = head_; 
  for (int i = 0; i < length_ / 3; i++) {
    if (i == 0) {
      for (int j = 1; j < 3; j++) {
        cur2 = cur2->next;
      }
    } else {
      for (int j = 0; j < 3; j++) {
        if (j == 1) {
          cur1 = cur2;
        }
        cur2 = cur2->next;
      }
    }
    if (i == 0) {
      head_ = cur1->next;
    }
    if (i == length_ / 3 - 1) {
      tail_ = cur1;
    }
    if (cur1->prev) {
      cur1->prev->next = cur1->next;
    }
    if (cur2->next) {
      cur2->next->prev = cur1;
    }
    cur1->next->prev = cur1->prev;
    cur1->next = cur2->next;
    cur1->prev = cur2;
    cur2->next = cur1;
    cur2 = cur1;
  }
  cur1 = cur2 = nullptr;
}

/**
 * Reverses the current List.
 */
template <typename T>
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
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in MP3.2
  ListNode* cur = startPoint;
  while (true) {
    ListNode* temp = cur->next;
    cur->next = cur->prev;
    cur->prev = temp;
    if (cur == endPoint) {
      break;
    }
    cur = cur->prev;
  }
  ListNode* temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;
  ListNode* temp1 = endPoint->next;
  ListNode* temp2 = startPoint->prev;
  startPoint->prev = temp1;
  endPoint->next = temp2;
  if (temp1) {
    temp1->next = startPoint;
    startPoint = head_;
  }
  if (temp2) {
    temp2->prev = endPoint;
    endPoint = tail_;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in MP3.2
  ListNode* beg = head_;
  ListNode* end = head_;
  while (true) {
    if (end == head_) {
      for (int i = 0; i < n - 1 && end->next; i++) {
        end = end->next;
      }
    } else {
      for (int i = 0; i < n && end->next; i++) {
        if (i == 1) {
          beg = end;
        }
        end = end->next;
      }
    }
    ListNode* temp1 = beg;
    ListNode* temp2 = end;
    reverse(temp1, temp2);
    if (end->prev == nullptr) {
      head_ = end;
    }
    end = beg;
    if (end->next == nullptr) {
      tail_ = end;
      break; 
    }
  }
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
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
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in MP3.2
  ListNode* head = nullptr;
  ListNode* cur1 = first;
  ListNode* cur2 = second; 
  (first->data) < (second->data) ? head = first : head = second;
  while (true) {
    T value1 = cur1->data;
    T value2 = cur2->data;
    ListNode* temp = cur1;
    if (value1 < value2) {
      cur1 = cur1->next;
      if (cur2->prev) {
        cur2->prev->next = temp;
      }
      temp->prev = cur2->prev;
      temp->next = cur2;
      cur2->prev = temp;
    } else {
      if (cur2->next) {
        cur2 = cur2->next;
      } else {
        cur2->next = temp;
        temp->prev = cur2;
        return head;
      }
    }
    if (cur1 == nullptr) {
      return head;
    }
  }
}

/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in MP3.2
  if (chainLength == 1 || chainLength == 0) {
    return start;
  }
  ListNode* l = start; 
  ListNode* r = split(start, chainLength / 2);
  ListNode* left = mergesort(l, chainLength / 2);
  ListNode* right = mergesort(r, chainLength - chainLength / 2);
  return merge(left, right); 
}
