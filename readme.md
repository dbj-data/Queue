
# Refactoring 

Branch (dbj_queue)

- made Visual Studio project
- mtr_queue == multi thread resilient queue
- dependency on `pthreads.h` has been removed
  - win32 critical section used instead
- divided into lib and example app
   - win32 app
   - using dbjsysloglib
      - use [SysLog Watcher](https://ezfive.com) in production or perhaps simpler [Visual Syslog](http://maxbelkov.github.io/visualsyslog/) in development

---
&copy; 2022 by dbj at dbj dot org

Please respect the [original licence](LICENSE).