#include "gameoverdialog.h"
#include "ui_gameoverdialog.h"
#include "mainmenudialog.h"
#include "tophighscores.h"

#include <QSize>
#include <QSettings>
#include <memory>
#include <QString>

extern std::shared_ptr<StudentSide::gameStatistics> smartStats;
extern std::map<std::shared_ptr<Interface::IActor>, QGraphicsPixmapItem*> smartActors;
extern QString playerAliasName;
namespace StudentSide {

GameOverDialog::GameOverDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GameOverDialog),
    _highScores(new topHighScores)
{
    ui->setupUi(this);
    this->setFixedSize(QSize(800, 600));
    this->setWindowTitle("Game Over");
    setToolTips();
    setPlayerPoints();

    _highScores->writeFile();
    _highScores->readFile();
    ui->topscoreWidget->setText(_highScores->scoreStream);
}

GameOverDialog::~GameOverDialog()
{
    initGameData();
    delete ui;
}

void GameOverDialog::setToolTips()
{
    ui->playAgainButton->setToolTip("Play Again");
    ui->gameOverCloseButton->setToolTip("Close Game");
    ui->statsButton->setToolTip("Show game statistics");
}

void GameOverDialog::setPlayerPoints()
{
    QString points = QString::number(smartStats->givePoints());
    ui->pointsLabel->setText("<p>GAME OVER! You got " + points +
                             " points in total, well done " +
                             playerAliasName + "!");

    ui->highScoresHeaderLabel->setText("<p>SCALED Top10 High Scores:</p>");
}

void GameOverDialog::initGameData()
{
    smartStats->initAllValues();
    smartActors.clear();
}

void GameOverDialog::on_gameOverCloseButton_clicked()
{
    this->close();
}

void GameOverDialog::on_playAgainButton_clicked()
{
    initGameData();
    MainMenuDialog *newMainMenu = new MainMenuDialog();
    newMainMenu->show();
    this->close();
}

void GameOverDialog::on_statsButton_clicked()
{
    statistisDialog *statsDialog = new statistisDialog();
    statsDialog->exec();
    this->setModal(false);
}
}
