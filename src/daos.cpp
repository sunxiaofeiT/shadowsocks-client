//
// Created by pikachu on 17-8-6.
//

#include <QtCore/QFileInfo>
#include <QtCore/QDir>
#include "daos.h"
#include <QDebug>
GuiConfigDao::GuiConfigDao() {
//    configFile.setFileName(QObject::tr("%1/.ss/gui-config.json").arg(QDir::homePath()));
    configFile.setFileName("/home/pikachu/Dropbox/备份/gui-config.json");
    if (!configFile.exists()) {
        qDebug() << "配置文件不存在,写入新的配置文件";
        QDir dir;
        dir.mkpath(QFileInfo(configFile).absolutePath());

        configFile.open(QIODevice::WriteOnly | QIODevice::Text);
        configFile.close();
    }
}
void GuiConfigDao::save(GuiConfig guiConfig) {
    if (!configFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "can't open config file " << configFile.fileName();
        exit(0);
    }
    QJsonDocument jsonDocument(guiConfig.toJsonObject());
    configFile.write(jsonDocument.toJson());
    configFile.close();
}

GuiConfig GuiConfigDao::get() {
    if (!configFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "can't open config file " << configFile.fileName();
        exit(0);
    }
    if (!configFile.isReadable()) {
        qDebug() << "config file " << configFile.fileName()
                 << " is not readable!";
        exit(0);
    }
    QJsonDocument jsonDocument;
    auto json = configFile.readAll();
    qDebug()<<"json"<<json;
    jsonDocument = jsonDocument.fromJson(json);
    qDebug()<<"json doc"<<jsonDocument.toJson();
    GuiConfig guiConfig;
    guiConfig.fromJsonObject(jsonDocument.object());
    configFile.close();
    return guiConfig;
}
