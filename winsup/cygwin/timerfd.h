/* timerfd.h: Define timerfd classes

This file is part of Cygwin.

This software is a copyrighted work licensed under the terms of the
Cygwin license.  Please consult the file "CYGWIN_LICENSE" for
details. */

#ifndef __TIMERFD_H__
#define __TIMERFD_H__

#include "clock.h"
#include "ntdll.h"

class timerfd_shared
{
  HANDLE _access_mtx;		/* controls access to shared data */
  HANDLE _arm_evt;		/* settimer sets event when timer is armed,
				   unsets event when timer gets disarmed. */
  HANDLE _disarm_evt;		/* settimer sets event when timer is armed,
				   unsets event when timer gets disarmed. */
  HANDLE _timer;		/* SynchronizationTimer */
  HANDLE _expired_evt;		/* Signal if timer expired, Unsignal on read. */
  LONG instance_count;		/* each open fd increments this.
				   If 0 -> delete timerfd_shared */

  clockid_t _clockid;		/* clockid */
  struct itimerspec _time_spec;	/* original incoming itimerspec */
  LONG64 _exp_ts;		/* start timestamp or next expire timestamp
				   in 100ns */
  LONG64 _interval;		/* timer interval in 100ns */
  LONG64 _expiration_count;	/* expiry counter */
  int _flags;			/* settime flags */
  DWORD _tc_time;		/* timestamp of the last WM_TIMECHANGE msg */

  int create (clockid_t);
  bool dtor ();

  /* read access methods */
  HANDLE arm_evt () const { return _arm_evt; }
  HANDLE disarm_evt () const { return _disarm_evt; }
  HANDLE timer () const { return _timer; }
  HANDLE expired_evt () const { return _expired_evt; }
  LONG64 get_clock_now () const { return get_clock (_clockid)->n100secs (); }
  struct itimerspec &time_spec () { return _time_spec; }
  int flags () const { return _flags; }

  /* write access methods */
  void increment_expiration_count (LONG64 add)
    { InterlockedAdd64 (&_expiration_count, add); }
  void set_expiration_count (LONG64 newval)
    { InterlockedExchange64 (&_expiration_count, newval); }
  LONG64 read_and_reset_expiration_count ()
    {
      LONG64 ret = InterlockedExchange64 (&_expiration_count, 0);
      if (ret)
	ResetEvent (_expired_evt);
      return ret;
    }
  bool enter_cs ()
    {
      return (WaitForSingleObject (_access_mtx, INFINITE) & ~WAIT_ABANDONED_0)
	      == WAIT_OBJECT_0;
    }
  void leave_cs ()
    {
      ReleaseMutex (_access_mtx);
    }
  int arm_timer (int, const struct itimerspec *);
  int disarm_timer ()
    {
      ResetEvent (_arm_evt);
      memset (&_time_spec, 0, sizeof _time_spec);
      _exp_ts = 0;
      _interval = 0;
      /* _flags = 0;  DON'T DO THAT.  Required for TFD_TIMER_CANCEL_ON_SET */
      NtCancelTimer (timer (), NULL);
      SetEvent (_disarm_evt);
      return 0;
    }
  void timer_expired () { SetEvent (_expired_evt); }
  void set_exp_ts (LONG64 ts) { _exp_ts = ts; }

  friend class timerfd_tracker;
};

class timerfd_tracker		/* cygheap! */
{
  HANDLE tfd_shared_hdl;	/* handle auf shared mem */
  timerfd_shared *tfd_shared;	/* pointer auf shared mem, needs
				   NtMapViewOfSection in each new process. */

  HANDLE cancel_evt;		/* Signal thread to exit. */
  HANDLE sync_thr;		/* cygthread sync object. */
  LONG local_instance_count;	/* each open fd increments this.
				   If 0 -> cancel thread.  */
  DWORD winpid;			/* This is used @ fork/exec time to know if
				   this tracker already has been fixed up. */
  HWND window;			/* window handle */
  ATOM atom;			/* window class */

  void create_timechange_window ();
  void delete_timechange_window ();
  void handle_timechange_window ();

  bool dtor ();

  bool enter_critical_section () const { return tfd_shared->enter_cs (); }
  void leave_critical_section () const { tfd_shared->leave_cs (); }

  int arm_timer (int flags, const struct itimerspec *new_value) const
    { return tfd_shared->arm_timer (flags, new_value); }
  int disarm_timer () const { return tfd_shared->disarm_timer (); }
  void timer_expired () const { tfd_shared->timer_expired (); }

  LONG64 expiration_count () const { return tfd_shared->_expiration_count; }
  void increment_expiration_count (LONG64 add) const
    { tfd_shared->increment_expiration_count (add); }
  void set_expiration_count (LONG64 exp_cnt) const
    { tfd_shared->set_expiration_count ((LONG64) exp_cnt); }
  LONG64 read_and_reset_expiration_count () const
    { return tfd_shared->read_and_reset_expiration_count (); }

  struct timespec it_value () const
    { return tfd_shared->time_spec ().it_value; }
  struct timespec it_interval () const
    { return tfd_shared->time_spec ().it_interval; }

  clock_t get_clockid () const { return tfd_shared->_clockid; }
  LONG64 get_clock_now () const { return tfd_shared->get_clock_now (); }
  struct itimerspec &time_spec () { return tfd_shared->time_spec (); }
  LONG64 get_exp_ts () const { return tfd_shared->_exp_ts; }
  LONG64 get_interval () const { return tfd_shared->_interval; }
  int flags () const { return tfd_shared->flags (); }
  DWORD tc_time () const { return tfd_shared->_tc_time; }
  void set_tc_time (DWORD new_time) { tfd_shared->_tc_time = new_time; }

  void set_exp_ts (LONG64 ts) const { tfd_shared->set_exp_ts (ts); }

 public:
  void *operator new (size_t, void *p) __attribute__ ((nothrow)) {return p;}
  timerfd_tracker ()
  : tfd_shared_hdl (NULL), tfd_shared (NULL), cancel_evt (NULL),
    sync_thr (NULL), local_instance_count (1), winpid (0), window (NULL),
    atom (0) {}
  int create (clockid_t);
  int gettime (struct itimerspec *);
  int settime (int, const struct itimerspec *, struct itimerspec *);
  static void dtor (timerfd_tracker *);
  void close ();
  int ioctl_set_ticks (uint64_t);
  void fixup_after_fork_exec (bool);
  void fixup_after_fork () { fixup_after_fork_exec (false); }
  void fixup_after_exec () { fixup_after_fork_exec (true); }
  HANDLE get_timerfd_handle () const { return tfd_shared->expired_evt (); }
  HANDLE get_disarm_evt () const { return tfd_shared->disarm_evt (); }
  LONG64 wait (bool);
  void increment_global_instances ()
    { InterlockedIncrement (&tfd_shared->instance_count); }
  void increment_instances ()
    {
      InterlockedIncrement (&tfd_shared->instance_count);
      InterlockedIncrement (&local_instance_count);
    }
  void decrement_instances ()
    {
      InterlockedDecrement (&tfd_shared->instance_count);
      InterlockedDecrement (&local_instance_count);
    }

  DWORD thread_func ();
};

#endif /* __TIMERFD_H__ */
