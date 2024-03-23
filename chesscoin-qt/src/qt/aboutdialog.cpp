#include "aboutdialog.h"
#include "ui_aboutdialog.h"
#include "clientmodel.h"

#include "version.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);

    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowCloseButtonHint);

#if (defined (WIN32) || defined (WIN64))
    setMinimumSize(560, 250);
    setMaximumSize(560, 250);
    resize(560, 250);
#elif (defined (LINUX) || defined (__linux__))
    setMinimumSize(600, 300);
    setMaximumSize(600, 300);
    resize(600, 300);
#else
    setMinimumSize(600, 350);
    setMaximumSize(600, 350);
    resize(600, 350);
#endif
}

void AboutDialog::setModel(ClientModel *model)
{
    if(model)
    {
        ui->versionLabel->setText(model->formatFullVersion());
    }
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_buttonBox_accepted()
{
    close();
}

