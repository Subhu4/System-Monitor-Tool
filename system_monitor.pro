QT       += core gui widgets charts   # <-- add charts here

CONFIG   += c++17

TEMPLATE = app
TARGET = system_monitor

# Include headers
INCLUDEPATH += include

# Source files
SOURCES += \
    src/main.cpp \
    src/system_info.cpp \
    src/process_table_model.cpp \
    src/usage_graph.cpp   # <-- usage graph cpp

# Headers for moc
HEADERS += \
    include/system_info.h \
    include/process_table_model.h \
    include/kill_button_delegate.h \
    include/usage_graph.h

# Output build dirs
OBJECTS_DIR = build/obj
MOC_DIR = build/moc
RCC_DIR = build/rcc
UI_DIR = build/ui
