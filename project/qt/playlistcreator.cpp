//#include "CustomWidgets.h"
#include "MainWindow.h"
#include "playlistcreator.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>
//#include <QLabel>

PlaylistCreator::PlaylistCreator(MainWindow *_parent) : parent(_parent) {

    Layout = new QVBoxLayout;
    setLayout(Layout);

    TextFields = new QList<QLineEdit*>;
    //FieldsWidget = new QWidget();
    grid = new QGridLayout;
    //Layout = new QVBoxLayout(this);
    submitBtn = new QPushButton("Submit");
    AddPlaylistBtn = new QPushButton("Add Song");
    AddSongBtn = new QPushButton("Add Playlist");
        grid->addWidget(createFirstExclusiveGroup(), 0, 0);
        grid->addWidget(createNonExclusiveGroup(), 0, 1);
        rawCounter = 1;
        AddPlaylist();

    Layout->addLayout(grid);
    gridButtons = new QGridLayout;
        gridButtons->addWidget(AddPlaylistBtn, 0, 0);
        gridButtons->addWidget(AddSongBtn, 0, 1);
    Layout->addLayout(gridButtons);
    Layout->addWidget(submitBtn);
    //FieldsWidget->setLayout(grid);
    //Layout->addWidget(Text);

    //Layout->addWidget(submitBtn);

    connect(submitBtn, SIGNAL(clicked()), this, SLOT(SubmitPlaylist()));
    connect(AddPlaylistBtn, SIGNAL(clicked()), this, SLOT(AddPlaylist()));
    connect(AddSongBtn, SIGNAL(clicked()), this, SLOT(AddSong()));
}

void PlaylistCreator::AddPlaylist() {
    grid->addWidget(createLable(". Playlist"), rawCounter, 0);
    TextFields->push_back(createLinedEdit("Enter Playlist URL"));
    grid->addWidget(TextFields->at(rawCounter - 1), rawCounter, 1);
    ++rawCounter;
}

void PlaylistCreator::AddSong() {
    grid->addWidget(createLable(". Song "), rawCounter, 0);
    TextFields->push_back(createLinedEdit("Enter Song URL"));
    grid->addWidget(TextFields->at(rawCounter - 1), rawCounter, 1);
    ++rawCounter;
}

void PlaylistCreator::SubmitPlaylist() {
    //for (unsigned int i = 0; i < rawCounter - 2; ++i){
    //    text = dynamic_cast<QLineEdit*>(grid->itemAtPosition(1, 1)->widget());
    //}
    parent->SumbitPlaylist(TextFields->at(0)->text());

    this->close();

    //SendPlaylist(text.toStdString(), UserID);
}

QGroupBox *PlaylistCreator::createFirstExclusiveGroup()
{
    QGroupBox *groupBox = new QGroupBox(tr("From"));

    QRadioButton *radioYT = new QRadioButton(tr("Youtube"));
    QRadioButton *radioSpoty = new QRadioButton(tr("Spotify"));
    //QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));

    radioYT->setChecked(true);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radioYT);
    vbox->addWidget(radioSpoty);
    //vbox->addWidget(radio3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QLabel* PlaylistCreator::createLable(QString name) {
    name.prepend(QString::number(rawCounter));
    QLabel* lable = new QLabel(name);
    return lable;
}

QLineEdit* PlaylistCreator::createLinedEdit(QString placeHolder) {
    QLineEdit* lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(QString(placeHolder));
    return lineEdit;
}

QGroupBox *PlaylistCreator::createNonExclusiveGroup() {
    QGroupBox *groupBox = new QGroupBox(tr("Transform to"));
    groupBox->setFlat(true);
    QCheckBox *checkBoxYT = new QCheckBox(tr("Youtube"));
    QCheckBox *checkBoxSpoty = new QCheckBox(tr("Spotify"));
    checkBoxSpoty->setChecked(true);
    //QCheckBox *checkBox3 = new QCheckBox(tr("Checkbox 2"));
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(checkBoxYT);
    vbox->addWidget(checkBoxSpoty);
    //vbox->addWidget(checkBox3);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}
