TEMPLATE = subdirs

core.subdir = coreSQLiteStudio

tests.subdir = Tests
tests.depends = core

gui.subdir = guiSQLiteStudio
gui.depends = core

cli.subdir = sqlitestudiocli
cli.depends = core

gui_app.subdir = sqlitestudio
gui_app.depends = gui

update_app.subdir = UpdateSQLiteStudio
update_app.depends = core

SUBDIRS += \
    core \
    gui \
    cli \
    gui_app

if(contains(DEFINES,tests)) {
    SUBDIRS += tests
}

win32: {
    SUBDIRS += update_app
}

linux: {
    portable.commands = sh $$PWD/create_linux_portable.sh $$PWD/../output $$QMAKE_QMAKE
    tgz.commands = sh $$PWD/create_linux_portable.sh $$PWD/../output $$QMAKE_QMAKE tgz
    QMAKE_EXTRA_TARGETS += portable tgz
}

macx: {
    bundle.commands = sh $$PWD/create_macosx_bundle.sh $$PWD/../output $$QMAKE_QMAKE
    dmg.commands = sh $$PWD/create_macosx_bundle.sh $$PWD/../output $$QMAKE_QMAKE dmg
    QMAKE_EXTRA_TARGETS += bundle dmg
}