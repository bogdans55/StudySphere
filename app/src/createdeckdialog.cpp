#include "lib/createdeckdialog.h"
#include "ui_createdeckdialog.h"

#include <QMessageBox>

CreateDeckDialog::CreateDeckDialog(QWidget *parent) : QDialog(parent), ui(new Ui::CreateDeckDialog)
{
	ui->setupUi(this);

	deckPrivacy = new QButtonGroup(this);
	deckPrivacy->addButton(ui->radioButton_private, 1);
	deckPrivacy->addButton(ui->radioButton_public, 2);
}

CreateDeckDialog::~CreateDeckDialog()
{
	delete ui;
}

QString CreateDeckDialog::getDeckName() const
{
	return ui->lineEdit_deckName->text();
}

Privacy CreateDeckDialog::getDeckPrivacy() const
{
	return deckPrivacy->checkedId() == 1 ? Privacy::PRIVATE : Privacy::PUBLIC;
}

void CreateDeckDialog::on_buttonBox_done_accepted()
{
	if (getDeckName().trimmed().isEmpty()) {
		QMessageBox::critical(this, tr("Pogrešan unos"), tr("Niste popunili polje za naziv špila!"));
		reject();
	}
}
