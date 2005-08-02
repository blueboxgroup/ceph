/////////////////////////////////////////////////////////////////////
//  Written by Phillip Sitbon
//  Copyright 2003
//
//  Posix/Mutex.h
//    - Resource locking mechanism using Posix mutexes
//
/////////////////////////////////////////////////////////////////////

#ifndef _Mutex_Posix_
#define _Mutex_Posix_

#include <pthread.h>
#include <cassert>

class Mutex
{
  mutable pthread_mutex_t M;
  void operator=(Mutex &M) {}
  Mutex( const Mutex &M ) {}
  bool tag;

  public:

  Mutex()
  {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&M,&attr);
    //cout << this << " mutex init = " << r << endl;
    pthread_mutexattr_destroy(&attr);
    this->tag = false;
  }

  Mutex(bool tag)
  {
    pthread_mutexattr_t attr;
    pthread_mutexattr_init(&attr);
    pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
	pthread_mutex_init(&M,&attr);
    //cout << this << " mutex init = " << r << endl;
    pthread_mutexattr_destroy(&attr);
    this->tag = tag;
  }

  virtual ~Mutex()
  { 
	//pthread_mutex_unlock(&M); 
	pthread_mutex_destroy(&M); 
  }

  int Lock()  { 
	if (tag) cout << this << " " << pthread_self() << endl; 
	int r = pthread_mutex_lock(&M);
	if (tag) cout << "lock = " << r << endl;
	return r;
  }

  int Lock(char *s)  { 
	cout << "Lock: " << s << endl;
	int r = pthread_mutex_lock(&M);
	cout << this << " " << pthread_self() << " lock = " << r << endl;
	return r;
  }

  int Lock_Try() const
  { 
	return pthread_mutex_trylock(&M); 
  }

  int Unlock() 
  { 
	if (tag) cout << this << " " << pthread_self() << endl;
	int r = pthread_mutex_unlock(&M);
	if (tag) cout << "lock = " << r << endl;
	return r;
  }

  int Unlock(char *s) 
  { 
	cout << "Unlock: " << s << endl;
	int r = pthread_mutex_unlock(&M);
	cout << this << " " << pthread_self() << " unlock = " << r << endl;
	return r;
  }

  friend class Cond;
};

#endif // !_Mutex_Posix_
