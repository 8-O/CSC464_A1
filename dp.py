"""
  CSC464 Assignment 1
  Dining Philosophers Classical Problem in C

  Thor Reite V00809409
  10/11/2018
"""

import threading
import time

fork = [threading.Lock() for i in range(5)]

def main():
  for i in range(5):
    philosopher(i).start()
  exit(0)

class philosopher(threading.Thread):
    def __init__(self, i):
        threading.Thread.__init__(self)
        self.i = i
    def run(self):
        print("Philosopher %s wants to eat.\n" % (self.i))
        fork[self.i].acquire()
        fork[(self.i+1)%5].acquire()
        print("Philosopher %s is eating with forks %s and %s.\n" % (self.i, self.i, (self.i+1)%5))
        time.sleep(1)
        fork[self.i].release()
        fork[(self.i+1)%5].release()
        print("Philosopher %s is done eating.\n" % (self.i))
        exit(0)

if __name__ == '__main__':
    main()
