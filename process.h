#ifndef __process_h__
#define __process_h__

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <thread>

#include "semaphore_layer.h"
#include "bank.h"
#include "vector_.h"
#include "time.h" // need to make rand() mostly random

class Bank; // forward declare pointer to Bank

class Process {
private:
  int pid_;
  int resources_;
  Bank *bank_;
  vector_<int> wants_;
  vector_<int> alloc_;
  vector_<int> needs_;

public:
  Process() : Process(0, 0, nullptr) {} // must exist to add to vector_ (which is added to std::vector)
  Process(int pid, int resources, Bank *bank) : pid_(pid),
                                                resources_(resources),
                                                bank_(bank) {
    wants_.resize(resources_); // DO NOT REMOVE these three lines
    alloc_.resize(resources_);
    needs_.resize(resources_);

    std::cin >> wants_; // std::cin >> depends on above three lines
    std::cin >> alloc_;
    needs_ = wants_ - alloc_;

    srand(time(NULL)); // make rand() mostly random
  }

  void set_bank(Bank *bank) { bank_ = bank; }
  Bank *bank() { return bank_; }

  int pid() const { return pid_; } // accessor
  vector_<int> &alloc() { return alloc_; } // rw accessors
  vector_<int> &wants() { return wants_; }
  vector_<int> &needs() { return needs_; }
  
  void request_granted(const vector_<int> &request) {
    alloc_ += request;
    needs_ -= request;
  }

  void request_rejected(const vector_<int> &request) {
    // Subtract the request from the current allocation and add it back to the needs.
    alloc_ -= request;
    needs_ += request;
  }

  bool can_request_more(const vector_<int> &request) { return needs_ >= request; }
  bool is_enough_for(const vector_<int> &request) const {
    if (request.size() != resources_)
      return false;
    for (size_t i = 0; i < request.size(); ++i) {
      if (wants_[i] < request[i])
        return false;
    }
    return true;
  }

  vector_<int> make_request() {
    vector_<int> request(resources_);
    if (needs_.is_zero()) {
      return request; // No request is needed if no needs exist
    }

    // Avoid infinite loops when needs has zero elements
    for (int i = 0; i < resources_; ++i) {
      // Skip if no need
      if (needs_[i] == 0)
        continue;
      // Generate a random number up to the size of needs_[i]
      request[i] = (rand() % (needs_[i] + 1));
    }
    return request;
  }

  bool has_all_resources() { return std::equal(wants_.begin(), wants_.end(), alloc_.begin()); }
  
  void release_all_resources() {
    std::fill(wants_.begin(), wants_.end(), 0);
    std::fill(alloc_.begin(), alloc_.end(), 0);
    std::fill(needs_.begin(), needs_.end(), 0);
  }

  friend std::ostream &operator<<(std::ostream &os,
                                  const Process &p) {
    os << "P#" << std::setw(2) << p.pid_ << "    " << p.wants_ << "    " << p.alloc_ << "    " << p.needs_;
    return os;
  }
};

#endif