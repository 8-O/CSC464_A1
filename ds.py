"""
  CSC464 Assignment 1
  Dining Savages Classical Problem in Python

  Thor Reite V00809409
  10/11/2018
"""

import threading
import time

eating_lock = threading.Lock()
print_mutex = threading.Lock()
restock_food = threading.Condition()

servings = 5

def main():
  for i in range(10):
    savage(i).start()
  cook(1).start()
  exit(0)

class savage(threading.Thread):
    def __init__(self, i):
        threading.Thread.__init__(self)
        self.i = i
    def run(self):
        while 1:
            print_mutex.acquire()
            print("Savage %s wants to eat.\n" % (self.i))
            print_mutex.release()
            eating_lock.acquire()
            global servings
            if servings == 0:
                time.sleep(1) ##gives cook a chance to wait
                restock_food.acquire()
                restock_food.notify()
                restock_food.wait()
                restock_food.release()
            servings -= 1
            print_mutex.acquire()
            print("Savage %s just ate and %s portions remain.\n" % (self.i, servings))
            print_mutex.release()
            eating_lock.release()
            time.sleep(1)
        exit(0)

class cook(threading.Thread):
    def __init__(self, i):
        threading.Thread.__init__(self)
        self.i = i
    def run(self):
          while 1:
              restock_food.acquire()
              restock_food.wait()
              global servings
              servings = 10
              print("Cook filled the pot with %d portions.\n" % (servings))
              restock_food.notify()
              restock_food.release()
          exit(0)

if __name__ == '__main__':
    main()
