######################################################################
# Automatically generated by qmake (2.01a) ?? 10? 6 13:20:25 2009
######################################################################

TEMPLATE = app
QT += network
TARGET = wing
DESTDIR = bin
UI_DIR = src/gui
DEFINES += QT_DEBUG
win32{
    CONFIG += console
    LIBS += -lws2_32
    RC_FILE = winresources.rc
}
RESOURCES += resources.qrc
TRANSLATIONS = wing_zh.ts

DEPENDPATH += . \
              src/core \
              src/gui \
              src/packets \
              src/core/feeds \
              src/core/lib \
              src/packets/inPackets \
              src/packets/outPackets
INCLUDEPATH += . \
               src/core \
               src/core/lib \
               src/core/feeds \
               src/gui \
               src/packets \
               src/packets/inPackets \
               src/packets/outPackets

# Input
HEADERS += src/core/BuddyInfo.h \
           src/core/BuddyInfoManager.h \
           src/core/EventStruct.h \
           src/core/LoginModule.h \
           src/core/NetworkManager.h \
           src/core/PacketProcesser.h \
           src/core/PacketStorage.h \
           src/core/WingEventProcesser.h \
           src/core/WingMain.h \
           src/core/WingUser.h \
           src/gui/GuiHandling.h \
           src/gui/WingDialogWindow.h \
           src/gui/WingLoginWindow.h \
           src/gui/WingMainWindow.h \
           src/gui/WingSystemTray.h \
           src/gui/WingTabWidget.h \
           src/packets/AllPacketsHead.h \
           src/packets/InPacket.h \
           src/packets/OutPacket.h \
           src/packets/Packet.h \
           src/packets/PacketBuilder.h \
           src/core/feeds/Signature.h \
           src/core/lib/crypt.h \
           src/core/lib/md5.h \
           src/core/lib/QQKeys.h \
           src/core/lib/ToolKit.h \
           src/core/lib/WingDebug.h \
           src/core/lib/Wingdefines.h \
           src/packets/inPackets/FriendChangeStatusPacket.h \
           src/packets/inPackets/ReceiveIMPacket.h \
           src/packets/inPackets/SignatureOpReplyPacket.h \
           src/packets/inPackets/TouchReplyPacket.h \
           src/packets/outPackets/ChangeStatusPacketStuff.h \
           src/packets/outPackets/GetFriendListPacketStuff.h \
           src/packets/outPackets/GetFriendOnlineListPacketStuff.h \
           src/packets/outPackets/GetUserInfoPacketStuff.h \
           src/packets/outPackets/GetVerifyPngPacketStuff.h \
           src/packets/outPackets/KeepAlivePacketStuff.h \
           src/packets/outPackets/LoginTokenRequestPacketStuff.h \
           src/packets/outPackets/LogoutPacketStuff.h \
           src/packets/outPackets/PreLoginTokenRequestPacketStuff.h \
           src/packets/outPackets/PreSessionKeyRequestPacketStuff.h \
           src/packets/outPackets/ReceiveIMReplyPacketStuff.h \
           src/packets/outPackets/SendIMPacketStuff.h \
           src/packets/outPackets/SessionKeyRequestPacketStuff.h \
           src/packets/outPackets/SignatureOpPacket.h \
           src/packets/outPackets/TouchRequestPacketStuff.h
FORMS += src/gui/DialogWindow.ui src/gui/LoginWindow.ui src/gui/MainWindow.ui
SOURCES += src/core/BuddyInfo.cpp \
           src/core/BuddyInfoManager.cpp \
           src/core/EventStruct.cpp \
           src/core/LoginModule.cpp \
           src/core/main.cpp \
           src/core/NetworkManager.cpp \
           src/core/PacketProcesser.cpp \
           src/core/PacketStorage.cpp \
           src/core/WingEventProcesser.cpp \
           src/core/WingMain.cpp \
           src/core/WingUser.cpp \
           src/gui/GuiHandling.cpp \
           src/gui/WingDialogWindow.cpp \
           src/gui/WingLoginWindow.cpp \
           src/gui/WingMainWindow.cpp \
           src/gui/WingSystemTray.cpp \
           src/packets/InPacket.cpp \
           src/packets/OutPacket.cpp \
           src/packets/Packet.cpp \
           src/packets/PacketBuilder.cpp \
           src/core/feeds/Signature.cpp \
           src/core/lib/crypt.cpp \
           src/core/lib/md5.c \
           src/core/lib/QQKeys.cpp \
           src/core/lib/ToolKit.cpp \
           src/packets/inPackets/FriendChangeStatusPacket.cpp \
           src/packets/inPackets/ReceiveIMPacket.cpp \
           src/packets/inPackets/SignatureOpReplyPacket.cpp \
           src/packets/inPackets/TouchReplyPacket.cpp \
           src/packets/outPackets/ChangeStatusPacketStuff.cpp \
           src/packets/outPackets/GetFriendListPacketStuff.cpp \
           src/packets/outPackets/GetFriendOnlineListPacketStuff.cpp \
           src/packets/outPackets/GetUserInfoPacketStuff.cpp \
           src/packets/outPackets/GetVerifyPngPacketStuff.cpp \
           src/packets/outPackets/KeepAlivePacketStuff.cpp \
           src/packets/outPackets/LoginTokenRequestPacketStuff.cpp \
           src/packets/outPackets/LogoutPacketStuff.cpp \
           src/packets/outPackets/PreLoginTokenRequestPacketStuff.cpp \
           src/packets/outPackets/PreSessionKeyRequestPacketStuff.cpp \
           src/packets/outPackets/ReceiveIMReplyPacketStuff.cpp \
           src/packets/outPackets/SendIMPacketStuff.cpp \
           src/packets/outPackets/SessionKeyRequestPacketStuff.cpp \
           src/packets/outPackets/SignatureOpPacket.cpp \
           src/packets/outPackets/TouchRequestPacketStuff.cpp
           
