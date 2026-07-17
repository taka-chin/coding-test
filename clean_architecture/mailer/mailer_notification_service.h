#pragma once
#include "../usecase/notification_service.h"
#include "mailer.cpp"

class MailerNotificationService : public NotificationService {
 private:
  Mailer* mailer;

 public:
  explicit MailerNotificationService(Mailer* mailer) : mailer(mailer) {}

  void sendUpdateNotification(const Email& to) override {
    mailer->send_update_notification(to.getValue());
  }

  void sendEmailChangeConfirmation(const Email& oldEmail) override {
    mailer->send_email_change_confirmation(oldEmail.getValue());
  }
};
