#include <QApplication>
#include <QCommandLineParser>

#include <KAboutData>
#include <KLocalizedString>

#include "mainwindow.h"

int main(int argc, char *argv[]) {
  QApplication app(argc, argv);
  KLocalizedString::setApplicationDomain("livetikz");

  KAboutData aboutData(
    QStringLiteral("livetikz"),
    i18n("LiveTikZ"),
    QStringLiteral("0.1"),
    i18n("A TikZ editor with live preview."),
    KAboutLicense::GPL,
    i18n("(c) 2017 Michael Schwarz"),
    "",
    "https://misc0110.net"
    );

  QCommandLineParser parser;
  parser.setApplicationDescription(QCoreApplication::translate("main", "A TikZ editor with live preview."));
  parser.addHelpOption();
  parser.addVersionOption();
  parser.addPositionalArgument("file", QCoreApplication::translate("main", "Document to open."));
  aboutData.setupCommandLine(&parser);
  parser.process(app);
  aboutData.processCommandLine(&parser);

  MainWindow *window = new MainWindow();
  window->show();

  const QStringList args = parser.positionalArguments();
  if (args.count()) {
    window->load(QUrl::fromLocalFile(args.at(0)));
  }

  return app.exec();
}
