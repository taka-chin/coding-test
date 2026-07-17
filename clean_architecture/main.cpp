#include <iostream>
#include <map>
#include <string>
#include "database/database.cpp"
#include "database/database_user_repository.h"
#include "mailer/mailer.cpp"
#include "mailer/mailer_notification_service.h"
#include "controller/user_controller.h"

using namespace std;

int main() {
    cout << "=== ユーザー情報更新システム ===" << endl << endl;
    
    Database db;
    Mailer mailer;

    // 初期化
    DatabaseUserRepository userRepository(&db);
    MailerNotificationService notificationService(&mailer);

    UpdateUser updateUser(&userRepository, &notificationService);
    UserController controller(&updateUser);

    // テストユーザー作成
    map<string, string> newUser;
    newUser["id"] = "1";
    newUser["name"] = "山田太郎";
    newUser["email"] = "yamada@example.com";
    newUser["phone"] = "09012345678";
    newUser["updated_at"] = "0";
    map<string, string> user = db.create_user(newUser);
    cout << "ユーザー作成: ID=" << user["id"] << ", " << user["name"] << ", " << user["email"] << endl << endl;

    // 電話番号更新
    cout << "1. 電話番号更新" << endl;
    try {
        UpdateUserRequest request;
        request.phone = "09099998888";
        controller.update_user(user["id"], request);
        cout << "✓ 更新成功" << endl;
    } catch (const exception& e) {
        cout << "✗ エラー: " << e.what() << endl;
    }
    cout << endl;

    // 名前更新
    cout << "2. 名前更新" << endl;
    try {
        UpdateUserRequest request;
        request.name = "山田花子";
        controller.update_user(user["id"], request);
        cout << "✓ 更新成功" << endl;
    } catch (const exception& e) {
        cout << "✗ エラー: " << e.what() << endl;
    }
    cout << endl;

    // メールアドレス更新
    cout << "3. メールアドレス更新" << endl;
    try {
        UpdateUserRequest request;
        request.email = "hanako@example.com";
        controller.update_user(user["id"], request);
        cout << "✓ 更新成功" << endl;
    } catch (const exception& e) {
        cout << "✗ エラー: " << e.what() << endl;
    }
    cout << endl;

    // バリデーションエラー（空の名前）
    cout << "4. バリデーションエラー（空の名前）" << endl;
    try {
        UpdateUserRequest request;
        request.name = "";
        controller.update_user(user["id"], request);
        cout << "✓ 更新成功" << endl;
    } catch (const exception& e) {
        cout << "✗ エラー: " << e.what() << endl;
    }
    cout << endl;

    // 名前の再変更
    try {
        UpdateUserRequest request;
        request.name = "田中一郎";
        controller.update_user(user["id"], request);
        cout << "✓ 更新成功" << endl;
    } catch (const exception& e) {
        cout << "✗ エラー: " << e.what() << endl;
    }
    
    return 0;
}
