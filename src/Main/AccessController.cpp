// AccessController.cpp
#include "AccessController.h"
#include "Config.h"

AccessController::AccessController(const String& password)
: _password(password), _failedAttempts(0), _lockStartMs(0UL)
{}

bool AccessController::verify(const String& attempt){
  if (isLocked()) return false;
  if (attempt.equals(_password)) {
    notifySuccess();
    return true;
  } else {
    notifyFailedAttempt();
    return false;
  }
}

void AccessController::notifyFailedAttempt(){
  _failedAttempts++;
  if (_failedAttempts >= MAX_FAILED_ATTEMPTS) {
    _lockStartMs = millis();
  }
}

void AccessController::notifySuccess(){
  _failedAttempts = 0;
  _lockStartMs = 0UL;
}

void AccessController::resetAttempts(){
  _failedAttempts = 0;
  _lockStartMs = 0UL;
}

bool AccessController::isLocked(){
  if (_lockStartMs == 0UL) return false;
  unsigned long elapsed = millis() - _lockStartMs;
  if (elapsed >= LOCKOUT_DURATION_MS) {
    // liberar
    _failedAttempts = 0;
    _lockStartMs = 0UL;
    return false;
  }
  return true;
}

unsigned long AccessController::lockRemainingMs(){
  if (!isLocked() && _lockStartMs==0UL) return 0;
  unsigned long elapsed = millis() - _lockStartMs;
  if (elapsed >= LOCKOUT_DURATION_MS) return 0;
  return LOCKOUT_DURATION_MS - elapsed;
}

int AccessController::getFailedAttempts(){
  return _failedAttempts;
}
