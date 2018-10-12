"""
  CSC464 Assignment 1
  Producer Consumer Classical Problem in Python

  Thor Reite V00809409
  10/11/2018
"""

import threading

pc_cond = threading.Condition()

item_buffer = 0; ##tracks items in buffer

def main():
  producer().start()
  consumer().start()
  producer().join()
  consumer().join()
  exit(1)

class producer(threading.Thread):
    def run(self):
        for i in range(1000):
            pc_cond.acquire() ##lock item item_buffer
            while item_buffer:
                pc_cond.wait() #wait until buffer empties
            global item_buffer
            item_buffer = i
            pc_cond.notify()
            pc_cond.release()

class consumer(threading.Thread):
    def run(self):
        for i in range(1000):
            pc_cond.acquire() ##lock item item_buffer
            while item_buffer is 0:
                pc_cond.wait() #wait until buffer has item
            global item_buffer
            item_buffer = 0
            pc_cond.notify()
            pc_cond.release()

if __name__ == '__main__':
    main()
