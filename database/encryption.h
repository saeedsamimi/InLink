#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <QCryptographicHash>

QString hashUsingSHA256(const QString &input) {
  // Convert QString to QByteArray
  QByteArray byteArray = input.toUtf8();

  // Hash the QByteArray using SHA-256
  QByteArray hash =
      QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256);

  // Convert the hashed QByteArray back to QString
  QString hashedString(hash.toHex());

  return hashedString;
}

#endif  // ENCRYPTION_H
