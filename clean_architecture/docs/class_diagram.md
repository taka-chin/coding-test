# 詳細クラス図

現在の設計方針では、`User` をドメインの中心に置き、`Name` / `Email` / `PhoneNumber` を Value Object として保持する。
ユースケース層の `UpdateUser` は、DB やメール送信の具体実装には依存せず、`UserRepository` と `NotificationService` のインターフェースに依存する。

```mermaid
classDiagram
direction LR

class User {
  <<Entity>>
  -int id
  -Name name
  -Email email
  -PhoneNumber phoneNumber
  -system_clock::time_point updatedAt
  +User(int id, Name name, Email email, PhoneNumber phoneNumber, time_point updatedAt)
  +int getId()
  +Name getName()
  +Email getEmail()
  +PhoneNumber getPhoneNumber()
  +void updateName(Name newName, time_point now)
  +void updateEmail(Email newEmail, time_point now)
  +void updatePhoneNumber(PhoneNumber newPhoneNumber, time_point now)
  +bool canUpdate(time_point now)
}

class Name {
  <<ValueObject>>
  -string value
  +Name(string value)
  +string getValue()
  -bool allDigit(string value)
  -void validate(string value)
}

class Email {
  <<ValueObject>>
  -string value
  +Email(string value)
  +string getValue()
  -void validate(string value)
}

class PhoneNumber {
  <<ValueObject>>
  -string value
  +PhoneNumber(string value)
  +string getValue()
  -void validate(string value)
}

class UpdateUser {
  <<UseCase>>
  -UserRepository* userRepository
  -NotificationService* notificationService
  +UpdateUser(UserRepository* userRepository, NotificationService* notificationService)
  +User execute(string userId, UpdateUserRequest request)
}

class UpdateUserRequest {
  <<DTO>>
  +optional~string~ name
  +optional~string~ email
  +optional~string~ phone
}

class UserRepository {
  <<Interface>>
  +optional~User~ findById(string userId)
  +void save(User user)
}

class NotificationService {
  <<Interface>>
  +void sendUpdateNotification(Email to)
  +void sendEmailChangeConfirmation(Email oldEmail)
}

class DatabaseUserRepository {
  <<Infrastructure>>
  -Database* database
  +optional~User~ findById(string userId)
  +void save(User user)
}

class MailerNotificationService {
  <<Infrastructure>>
  -Mailer* mailer
  +void sendUpdateNotification(Email to)
  +void sendEmailChangeConfirmation(Email oldEmail)
}

User *-- Name
User *-- Email
User *-- PhoneNumber

UpdateUser --> UpdateUserRequest
UpdateUser --> User
UpdateUser --> UserRepository
UpdateUser --> NotificationService

UserRepository <|.. DatabaseUserRepository
NotificationService <|.. MailerNotificationService

DatabaseUserRepository --> User
MailerNotificationService --> Email
```

## 依存の向き

```mermaid
flowchart TD
  Controller[controller]
  UseCase[usecase: UpdateUser]
  Domain[domain: User / Value Objects]
  Ports[interfaces: UserRepository / NotificationService]
  Infra[database / mailer implementations]
  External[Database / Mailer]

  Controller --> UseCase
  UseCase --> Domain
  UseCase --> Ports
  Infra --> Ports
  Infra --> Domain
  Infra --> External
```

## 責務の分担

- `Name` / `Email` / `PhoneNumber`: 値そのものの妥当性を守る。
- `User`: ユーザーの状態を持ち、更新日時や30日制限などユーザーに関するルールを扱う。
- `UpdateUser`: ユーザー取得、更新、保存、通知依頼というアプリケーションの手順を扱う。
- `UserRepository`: `UpdateUser` がユーザーを取得・保存するための抽象。
- `NotificationService`: `UpdateUser` が通知を依頼するための抽象。
- `DatabaseUserRepository`: `Database` と `User` の変換を担当する外側の実装。
- `MailerNotificationService`: `Mailer` を使って通知を送る外側の実装。
