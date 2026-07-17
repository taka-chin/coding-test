# コンパイラとフラグ
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

# ターゲット実行ファイル名
TARGET = a.out

# ソースファイル
SOURCES = main.cpp

# ヘッダーファイル
HEADERS = domain/user.h domain/email.h domain/name.h domain/phone_number.h usecase/update_user.h usecase/user_repository.h usecase/notification_service.h database/database.cpp database/database_user_repository.h mailer/mailer.cpp mailer/mailer_notification_service.h controller/user_controller.h

# デフォルトターゲット
all: $(TARGET)

# 実行ファイルのビルド
$(TARGET): $(SOURCES) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

# 実行
run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TEST_TARGET)

re: clean all

.PHONY: all run clean rebuild

# GoogleTest
GTEST_DIR = $(shell brew --prefix googletest)

TEST_CFLAGS = -I$(GTEST_DIR)/include

TEST_LDFLAGS = -L$(GTEST_DIR)/lib

TEST_TARGET = test_runner

TEST_SOURCES = tests/domain/*.cpp tests/usecase/*.cpp tests/database/*.cpp tests/mailer/*.cpp

TEST_LIBS = -lgtest -lgtest_main -pthread

test:
	$(CXX) $(CXXFLAGS) \
	$(TEST_CFLAGS) \
	$(TEST_SOURCES) \
	$(TEST_LDFLAGS) \
	$(TEST_LIBS) \
	-o $(TEST_TARGET) \

run-test: test
	./$(TEST_TARGET)
