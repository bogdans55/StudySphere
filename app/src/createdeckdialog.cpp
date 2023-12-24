#include "lib/createdeckdialog.h"
#include "ui_createdeckdialog.h"

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
	//    return deckPrivacy->checkedId();
}
