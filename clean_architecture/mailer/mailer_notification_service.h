#pragma once
#include "mailer.cpp"
#include "../usecase/notification_service.h"

class MailerNotificationService : public NotificationService {
private:
    Mailer* mailer;

public:
    explicit MailerNotificationService(Mailer* mailer)
        : mailer(mailer) {}

    void sendUpdateNotification(const Email& to) override {
        mailer->send_update_notification(to.getValue());
    }

    void sendEmailChangeConfirmation(const Email& oldEmail) override {
        mailer->send_email_change_confirmation(oldEmail.getValue());
    }
};
