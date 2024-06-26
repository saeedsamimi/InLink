#ifndef CAPTCHA_H
#define CAPTCHA_H

#include <QDebug>
#include <QFile>
#include <QFont>
#include <QImage>
#include <QObject>
#include <QPainter>
#include <QPainterPath>
#include <QStringList>
#include <QTextStream>
#include <QTime>
#include <QVector>
#include <QtMath>
#include <cstdlib>

class Captcha : public QObject {
  Q_OBJECT
  // clang-format off
  Q_PROPERTY(QFont font READ font WRITE setFont)
  Q_PROPERTY(QImage captchaImage READ captchaImage)
  Q_PROPERTY(QString captchaText READ captchaText WRITE setCaptchaText)
  Q_PROPERTY(DeformType deformationType READ deformationType WRITE setDeformationType)
  Q_PROPERTY(TextGenerationMode textGeneration READ textGeneration WRITE setTextGeneration)
  Q_PROPERTY(QStringList dictionary READ dictionary WRITE setDictionary)
  Q_PROPERTY(QColor fontColor READ fontColor WRITE setFontColor)
  Q_PROPERTY(QColor backColor READ backColor WRITE setBackColor)
  Q_PROPERTY(bool drawLines READ drawLines WRITE setDrawLines)
  Q_PROPERTY(bool drawEllipses READ drawEllipses WRITE setDrawEllipses)
  Q_PROPERTY(bool drawNoise READ drawNoise WRITE setDrawNoise)
  Q_PROPERTY(int noiseCount READ noiseCount WRITE setNoiseCount)
  Q_PROPERTY(int lineCount READ lineCount WRITE setLineCount)
  Q_PROPERTY(int ellipseCount READ ellipseCount WRITE setEllipseCount)
  Q_PROPERTY(int lineWidth READ lineWidth WRITE setLineWidth)
  Q_PROPERTY(int ellipseMinRadius READ ellipseMinRadius WRITE setEllipseMinRadius)
  Q_PROPERTY(int ellipseMaxRadius READ ellipseMaxRadius WRITE setEllipseMaxRadius)
  Q_PROPERTY(int noisePointSize READ noisePointSize WRITE setNoisePointSize)
  // clang-format off
 public:
  enum DeformType { Deform_SinCurve };

  enum TextGenerationMode { TextGeneration_Random, TextGeneration_Dictionary };
  Q_ENUM(DeformType)
  Q_ENUM(TextGenerationMode)

 public:
  explicit Captcha(QObject *parent = 0);

  QFont font() const;
  QImage captchaImage() const;
  DeformType deformationType() const;
  QString captchaText() const;
  TextGenerationMode textGeneration() const;
  const QStringList &dictionary() const;
  QColor fontColor() const;
  QColor backColor() const;
  bool drawLines() const;
  bool drawEllipses() const;
  bool drawNoise() const;
  int noiseCount() const;
  int lineCount() const;
  int ellipseCount() const;
  int lineWidth() const;
  int ellipseMinRadius() const;
  int ellipseMaxRadius() const;
  int noisePointSize() const;

 signals:
  void catpchaGenerated(const QImage &img, QString text);

 public slots:
  void setFont(const QFont &arg);
  void setDeformationType(DeformType arg);
  void updateCaptcha();
  void randomize();
  void generateText(int noOfChars = 5, bool includeNumbers = false,
                    bool includeSymbols = false, bool allCapital = true);
  void setCaptchaText(QString arg);
  void setTextGeneration(TextGenerationMode arg);
  void setDictionary(const QStringList &arg);
  void loadDictionary(QString FileName);
  void setFontColor(QColor arg);
  void setBackColor(QColor arg);
  void setSinDeform(qreal hAmplitude, qreal hFrequency, qreal vAmplitude,
                    qreal vFrequency);
  QPair<QString, QImage> generateCaptcha();
  void setDrawLines(bool arg);
  void setDrawEllipses(bool arg);
  void setDrawNoise(bool arg);
  void setNoiseCount(int arg);
  void setLineCount(int arg);
  void setEllipseCount(int arg);
  void setLineWidth(int arg);
  void setEllipseMinRadius(int arg);
  void setEllipseMaxRadius(int arg);
  void setNoisePointSize(int arg);
  void setDifficulty(int val);

 private:
  qreal m_hmod1;
  qreal m_hmod2;

  qreal m_vmod1;
  qreal m_vmod2;

  QFont m_font;
  QImage m_captchaImage;
  DeformType m_deformationType;
  QString m_captchaText;
  TextGenerationMode m_textGeneration;
  QStringList m_dictionary;
  QColor m_fontColor;
  QColor m_backColor;
  qreal m_padding;
  bool m_drawLines;
  bool m_drawEllipses;
  bool m_drawNoise;
  int m_noiseCount;
  int m_lineCount;
  int m_ellipseCount;
  int m_lineWidth;
  int m_ellipseMinRadius;
  int m_ellipseMaxRadius;
  int m_noisePointSize;
};

#endif  // CAPTCHA_H
