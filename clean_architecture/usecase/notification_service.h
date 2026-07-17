#pragma once
#include "../domain/email.h"

// 2. **更新通知メールの送信**
//    - 更新があったUserにメールを送信
//    - 重要な変更（メール、名前）は必ず通知
//    - 電話番号のみの変更は通知しない
//    - メールアドレス変更時は確認メールを送信

class NotificationService {
public:
    virtual void sendUpdateNotification(const Email& to) = 0;
    virtual void sendEmailChangeConfirmation(const Email& oldEmail) = 0;
    virtual ~NotificationService() = default;
};