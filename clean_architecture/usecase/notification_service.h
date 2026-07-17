#pragma once

// ドメイン層
#include "../domain/email.h"

class NotificationService {
 public:
  virtual void sendUpdateNotification(const Email& to) = 0;
  virtual void sendEmailChangeConfirmation(const Email& oldEmail) = 0;
  virtual ~NotificationService() = default;
};
