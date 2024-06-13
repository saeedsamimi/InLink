#ifndef ENCRYPTION_HPP
#define ENCRYPTION_HPP

#include <QByteArray>
#include <QCryptographicHash>
#include <QDataStream>
#include <QDebug>
#include <QFile>
#include <QIODevice>
#include <QtCore>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <secret_key.h>

QByteArray generateKey();

QByteArray generateIV();

QByteArray encryptData(const QString &plaintext, const QByteArray &key,
                       QByteArray &iv);

void saveLoginInfo(const QString &username, const QString &password,
                   const QString &filePath, const QByteArray &key);

QByteArray decryptData(const QByteArray &encryptedData, const QByteArray &key,
                       const QByteArray &iv);

QStringList readLoginInfo(const QString &filePath, const QByteArray &key);

QString hashUsingSHA256(const QString &input);

#endif // ENCRYPTION_HPP
