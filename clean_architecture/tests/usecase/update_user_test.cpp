#include "../../domain/user.h"

#include "../../domain/name.h"
#include "../../domain/email.h"
#include "../../domain/phone_number.h"
#include "../../usecase/update_user.h"
#include "../../usecase/user_repository.h"
#include "../../usecase/notification_service.h"

#include <gtest/gtest.h>

class FakeUserRepository : public UserRepository {
public:
    std::optional<User> user;
    bool saved = false;

    std::optional<User> findById(const std::string& userId) override {
        (void)userId;
        return user;
    }

    void save(const User& updatedUser) override {
        user = updatedUser;
        saved = true;
    }
};

class FakeNotificationService : public NotificationService {
public:
    bool updateNotificationSent = false;
    bool emailChangeConfirmationSent = false;

    void sendUpdateNotification(const Email& to) override {
        (void)to;
        updateNotificationSent = true;
    }

    void sendEmailChangeConfirmation(const Email& oldEmail) override {
        (void)oldEmail;
        emailChangeConfirmationSent = true;
    }
};

TEST(UpdateUserTest, UpdateName) {
    FakeUserRepository repository;
    FakeNotificationService notificationService;

    auto oldUpdatedAt = std::chrono::system_clock::now() - std::chrono::hours(24 * 31);

    repository.user = User(
        1,
        Name("Taka"),
        Email("taka@example.com"),
        PhoneNumber("01012345678"),
        oldUpdatedAt
    );

    UpdateUser usecase(&repository, &notificationService);

    UpdateUserRequest request;
    request.name = "Taro";

    User updatedUser = usecase.execute("1", request);

    EXPECT_EQ(updatedUser.getName().getValue(), "Taro");
    EXPECT_TRUE(repository.saved);
    EXPECT_TRUE(notificationService.updateNotificationSent);
}
