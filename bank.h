#ifndef __bank_h__
#define __bank_h__

#include <iostream>
#include <vector>
#include <algorithm>

#include "process.h"
#include "vector_.h"
#include "semaphore_layer.h"

class Bank {
  private:
  int n_proc_;
  int n_res_;
  vector_ < int > resources_;
  std::vector < Process * > processes_;

  public:
  Bank(): Bank(0, 0) {}
  Bank(int n_proc, int n_res): n_proc_(n_proc),
  n_res_(n_res),
  resources_(n_res) {}

  ~Bank() {
    for (auto & process: processes_) {
      delete process;
    }
  }

  vector_ < int > & resources() { return resources_; }

  Process * process(int i) {
    if (i >= n_proc_) {
      throw std::out_of_range("Index out of range\n");
    }
    return processes_[i];
  }

  bool grant_request(int pid,
    const vector_ < int > & request) {
    if (pid >= n_proc_) {
      std::cerr << "Invalid process ID: " << pid << "\n";
      return false;
    }

    Process * p = processes_[pid];
    std::cout << "P #" << pid << " request: [" << request << "] is: ";

    if (!(p -> wants() >= (request + p -> alloc()))) {
      std::cout << "rejected (exceeds maximum claim)\n";
      return false;
    }

    if (request.is_zero()) {
      std::cout << "rejected (request is zero)\n";
      return false;
    }

    if (!resources_.is_enough_for(request)) {
      std::cout << "rejected (not enough resources)\n";
      return false;
    }

    bool result = is_safe(pid, request);

    std::cout << (result ? "GRANTED" : "rejected") << "\n";
    return result;
  }

  bool is_safe(int pid,
    const vector_ < int > & request) {
    vector_ < int > original_resources = resources_;
    Process * p = processes_[pid];

    resources_ -= request; // Temporarily simulate allocation
    p -> request_granted(request);

    std::vector < bool > finish(n_proc_, false);
    finish[pid] = true; // The requesting process can complete

    bool progress;
    do {
      progress = false;
      for (int i = 0; i < n_proc_; ++i) {
        if (!finish[i] && processes_[i] -> needs() <= resources_) {
          resources_ += processes_[i] -> alloc(); // Simulate release
          finish[i] = true;
          progress = true;
        }
      }
    } while (progress);

    bool all_finished = std::all_of(finish.begin(), finish.end(), [](bool f) {
      return f;
    });

    // Rollback if not safe
    if (!all_finished) {
      resources_ = original_resources; // Rollback
      p -> request_rejected(request);
    }
    return all_finished;
  }

  void add_resources(const vector_ < int > & new_resources) {
    resources_ = new_resources;
  }

  void add_process(Process * p) {
    if (processes_.size() < static_cast < size_t > (n_proc_)) {
      processes_.push_back(p);
    }
  }

  friend std::ostream & operator << (std::ostream & os,
    const Bank & b) {
    os << "+---------------------------------------------------------\n";
    os << "|   Bank avail: [" << b.resources_ << "]\n";
    os << "+---------------------------------------------------------\n";
    for (int i = 0; i < b.n_proc_; ++i) {
      os << "| " << * b.processes_[i] << "\n";
      if (i % 5 == 4) {
        os << "|\n";
      }
    }
    os << "+---------------------------------------------------------\n";
    return os << "\n";
  }
};

#endif // __bank_h__