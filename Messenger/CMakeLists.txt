# CMakeList.txt: проект CMake для Messenger; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#

# Добавьте источник в исполняемый файл этого проекта.
add_executable (Messenger  "main.cpp" "User.h" "User.cpp" "Chat.h" "Chat.cpp" "Message.h" "Message.cpp" "Program.h" "Program.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Messenger PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
