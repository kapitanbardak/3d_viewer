QT       += core gui opengl printsupport
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(./qt-gif-image-master/src/gifimage/qtgifimage.pri)

CONFIG += c++17 sdk_no_version_check
DEFINES += QT_OPENGL_LIB

INCLUDEPATH += .

mac {
    DEFINES += __APPLE__
    INCLUDEPATH += /opt/homebrew/include
    QT += openglwidgets
}
linux {
    LIBS += -lGL -lGLU
}

windows {
    LIBS += -lopengl32 -lglu32 -lgdi32
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/commands/change_item_color_command.cc \
    controller/commands/change_item_type_command.cc \
    controller/commands/change_model_command.cc \
    controller/commands/change_projection_mode_command.cc \
    controller/items_property_controller.cc \
    controller/commands/items_size_command.cc \
    controller/commands/open_file_command.cc \
    controller/commands/save_gif_command.cc \
    controller/commands/save_img_command.cc \
    controller/commands/reset_position_command.cc \
    controller/cursorchecker.cc \
    core/glcanvas.cc \
    core/main.cpp \
    core/settings.cc \
    model/interface/data_model.cc \
    model/object_3d.cc \
    model/parser.cc \
    model/strategy/move_strategy.cc \
    model/strategy/rotate_strategy.cc \
    model/strategy/scale_strategy.cc \
    view/mainwindow.cc \
    controller/controller.cc


HEADERS += \
    controller/commands/change_item_color_command.h \
    controller/items_property_controller.h \
    controller/commands/change_item_type_command.h \
    controller/commands/change_model_command.h \
    controller/commands/change_projection_mode_command.h \
    controller/commands/commands_list.h \
    controller/commands/interface_controller_command.h \
    controller/commands/items_size_command.h \
    controller/commands/open_file_command.h \
    controller/commands/save_gif_command.h \
    controller/commands/save_img_command.h \
    controller/commands/reset_position_command.h \
    controller/cursorchecker.h \
    core/glcanvas.h \
    core/internal_names.h \
    core/settings.h \
    model/interface/data_model.h \
    model/object_3d.h \
    model/parser.h \
    model/strategy/interface_object_transformation_strategy.h \
    model/strategy/move_strategy.h \
    model/strategy/rotate_strategy.h \
    model/strategy/scale_strategy.h \
    view/mainwindow.h \
    controller/controller.h


FORMS += \
    view/mainwindow.ui

RESOURCES += resources.qrc

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
