// AccessController.h
#ifndef ACCESSCONTROLLER_H
#define ACCESSCONTROLLER_H

#include <Arduino.h>

class AccessController {
public:
  AccessController(const String& password);
  bool verify(const String& attempt);
  void resetAttempts();
  bool isLocked();
  unsigned long lockRemainingMs(); // ms restantes de bloqueo
  int getFailedAttempts();
  void notifyFailedAttempt();
  void notifySuccess();
private:
  String _password;
  int _failedAttempts;
  unsigned long _lockStartMs;
};

#endif
