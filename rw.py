"""
  CSC464 Assignment 1
  Readers Writers Classical Problem in Python

  Thor Reite V00809409
  10/11/2018
"""

import threading

sema_w = threading.Semaphore(5)
sema_r = threading.Semaphore(1)

content = 0 ##content to read and write
num_readers = 0

def main():
  for i in range(10):
    reader(i).start()
    writer(i).start()

class reader(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id
    def run(self):
        sema_r.acquire()
        global num_readers
        global content
        num_readers+=1
        if num_readers is 1:
            sema_w.acquire() ##only first reader needs
                             ##  to claim write lock
        print("Reader %s read content value %s.\n" % (self.id, content))
        num_readers-=1
        if num_readers is 0:
            sema_w.release() ##can write if 0 readers
        sema_r.release()

class writer(threading.Thread):
    def __init__(self, id):
        threading.Thread.__init__(self)
        self.id = id
    def run(self):
        sema_w.acquire()
        sema_r.acquire()
        global content
        content+=1
        print("Writer %s wrote content value %s.\n" % (self.id, content))
        sema_w.release()
        sema_r.release()

if __name__ == '__main__':
    main()
