# CMakeList.txt: проект CMake для Messenger; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#


# Добавьте источник в исполняемый файл этого проекта.
add_executable (Messenger "main.cpp" "User.h" "User.cpp" "Chat.h" "Chat.cpp" "Message.h" "Message.cpp" "Program.h" "Program.cpp" "SQL.h" "SQL.cpp" "Connection.h" "Connection.cpp")

if(${CMAKE_SYSTEM_NAME} STREQUAL Windows)

target_include_directories(Messenger PRIVATE
"C:/Users/olezh/source/repos/libraries/json/include"
"C:/Users/olezh/source/repos/libraries/boost_1_82_0"
"C:/Program Files/MySQL/MySQL Server 8.0/include")

target_link_libraries(Messenger PRIVATE
"C:/Program Files/MySQL/MySQL Server 8.0/lib/libmysql.lib")

elseif(${CMAKE_SYSTEM_NAME} STREQUAL Linux)

target_include_directories(Messenger PRIVATE
"/usr/include"
"~/lib/json/include")

endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Messenger PROPERTY CXX_STANDARD 20)
endif()
# TODO: Добавьте тесты и целевые объекты, если это необходимо.
