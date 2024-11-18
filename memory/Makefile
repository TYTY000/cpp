# 定义编译器
CC = g++

# 定义编译选项
CFLAGS = -Wall -g

# 定义目标文件
TARGET = mp_test

# 定义源文件
SRCS = memorypool_test.cc

# 定义头文件
HDRS = memorypool.h

# 定义对象文件
OBJS = $(SRCS:.cc=.o)

# 默认目标
all: $(TARGET)

# 链接目标文件
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译源文件
%.o: %.cc $(HDRS)
	$(CC) $(CFLAGS) -c $< -o $@

# 运行测试
test: $(TARGET)
	./$(TARGET)

# 清理目标文件和对象文件
clean:
	rm -f $(TARGET) $(OBJS)

