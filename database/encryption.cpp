#include "encryption.hpp"

QByteArray generateKey() {
  QString secretKey(SECRET_KEY);
  return QCryptographicHash::hash(secretKey.toUtf8(),
                                  QCryptographicHash::Sha256);
}

QByteArray generateIV() {
  QByteArray iv(EVP_MAX_IV_LENGTH, 0);
  if (!RAND_bytes(reinterpret_cast<unsigned char *>(iv.data()),
                  EVP_MAX_IV_LENGTH)) {
    qFatal("Failed to generate IV");
  }
  return iv;
}

QByteArray encryptData(const QString &plaintext, const QByteArray &key,
                       QByteArray &iv) {
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    qFatal("Failed to create cipher context");
  }

  iv = generateIV(); // Generate a new IV for each encryption
  QByteArray plaintextBytes = plaintext.toUtf8();
  QByteArray encryptedData(
      plaintextBytes.size() + EVP_CIPHER_block_size(EVP_aes_256_cbc()), 0);

  int len;
  int ciphertext_len;

  if (1 !=
      EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                         reinterpret_cast<const unsigned char *>(key.data()),
                         reinterpret_cast<const unsigned char *>(iv.data()))) {
    qFatal("Encryption init failed");
  }

  if (1 != EVP_EncryptUpdate(
               ctx, reinterpret_cast<unsigned char *>(encryptedData.data()),
               &len,
               reinterpret_cast<const unsigned char *>(plaintextBytes.data()),
               plaintextBytes.size())) {
    qFatal("Encryption update failed");
  }
  ciphertext_len = len;

  if (1 != EVP_EncryptFinal_ex(
               ctx,
               reinterpret_cast<unsigned char *>(encryptedData.data()) + len,
               &len)) {
    qFatal("Encryption final failed");
  }
  ciphertext_len += len;

  encryptedData.resize(ciphertext_len);
  EVP_CIPHER_CTX_free(ctx);

  return encryptedData;
}

void saveLoginInfo(const QString &username, const QString &password,
                   const QString &filePath, const QByteArray &key) {
  QByteArray iv;
  QString plaintext = username + '\n' + password;
  QByteArray encryptedData = encryptData(plaintext, key, iv);

  QFile file(filePath);
  if (file.open(QIODevice::WriteOnly)) {
    QDataStream out(&file);
    out << iv << encryptedData;
    file.close();
  }
}

QByteArray decryptData(const QByteArray &encryptedData, const QByteArray &key,
                       const QByteArray &iv) {
  EVP_CIPHER_CTX *ctx = EVP_CIPHER_CTX_new();
  if (!ctx) {
    qFatal("Failed to create cipher context");
  }

  QByteArray decryptedData(encryptedData.size(), 0);

  int len;
  int plaintext_len;

  // clang-format off
  if (EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL,
                         reinterpret_cast<const unsigned char *>(key.data()),
                         reinterpret_cast<const unsigned char *>(iv.data())) != 1) {
    qFatal("Decryption init failed");
  }

  if (EVP_DecryptUpdate(ctx, reinterpret_cast<unsigned char *>(decryptedData.data()),
               &len,reinterpret_cast<const unsigned char *>(encryptedData.data()),encryptedData.size()) != 1) {
    qFatal("Decryption update failed");
  }
  plaintext_len = len;

  if (EVP_DecryptFinal_ex(ctx,reinterpret_cast<unsigned char *>(decryptedData.data()) + len,&len) != 1) {
    qFatal("Decryption final failed");
  }
  // clang-format on
  plaintext_len += len;

  decryptedData.resize(plaintext_len);
  EVP_CIPHER_CTX_free(ctx);

  return decryptedData;
}

QStringList readLoginInfo(const QString &filePath, const QByteArray &key) {
  QFile file(filePath);
  if (file.open(QIODevice::ReadOnly)) {
    QDataStream in(&file);
    QByteArray iv, encryptedData;
    in >> iv >> encryptedData;
    file.close();

    QByteArray decryptedData = decryptData(encryptedData, key, iv);
    QString decryptedString = QString::fromUtf8(decryptedData).trimmed();
    return decryptedString.split('\n');
  }
  return QStringList();
}

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
