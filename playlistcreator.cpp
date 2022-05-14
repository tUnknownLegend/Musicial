#include "playlistcreator.h"
#include "MainWindow.h"

PlaylistCreator::PlaylistCreator(MainWindow *_parent) : parent(_parent) {
    Text = new QLineEdit();
    Text->setPlaceholderText(QString("Enter Playlist URL"));
    Layout = new QVBoxLayout(this);
    Layout->addWidget(Text);
    submitBtn = new QPushButton("submit");
    Layout->addWidget(submitBtn);

    connect(submitBtn, SIGNAL(clicked()), this, SLOT(SubmitPlaylist()));
}

void PlaylistCreator::SubmitPlaylist() {
    QString *text = new QString();
    *text = Text->displayText();

    parent->SumbitPlaylist(*text);

    this->close();


    //SendPlaylist(text.toStdString(), UserID);
}
