#include "../../mailer/mailer_notification_service.h"

#include <gtest/gtest.h>

#include <iostream>
#include <sstream>
#include <string>

class CoutCapture {
private:
    std::ostringstream output;
    std::streambuf* originalBuffer;

public:
    CoutCapture()
        : originalBuffer(std::cout.rdbuf(output.rdbuf())) {}

    ~CoutCapture() {
        std::cout.rdbuf(originalBuffer);
    }

    std::string str() const {
        return output.str();
    }
};

TEST(MailerNotificationServiceTest, SendUpdateNotificationUsesMailer) {
    Mailer mailer;
    MailerNotificationService service(&mailer);
    CoutCapture capture;

    service.sendUpdateNotification(Email("taka@example.com"));

    std::string output = capture.str();
    EXPECT_NE(output.find("taka@example.com"), std::string::npos);
    EXPECT_NE(output.find("ユーザー情報が更新されました"), std::string::npos);
}

TEST(MailerNotificationServiceTest, SendEmailChangeConfirmationUsesMailer) {
    Mailer mailer;
    MailerNotificationService service(&mailer);
    CoutCapture capture;

    service.sendEmailChangeConfirmation(Email("old@example.com"));

    std::string output = capture.str();
    EXPECT_NE(output.find("old@example.com"), std::string::npos);
    EXPECT_NE(output.find("メールアドレス変更のお知らせ"), std::string::npos);
}
