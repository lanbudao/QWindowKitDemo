#include "widgetuseuifile.h"
#include "ui_WidgetUseUiFile.h"

WidgetUseUiFile::WidgetUseUiFile(QWidget *parent) :
    QWK::FramelessWidget(parent),
    ui(new Ui::WidgetUseUiFile)
{
    setupUi<Ui::WidgetUseUiFile>(ui);
    setTheme(Dark);
    resize(600, 480);
}

WidgetUseUiFile::~WidgetUseUiFile() {
    delete ui;
}
