#include "../FuzzProtoType.hpp"
#include <iostream>

// Taken From OSLabs
#define QUEUEMAX 10
#define bool int
#define false 0
#define true 1
#define MAX(a, b) ((a > b) ? a : b)
#define MIN(a, b) ((a > b) ? b : a)
#define ABS(a) ((a < 0) ? a * -1 : a)

struct PCB {
  int process_id;
  int arrival_timestamp;
  int total_bursttime;
  int execution_starttime;
  int execution_endtime;
  int remaining_bursttime;
  int process_priority;
};

struct PCB NULLPCB = {0, 0, 0, 0, 0, 0, 0};

bool compare_structs(PCB A, PCB B) {
  if (A.arrival_timestamp == B.arrival_timestamp &&
      A.execution_endtime == B.execution_endtime &&
      A.execution_starttime == B.execution_starttime &&
      A.process_id == B.process_id &&
      A.process_priority == B.process_priority &&
      A.remaining_bursttime == B.remaining_bursttime &&
      A.total_bursttime == B.total_bursttime) {
    return true;
  }
  return false;
}

bool is_empty(PCB A) { return compare_structs(A, NULLPCB); }

void remove_arr_element(PCB *arr, int element_to_remove) {
  if (element_to_remove > 9) {
    return;
  } else {
    for (int i = element_to_remove; i < 9; i++) {
      arr[i] = arr[i + 1];
    }
    arr[9] = NULLPCB;
  }
}

PCB handle_process_arrival_pp(struct PCB ready_queue[QUEUEMAX],
                                     int *queue_cnt, struct PCB current_process,
                                     struct PCB new_process, int timestamp) {
  if (is_empty(current_process)) {
    new_process.execution_starttime = timestamp;
    new_process.execution_endtime = timestamp + new_process.total_bursttime;
    new_process.remaining_bursttime = new_process.total_bursttime;
    return new_process;
  } else {
    // New has lesser priority
    if (current_process.process_priority <= new_process.process_priority) {
      new_process.execution_endtime = 0;
      new_process.execution_starttime = 0;
      new_process.remaining_bursttime = new_process.total_bursttime;
      ready_queue[*queue_cnt] = new_process;
      *queue_cnt = *queue_cnt + 1;
      return current_process;
    } else {
      current_process.execution_endtime = 0;
      ready_queue[*queue_cnt] = current_process;
      *queue_cnt = *queue_cnt + 1;
      new_process.execution_starttime = timestamp;
      new_process.execution_endtime = timestamp + new_process.total_bursttime;
      new_process.remaining_bursttime = new_process.total_bursttime;
      return new_process;
    }
  }
}

PCB generatingRandomPCB() {
  return {Fuzz::RandomGenerators::generate_int(101),
          Fuzz::RandomGenerators::generate_int(11444),
          Fuzz::RandomGenerators::generate_int(11111),
          Fuzz::RandomGenerators::generate_int(1123343435),
          Fuzz::RandomGenerators::generate_int(112323),
          Fuzz::RandomGenerators::generate_int(11555353),
          Fuzz::RandomGenerators::generate_int(1111323)};
}

int main() {

  PCB readyqueue[10] = {generatingRandomPCB(),generatingRandomPCB(),generatingRandomPCB(),generatingRandomPCB()};
  int *queue_count = new int;
  *queue_count = 3;  
  auto returnPCB = handle_process_arrival_pp(readyqueue, queue_count, generatingRandomPCB(), generatingRandomPCB(), Fuzz::RandomGenerators::generate_int(500));

//   std::cout << "Random Int:  " << Fuzz::RandomGenerators::generate_int(300)
//             << std::endl;
//   std::cout << "Random String:  " << Fuzz::RandomGenerators::generate_string(10)
//             << std::endl;
//   std::cout << "Random Double:  " << Fuzz::RandomGenerators::generate_double(250)
//             << std::endl;
  return 0;
}