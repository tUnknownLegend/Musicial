#include "MainWindow.h"
#include "playlistcreator.h"
#include <QGroupBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QGridLayout>
#include <QMessageBox>

PlaylistCreator::PlaylistCreator(MainWindow *_parent) : parent(_parent) {
    setWindowTitle("Generate Playlist");
    Layout = new QVBoxLayout;
    setLayout(Layout);

    PlaylistFields = new QList<QLineEdit *>;
    SongFields = new QList<QLineEdit *>;
    fromPlatformList = new QList<QRadioButton *>;
    toPlatformList = new QList<QCheckBox *>;

    grid = new QGridLayout;
    submitBtn = new QPushButton("Submit");
    AddPlaylistBtn = new QPushButton("Add Playlist");
    AddSongBtn = new QPushButton("Add Song");
    grid->addWidget(createExclusiveGroup(*fromPlatformList), 0, 0);
    grid->addWidget(createNonExclusiveGroup(*toPlatformList), 0, 1);
    rawCounter = 1;
    AddPlaylist();

    Layout->addLayout(grid);
    gridButtons = new QGridLayout;
    gridButtons->addWidget(AddPlaylistBtn, 0, 0);
    gridButtons->addWidget(AddSongBtn, 0, 1);
    Layout->addLayout(gridButtons);
    Layout->addWidget(submitBtn);

    connect(submitBtn, SIGNAL(clicked()), this, SLOT(SubmitPlaylist()));
    connect(AddPlaylistBtn, SIGNAL(clicked()), this, SLOT(AddPlaylist()));
    connect(AddSongBtn, SIGNAL(clicked()), this, SLOT(AddSong()));
}

void PlaylistCreator::AddPlaylist() {
    grid->addWidget(createLable(". Playlist"), rawCounter, 0);
    PlaylistFields->push_back(createLinedEdit("Enter Playlist URL"));
    grid->addWidget(PlaylistFields->back(), rawCounter, 1);
    ++rawCounter;
}

void PlaylistCreator::AddSong() {
    grid->addWidget(createLable(". Song "), rawCounter, 0);
    SongFields->push_back(createLinedEdit("Enter Song URL"));
    grid->addWidget(SongFields->back(), rawCounter, 1);
    ++rawCounter;
}

void PlaylistCreator::SubmitPlaylist() {
    sharedLib::Platform fromPlatform = sharedLib::None;
    unsigned int platformN = sharedLib::YouTube;

    for (auto &i : *fromPlatformList) {
        if (i->isChecked())
            fromPlatform = (sharedLib::Platform) platformN;
        ++platformN;
    }

    if (!ShowErrorMessage(fromPlatform == sharedLib::None,
        tr("Choose from which platform to transform")))
        return;

    std::vector<sharedLib::Platform> toPlatform;
    platformN = sharedLib::YouTube;
    for (auto &i : *toPlatformList) {
        ++platformN;
        if (i->isChecked())
            toPlatform.emplace_back((sharedLib::Platform) platformN);
    }

    if (!ShowErrorMessage(toPlatform.size() == 0,
        tr("Choose to which platform(s) to transform")))
        return;

    std::vector<sharedLib::Playlist> playlists;
    for (auto &i : *PlaylistFields) {
        playlists.emplace_back(
            sharedLib::Playlist(
                sharedLib::URL(i->text().toStdString()), fromPlatform));
    }

    std::vector<sharedLib::Song> songs;
    for (auto &i : *SongFields) {
        songs.emplace_back(
            sharedLib::Song(
                sharedLib::URL(i->text().toStdString()), fromPlatform));
    }

    if (!ShowErrorMessage(playlists.size() == 0 && songs.size() == 0,
                          tr("Insert at least one link to playlist or song")))
        return;

    if (playlists.size() != 0 &&
        !ShowErrorMessage(
            !client::checkURLs<sharedLib::Playlist>(
                playlists.begin(), playlists.end()),
                          tr("Wrong playlist URL format")))
        return;

    if (songs.size() != 0 &&
        !ShowErrorMessage(
            !client::checkURLs<sharedLib::Song>(songs.begin(), songs.end()),
            tr("Wrong song URL format")))
        return;

    client::MessageGroup messages(
        std::to_string(rawCounter) + " field(s) was sent",
        USER_ID, fromPlatform, playlists, songs, toPlatform);

    parent->SumbitPlaylist(messages);

    this->close();
}

QGroupBox *PlaylistCreator::createExclusiveGroup(QList<QRadioButton *> &list) {
    QGroupBox *groupBox = new QGroupBox(tr("From"));

    QRadioButton *radioYT = new QRadioButton(tr("Youtube"));
    QRadioButton *radioSpoty = new QRadioButton(tr("Spotify"));
    list.append(radioYT);
    list.append(radioSpoty);

    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(radioYT);
    vbox->addWidget(radioSpoty);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

QLabel *PlaylistCreator::createLable(QString name) {
    name.prepend(QString::number(rawCounter));
    QLabel *lable = new QLabel(name);
    return lable;
}

QLineEdit *PlaylistCreator::createLinedEdit(QString placeHolder) {
    QLineEdit *lineEdit = new QLineEdit();
    lineEdit->setPlaceholderText(QString(placeHolder));
    return lineEdit;
}

QGroupBox *PlaylistCreator::createNonExclusiveGroup(QList<QCheckBox *> &list) {
    QGroupBox *groupBox = new QGroupBox(tr("Transform to"));
    groupBox->setFlat(true);
    QCheckBox *checkBoxYT = new QCheckBox(tr("Youtube"));
    QCheckBox *checkBoxSpoty = new QCheckBox(tr("Spotify"));
    list.append(checkBoxYT);
    list.append(checkBoxSpoty);
    QVBoxLayout *vbox = new QVBoxLayout;
    vbox->addWidget(checkBoxYT);
    vbox->addWidget(checkBoxSpoty);
    vbox->addStretch(1);
    groupBox->setLayout(vbox);

    return groupBox;
}

bool PlaylistCreator::ShowErrorMessage(bool error, QString errorBody) {
    if (error) {
        QMessageBox::information(this, tr("Error"), errorBody);
        return false;
    }
    return true;
}
